/*
Problem: Document Version Control (Git-like System)
Implement a version control system for documents, supporting commit and rollback.

Approach:
- Use a stack for version history
- Use a hash map for version content
- Commit pushes new version, rollback pops the latest

==================== PERFORMANCE ====================
Time Complexity:  O(1) per commit/rollback
Space Complexity: O(n * m) where n = versions, m = avg content length
=======================================================
*/

#include "TestBase.h"
#include <stack>
#include <unordered_map>
#include <string>

namespace DocumentVersionControl {

class VersionControl {
public:
    void commit(const std::string& content) {
        ++currentVersion;
        versionStack.push(currentVersion);
        versionContent[currentVersion] = content;
    }

    void rollback() {
        if (!versionStack.empty()) {
            versionContent.erase(versionStack.top());
            versionStack.pop();
        }
    }

    std::string getCurrentContent() {
        return versionStack.empty() ? "" : versionContent[versionStack.top()];
    }

private:
    std::stack<int> versionStack;
    std::unordered_map<int, std::string> versionContent;
    int currentVersion = 0;
};

// ========== Tests ==========

TEST(VersionControl_CommitAndGet) {
    VersionControl vc;
    vc.commit("Hello");
    TestBase::assertTrue(vc.getCurrentContent() == "Hello", "After first commit");
    vc.commit("World");
    TestBase::assertTrue(vc.getCurrentContent() == "World", "After second commit");
}

TEST(VersionControl_Rollback) {
    VersionControl vc;
    vc.commit("v1");
    vc.commit("v2");
    vc.rollback();
    TestBase::assertTrue(vc.getCurrentContent() == "v1", "After rollback");
}

TEST(VersionControl_RollbackToEmpty) {
    VersionControl vc;
    vc.commit("only");
    vc.rollback();
    TestBase::assertTrue(vc.getCurrentContent().empty(), "After rolling back all versions");
}

TEST(VersionControl_MultipleRollbacks) {
    VersionControl vc;
    vc.commit("A");
    vc.commit("B");
    vc.commit("C");
    vc.rollback();
    TestBase::assertTrue(vc.getCurrentContent() == "B", "After first rollback");
    vc.rollback();
    TestBase::assertTrue(vc.getCurrentContent() == "A", "After second rollback");
}

TEST(VersionControl_RollbackEmpty) {
    VersionControl vc;
    vc.rollback();
    TestBase::assertTrue(vc.getCurrentContent().empty(), "Rollback on empty");
}

TEST(VersionControl_CommitAfterRollback) {
    VersionControl vc;
    vc.commit("A");
    vc.commit("B");
    vc.rollback();
    vc.commit("C");
    TestBase::assertTrue(vc.getCurrentContent() == "C", "New commit after rollback");
}

TEST(VersionControl_EmptyContent) {
    VersionControl vc;
    TestBase::assertTrue(vc.getCurrentContent().empty(), "No commits yet");
}

} // namespace DocumentVersionControl
