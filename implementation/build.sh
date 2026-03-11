#!/bin/bash

# DSA Project - Build, Test & Analyze
# Cross-platform: macOS, Linux, Windows (WSL/MinGW)

set -e  # Exit on error


PROJECT_NAME="DSA"
CPP_STANDARD="c++20"

# --- Path setup ---
IMPL_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$IMPL_DIR/.." && pwd)"
MAIN_FILE="$IMPL_DIR/main.cpp"
OUTPUT_BIN="$IMPL_DIR/main"
PROBLEMS_DIR="$ROOT_DIR/Answers"


if [ -t 1 ]; then
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    YELLOW='\033[1;33m'
    BLUE='\033[0;34m'
    NC='\033[0m' # No Color
else
    RED=''
    GREEN=''
    YELLOW=''
    BLUE=''
    NC=''
fi


info()    { echo -e "${BLUE}[INFO]${NC} $1"; }
success() { echo -e "${GREEN}[OK]${NC} $1"; }
warn()    { echo -e "${YELLOW}[WARN]${NC} $1"; }
error()   { echo -e "${RED}[ERROR]${NC} $1"; }


detect_platform() {
    case "$(uname -s)" in
        Darwin*)  PLATFORM="macos" ;;
        Linux*)   PLATFORM="linux" ;;
        MINGW*|CYGWIN*|MSYS*) PLATFORM="windows" ;;
        *)        PLATFORM="unknown" ;;
    esac

    case "$(uname -m)" in
        arm64|aarch64) ARCH="arm64" ;;
        x86_64|AMD64)  ARCH="x86_64" ;;
        *)             ARCH="unknown" ;;
    esac
}


check_compiler() {
    if command -v clang++ &> /dev/null; then
        CXX="clang++"
    elif command -v g++ &> /dev/null; then
        CXX="g++"
    else
        error "No C++ compiler found!"
        echo ""
        echo "Please install a C++ compiler:"
        case "$PLATFORM" in
            macos)
                echo "  xcode-select --install"
                echo "  # or"
                echo "  brew install llvm"
                ;;
            linux)
                echo "  sudo apt install g++        # Debian/Ubuntu"
                echo "  sudo yum install gcc-c++    # RHEL/CentOS"
                echo "  sudo pacman -S gcc          # Arch"
                ;;
            windows)
                echo "  Install MinGW-w64 or Visual Studio Build Tools"
                ;;
        esac
        return 1
    fi
    return 0
}

check_clang_tidy() {
    # First check if in PATH
    if command -v clang-tidy &> /dev/null; then
        CLANG_TIDY="clang-tidy"
        return 0
    fi

    # Fallback: check common install locations
    local candidates=(
        "/opt/homebrew/opt/llvm/bin/clang-tidy"   # macOS ARM Homebrew
        "/usr/local/opt/llvm/bin/clang-tidy"      # macOS Intel Homebrew
        "/usr/bin/clang-tidy"                      # Linux system
        "/usr/local/bin/clang-tidy"                # Linux local
    )

    for candidate in "${candidates[@]}"; do
        if [ -x "$candidate" ]; then
            CLANG_TIDY="$candidate"
            return 0
        fi
    done

    CLANG_TIDY=""
    return 1
}

show_install_instructions() {
    echo ""
    echo "  Missing Dependencies"
    echo ""

    case "$PLATFORM" in
        macos)
            echo "Install all tools with Homebrew:"
            echo ""
            echo "  # Install Homebrew (if not installed)"
            echo '  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
            echo ""
            echo "  # Install LLVM (includes clang++, clang-tidy)"
            echo "  brew install llvm"
            echo ""
            echo "  # Add to PATH (add to ~/.zshrc or ~/.bashrc)"
            echo '  export PATH="/opt/homebrew/opt/llvm/bin:$PATH"'
            echo ""
            ;;
        linux)
            echo "Install tools with your package manager:"
            echo ""
            echo "  # Debian/Ubuntu:"
            echo "  sudo apt update"
            echo "  sudo apt install build-essential clang clang-tidy"
            echo ""
            echo "  # RHEL/CentOS/Fedora:"
            echo "  sudo yum install gcc-c++ clang clang-tools-extra"
            echo ""
            echo "  # Arch:"
            echo "  sudo pacman -S gcc clang"
            echo ""
            ;;
        windows)
            echo "Windows (WSL recommended):"
            echo ""
            echo "  # Install WSL2 with Ubuntu"
            echo "  wsl --install"
            echo ""
            echo "  # Then inside WSL:"
            echo "  sudo apt install build-essential clang clang-tidy"
            echo ""
            ;;
        *)
            echo "Please install a C++ compiler and clang-tidy for your platform."
            ;;
    esac
}


cd "$IMPL_DIR"


cmd_build() {
    info "Building project..."

    if ! check_compiler; then
        show_install_instructions
        exit 1
    fi

    $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -O2 "$MAIN_FILE" -o "$OUTPUT_BIN"
    success "Built: $OUTPUT_BIN"
}

cmd_run() {
    cmd_build
    echo ""
    info "Running tests..."
    echo ""
    "$OUTPUT_BIN"
}

cmd_clean() {
    info "Cleaning build artifacts..."
    rm -f "$IMPL_DIR"/main "$IMPL_DIR"/main_* 2>/dev/null || true
    rm -rf "$IMPL_DIR"/*.dSYM 2>/dev/null || true
    success "Cleaned"
}

cmd_lint() {
    info "Running static analysis (clang-tidy)..."

    if ! check_clang_tidy; then
        warn "clang-tidy not found in PATH"
        show_install_instructions
        return 1
    fi

    local issues=0
    local files_checked=0

    while IFS= read -r -d '' f; do
        files_checked=$((files_checked + 1))
        result=$("$CLANG_TIDY" "$f" -- -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" 2>&1 | grep -E "(warning|error):" || true)
        if [ -n "$result" ]; then
            warn "$f:"
            echo "$result"
            issues=$((issues + 1))
        else
            echo "  ✓ $f"
        fi
    done < <(find "$PROBLEMS_DIR" -name "*.cpp" -print0 2>/dev/null)

    echo ""
    if [ $issues -eq 0 ]; then
        success "All $files_checked files passed static analysis"
    else
        warn "$issues file(s) have issues"
    fi
}

cmd_check() {
    info "Running compiler with strict warnings..."

    if ! check_compiler; then
        show_install_instructions
        exit 1
    fi

    local flags="-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wunused"

    if [[ "$CXX" == *"clang"* ]]; then
        flags="$flags -Wold-style-cast -Wcast-align"
    fi

    local check_bin="$IMPL_DIR/main_check"
    if $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" $flags "$MAIN_FILE" -o "$check_bin" 2>&1; then
        success "No compiler warnings"
        rm -f "$check_bin"
    else
        error "Warnings or errors found"
        rm -f "$check_bin"
        return 1
    fi
}

cmd_asan() {
    info "Building with AddressSanitizer..."

    if ! check_compiler; then
        show_install_instructions
        exit 1
    fi

    if ! $CXX -fsanitize=address -x c++ -E - < /dev/null &> /dev/null; then
        warn "AddressSanitizer not supported by $CXX"
        return 1
    fi

    local asan_bin="$IMPL_DIR/main_asan"
    $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -fsanitize=address -fno-omit-frame-pointer -g \
        "$MAIN_FILE" -o "$asan_bin"

    info "Running with ASan..."
    if "$asan_bin" 2>&1; then
        success "No memory errors detected"
    else
        error "Memory errors detected"
    fi

    rm -f "$asan_bin"
}

cmd_ubsan() {
    info "Building with UndefinedBehaviorSanitizer..."

    if ! check_compiler; then
        show_install_instructions
        exit 1
    fi

    if ! $CXX -fsanitize=undefined -x c++ -E - < /dev/null &> /dev/null; then
        warn "UBSan not supported by $CXX"
        return 1
    fi

    local ubsan_bin="$IMPL_DIR/main_ubsan"
    $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -fsanitize=undefined -fno-omit-frame-pointer -g \
        "$MAIN_FILE" -o "$ubsan_bin"

    info "Running with UBSan..."
    if "$ubsan_bin" 2>&1; then
        success "No undefined behavior detected"
    else
        error "Undefined behavior detected"
    fi

    rm -f "$ubsan_bin"
}

cmd_debug() {
    info "Building with debug symbols (no optimizations)..."

    if ! check_compiler; then
        show_install_instructions
        exit 1
    fi

    local debug_bin="$IMPL_DIR/main_debug"
    $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -g -O0 "$MAIN_FILE" -o "$debug_bin"
    success "Built: $debug_bin (with debug symbols)"

    info "Opening in VSCode debugger..."
    echo ""
    echo "  VSCode Debugger"
    echo "  1. Set breakpoints by clicking line numbers"
    echo "  2. Press F5 or click 'Run and Debug'"
    echo "  3. Use debug toolbar to step through code"
    echo ""

    # Create launch.json if it doesn't exist
    mkdir -p "$IMPL_DIR/.vscode"
    cat > "$IMPL_DIR/.vscode/launch.json" << 'EOF'
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug DSA",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/implementation/main_debug",
            "args": [],
            "cwd": "${workspaceFolder}",
            "preLaunchTask": ""
        },
        {
            "name": "Debug DSA (CodeLLDB)",
            "type": "lldb",
            "request": "launch",
            "program": "${workspaceFolder}/implementation/main_debug",
            "args": [],
            "cwd": "${workspaceFolder}"
        }
    ]
}
EOF
    success "Created .vscode/launch.json"
    echo ""
    echo "To debug: Open VSCode, press F5 or go to Run > Start Debugging"
}

cmd_debugout() {
    info "Building with DEBUG_OUTPUT enabled..."

    if ! check_compiler; then
        show_install_instructions
        exit 1
    fi

    local debugout_bin="$IMPL_DIR/main_debugout"
    $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -DDEBUG_OUTPUT -g -O0 "$MAIN_FILE" -o "$debugout_bin"
    success "Built: $debugout_bin (with debug output enabled)"

    info "Running with debug output..."
    echo ""
    "$debugout_bin"
}

cmd_all() {
    echo ""
    echo "  $PROJECT_NAME - Full Build & Analysis"
    echo "  Platform: $PLATFORM ($ARCH)"
    echo "  Compiler: ${CXX:-not found}"
    echo "  Linter:   ${CLANG_TIDY:-not found}"
    echo ""

    cmd_clean
    echo ""
    cmd_check
    echo ""
    cmd_lint || true  # Don't fail if clang-tidy missing
    echo ""
    cmd_asan || true
    echo ""
    cmd_ubsan || true
    echo ""
    cmd_build
    echo ""
    info "Running tests..."
    echo ""
    "$OUTPUT_BIN"

    echo ""
    success "All steps completed!"
}

cmd_help() {
    echo "$PROJECT_NAME Build System"
    echo ""
    echo "Usage: ./dsa <command>"
    echo ""
    echo "Commands:"
    echo "  run       Build and run tests (default)"
    echo "  all       Run all checks, then build and run"
    echo "  build     Compile the project only"
    echo "  clean     Remove build artifacts"
    echo "  lint      Run clang-tidy static analysis"
    echo "  check     Compile with strict warnings"
    echo "  asan      Run AddressSanitizer (memory errors)"
    echo "  ubsan     Run UndefinedBehaviorSanitizer"
    echo "  debug     Build with debug symbols for VSCode debugger"
    echo "  debugout  Build with DEBUG_OUT macro enabled and run"
    echo "  deps      Show dependency install instructions"
    echo "  help      Show this help"
    echo ""
    echo "Examples:"
    echo "  ./dsa run               # Build and run (default)"
    echo "  ./dsa build             # Just compile"
    echo "  ./dsa all               # Full analysis + build + run"
    echo "  ./dsa lint check        # Run multiple commands"
}

cmd_deps() {
    detect_platform
    show_install_instructions
}


detect_platform
check_compiler || true
check_clang_tidy || true

if [ $# -eq 0 ]; then
    cmd_run
    exit 0
fi

for cmd in "$@"; do
    case "$cmd" in
        build)   cmd_build ;;
        run)     cmd_run ;;
        clean)   cmd_clean ;;
        lint)    cmd_lint ;;
        check)   cmd_check ;;
        asan)    cmd_asan ;;
        ubsan)   cmd_ubsan ;;
        debug)   cmd_debug ;;
        debugout) cmd_debugout ;;
        all)     cmd_all ;;
        deps)    cmd_deps ;;
        help|-h|--help) cmd_help ;;
        *)
            error "Unknown command: $cmd"
            echo ""
            cmd_help
            exit 1
            ;;
    esac
done
