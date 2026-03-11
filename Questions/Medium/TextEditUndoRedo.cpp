/*
Problem: Text Editor Undo/Redo
Implement undo and redo operations for a text editor.

Approach:
- Maintain a current text string
- Use an undo stack: push current state before each edit
- Use a redo stack: push undone state when undoing
- Any new edit clears the redo stack

==================== PERFORMANCE ====================
Time Complexity:  O(1) per operation (amortized)
Space Complexity: O(n * m) where n = operations, m = avg text length
=======================================================
*/

#include "TestBase.h"
#include <stack>

namespace TextEditor {

class TextSystem {
public:
    // TODO: implement addText, undo, redo, canUndo, canRedo, getText
    void addText(const std::string& str) {}
    bool canUndo() { return false; }
    void undo() {}
    bool canRedo() { return false; }
    void redo() {}
    std::string getText() const { return currentText; }

private:
    std::string currentText;
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;
};

// ========== Tests ==========

TEST(TextEditor_AddText) {
    TextSystem editor;
    editor.addText("Hello");
    TestBase::assertTrue(editor.getText() == "Hello", "After adding Hello");
    editor.addText(" World");
    TestBase::assertTrue(editor.getText() == "Hello World", "After adding World");
}

TEST(TextEditor_Undo) {
    TextSystem editor;
    editor.addText("Hello");
    editor.addText(" World");
    editor.undo();
    TestBase::assertTrue(editor.getText() == "Hello", "After undo");
    editor.undo();
    TestBase::assertTrue(editor.getText() == "", "After second undo");
}

TEST(TextEditor_Redo) {
    TextSystem editor;
    editor.addText("Hello");
    editor.addText(" World");
    editor.undo();
    editor.redo();
    TestBase::assertTrue(editor.getText() == "Hello World", "After redo");
}

TEST(TextEditor_RedoClearedOnEdit) {
    TextSystem editor;
    editor.addText("Hello");
    editor.undo();
    TestBase::assertTrue(editor.canRedo(), "Should be able to redo");
    editor.addText("Bye");
    TestBase::assertFalse(editor.canRedo(), "Redo cleared after new edit");
    TestBase::assertTrue(editor.getText() == "Bye", "New text after edit");
}

TEST(TextEditor_CanUndoRedo) {
    TextSystem editor;
    TestBase::assertFalse(editor.canUndo(), "No undo on fresh editor");
    TestBase::assertFalse(editor.canRedo(), "No redo on fresh editor");
    editor.addText("A");
    TestBase::assertTrue(editor.canUndo(), "Can undo after edit");
}

TEST(TextEditor_MultipleUndoRedo) {
    TextSystem editor;
    editor.addText("A");
    editor.addText("B");
    editor.addText("C");
    TestBase::assertTrue(editor.getText() == "ABC", "ABC");
    editor.undo();
    TestBase::assertTrue(editor.getText() == "AB", "AB after undo");
    editor.undo();
    TestBase::assertTrue(editor.getText() == "A", "A after 2 undos");
    editor.redo();
    TestBase::assertTrue(editor.getText() == "AB", "AB after redo");
    editor.redo();
    TestBase::assertTrue(editor.getText() == "ABC", "ABC after 2 redos");
}

TEST(TextEditor_UndoPastEmpty) {
    TextSystem editor;
    editor.addText("X");
    editor.undo();
    editor.undo();
    TestBase::assertTrue(editor.getText() == "", "Should stay empty");
}

TEST(TextEditor_RedoPastEnd) {
    TextSystem editor;
    editor.addText("X");
    editor.undo();
    editor.redo();
    editor.redo();
    TestBase::assertTrue(editor.getText() == "X", "Should stay at X");
}

}
