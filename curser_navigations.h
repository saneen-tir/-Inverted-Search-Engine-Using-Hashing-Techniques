/*
* Author : Muhammed Saneen P
* Date : 20-12-2025
* Description : This file has all the prototypes of cursor navigation functions
*/
#include "text_editor.h"

void moveCursorUp(TextEditor *editor);
void moveCursorDown(TextEditor *editor);
void moveCursorLeft(TextEditor *editor);
void moveCursorRight(TextEditor *editor);
void jumpToStartOfFile(TextEditor *editor);
void jumpToEndOfFile(TextEditor *editor);
void jumpToStartOfLine(TextEditor *editor);
void jumpToEndOfLine(TextEditor *editor);
