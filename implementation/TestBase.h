#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <random>
#include <limits>
#include <algorithm>

class TestBase {
public:
    static TestBase& getInstance() {
        static TestBase instance;
        return instance;
    }

    // Delete copy/move to enforce singleton
    TestBase(const TestBase&) = delete;
    TestBase& operator=(const TestBase&) = delete;
    TestBase(TestBase&&) = delete;
    TestBase& operator=(TestBase&&) = delete;

    // Register a test case
    void addTest(const std::string& name, std::function<void()> func) {
        tests_.push_back({name, std::move(func)});
    }

    // Run all registered tests
    void runAll() {
        std::cout << "\n========== Running Tests ==========\n\n";

        int passed = 0;
        int failed = 0;

        for (const auto& test : tests_) {
            std::cout << "Running: " << test.name << " ... ";

            auto start = std::chrono::high_resolution_clock::now();

            try {
                test.func();
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

                std::cout << "PASSED (" << duration.count() << " μs)\n";
                passed++;
            } catch (const std::exception& e) {
                std::cout << "FAILED: " << e.what() << "\n";
                failed++;
            }
        }

        std::cout << "\n========== Results ==========\n";
        std::cout << "Passed: " << passed << "/" << tests_.size() << "\n";
        std::cout << "Failed: " << failed << "/" << tests_.size() << "\n";
        std::cout << "=================================\n";
    }

    // ==================== ASSERTIONS ====================

    template<typename T>
    static void assertEqual(const T& expected, const T& actual, const std::string& msg = "") {
        if (expected != actual) {
            throw std::runtime_error(
                "Expected: " + std::to_string(expected) +
                ", Got: " + std::to_string(actual) +
                (msg.empty() ? "" : " - " + msg)
            );
        }
    }

    static void assertTrue(bool condition, const std::string& msg = "Condition was false") {
        if (!condition) {
            throw std::runtime_error(msg);
        }
    }

    static void assertFalse(bool condition, const std::string& msg = "Condition was true") {
        if (condition) {
            throw std::runtime_error(msg);
        }
    }

    template<typename T>
    static void assertVectorEqual(const std::vector<T>& expected, const std::vector<T>& actual, const std::string& msg = "") {
        if (expected.size() != actual.size()) {
            throw std::runtime_error(
                "Vector size mismatch. Expected: " + std::to_string(expected.size()) +
                ", Got: " + std::to_string(actual.size()) +
                (msg.empty() ? "" : " - " + msg)
            );
        }
        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != actual[i]) {
                throw std::runtime_error(
                    "Mismatch at index " + std::to_string(i) +
                    ". Expected: " + std::to_string(expected[i]) +
                    ", Got: " + std::to_string(actual[i]) +
                    (msg.empty() ? "" : " - " + msg)
                );
            }
        }
    }

    static void assertThrows(const std::function<void()>& func, const std::string& msg = "Expected exception not thrown") {
        try {
            func();
            throw std::runtime_error(msg);
        } catch (const std::exception&) {
            // Expected
        }
    }

    // ==================== BENCHMARKING ====================

    // Benchmark a function and print results
    template<typename Func>
    static void benchmark(const std::string& name, Func func, int iterations = 1000) {
        // Warmup
        for (int i = 0; i < 10; i++) func();

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {
            func();
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        auto avg = total / iterations;

        std::cout << "⏱️  " << name << ": " << avg << " μs/op"
                  << " (total: " << total << " μs for " << iterations << " iterations)\n";
    }

    // Compare two implementations
    template<typename Func1, typename Func2>
    static void compareBenchmark(const std::string& name1, Func1 func1,
                                  const std::string& name2, Func2 func2,
                                  int iterations = 1000) {
        std::cout << "\n📊 Comparing implementations:\n";
        benchmark(name1, func1, iterations);
        benchmark(name2, func2, iterations);
        std::cout << "\n";
    }

    // ==================== EDGE CASE GENERATORS ====================

    // Generate random integers
    static std::vector<int> randomInts(size_t count, int min = -1000, int max = 1000) {
        std::vector<int> result(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        for (size_t i = 0; i < count; i++) {
            result[i] = dist(gen);
        }
        return result;
    }

    // Generate sorted array
    static std::vector<int> sortedInts(size_t count, int start = 0) {
        std::vector<int> result(count);
        for (size_t i = 0; i < count; i++) {
            result[i] = start + static_cast<int>(i);
        }
        return result;
    }

    // Generate reverse sorted array
    static std::vector<int> reverseSortedInts(size_t count, int start = 0) {
        auto result = sortedInts(count, start);
        std::reverse(result.begin(), result.end());
        return result;
    }

    // Common edge case values
    static constexpr int INT_MIN_VAL = std::numeric_limits<int>::min();
    static constexpr int INT_MAX_VAL = std::numeric_limits<int>::max();

    // Edge case integer sets
    static std::vector<int> edgeCaseInts() {
        return {0, 1, -1, INT_MIN_VAL, INT_MAX_VAL, INT_MIN_VAL + 1, INT_MAX_VAL - 1};
    }

    // Empty, single, two element arrays
    static std::vector<std::vector<int>> edgeCaseArrays() {
        return {
            {},                          // empty
            {0},                         // single zero
            {1},                         // single positive
            {-1},                        // single negative
            {INT_MIN_VAL},              // single min
            {INT_MAX_VAL},              // single max
            {1, 2},                      // two elements sorted
            {2, 1},                      // two elements reverse
            {1, 1},                      // two same elements
            {INT_MIN_VAL, INT_MAX_VAL}  // extreme range
        };
    }

    // Generate array with duplicates
    static std::vector<int> withDuplicates(size_t count, int numUnique = 5) {
        std::vector<int> result(count);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, numUnique - 1);
        for (size_t i = 0; i < count; i++) {
            result[i] = dist(gen);
        }
        return result;
    }

    // Generate large array for stress testing
    static std::vector<int> largeArray(size_t count = 100000) {
        return randomInts(count);
    }

private:
    TestBase() = default;

    struct TestCase {
        std::string name;
        std::function<void()> func;
    };

    std::vector<TestCase> tests_;
};

// Macro to define and register tests in one step
// Usage: TEST(MyTestName) { /* test body */ }
#define TEST(name) \
    static void TEST_FUNC_##name(); \
    namespace { \
        struct TestRegistrar_##name { \
            TestRegistrar_##name() { \
                TestBase::getInstance().addTest(#name, TEST_FUNC_##name); \
            } \
        } testRegistrar_##name; \
    } \
    static void TEST_FUNC_##name()

// Debug output macro - only prints when DEBUG_OUTPUT is defined
// Usage: DEBUG_OUT("message: " << variable << " more text");
#ifdef DEBUG_OUTPUT
    #define DEBUG_OUT(x) std::cout << "[DEBUG] " << x << "\n"
#else
    #define DEBUG_OUT(x) do {} while(0)
#endif
