#!/usr/bin/env bash

# DSA Setup - Installs required dependencies for your platform
#
# Usage:
#   ./setup.sh           # Install everything (compiler + optional tools)
#   ./setup.sh --check   # Just check what's installed/missing

set -e

# ==================== Colors ====================

if [ -t 1 ]; then
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    YELLOW='\033[1;33m'
    BLUE='\033[0;34m'
    BOLD='\033[1m'
    NC='\033[0m'
else
    RED=''
    GREEN=''
    YELLOW=''
    BLUE=''
    BOLD=''
    NC=''
fi

info()    { echo -e "${BLUE}[INFO]${NC} $1"; }
success() { echo -e "${GREEN}  ✓${NC} $1"; }
warn()    { echo -e "${YELLOW}  ✗${NC} $1"; }
error()   { echo -e "${RED}[ERROR]${NC} $1"; }

# ==================== Platform Detection ====================

detect_platform() {
    case "$(uname -s)" in
        Darwin*)  PLATFORM="macos" ;;
        Linux*)   PLATFORM="linux" ;;
        MINGW*|CYGWIN*|MSYS*) PLATFORM="windows" ;;
        *)        PLATFORM="unknown" ;;
    esac
}

detect_linux_distro() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        DISTRO_ID="$ID"
        DISTRO_LIKE="$ID_LIKE"
    elif command -v lsb_release &> /dev/null; then
        DISTRO_ID=$(lsb_release -si | tr '[:upper:]' '[:lower:]')
        DISTRO_LIKE=""
    else
        DISTRO_ID="unknown"
        DISTRO_LIKE=""
    fi
}

is_debian_based() {
    [[ "$DISTRO_ID" == "ubuntu" || "$DISTRO_ID" == "debian" || "$DISTRO_LIKE" == *"debian"* ]]
}

is_rhel_based() {
    [[ "$DISTRO_ID" == "fedora" || "$DISTRO_ID" == "centos" || "$DISTRO_ID" == "rhel" || "$DISTRO_LIKE" == *"rhel"* || "$DISTRO_LIKE" == *"fedora"* ]]
}

is_arch_based() {
    [[ "$DISTRO_ID" == "arch" || "$DISTRO_ID" == "manjaro" || "$DISTRO_LIKE" == *"arch"* ]]
}

# ==================== Dependency Checks ====================

HAS_CXX=false
HAS_CLANG_TIDY=false
HAS_CLANG_FORMAT=false

check_deps() {
    echo ""
    echo -e "${BOLD}Checking dependencies...${NC}"
    echo ""

    # C++ compiler (required)
    if command -v clang++ &> /dev/null; then
        success "clang++ found: $(clang++ --version | head -1)"
        HAS_CXX=true
    elif command -v g++ &> /dev/null; then
        success "g++ found: $(g++ --version | head -1)"
        HAS_CXX=true
    else
        warn "No C++ compiler found (clang++ or g++)"
    fi

    # C++20 support check
    if $HAS_CXX; then
        local test_cxx=""
        if command -v clang++ &> /dev/null; then test_cxx="clang++"; else test_cxx="g++"; fi
        if echo "int main(){}" | $test_cxx -std=c++20 -x c++ - -o /dev/null 2>/dev/null; then
            success "C++20 support confirmed"
        else
            warn "Compiler found but C++20 not supported — upgrade needed"
            HAS_CXX=false
        fi
    fi

    # clang-tidy (optional)
    if command -v clang-tidy &> /dev/null; then
        success "clang-tidy found (static analysis)"
        HAS_CLANG_TIDY=true
    else
        warn "clang-tidy not found (optional — needed for ./dsa lint)"
    fi

    # clang-format (optional)
    if command -v clang-format &> /dev/null; then
        success "clang-format found (code formatting)"
        HAS_CLANG_FORMAT=true
    else
        warn "clang-format not found (optional — auto-formatting)"
    fi

    echo ""
}

# ==================== Install ====================

install_macos() {
    info "Detected macOS"

    if ! command -v clang++ &> /dev/null; then
        info "Installing Xcode Command Line Tools (includes clang++)..."
        xcode-select --install 2>/dev/null || true
        echo ""
        echo "  If a dialog appeared, click 'Install' and wait for it to finish."
        echo "  Then re-run this script: ./setup.sh"
        echo ""
        exit 0
    fi

    if ! $HAS_CLANG_TIDY || ! $HAS_CLANG_FORMAT; then
        if command -v brew &> /dev/null; then
            info "Installing LLVM via Homebrew (includes clang-tidy, clang-format)..."
            brew install llvm

            local brew_prefix
            brew_prefix=$(brew --prefix llvm 2>/dev/null)
            if [ -n "$brew_prefix" ] && ! command -v clang-tidy &> /dev/null; then
                echo ""
                echo -e "  ${YELLOW}Add LLVM to your PATH by adding this to ~/.zshrc:${NC}"
                echo ""
                echo "    export PATH=\"$brew_prefix/bin:\$PATH\""
                echo ""
            fi
        else
            echo ""
            echo "  Homebrew not found. Install it first:"
            echo '    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
            echo ""
            echo "  Then re-run: ./setup.sh"
            echo ""
        fi
    fi
}

install_linux() {
    detect_linux_distro
    info "Detected Linux ($DISTRO_ID)"

    if is_debian_based; then
        info "Installing via apt..."
        sudo apt update
        sudo apt install -y build-essential

        if ! $HAS_CLANG_TIDY || ! $HAS_CLANG_FORMAT; then
            sudo apt install -y clang clang-tidy clang-format
        fi

    elif is_rhel_based; then
        info "Installing via yum/dnf..."
        if command -v dnf &> /dev/null; then
            sudo dnf install -y gcc-c++
            if ! $HAS_CLANG_TIDY || ! $HAS_CLANG_FORMAT; then
                sudo dnf install -y clang clang-tools-extra
            fi
        else
            sudo yum install -y gcc-c++
            if ! $HAS_CLANG_TIDY || ! $HAS_CLANG_FORMAT; then
                sudo yum install -y clang clang-tools-extra
            fi
        fi

    elif is_arch_based; then
        info "Installing via pacman..."
        sudo pacman -S --needed gcc
        if ! $HAS_CLANG_TIDY || ! $HAS_CLANG_FORMAT; then
            sudo pacman -S --needed clang
        fi

    else
        error "Unrecognized Linux distribution: $DISTRO_ID"
        echo ""
        echo "  Please install manually:"
        echo "    - A C++ compiler with C++20 support (g++ >= 10 or clang++ >= 10)"
        echo "    - clang-tidy (optional, for static analysis)"
        echo "    - clang-format (optional, for code formatting)"
        echo ""
        exit 1
    fi
}

install_windows() {
    echo ""
    error "Native Windows is not supported."
    echo ""
    echo "  Please use WSL2 (Windows Subsystem for Linux):"
    echo ""
    echo "    1. Open PowerShell as Administrator and run:"
    echo "       wsl --install"
    echo ""
    echo "    2. Restart your PC, then open Ubuntu from the Start menu."
    echo ""
    echo "    3. Inside WSL, navigate to this project and run:"
    echo "       ./setup.sh"
    echo ""
    exit 1
}

do_install() {
    case "$PLATFORM" in
        macos)   install_macos ;;
        linux)   install_linux ;;
        windows) install_windows ;;
        *)
            error "Unknown platform: $(uname -s)"
            exit 1
            ;;
    esac
}

# ==================== Summary ====================

print_summary() {
    check_deps

    if $HAS_CXX; then
        echo -e "${GREEN}${BOLD}Ready to go!${NC}"
        echo ""
        echo "  Get started:"
        echo "    ./dsa list              # Browse questions"
        echo "    ./dsa create TwoSum     # Load a question"
        echo "    ./dsa run               # Build and run tests"
        echo ""
    else
        echo -e "${RED}${BOLD}Setup incomplete.${NC} A C++ compiler with C++20 support is required."
        echo ""
        echo "  Re-run: ./setup.sh"
        echo ""
        exit 1
    fi
}

# ==================== Main ====================

detect_platform

case "${1:-}" in
    --check|-c)
        check_deps
        if $HAS_CXX; then
            echo -e "${GREEN}${BOLD}All required dependencies installed.${NC}"
            if ! $HAS_CLANG_TIDY; then
                echo -e "  ${YELLOW}Optional: install clang-tidy for ./dsa lint${NC}"
            fi
            echo ""
        else
            echo -e "${RED}${BOLD}Missing required dependency: C++ compiler with C++20 support.${NC}"
            echo "  Run ./setup.sh to install."
            echo ""
            exit 1
        fi
        ;;
    *)
        echo ""
        echo -e "${BOLD}DSA Setup${NC}"
        echo ""

        check_deps

        if $HAS_CXX && $HAS_CLANG_TIDY && $HAS_CLANG_FORMAT; then
            echo -e "${GREEN}${BOLD}Everything is already installed!${NC}"
            echo ""
            echo "  Get started:"
            echo "    ./dsa list              # Browse questions"
            echo "    ./dsa create TwoSum     # Load a question"
            echo "    ./dsa run               # Build and run tests"
            echo ""
            exit 0
        fi

        do_install
        print_summary
        ;;
esac
