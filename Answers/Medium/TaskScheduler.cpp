/*
Problem: Task Scheduler with Priorities
Schedule tasks, always executing the highest-priority task next.

Approach:
- Use a priority queue (max-heap) to pick tasks by priority
- Higher priority value = executed first

==================== PERFORMANCE ====================
Time Complexity:  O(log n) per addTask, O(log n) per executeTask
Space Complexity: O(n) where n = number of pending tasks
=======================================================
*/

#include "TestBase.h"
#include <queue>
#include <string>

namespace TaskScheduler {

struct Task {
    int priority;
    std::string description;
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

class TaskSchedulerSystem {
public:
    void addTask(int priority, const std::string& desc) {
        tasks.push({priority, desc});
    }

    std::string executeTask() {
        if (tasks.empty()) return "";
        std::string desc = tasks.top().description;
        tasks.pop();
        return desc;
    }

private:
    std::priority_queue<Task> tasks;
};

// ========== Tests ==========

TEST(TaskScheduler_BasicExecution) {
    TaskSchedulerSystem ts;
    ts.addTask(1, "Low priority");
    ts.addTask(3, "High priority");
    ts.addTask(2, "Medium priority");

    TestBase::assertTrue(ts.executeTask() == "High priority", "Highest first");
    TestBase::assertTrue(ts.executeTask() == "Medium priority", "Medium second");
    TestBase::assertTrue(ts.executeTask() == "Low priority", "Low third");
}

TEST(TaskScheduler_EmptyQueue) {
    TaskSchedulerSystem ts;
    TestBase::assertTrue(ts.executeTask().empty(), "No tasks to execute");
}

TEST(TaskScheduler_SingleTask) {
    TaskSchedulerSystem ts;
    ts.addTask(5, "Only task");
    TestBase::assertTrue(ts.executeTask() == "Only task", "Execute single task");
    TestBase::assertTrue(ts.executeTask().empty(), "Queue now empty");
}

TEST(TaskScheduler_SamePriority) {
    TaskSchedulerSystem ts;
    ts.addTask(1, "Task A");
    ts.addTask(1, "Task B");
    std::string first = ts.executeTask();
    std::string second = ts.executeTask();
    TestBase::assertTrue(!first.empty() && !second.empty(), "Both executed");
    TestBase::assertTrue(first != second, "Different tasks");
}

TEST(TaskScheduler_AddAfterExecute) {
    TaskSchedulerSystem ts;
    ts.addTask(1, "First");
    TestBase::assertTrue(ts.executeTask() == "First", "Execute first");
    ts.addTask(2, "Second");
    TestBase::assertTrue(ts.executeTask() == "Second", "Execute newly added");
}

TEST(TaskScheduler_ManyTasks) {
    TaskSchedulerSystem ts;
    ts.addTask(10, "Urgent");
    ts.addTask(1, "Lowest");
    ts.addTask(5, "Medium");
    ts.addTask(8, "High");

    TestBase::assertTrue(ts.executeTask() == "Urgent", "10 first");
    TestBase::assertTrue(ts.executeTask() == "High", "8 second");
    TestBase::assertTrue(ts.executeTask() == "Medium", "5 third");
    TestBase::assertTrue(ts.executeTask() == "Lowest", "1 last");
}

} // namespace TaskScheduler
