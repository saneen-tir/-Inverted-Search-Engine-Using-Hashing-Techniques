/*
* Author : Muhammed Saneen P
* Date : 20-12-2025
* Description : This file contains the main structure definitions
*/
#ifndef TEXT_EDITOR
#define TEXT_EDITOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

// Define the structure for a node in the linked list (each line in the editor)
typedef struct Node {
    char *line;
    struct Node *prev;
    struct Node *next;
} Node;

// Define the structure for the text editor
typedef struct {
    Node *head;       // Pointer to the first line
    Node *tail;       // Pointer to the last line
    Node *cursor;     // Pointer to the current line where the cursor is
    int cursorLine;   // Line number of the cursor
    int cursorPos;    // Column position of the cursorhjb
} TextEditor;

// Define the structure for an action (used for undo/redo operations)
typedef struct {
    char *operation;  // Operation type ("insert" or "delete")
    char *text;       // Text involved in the operation
    int cursorLine;   // Line number where the operation occurred
    int cursorPos;    // Column position where the operation occurred
} Action;

// Define the structure for a dynamic array stack (used for undo/redo stacks)
typedef struct {
    Action *actions;  // Dynamic array of actions
    int top;         // Current size of the stack
    int capacity;     // Current capacity of the stack
} DynamicArrayStack;


void init(TextEditor *, DynamicArrayStack *, DynamicArrayStack *);
#endif