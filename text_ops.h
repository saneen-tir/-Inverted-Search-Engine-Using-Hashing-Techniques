/*
* Author : Muhammed Saneen P
* Date : 20-12-2025
* Description : This file contains the function prototypes for text operation functions
*/
#include "text_editor.h"

void insertText(TextEditor *editor, const char *text , DynamicArrayStack* Stack);
int handleCommand(char *command, TextEditor *editor, DynamicArrayStack* undoStack,DynamicArrayStack* redoStack);
void deleteCharacters(TextEditor *editor, int length , DynamicArrayStack* undoStack);
void copyText(TextEditor *editor, int n);
void cutText(TextEditor *editor, int n , DynamicArrayStack *undoStack);
void displayText(TextEditor *editor);
void printMenu();