/*
* Author : Muhammed Saneen P
* Date : 20-12-2025
* Description : This file contains the function prototypes for all redo/undo stack related functions
*/
#include "text_editor.h"

// Stack operations
void initStack(DynamicArrayStack *stack);
void pushStack(DynamicArrayStack *stack, Action action);
Action popStack(DynamicArrayStack *stack);
int isStackEmpty(DynamicArrayStack *stack);

// Undo/redo operations
void undo(TextEditor *editor,DynamicArrayStack* undoStack,DynamicArrayStack *redoStack);
void redo(TextEditor *editor,DynamicArrayStack* undoStack,DynamicArrayStack *redoStack);

// Utility functions
void init(TextEditor *, DynamicArrayStack *, DynamicArrayStack *); 