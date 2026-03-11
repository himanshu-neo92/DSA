#!/usr/bin/env bash

# DSA Practice - Question & Answer Workflow
# Usage:
#   ./dsa create <question_name>    - Load a question to solve
#   ./dsa submit                    - Submit and test your answer
#   ./dsa finish                    - Archive solution with analytics
#   ./dsa list [category]           - List available questions
#
# Examples:
#   ./dsa create TwoSum
#   ./dsa create Medium/AirPath
#   ./dsa submit
#   ./dsa finish
#   ./dsa list
#   ./dsa list Easy

set -e

# ==================== Configuration ====================

IMPL_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$IMPL_DIR/.." && pwd)"
QUESTIONS_DIR="$ROOT_DIR/Questions"
ANSWERS_DIR="$ROOT_DIR/Answers"
ANSWERED_DIR="$ROOT_DIR/Answered"
CURRENT_DIR="$ROOT_DIR/CurrentProblem"
METADATA_FILE="$CURRENT_DIR/.current_question"
TEST_REGISTER="$IMPL_DIR/TestRegister.cpp"

# ==================== Colors ====================

if [ -t 1 ]; then
    RED='\033[0;31m'
    GREEN='\033[0;32m'
    YELLOW='\033[1;33m'
    BLUE='\033[0;34m'
    CYAN='\033[0;36m'
    BOLD='\033[1m'
    NC='\033[0m'
else
    RED=''
    GREEN=''
    YELLOW=''
    BLUE=''
    CYAN=''
    BOLD=''
    NC=''
fi

info()    { echo -e "${BLUE}[INFO]${NC} $1"; }
success() { echo -e "${GREEN}[OK]${NC} $1"; }
warn()    { echo -e "${YELLOW}[WARN]${NC} $1"; }
error()   { echo -e "${RED}[ERROR]${NC} $1"; }

# ==================== CreateQuestion ====================
# Copies a question from Questions/ to CurrentProblem/ so you can solve it.
# Updates TestRegister.cpp to include the current problem.
# Records metadata (start time, source path) for analytics.

CreateQuestion() {
    local query="$1"

    if [ -z "$query" ]; then
        error "Usage: ./dsa create <question_name>"
        echo ""
        echo "  Examples:"
        echo "    ./dsa create TwoSum"
        echo "    ./dsa create Medium/AirPath"
        echo "    ./dsa create Easy/Fibonacci"
        echo ""
        echo "  Run './dsa list' to see available questions."
        return 1
    fi

    # Check if there's already a problem in progress
    if [ -f "$METADATA_FILE" ]; then
        local current_name
        current_name=$(grep '^name=' "$METADATA_FILE" | cut -d'=' -f2)
        warn "You already have a problem loaded: $current_name"
        echo ""
        read -r -p "  Overwrite and start a new problem? (y/N): " confirm
        if [[ ! "$confirm" =~ ^[Yy]$ ]]; then
            info "Keeping current problem. Use './dsa run' to test your solution."
            return 0
        fi
        echo ""
    fi

    # Search for the question file
    local found_file=""
    local found_count=0
    local found_files=()

    # Try exact path first (e.g., "Medium/AirPath" or "Easy/TwoSum")
    if [ -f "$QUESTIONS_DIR/${query}.cpp" ]; then
        found_file="$QUESTIONS_DIR/${query}.cpp"
        found_count=1
    else
        # Search by filename across all categories
        while IFS= read -r -d '' f; do
            found_files+=("$f")
            found_count=$((found_count + 1))
        done < <(find "$QUESTIONS_DIR" -name "${query}.cpp" -print0 2>/dev/null)

        if [ $found_count -eq 0 ]; then
            # Try partial/case-insensitive match
            while IFS= read -r -d '' f; do
                found_files+=("$f")
                found_count=$((found_count + 1))
            done < <(find "$QUESTIONS_DIR" -iname "*${query}*.cpp" -print0 2>/dev/null)
        fi

        if [ $found_count -eq 0 ]; then
            error "No question found matching '$query'"
            echo ""
            echo "  Available questions:"
            ListQuestions
            return 1
        elif [ $found_count -eq 1 ]; then
            found_file="${found_files[0]}"
        else
            echo ""
            echo -e "${BOLD}  Multiple matches found:${NC}"
            echo ""
            for i in "${!found_files[@]}"; do
                local rel_path="${found_files[$i]#$QUESTIONS_DIR/}"
                echo "    $((i + 1)). ${rel_path%.cpp}"
            done
            echo ""
            read -r -p "  Select a number (1-$found_count): " selection
            if [[ "$selection" =~ ^[0-9]+$ ]] && [ "$selection" -ge 1 ] && [ "$selection" -le "$found_count" ]; then
                found_file="${found_files[$((selection - 1))]}"
            else
                error "Invalid selection"
                return 1
            fi
        fi
    fi

    # Extract relative path and question name
    local rel_path="${found_file#$QUESTIONS_DIR/}"
    local category
    category=$(dirname "$rel_path")
    local filename
    filename=$(basename "$rel_path")
    local question_name="${filename%.cpp}"

    info "Loading question: ${category}/${question_name}"

    # Create CurrentProblem directory
    mkdir -p "$CURRENT_DIR"

    # Copy the question file (includes use "TestBase.h", resolved via -I flag)
    cp "$found_file" "$CURRENT_DIR/${filename}"

    # Write metadata
    cat > "$METADATA_FILE" << EOF
name=${question_name}
category=${category}
source=${rel_path}
start_time=$(date +%s)
start_timestamp=$(date '+%Y-%m-%d %H:%M:%S')
EOF

    # Update TestRegister.cpp to include only the current problem
    cat > "$TEST_REGISTER" << EOF
// Test Register - Auto-generated by dsa.sh
// Currently solving: ${category}/${question_name}

#include "CurrentProblem/${filename}"
EOF

    success "Question loaded: ${category}/${question_name}"
    echo ""
    echo -e "  ${BOLD}What to do next:${NC}"
    echo -e "    1. Open ${CYAN}CurrentProblem/${filename}${NC}"
    echo -e "    2. Implement the solution where you see // TODO"
    echo -e "    3. Run ${CYAN}./dsa run${NC} to test your solution"
    echo -e "    4. Run ${CYAN}./dsa submit${NC} when all tests pass"
    echo ""

    return 0
}

# ==================== ListQuestions ====================
# Lists all available questions, optionally filtered by category.

ListQuestions() {
    local filter="$1"

    echo ""
    echo -e "${BOLD}  Available Questions${NC}"
    echo ""

    local categories=("Easy" "Medium" "Hard")

    for category in "${categories[@]}"; do
        # Skip if filter is set and doesn't match
        if [ -n "$filter" ] && ! echo "$category" | grep -qi "^${filter}$"; then
            continue
        fi

        local dir="$QUESTIONS_DIR/$category"
        if [ ! -d "$dir" ]; then
            continue
        fi

        local files
        files=$(find "$dir" -name "*.cpp" -maxdepth 1 2>/dev/null | sort)
        if [ -z "$files" ]; then
            continue
        fi

        echo -e "  ${BOLD}${category}:${NC}"
        while IFS= read -r f; do
            local name
            name=$(basename "$f" .cpp)
            echo -e "    ${CYAN}•${NC} $name"
        done <<< "$files"
        echo ""
    done
}

# ==================== SubmitAnswer ====================
# Compiles and runs the tests for the current problem in CurrentProblem/.
# If all tests pass, the answer is correct.
# Delegates to Step 6 (move to Answered/ with analytics) on success.

SubmitAnswer() {
    # --- Validate that a problem is loaded ---
    if [ ! -f "$METADATA_FILE" ]; then
        error "No problem is currently loaded."
        echo ""
        echo "  Load a question first:"
        echo "    ./dsa create <question_name>"
        return 1
    fi

    local question_name category source_path start_time
    question_name=$(grep '^name=' "$METADATA_FILE" | cut -d'=' -f2)
    category=$(grep '^category=' "$METADATA_FILE" | cut -d'=' -f2)
    source_path=$(grep '^source=' "$METADATA_FILE" | cut -d'=' -f2)
    start_time=$(grep '^start_time=' "$METADATA_FILE" | cut -d'=' -f2)
    local filename="${question_name}.cpp"

    if [ ! -f "$CURRENT_DIR/$filename" ]; then
        error "Solution file not found: CurrentProblem/$filename"
        return 1
    fi

    info "Submitting answer for: ${category}/${question_name}"
    echo ""

    # --- Detect compiler ---
    local CXX=""
    if command -v clang++ &> /dev/null; then
        CXX="clang++"
    elif command -v g++ &> /dev/null; then
        CXX="g++"
    else
        error "No C++ compiler found. Run ./dsa deps for install instructions."
        return 1
    fi

    local CPP_STANDARD="c++20"
    local SUBMIT_BIN="$IMPL_DIR/.submit_runner"

    # --- Ensure TestRegister.cpp points at CurrentProblem ---
    cat > "$TEST_REGISTER" << EOF
// Test Register - Auto-generated by dsa.sh (submit)
// Submitting: ${category}/${question_name}

#include "CurrentProblem/${filename}"
EOF

    # --- Build ---
    info "Compiling your solution..."
    if ! $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -O2 \
        "$IMPL_DIR/main.cpp" -o "$SUBMIT_BIN" 2>&1; then
        echo ""
        error "Compilation failed. Fix the errors above and try again."
        rm -f "$SUBMIT_BIN"
        return 1
    fi
    success "Compilation succeeded"
    echo ""

    # --- Run tests and capture output ---
    info "Running tests..."
    echo ""

    local test_output
    test_output=$("$SUBMIT_BIN" 2>&1) || true
    echo "$test_output"
    echo ""

    # --- Parse results ---
    local passed_line failed_line
    passed_line=$(echo "$test_output" | grep -E '^Passed:' || true)
    failed_line=$(echo "$test_output" | grep -E '^Failed:' || true)

    local num_passed=0 num_failed=0 total=0
    if [ -n "$passed_line" ]; then
        num_passed=$(echo "$passed_line" | sed 's|Passed: \([0-9]*\)/.*|\1|')
        total=$(echo "$passed_line" | sed 's|Passed: [0-9]*/\([0-9]*\)|\1|')
    fi
    if [ -n "$failed_line" ]; then
        num_failed=$(echo "$failed_line" | sed 's|Failed: \([0-9]*\)/.*|\1|')
    fi

    # --- Cleanup build artifact ---
    rm -f "$SUBMIT_BIN"

    # --- Report results ---
    if [ "$num_failed" -eq 0 ] && [ "$total" -gt 0 ]; then
        echo ""
        echo -e "  ${GREEN}${BOLD}✅ ALL $total TESTS PASSED!${NC}"
        echo -e "  ${GREEN}Your solution for ${category}/${question_name} is correct.${NC}"
        echo ""

        # Calculate time spent
        local end_time
        end_time=$(date +%s)
        local elapsed=$((end_time - start_time))
        local minutes=$((elapsed / 60))
        local seconds=$((elapsed % 60))
        echo -e "  ⏱️  Time spent: ${BOLD}${minutes}m ${seconds}s${NC}"
        echo ""

        # Record submit time in metadata for Step 6
        echo "submit_time=$end_time" >> "$METADATA_FILE"
        echo "submit_timestamp=$(date '+%Y-%m-%d %H:%M:%S')" >> "$METADATA_FILE"
        echo "tests_passed=$num_passed" >> "$METADATA_FILE"
        echo "tests_total=$total" >> "$METADATA_FILE"

        # Update TestRegister.cpp to point at the reference answer
        local answer_file="Answers/${source_path}"
        if [ -f "$ROOT_DIR/$answer_file" ]; then
            cat > "$TEST_REGISTER" << EOF
// Test Register - Auto-generated by dsa.sh (submit)
// ✅ Passed: ${category}/${question_name}
// Pointing at reference answer for comparison.
// Run ./dsa run to see the ideal solution's tests.

#include "${answer_file}"
EOF
            info "TestRegister.cpp now points to the reference answer: ${answer_file}"
        fi

        echo -e "  Run ${CYAN}./dsa finish${NC} to archive with full analytics,"
        echo -e "  or ${CYAN}./dsa create <name>${NC} to start a new problem."
        echo ""
        return 0
    else
        echo ""
        echo -e "  ${RED}${BOLD}❌ ${num_failed}/${total} TESTS FAILED${NC}"
        echo -e "  ${YELLOW}Keep working on your solution and submit again.${NC}"
        echo ""
        echo -e "  Tips:"
        echo -e "    • Edit ${CYAN}CurrentProblem/${filename}${NC}"
        echo -e "    • Run ${CYAN}./dsa run${NC} for quick iteration"
        echo -e "    • Run ${CYAN}./dsa submit${NC} when ready"
        echo ""
        return 1
    fi
}

# ==================== FinishAnswer ====================
# Archives a correctly submitted solution to Answered/ with an analytics report.
# Generates: stress test timing, static analysis, diff vs reference answer, solve time.

FinishAnswer() {
    # --- Validate that a problem was submitted successfully ---
    if [ ! -f "$METADATA_FILE" ]; then
        error "No problem is currently loaded."
        echo ""
        echo "  Load a question first:"
        echo "    ./dsa create <question_name>"
        return 1
    fi

    local question_name category source_path start_time
    question_name=$(grep '^name=' "$METADATA_FILE" | cut -d'=' -f2)
    category=$(grep '^category=' "$METADATA_FILE" | cut -d'=' -f2)
    source_path=$(grep '^source=' "$METADATA_FILE" | cut -d'=' -f2)
    start_time=$(grep '^start_time=' "$METADATA_FILE" | cut -d'=' -f2)
    local start_timestamp
    start_timestamp=$(grep '^start_timestamp=' "$METADATA_FILE" | cut -d'=' -f2-)
    local filename="${question_name}.cpp"

    local submit_time
    submit_time=$(grep '^submit_time=' "$METADATA_FILE" 2>/dev/null | cut -d'=' -f2 || true)

    if [ -z "$submit_time" ]; then
        warn "You haven't submitted a passing solution yet."
        echo ""
        echo "  Run ${CYAN}./dsa submit${NC} first and make sure all tests pass."
        return 1
    fi

    if [ ! -f "$CURRENT_DIR/$filename" ]; then
        error "Solution file not found: CurrentProblem/$filename"
        return 1
    fi

    info "Archiving solution for: ${category}/${question_name}"
    echo ""

    # --- Detect compiler & tools ---
    local CXX=""
    if command -v clang++ &> /dev/null; then
        CXX="clang++"
    elif command -v g++ &> /dev/null; then
        CXX="g++"
    else
        error "No C++ compiler found."
        return 1
    fi

    local CLANG_TIDY=""
    if command -v clang-tidy &> /dev/null; then
        CLANG_TIDY="clang-tidy"
    else
        local candidates=(
            "/opt/homebrew/opt/llvm/bin/clang-tidy"
            "/usr/local/opt/llvm/bin/clang-tidy"
            "/usr/bin/clang-tidy"
            "/usr/local/bin/clang-tidy"
        )
        for candidate in "${candidates[@]}"; do
            if [ -x "$candidate" ]; then
                CLANG_TIDY="$candidate"
                break
            fi
        done
    fi

    local CPP_STANDARD="c++20"

    # --- Ensure TestRegister.cpp points at CurrentProblem ---
    cat > "$TEST_REGISTER" << EOF
// Test Register - Auto-generated by dsa.sh (finish)
// Archiving: ${category}/${question_name}

#include "CurrentProblem/${filename}"
EOF

    # ============================================================
    # 1. Time spent solving
    # ============================================================
    local elapsed=$((submit_time - start_time))
    local hours=$((elapsed / 3600))
    local minutes=$(( (elapsed % 3600) / 60 ))
    local seconds=$((elapsed % 60))
    local time_display=""
    if [ "$hours" -gt 0 ]; then
        time_display="${hours}h ${minutes}m ${seconds}s"
    else
        time_display="${minutes}m ${seconds}s"
    fi
    local submit_timestamp
    submit_timestamp=$(grep '^submit_timestamp=' "$METADATA_FILE" | cut -d'=' -f2-)

    info "⏱️  Time to solve: $time_display"

    # ============================================================
    # 2. Diff vs reference answer (code only — comments stripped)
    # ============================================================
    local reference_file="$ANSWERS_DIR/${source_path}"
    local diff_output=""
    local diff_summary=""

    info "📝 Comparing with reference answer..."

    if [ -f "$reference_file" ]; then
        # Strip comments and blank lines for a fair code-only comparison
        local tmp_ref tmp_usr
        tmp_ref=$(mktemp)
        tmp_usr=$(mktemp)

        # Remove // comments, /* */ block comments, #include lines, and blank lines
        _strip_comments() {
            sed \
                -e 's|//.*||' \
                -e '/^[[:space:]]*$/d' \
                -e '/^[[:space:]]*#include/d' \
                -e '/^[[:space:]]*\/\*/,/\*\//d' \
                "$1"
        }

        _strip_comments "$reference_file" > "$tmp_ref"
        _strip_comments "$CURRENT_DIR/$filename" > "$tmp_usr"

        diff_output=$(diff -u \
            --label "Reference (Answers/${source_path})" "$tmp_ref" \
            --label "Your Solution (CurrentProblem/${filename})" "$tmp_usr" \
            2>&1) || true

        rm -f "$tmp_ref" "$tmp_usr"

        if [ -z "$diff_output" ]; then
            diff_summary="Your solution is identical to the reference answer (ignoring comments)."
            success "Solution matches reference exactly"
        else
            local lines_added lines_removed
            lines_added=$(echo "$diff_output" | grep -c '^+[^+]' || true)
            lines_removed=$(echo "$diff_output" | grep -c '^-[^-]' || true)
            diff_summary="${lines_added} line(s) added, ${lines_removed} line(s) removed vs reference (code only)."
            info "Differences found: $diff_summary"
        fi
    else
        diff_summary="No reference answer found for this problem."
        warn "No reference answer at Answers/${source_path}"
    fi

    # ============================================================
    # 3. Stress test (ASan + UBSan + timing)
    # ============================================================
    local stress_output=""
    local asan_result="⏭️  Skipped"
    local ubsan_result="⏭️  Skipped"
    local stress_time_display="N/A"

    info "🔥 Running stress tests..."

    local stress_start
    stress_start=$(date +%s)

    # --- AddressSanitizer ---
    local ASAN_BIN="$IMPL_DIR/.finish_asan"
    if $CXX -fsanitize=address -x c++ -E - < /dev/null &> /dev/null 2>&1; then
        if $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -fsanitize=address \
            -fno-omit-frame-pointer -g "$IMPL_DIR/main.cpp" -o "$ASAN_BIN" 2>/dev/null; then
            local asan_output
            asan_output=$("$ASAN_BIN" 2>&1) || true
            if echo "$asan_output" | grep -q "ERROR:.*Sanitizer\|ABORTING"; then
                asan_result="❌ Memory errors detected"
            else
                asan_result="✅ No memory errors"
            fi
        else
            asan_result="⚠️  ASan build failed"
        fi
        rm -f "$ASAN_BIN"
    else
        asan_result="⚠️  ASan not supported by $CXX"
    fi
    info "  ASan: $asan_result"

    # --- UndefinedBehaviorSanitizer ---
    local UBSAN_BIN="$IMPL_DIR/.finish_ubsan"
    if $CXX -fsanitize=undefined -x c++ -E - < /dev/null &> /dev/null 2>&1; then
        if $CXX -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" -fsanitize=undefined \
            -fno-omit-frame-pointer -g "$IMPL_DIR/main.cpp" -o "$UBSAN_BIN" 2>/dev/null; then
            local ubsan_output
            ubsan_output=$("$UBSAN_BIN" 2>&1) || true
            if echo "$ubsan_output" | grep -qi "runtime error\|undefined behavior"; then
                ubsan_result="❌ Undefined behavior detected"
            else
                ubsan_result="✅ No undefined behavior"
            fi
        else
            ubsan_result="⚠️  UBSan build failed"
        fi
        rm -f "$UBSAN_BIN"
    else
        ubsan_result="⚠️  UBSan not supported by $CXX"
    fi
    info "  UBSan: $ubsan_result"

    local stress_end
    stress_end=$(date +%s)
    local stress_elapsed=$((stress_end - stress_start))
    stress_time_display="${stress_elapsed}s"
    info "  Stress test duration: ${stress_time_display}"

    # ============================================================
    # 4. Static analysis (clang-tidy)
    # ============================================================
    local lint_output=""
    local lint_summary=""

    info "🔍 Running static analysis..."

    if [ -n "$CLANG_TIDY" ]; then
        lint_output=$("$CLANG_TIDY" "$CURRENT_DIR/$filename" \
            -- -std=$CPP_STANDARD -I"$ROOT_DIR" -I"$IMPL_DIR" 2>&1 | \
            grep -E "(warning|error):" || true)

        if [ -z "$lint_output" ]; then
            lint_summary="No issues found."
            success "Static analysis: clean"
        else
            local lint_warnings lint_errors
            lint_warnings=$(echo "$lint_output" | grep -c "warning:" || true)
            lint_errors=$(echo "$lint_output" | grep -c "error:" || true)
            lint_summary="${lint_warnings} warning(s), ${lint_errors} error(s)"
            warn "Static analysis: $lint_summary"
        fi
    else
        lint_summary="clang-tidy not available (install with: brew install llvm)"
        warn "clang-tidy not found, skipping static analysis"
    fi

    # ============================================================
    # 5. Generate analytics MD report
    # ============================================================
    local tests_passed tests_total
    tests_passed=$(grep '^tests_passed=' "$METADATA_FILE" | cut -d'=' -f2)
    tests_total=$(grep '^tests_total=' "$METADATA_FILE" | cut -d'=' -f2)

    local revision=1
    while [ -d "$ANSWERED_DIR/${question_name}-rev${revision}" ]; do
        revision=$((revision + 1))
    done
    local dest_dir="$ANSWERED_DIR/${question_name}-rev${revision}"
    mkdir -p "$dest_dir"

    local report_file="$dest_dir/report.md"

    info "📄 Generating analytics report..."

    cat > "$report_file" << REPORT_EOF
# ${question_name} — Solution Report

**Category:** ${category}
**Date:** ${submit_timestamp}

---

## ⏱️ Time to Solve

| Metric | Value |
|--------|-------|
| Started | ${start_timestamp} |
| Submitted | ${submit_timestamp} |
| Duration | **${time_display}** |

---

## ✅ Test Results

| Metric | Value |
|--------|-------|
| Passed | ${tests_passed}/${tests_total} |
| Failed | 0/${tests_total} |
| Status | **All tests passed** |

---

## 🔥 Stress Test Results

| Sanitizer | Result | Duration |
|-----------|--------|----------|
| AddressSanitizer | ${asan_result} | — |
| UBSanitizer | ${ubsan_result} | — |
| **Total stress time** | | **${stress_time_display}** |

---

## 🔍 Static Analysis (clang-tidy)

**Summary:** ${lint_summary}

REPORT_EOF

    # Append lint details if there were issues
    if [ -n "$lint_output" ]; then
        cat >> "$report_file" << LINT_EOF

<details>
<summary>Detailed findings</summary>

\`\`\`
${lint_output}
\`\`\`

</details>

LINT_EOF
    fi

    # Append diff section
    cat >> "$report_file" << DIFF_HEADER_EOF

---

## 📝 Comparison with Reference Answer

**Summary:** ${diff_summary}

DIFF_HEADER_EOF

    if [ -n "$diff_output" ] && [ "$diff_summary" != "No reference answer found for this problem." ]; then
        cat >> "$report_file" << DIFF_DETAIL_EOF

<details>
<summary>Full diff</summary>

\`\`\`diff
${diff_output}
\`\`\`

</details>

DIFF_DETAIL_EOF
    fi

    # ============================================================
    # 6. Move solution file to Answered/
    # ============================================================
    cp "$CURRENT_DIR/$filename" "$dest_dir/${filename}"

    # ============================================================
    # 7. Cleanup
    # ============================================================
    rm -rf "$CURRENT_DIR"
    rm -f "$IMPL_DIR/.finish_asan" "$IMPL_DIR/.finish_ubsan"

    # Restore TestRegister.cpp to default
    cat > "$TEST_REGISTER" << 'EOF'
// Test Register - Managed by dsa.sh
//
// This file is auto-generated during the practice workflow:
//
//   ./dsa create <name>   → includes CurrentProblem/<name>.cpp
//   ./dsa submit          → switches to Answers/<category>/<name>.cpp
//   ./dsa finish          → resets to this default state
//
// No problem currently loaded. Run ./dsa create <name> to start.
EOF

    echo ""
    echo -e "  ${GREEN}${BOLD}🎉 Solution archived successfully!${NC}"
    echo ""
    echo -e "  📁 Solution: ${CYAN}Answered/${question_name}-rev${revision}/${filename}${NC}"
    echo -e "  📄 Report:   ${CYAN}Answered/${question_name}-rev${revision}/report.md${NC}"
    echo ""
    echo -e "  Ready for the next challenge? Run ${CYAN}./dsa create <name>${NC}"
    echo ""

    return 0
}

# ==================== Main ====================

cd "$ROOT_DIR"

case "${1:-}" in
    create)
        CreateQuestion "$2"
        ;;
    submit)
        SubmitAnswer
        ;;
    finish)
        FinishAnswer
        ;;
    list)
        ListQuestions "$2"
        ;;
    help|-h|--help)
        echo "DSA Practice Workflow"
        echo ""
        echo "Usage: ./dsa <command> [args]"
        echo ""
        echo "Commands:"
        echo "  create <name>      Load a question to solve"
        echo "  submit             Submit and test your current answer"
        echo "  finish             Archive solution with full analytics report"
        echo "  list [category]    List available questions"
        echo "  help               Show this help"
        echo ""
        echo "Examples:"
        echo "  ./dsa create TwoSum"
        echo "  ./dsa create Medium/AirPath"
        echo "  ./dsa submit"
        echo "  ./dsa finish"
        echo "  ./dsa list"
        echo "  ./dsa list Easy"
        echo ""
        echo "Workflow:"
        echo "  1. ./dsa create TwoSum       # Load a question"
        echo "  2. Edit CurrentProblem/TwoSum.cpp"
        echo "  3. ./dsa run                  # Quick test iteration"
        echo "  4. ./dsa submit               # Submit when ready"
        echo "  5. ./dsa finish               # Archive with analytics"
        ;;
    *)
        if [ -n "${1:-}" ]; then
            error "Unknown command: $1"
            echo ""
        fi
        echo "Usage: ./dsa <command>"
        echo ""
        echo "Commands:"
        echo "  create <name>      Load a question to solve"
        echo "  submit             Submit and test your current answer"
        echo "  finish             Archive solution with full analytics report"
        echo "  list [category]    List available questions"
        echo "  help               Show this help"
        ;;
esac
