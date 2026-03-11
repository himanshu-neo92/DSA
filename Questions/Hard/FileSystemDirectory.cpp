/*
Problem: File System Directory Structure
Implement an in-memory file system supporting mkdir, addFile, readFile, and ls.

Approach:
- Use a tree structure with nodes containing maps of children
- Each node can be a directory or a file
- Navigate paths by splitting on '/' delimiter

==================== PERFORMANCE ====================
Time Complexity:  O(p) per operation where p = path depth
Space Complexity: O(total nodes in the file system)
=======================================================
*/

#include "TestBase.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace FileSystemDirectory {

class FileSystem {
public:
    // TODO: implement mkdir, addFile, readFile, ls
    FileSystem() { root = new Node(); }

    void mkdir(const std::string& path) {}

    void addFile(const std::string& filePath, const std::string& content) {}

    std::string readFile(const std::string& filePath) {
        return "";
    }

    std::vector<std::string> ls(const std::string& path) {
        return {};
    }

private:
    struct Node {
        bool isFile = false;
        std::string content;
        std::unordered_map<std::string, Node*> children;
    };

    Node* root;

    std::vector<std::string> split(const std::string& path) {
        std::vector<std::string> res;
        size_t pos = 1, found;
        while ((found = path.find('/', pos)) != std::string::npos) {
            res.push_back(path.substr(pos, found - pos));
            pos = found + 1;
        }
        if (pos < path.size()) res.push_back(path.substr(pos));
        return res;
    }
};

// ========== Tests ==========

TEST(FileSystem_MkdirAndLs) {
    FileSystem fs;
    fs.mkdir("/a/b/c");
    auto listing = fs.ls("/a");
    TestBase::assertEqual(1, (int)listing.size());
    TestBase::assertTrue(listing[0] == "b", "Should contain b");
}

TEST(FileSystem_AddAndReadFile) {
    FileSystem fs;
    fs.addFile("/readme.txt", "Hello World");
    TestBase::assertTrue(fs.readFile("/readme.txt") == "Hello World", "Read file content");
}

TEST(FileSystem_NestedFile) {
    FileSystem fs;
    fs.mkdir("/a/b");
    fs.addFile("/a/b/file.txt", "content");
    TestBase::assertTrue(fs.readFile("/a/b/file.txt") == "content", "Nested file");
}

TEST(FileSystem_LsRoot) {
    FileSystem fs;
    fs.mkdir("/a");
    fs.mkdir("/b");
    fs.addFile("/c.txt", "data");

    auto listing = fs.ls("/");
    TestBase::assertEqual(3, (int)listing.size());
}

TEST(FileSystem_LsFile) {
    FileSystem fs;
    fs.addFile("/myfile.txt", "data");
    auto listing = fs.ls("/myfile.txt");
    TestBase::assertEqual(1, (int)listing.size());
    TestBase::assertTrue(listing[0] == "myfile.txt", "ls on file returns filename");
}

TEST(FileSystem_EmptyDirectory) {
    FileSystem fs;
    fs.mkdir("/empty");
    auto listing = fs.ls("/empty");
    TestBase::assertEqual(0, (int)listing.size());
}

TEST(FileSystem_DeepNesting) {
    FileSystem fs;
    fs.mkdir("/a/b/c/d/e");
    fs.addFile("/a/b/c/d/e/deep.txt", "deep content");
    TestBase::assertTrue(fs.readFile("/a/b/c/d/e/deep.txt") == "deep content", "Deep nesting");
}

TEST(FileSystem_MultipleFilesInDir) {
    FileSystem fs;
    fs.mkdir("/docs");
    fs.addFile("/docs/a.txt", "A");
    fs.addFile("/docs/b.txt", "B");
    fs.addFile("/docs/c.txt", "C");

    auto listing = fs.ls("/docs");
    TestBase::assertEqual(3, (int)listing.size());
}

} // namespace FileSystemDirectory
