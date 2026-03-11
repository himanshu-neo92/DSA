# DSA - Data Structures & Algorithms Practice

A lightweight, cross-platform C++20 testing framework for practicing DSA problems with built-in performance analysis, correctness checks, and a guided solve-submit-archive workflow.

## Features

- ✅ **Practice Workflow** - Load questions, solve, submit, and archive with `./dsa`
- ✅ **Simple Testing Framework** - Register tests with a single macro
- ✅ **Performance Analysis** - Static analysis with clang-tidy
- ✅ **Memory Safety** - AddressSanitizer for memory errors
- ✅ **Undefined Behavior Detection** - UBSan for UB bugs
- ✅ **Benchmarking** - Built-in timing and comparison utilities
- ✅ **Edge Case Generators** - Random arrays, sorted arrays, edge cases
- ✅ **Solution Analytics** - Time tracking, diff vs reference, sanitizer reports
- ✅ **Cross-Platform** - Works on macOS, Linux, and Windows (WSL)

---

## Quick Start

```bash
cd DSA

# 1. Install dependencies (auto-detects your platform)
./setup.sh

# 2. Browse available questions
./dsa list
./dsa list Easy          # Filter by category

# 3. Load a question
./dsa create TwoSum

# 4. Implement your solution
#    Open CurrentProblem/TwoSum.cpp and fill in the TODO

# 5. Iterate — build and run tests
./dsa run

# 6. Submit when ready
./dsa submit

# 7. Archive with full analytics report
./dsa finish
```

---

## Prerequisites

**macOS / Linux:** Run `./setup.sh` to auto-install everything.
**Windows:** Double-click `setup.bat` — it installs WSL2 + Ubuntu, then runs `setup.sh` for you.
**Check status:** Run `./setup.sh --check` to see what's installed/missing.

The setup scripts handle:

| Platform | How to set up | What gets installed |
|----------|--------------|---------------------|
| **macOS** | `./setup.sh` | Xcode Command Line Tools + LLVM via Homebrew |
| **Linux** | `./setup.sh` | `build-essential clang clang-tidy` via apt/dnf/pacman |
| **Windows** | Double-click `setup.bat` | WSL2 + Ubuntu, then C++ toolchain inside WSL |

<details>
<summary>Manual installation</summary>

### macOS

```bash
# Install Xcode Command Line Tools (includes clang++)
xcode-select --install

# Install LLVM for clang-tidy (optional, for static analysis)
brew install llvm

# Add to PATH (~/.zshrc or ~/.bashrc)
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
```

### Linux (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install build-essential clang clang-tidy
```

### Linux (RHEL/CentOS/Fedora)

```bash
sudo yum install gcc-c++ clang clang-tools-extra
```

### Windows

Use WSL2 (Windows Subsystem for Linux):

```bash
# Install WSL2 with Ubuntu (run in PowerShell as Admin)
wsl --install

# Inside WSL, install tools
sudo apt install build-essential clang clang-tidy
```

</details>

---

## Project Structure

```text
DSA/
├── dsa                       # Unified entry point (routes to implementation scripts)
├── setup.sh                  # Platform-independent dependency installer (macOS/Linux)
├── setup.bat                 # Windows bootstrap (installs WSL2, then runs setup.sh)
├── README.md
├── Questions/                # Question templates (problem + tests, empty solution stubs)
│   ├── Easy/                 #  15 questions (TwoSum, Fibonacci, BestTimeToSell, ...)
│   ├── Medium/               #  25 questions (3Sum, AirPath, NumberOfIslands, ...)
│   └── Hard/                 #   4 questions (AllPathsFromStartToDest, SerializeBTree, ...)
├── Answers/                  # Reference solutions with full implementations
│   ├── Easy/
│   ├── Medium/
│   └── Hard/
├── CurrentProblem/           # Your active workspace (created/cleaned by ./dsa)
├── Answered/                 # Completed solutions + analytics reports (.md)
└── implementation/           # Build system and framework internals
    ├── main.cpp              #   Entry point (don't modify)
    ├── TestBase.h             #   Testing framework (assertions, benchmarks, generators)
    ├── TestRegister.cpp       #   Auto-managed by ./dsa — points at current problem
    ├── build.sh               #   Build & test script
    ├── dsa.sh                 #   Workflow script
    ├── .clang-tidy            #   Static analysis config
    └── .clang-format          #   Code formatting config
```

---

## Practice Workflow

### Commands

| Command | Description |
|---------|-------------|
| `./dsa create <name>` | Load a question to solve |
| `./dsa submit` | Compile and run tests against your solution |
| `./dsa finish` | Archive solution with full analytics report |
| `./dsa list [category]` | List available questions |
| `./dsa run` | Build and run tests |
| `./dsa build` | Compile the project only |
| `./dsa clean` | Remove build artifacts |
| `./dsa lint` | Run clang-tidy static analysis |
| `./dsa help` | Show all commands |

### How it works

```text
  create             submit (pass)         finish
┌──────────┐      ┌───────────────┐      ┌──────────────┐
│ Question │ ───► │ CurrentProblem│ ───► │  Answered/   │
│ template │      │  (your code)  │      │  .cpp + .md  │
└──────────┘      └───────────────┘      └──────────────┘
```

### Step by step

**1. Load a question:**

```bash
./dsa create TwoSum              # search by name
./dsa create Medium/AirPath      # or specify category
```

This copies the question template to `CurrentProblem/TwoSum.cpp` with TODO stubs and updates the test register to include it.

**2. Implement your solution:**

Open `CurrentProblem/TwoSum.cpp` and replace the `// TODO` comments with your code. The file includes the problem statement, complexity analysis, and all test cases.

**3. Iterate with build:**

```bash
./dsa run          # Quick compile + run tests
./dsa all          # Full analysis (lint + ASan + UBSan + tests)
```

**4. Submit your answer:**

```bash
./dsa submit
```

If all tests pass, the test register switches to the reference answer so you can run `./dsa run` to compare behavior.

**5. Archive with analytics:**

```bash
./dsa finish
```

This generates a report in `Answered/<category>/<name>.md` with:

- ⏱️ **Time to solve** — duration from create to submit
- 📝 **Diff vs reference** — unified diff between your solution and the ideal answer
- 🔥 **Stress tests** — AddressSanitizer + UBSan results and timing
- 🔍 **Static analysis** — clang-tidy warnings and errors

Then cleans up `CurrentProblem/` so you're ready for the next challenge.

---

## Build Commands

| Command | Description |
|---------|-------------|
| `./dsa run` | Build and run tests |
| `./dsa all` | Full analysis + build + run |
| `./dsa build` | Compile the project only |
| `./dsa clean` | Remove build artifacts |
| `./dsa lint` | Run clang-tidy static analysis |
| `./dsa check` | Compile with strict warnings |
| `./dsa asan` | Run AddressSanitizer (memory errors) |
| `./dsa ubsan` | Run UndefinedBehaviorSanitizer |
| `./dsa debug` | Build with debug symbols for VSCode debugger |
| `./dsa debugout` | Build with DEBUG_OUT macro enabled and run |
| `./dsa deps` | Show install instructions |

---

## Adding a New Question

### 1. Create the question file

Create a new file in `Questions/Easy/`, `Questions/Medium/`, or `Questions/Hard/`:

```cpp
// Questions/Easy/MyProblem.cpp

#include "TestBase.h"
#include <vector>

namespace MyProblem {

// ========== Solution ==========
int solve(int n) {
    // TODO: implement your solution here
    return 0;
}

// ========== Tests ==========
TEST(MyProblem_Basic) {
    TestBase::assertEqual(4, solve(2));
    TestBase::assertEqual(10, solve(5));
}

TEST(MyProblem_EdgeCases) {
    TestBase::assertEqual(0, solve(0));
    TestBase::assertEqual(-2, solve(-1));
}

} // namespace MyProblem
```

### 2. Create the reference answer

Copy the question to `Answers/Easy/MyProblem.cpp` and fill in the correct implementation. This is used for the diff comparison in `./dsa finish`.

### 3. Load and solve

```bash
./dsa create MyProblem    # Load the question
# Edit CurrentProblem/MyProblem.cpp
./dsa run                 # Test your solution
./dsa submit              # Submit when ready
./dsa finish              # Archive with analytics
```

---

## Testing Framework API

### Assertions

```cpp
// Basic assertions
TestBase::assertEqual(expected, actual);
TestBase::assertEqual(expected, actual, "custom message");

TestBase::assertTrue(condition);
TestBase::assertFalse(condition);

// Vector comparison
TestBase::assertVectorEqual({1, 2, 3}, result);

// Exception testing
TestBase::assertThrows([]() { throw std::runtime_error("error"); });
```

### Benchmarking

```cpp
// Benchmark a single function
TestBase::benchmark("My Algorithm", []() {
    myFunction();
}, 1000);  // 1000 iterations

// Compare two implementations
TestBase::compareBenchmark(
    "Naive O(n²)", []() { naiveSolution(); },
    "Optimized O(n)", []() { optimizedSolution(); },
    1000
);
```

### Edge Case Generators

```cpp
// Random arrays
auto arr = TestBase::randomInts(100);              // 100 random ints
auto arr = TestBase::randomInts(100, -50, 50);     // Range [-50, 50]

// Sorted arrays
auto sorted = TestBase::sortedInts(100);           // [0, 1, 2, ..., 99]
auto reversed = TestBase::reverseSortedInts(100);  // [99, 98, ..., 0]

// Edge case values
auto edges = TestBase::edgeCaseInts();  // {0, 1, -1, INT_MIN, INT_MAX, ...}

// Edge case arrays
auto arrays = TestBase::edgeCaseArrays();  // Empty, single, two elements, etc.

// Arrays with duplicates
auto dups = TestBase::withDuplicates(100, 5);  // 100 elements, only 5 unique values

// Large array for stress testing
auto large = TestBase::largeArray(100000);

// Constants
TestBase::INT_MIN_VAL  // std::numeric_limits<int>::min()
TestBase::INT_MAX_VAL  // std::numeric_limits<int>::max()
```

---

## Static Analysis Checks

The `.clang-tidy` configuration checks for:

| Category | What It Detects |
|----------|-----------------|
| **Unnecessary copies** | Pass-by-value when const& would work |
| **Missing std::move** | Opportunities to use move semantics |
| **Missing const** | Variables that should be const |
| **Inefficient loops** | Copies in range-based for loops |
| **Vector operations** | Missing `reserve()` before push_back loops |
| **String operations** | Inefficient concatenation patterns |
| **Undefined behavior** | Use-after-move, object slicing |

Run static analysis:

```bash
./dsa lint
```

---

## Sanitizers

### AddressSanitizer (ASan)

Detects memory errors:

- Buffer overflows
- Use-after-free
- Memory leaks (Linux only)
- Stack buffer overflow

```bash
./dsa asan
```

### UndefinedBehaviorSanitizer (UBSan)

Detects undefined behavior:

- Integer overflow
- Null pointer dereference
- Division by zero
- Out-of-bounds array access

```bash
./dsa ubsan
```

---

## Example Session

```bash
$ ./dsa create TwoSum
[INFO] Loading question: Easy/TwoSum
[OK] Question loaded: Easy/TwoSum

  What to do next:
    1. Open CurrentProblem/TwoSum.cpp
    2. Implement the solution where you see // TODO
    3. Run ./dsa run to test your solution

$ ./dsa run
[INFO] Building project...
[OK] Built: ./main

========== Running Tests ==========
Running: TwoSum_Basic ... PASSED (0 μs)
Running: TwoSum_MiddleElements ... PASSED (0 μs)

========== Results ==========
Passed: 2/2
Failed: 0/2
=================================

$ ./dsa submit
[INFO] Submitting answer for: Easy/TwoSum
[OK] Compilation succeeded

  ✅ ALL 2 TESTS PASSED!
  Your solution for Easy/TwoSum is correct.
  ⏱️  Time spent: 3m 42s

$ ./dsa finish
[INFO] Archiving solution for: Easy/TwoSum
[INFO] ⏱️  Time to solve: 3m 42s
[INFO] 📝 Comparing with reference answer...
[INFO] 🔥 Running stress tests...
[INFO]   ASan: ✅ No memory errors
[INFO]   UBSan: ✅ No undefined behavior
[INFO] 🔍 Running static analysis...
[OK] Static analysis: clean

  🎉 Solution archived successfully!
  📁 Solution: Answered/Easy/TwoSum.cpp
  📄 Report:   Answered/Easy/TwoSum.md
```

---

## Tips

1. **Use `./dsa list` to browse questions** — filter by Easy, Medium, or Hard
2. **Iterate fast with `./dsa run`** — only submit when you're confident
3. **Use `const` liberally** — helps compiler optimize and catches bugs
4. **Test edge cases** — use `TestBase::edgeCaseArrays()` and `edgeCaseInts()`
5. **Benchmark before optimizing** — use `TestBase::compareBenchmark()` to verify improvements
6. **Check memory with ASan** — run `./dsa asan` for linked list / tree problems
7. **Review the reference answer** — after submit, run `./dsa run` to see the ideal solution

---

## Troubleshooting

### "clang-tidy not found"

```bash
./dsa deps  # Shows platform-specific install instructions
```

### "No C++ compiler found"

macOS:

```bash
xcode-select --install
```

Linux:

```bash
sudo apt install build-essential
```

### Tests not running

Make sure you have a problem loaded:

```bash
./dsa create TwoSum   # Load a question first
./dsa run             # Then run tests
```

Or manually include an answer file in `implementation/TestRegister.cpp`:

```cpp
#include "Answers/Easy/TwoSum.cpp"
```

---

## License

Personal use for DSA practice.
