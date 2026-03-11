// Problem: Invalid Transactions
// Given a list of transactions, return those that are invalid:
// - Amount exceeds 1000, OR
// - Same name in different city within 60 minutes.
//
// ==================== PERFORMANCE ====================
// Time Complexity:  O(n) average - bucket-based conflict detection with 3-bucket scan
// Space Complexity: O(n) - maps for name→bucket→indices and invalid set
//
// Key concepts:
// - Time bucketing (time/60) limits neighbor checks to 3 buckets
// - Separate checks for amount threshold and city conflict
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

  // O(n) average, NO sorting at all.
  //
  // Key idea: bucket each transaction by  time / 60 .
  // Two transactions can only conflict (abs(time diff) <= 60) if their
  // buckets differ by at most 1.  So for each transaction we only need
  // to check buckets  [b-1, b, b+1]  — a constant number of buckets.
  //
  // Data structure:  name → bucket → vector<index>
  //
  // Per transaction we scan O(w) entries across 3 buckets, where w is
  // the number of same-name transactions that land in nearby buckets.
  // In practice w is tiny.  Total: O(n) average.
  std::vector<Transact> returnInvalidTransact(const std::vector<Transact> & transacts) {

    std::unordered_set<int> invalidIdx;

    // name → (bucket → list of indices)
    std::unordered_map<std::string,
      std::unordered_map<int, std::vector<int>>> nameBuckets;

    for (int i = 0; i < static_cast<int>(transacts.size()); i++) {
      const auto& t = transacts[i];

      if (t.val > 1000) {
        invalidIdx.insert(i);
      }

      int bucket = t.time / 60;

      // Check the 3 neighboring buckets for conflicts
      for (int b = bucket - 1; b <= bucket + 1; b++) {
        auto nameIt = nameBuckets.find(t.name);
        if (nameIt == nameBuckets.end()) continue;

        auto bucketIt = nameIt->second.find(b);
        if (bucketIt == nameIt->second.end()) continue;

        for (int prevIdx : bucketIt->second) {
          if (transacts[prevIdx].place != t.place &&
              std::abs(transacts[prevIdx].time - t.time) <= 60) {
            invalidIdx.insert(prevIdx);
            invalidIdx.insert(i);
          }
        }
      }

      nameBuckets[t.name][bucket].push_back(i);
    }

    std::vector<Transact> result;
    for (int idx : invalidIdx) {
      result.push_back(transacts[idx]);
    }
    return result;
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
        {"alice", 600, "paris",  130},  // abs(100-130)=30 <= 60
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Both transactions in a conflict should be invalid");
}

TEST(InvalidTransactions_DifferentCity_OutsideTimeWindow) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  30},   // abs(100-30)=70 > 60
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Different city but time diff > 60 should be valid");
}

TEST(InvalidTransactions_DifferentCity_ExactlyAt60) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  160},  // abs(100-160)=60
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Exactly 60 min apart in different cities should be invalid");
}

TEST(InvalidTransactions_DifferentCity_At61) {
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 100},
        {"alice", 600, "paris",  161},  // abs(100-161)=61 > 60
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
    // time 59 → bucket 0, time 61 → bucket 1.  abs(59-61)=2 <= 60 → conflict.
    // Tests that we correctly check adjacent buckets.
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 59},
        {"alice", 500, "paris",  61},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(2, static_cast<int>(result.size()), "Cross-bucket boundary should still detect conflict");
}

TEST(InvalidTransactions_SameBucketNoConflict) {
    // Both in bucket 1 (times 60 and 119), same city → no conflict
    std::vector<InvalidTransactions::Transact> input = {
        {"alice", 500, "london", 60},
        {"alice", 500, "london", 119},
    };
    auto result = InvalidTransactions::returnInvalidTransact(input);
    TestBase::assertEqual(0, static_cast<int>(result.size()), "Same bucket same city should be valid");
}
