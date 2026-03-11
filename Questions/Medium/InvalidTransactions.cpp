// Problem: Invalid Transactions
// A transaction is invalid if:
// 1. The amount exceeds $1000, OR
// 2. It occurs within 60 minutes of another transaction with the same name
//    in a different city
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) average - bucket by time/60, check neighboring buckets
// Space Complexity: O(n) - Hash maps for buckets and invalid indices
//
// Key concepts:
// - Bucket transactions by time / 60
// - For each transaction, only check buckets [b-1, b, b+1]
// - Same name + different city + abs(time diff) <= 60 => both invalid
// - Amount > 1000 => invalid regardless
// =======================================================

#include "TestBase.h"
#include <unordered_map>
#include <unordered_set>
#include <cmath>

namespace InvalidTransactions {

struct Transact {
    std::string name;
    int val;
    std::string place;
    int time;
};

// ========== Solution ==========
std::vector<Transact> returnInvalidTransact(const std::vector<Transact>& transacts) {
    // TODO: implement your solution here
    return {};
}

}

// ==================== TEST CASES ====================

TEST(InvalidTransactions_EmptyInput) {
    std::vector<InvalidTransactions::Transact> input = {};
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Empty input should return no invalid transactions");
}

TEST(InvalidTransactions_AllValid) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 10},
        {"bob",   200, "paris",  20},
        {"carol", 999, "tokyo",  30},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "All valid transactions should return empty");
}

TEST(InvalidTransactions_SingleOverLimit) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 1001, "london", 10},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(1, static_cast<int>(result.size()), "One transaction over 1000 should be invalid");
    TestBase::assertTrue(result[0].name == "alice", "Invalid transaction should be alice's");
}

TEST(InvalidTransactions_ExactlyAtLimit) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 1000, "london", 10},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Transaction of exactly 1000 should be valid");
}

TEST(InvalidTransactions_MultipleOverLimit) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 2000, "london", 10},
        {"bob",   5000, "paris",  20},
        {"carol", 1500, "tokyo",  30},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(3, static_cast<int>(result.size()), "All three over-limit transactions should be invalid");
}

TEST(InvalidTransactions_DifferentCity_WithinTimeWindow) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  130},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Both transactions in a conflict should be invalid");
}

TEST(InvalidTransactions_DifferentCity_OutsideTimeWindow) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  30},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Different city but time diff > 60 should be valid");
}

TEST(InvalidTransactions_DifferentCity_ExactlyAt60) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  160},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Exactly 60 min apart in different cities should be invalid");
}

TEST(InvalidTransactions_DifferentCity_At61) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  161},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "61 min apart in different cities should be valid");
}

TEST(InvalidTransactions_SameCity_WithinTimeWindow) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "london", 130},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Same city within time window should be valid");
}

TEST(InvalidTransactions_DifferentUsers_DontAffectEachOther) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"bob",   600, "paris",  110},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Different users should not flag each other");
}

TEST(InvalidTransactions_MixedInvalidReasons) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 2000, "london", 10},
        {"bob",   500,  "london", 100},
        {"bob",   600,  "paris",  130},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(3, static_cast<int>(result.size()), "Should have 3 invalid: alice + both bobs");
}

TEST(InvalidTransactions_SingleTransaction_Valid) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 100, "london", 10},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Single valid transaction should return empty");
}

TEST(InvalidTransactions_ZeroAmount) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 0, "london", 10},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Zero amount should be valid");
}

TEST(InvalidTransactions_UnsortedInput) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "paris",  130},
        {"alice", 600, "london", 100},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Unsorted input should still detect conflicts");
}

TEST(InvalidTransactions_ThreeWayConflict) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 500, "paris",  120},
        {"alice", 500, "tokyo",  140},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(3, static_cast<int>(result.size()), "All three in a 3-way conflict should be invalid");
}

TEST(InvalidTransactions_OverLimitAndCityConflict) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500,  "london", 100},
        {"alice", 2000, "paris",  120},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Over-limit + city conflict should not duplicate");
}

TEST(InvalidTransactions_ManyTransactions_OnlyWindowScanned) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 0},
        {"alice", 500, "paris",  1000},
        {"alice", 500, "tokyo",  2000},
        {"alice", 500, "berlin", 3000},
        {"alice", 500, "rome",   3030},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Only berlin+rome should conflict");
}

TEST(InvalidTransactions_CrossBucketBoundary) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 59},
        {"alice", 500, "paris",  61},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Cross-bucket boundary should still detect conflict");
}

TEST(InvalidTransactions_SameBucketNoConflict) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 60},
        {"alice", 500, "london", 119},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Same bucket same city should be valid");
}
