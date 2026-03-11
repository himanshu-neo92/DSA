// Problem: Rule of 0/3/5
// Demonstrate proper C++ resource management with the Rule of 3/5/0.
// A class managing a raw pointer must define destructor, copy ctor,
// copy assignment, move ctor, and move assignment (Rule of 5).
//
// ==================== CONCEPTS ====================
// Rule of 0: If a class manages no resources, omit special members.
// Rule of 3: If you define destructor, copy ctor, or copy assignment,
//            you usually need all three.
// Rule of 5: Add move ctor and move assignment for efficiency.
// =======================================================

#include "TestBase.h"

namespace RuleOf035 {

class ManagedInt {
public:
    ManagedInt(int i) : ptr(new int(i)) {}

    ~ManagedInt() { delete ptr; }

    // Copy constructor — deep copy
    ManagedInt(const ManagedInt& obj) : ptr(new int(*obj.ptr)) {}

    // Copy assignment — deep copy with self-assignment guard
    ManagedInt& operator=(const ManagedInt& obj) {
        if (this != &obj) {
            *ptr = *obj.ptr;
        }
        return *this;
    }

    // Move constructor — steal resources
    ManagedInt(ManagedInt&& obj) noexcept : ptr(obj.ptr) {
        obj.ptr = nullptr;
    }

    // Move assignment — release current, steal resources
    ManagedInt& operator=(ManagedInt&& obj) noexcept {
        if (this != &obj) {
            delete ptr;
            ptr = obj.ptr;
            obj.ptr = nullptr;
        }
        return *this;
    }

    int value() const { return ptr ? *ptr : 0; }
    bool valid() const { return ptr != nullptr; }

private:
    int* ptr;
};

// ========== Tests ==========

TEST(RuleOf035_Construct) {
    ManagedInt a(42);
    TestBase::assertEqual(42, a.value());
    TestBase::assertTrue(a.valid(), "Constructed object should be valid");
}

TEST(RuleOf035_CopyConstruct) {
    ManagedInt a(10);
    ManagedInt b(a);
    TestBase::assertEqual(10, b.value());
    TestBase::assertEqual(10, a.value());
    TestBase::assertTrue(a.valid() && b.valid(), "Both should be valid after copy");
}

TEST(RuleOf035_CopyAssign) {
    ManagedInt a(10);
    ManagedInt b(20);
    b = a;
    TestBase::assertEqual(10, b.value());
    TestBase::assertEqual(10, a.value());
}

TEST(RuleOf035_MoveConstruct) {
    ManagedInt a(30);
    ManagedInt b(std::move(a));
    TestBase::assertEqual(30, b.value());
    TestBase::assertFalse(a.valid(), "Moved-from object should be invalid");
}

TEST(RuleOf035_MoveAssign) {
    ManagedInt a(40);
    ManagedInt b(0);
    b = std::move(a);
    TestBase::assertEqual(40, b.value());
    TestBase::assertFalse(a.valid(), "Moved-from object should be invalid");
}

TEST(RuleOf035_SelfAssign) {
    ManagedInt a(50);
    a = a;
    TestBase::assertEqual(50, a.value());
}

} // namespace RuleOf035
