/*
* Author : Muhammed Saneen P
* Date : 20-12-2025
* Description : This file contains functions related to undo/redo stacks
*/
#include "text_editor.h"
#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"


void pushStack(DynamicArrayStack *stack, Action action)
{
    if(stack->top != stack->capacity - 1 )
    {
        (stack->top)++;
        stack->actions[stack->top] = action;
    }
}

Action popStack(DynamicArrayStack *stack)
{
    if(!isStackEmpty(stack))
    {
        Action temp = stack->actions[stack->top];
        (stack->top)--;
        return temp;
    }
}


int isStackEmpty(DynamicArrayStack *stack)
{
    if(stack->top == -1)
        return 1;
    else
        return 0;    
}


void undo(TextEditor *editor,DynamicArrayStack* undoStack,DynamicArrayStack* redoStack)
{

    if(!isStackEmpty(undoStack))
    {
        Action action = popStack(undoStack);
        // for cursor to reach the required line and pos
        int line = 1;
        int req_line = action.cursorLine;

        Node* temp = editor->head;
        
        while(temp != NULL  && line != req_line)
        {
            temp = temp->next;
            line++;
        }
        
        editor->cursor = temp;
        editor->cursorLine = action.cursorLine;
        editor->cursorPos = action.cursorPos;
        
        if(strcmp(action.operation , "insert" ) == 0)
        {
            deleteCharacters(editor,strlen(action.text),redoStack);
        }
        else if(strcmp(action.operation,"delete")==0)
        {
            insertText(editor,action.text,redoStack);
        }

        printf("\nUndo operation successfull✅\n");
    }
    else
    {
        printf("\nError: Nothing to undo.\n");
    }
}


void redo(TextEditor *editor,DynamicArrayStack* undoStack,DynamicArrayStack* redoStack)
{


    if(!isStackEmpty(redoStack))
    {
        Action action = popStack(redoStack);
        // for cursor to reach the required line and pos
        int line = 1;
        int req_line = action.cursorLine;

        Node* temp = editor->head;
        
        while(temp != NULL  && line != req_line)
        {
            temp = temp->next;
            line++;
        }

        editor->cursor = temp;
        editor->cursorLine = action.cursorLine;
        editor->cursorPos = action.cursorPos;
        

        if(strcmp(action.operation , "insert" ) == 0)
        {
            deleteCharacters(editor,strlen(action.text),undoStack);
        }
        else if(strcmp(action.operation,"delete")==0)
        {
            insertText(editor,action.text,undoStack);
        }

        printf("\nRedo operation successfull✅\n");

    }
    else
    {
        printf("\nError: Nothing to redo.\n");
    }
}




