/*
* Author : Muhammed Saneen P
* Date : 20-12-2025
* Description : This file acts like a main file which also contains the required functions
*/
#include "text_editor.h"
#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"


int total_line = 1;
//flag to check if opening is possible ,  if 1 , occupied 
int flag = 0;


char copy_buf[100];

int main()
{
    
    // Initialize the text editor and stacks
    TextEditor editor;
    DynamicArrayStack undoStack;
    DynamicArrayStack redoStack;

    //initialize
    init(&editor, &undoStack, &redoStack);


    // User interaction loop
    char command[256];

    while (1) 
    {
        printMenu();

        printf("Enter command: ");
        scanf(" %255[^\n]",command);

        if (strcmp(command, "exit") == 0) {
            break;
        } else {
            handleCommand(command, &editor,&undoStack,&redoStack);
        }
    }


    return 0;
}

void printMenu()
{
    printf("\nText Editor Commands:\n");

    printf("1. insert <text>        - Insert text at the current cursor position\n");

    printf("2. delete <n>           - Delete <n> characters from the cursor position\n");
    printf("   delete line          - Delete the contents of the current line\n");

    printf("3. undo                 - Undo the last operation\n");
    printf("4. redo                 - Redo the last undone operation\n");

    printf("5. print                - Display the current editor content\n");

    printf("6. open <filename>      - Open a text file\n");

    printf("7. cursor <dir>         - Move cursor (left | right | up | down)\n");

    printf("8. save <filename>      - Save the text to a file\n");

    printf("9. jump <pos>           - Jump to position (BOF | EOF | BOL | EOL)\n");

    printf("10. copy <n>            - Copy <n> characters from cursor position\n");

    printf("11. cut <n>             - Cut <n> characters from cursor position\n");

    printf("12. paste               - Paste the copied/cut text\n");

    printf("13. close               - close the current file\n");

    printf("14. exit                - Exit the text editor\n");
}



void deleteLine(TextEditor *editor)
{
    //consider last line case also
    Node* temp = editor->cursor;
    temp->line[0] = '\0';
    editor->cursorPos = 0;

    printf("\nDeleted current line successfully.✅\n");
    
}

void cutText(TextEditor *editor, int n , DynamicArrayStack *undoStack)
{
    Node* cur_node = editor->cursor;
    strncpy(copy_buf , cur_node->line + editor->cursorPos , n);
    copy_buf[n] = '\0';
    deleteCharacters(editor,n, undoStack);
}


void copyText(TextEditor *editor, int n)
{
    Node* cur_node = editor->cursor;
    strncpy(copy_buf , cur_node->line + editor->cursorPos , n);
    copy_buf[n] = '\0';
    // printf("copy buf is %s\n",copy_buf);
}

void pasteText(TextEditor *editor,DynamicArrayStack *undoStack)
{ 
    insertText(editor,copy_buf,undoStack);
}


void init(TextEditor *editor, DynamicArrayStack *undoStack, DynamicArrayStack *redoStack)
{

    //creating first line , by default cursor is in first line
    Node *new = malloc(sizeof(Node));
    new->line = malloc(1023);
    new->line[0] = '\0';
    new->next = NULL;
    new->prev = NULL;

    editor -> head = new;
    editor ->tail = new;       
    editor ->cursor = new;
    editor ->cursorLine = 1;
    editor ->cursorPos = 0;

    undoStack -> actions = malloc(INITIAL_CAPACITY * sizeof(Action));
    undoStack -> top = -1 ;        
    undoStack -> capacity = INITIAL_CAPACITY;  

    redoStack -> actions = malloc(INITIAL_CAPACITY * sizeof(Action));
    redoStack -> top = -1 ;        
    redoStack -> capacity = INITIAL_CAPACITY;  
}



int handleCommand(char *command, TextEditor *editor, DynamicArrayStack* undoStack , DynamicArrayStack* redoStack)
{


    char first_word[10];
    char second_word[1023];

    sscanf(command,"%s",first_word);
    int f_len = strlen(first_word);
    sscanf(command+f_len+1 , "%[^\n]" , second_word);

    

    

    if( strcmp(first_word,"insert") == 0 )
    {
        if(second_word[0] == '\0')
        {
            printf("ERROR : give a valid second argument\n");
            return 1;
        }

        insertText(editor,second_word,undoStack);
        printf("\nText inserted successfully✅\n");
    }
    else if(strcmp(first_word,"print") == 0)
    {
        displayText(editor);
    }
    else if(strcmp(first_word,"delete") == 0)
    {
        if(second_word[0] == '\0')
        {
             printf("ERROR : give a valid second argument\n");
            return 1;
        }

        if(strcmp(second_word,"line") == 0)
        {
            deleteLine(editor);
        }
        else if(second_word[0] >= '0' && second_word[0] <= '9')
        {
            int length = atoi(second_word);
            deleteCharacters(editor,length,undoStack);
        }
        
    }
    else if(strcmp(first_word,"cursor") == 0)
    {

        if(second_word[0] == '\0')
        {
             printf("ERROR : give a valid second argument\n");
            return 1;
        }

        if(strcmp(second_word,"down") == 0)
        {
            moveCursorDown(editor);
        }
        else if(strcmp(second_word,"left") == 0)
        {
            moveCursorLeft(editor);
        }
        else if(strcmp(second_word,"right") == 0)
        {
            moveCursorRight(editor);
        }
        else if(strcmp(second_word,"up") == 0)
        {
            moveCursorUp(editor);
        }
        else
        {
            printf("ERROR : give a valid second argument\n");
        }
        
    }
    else if(strcmp(first_word,"jump") == 0)
    {

        if(second_word[0] == '\0')
        {
             printf("ERROR : give a valid second argument\n");
            return 1;
        }

        if(strcmp(second_word,"EOF") == 0)
        {
            jumpToEndOfFile(editor);
            
        }
        else if(strcmp(second_word,"BOF") == 0)
        {
            jumpToStartOfFile(editor);
        }
        else if(strcmp(second_word,"BOL") == 0)
        {
            jumpToStartOfLine(editor);
        }
        else if(strcmp(second_word,"EOL") == 0)
        {
            jumpToEndOfLine(editor);
        }
        else
        {
            printf("ERROR : give a valid second argument\n");
        }
        
    }
    else if(strcmp(first_word,"undo") == 0)
    {
        undo(editor,undoStack,redoStack);
    }
    else if(strcmp(first_word,"redo") == 0)
    {
        redo(editor,undoStack,redoStack);
    }
    else if(strcmp(first_word,"copy") == 0)
    {
        if(second_word[0] == '\0')
        {
            printf("ERROR : give a valid second argument\n");
            return 1;
        }

        int length = atoi(second_word);
        copyText(editor, length);
    }
    else if(strcmp(first_word,"paste") == 0)
    {
        pasteText(editor,undoStack);    
    }
    else if(strcmp(first_word,"cut") == 0)
    {
        if(second_word[0] == '\0')
        {
            printf("ERROR : give a valid second argument\n");
            return 1;
        }

        int length = atoi(second_word);
        cutText(editor, length ,undoStack);
    }
    else if(strcmp(first_word,"save") == 0)
    {
        if(second_word[0] == '\0' || !strstr(second_word,".txt"))
        {
            printf("ERROR : give a valid .txt file as second argument\n");
            return 1;
        }

        saveFile(editor,second_word);
    }
    else if(strcmp(first_word,"open") == 0)
    {
        if(second_word[0] == '\0' || !strstr(second_word,".txt"))
        {
            printf("ERROR : give a valid .txt file as second argument\n");
            return 1;
        }
        if(flag == 1)
        {
            printf("\nERROR : Can't open the file as already a file exists\n");
            return -1;
        }
        
        openFile(editor,second_word);
        flag = 1;
        
    }
    else if(strcmp(first_word,"close") == 0)
    {
        closeFile(editor);
        init(editor,undoStack,redoStack);
    }
    else
    {
        printf("\nError: Unknown command '%s'.\n",command);
    }
}



void closeFile(TextEditor *editor)
{
    Node* temp = editor->head;

    while(temp)
    {
        Node* backup = temp->next;
        free(temp);
        temp = backup;
    }

    
    printf("\nFile closed successfully✅\n");
}


void saveFile(TextEditor *editor, const char *filename)
{
    FILE*fptr = fopen(filename,"w");

    if(fptr == NULL)
    {
        perror("file\n");
        return;
    }

    Node* temp = editor->head;

    if(temp == NULL)
    {
        printf("Nothing to save\n");
        return ;
    }

    
    while(temp != NULL)
    {
        fprintf(fptr,"%s",temp->line);
        //to avoid new line after the last node
        if(temp->next != NULL)
        {
            fprintf(fptr,"\n");
        }
        temp = temp -> next;
    }

    fclose(fptr);
}


void openFile(TextEditor *editor, const char *filename)
{
    FILE* fptr = fopen(filename,"r");
    if(fptr == NULL)
    {
        printf("\nError: File '%s' not found.\n",filename);
        return;
    }

    char buff[1023];

    //first line is already created while initialisation
    fscanf(fptr,"%[^\n]\n",buff);
    strcpy(editor->head->line,buff);


    while( fscanf(fptr,"%[^\n]\n",buff) == 1)
    {
        Node* new = malloc(1023);
        new->line = strdup(buff);
        new->next = NULL;

        editor->tail->next = new;
        new->prev =  editor->tail;
        editor->tail = new;   
    }

    printf("\nFile opened successfully✅\n");
    //cursorline and pos remains same as we have given in the initialisation function
}

void moveCursorDown(TextEditor *editor)
{
    
    Node* temp = editor->cursor;

    if(temp->next == NULL)
    {
        Node *new = malloc(sizeof(Node));
        new->line = malloc(1023);
        new->next = NULL;
        new->prev = NULL;
        new->prev = temp;
        temp -> next = new;
        editor->tail = new;
        editor->cursor = new;
        editor->cursorPos = 0;
        total_line++;
    }
    else
    {
        /* if current line has greater size than next line , curosor will move to end of the second line*/
        int next_size = strlen(temp->next->line);
        editor->cursor = temp->next;
        if(editor->cursorPos > next_size)
        {
            editor->cursorPos = next_size;
        }
    }

    (editor->cursorLine)++;
}

void moveCursorUp(TextEditor *editor)
{
    Node* temp = editor->cursor;

    

    if( temp->prev != NULL) 
    {
        int prev_size = strlen(temp->prev->line);
        if(prev_size < editor->cursorPos)
        {
            editor->cursorPos = prev_size;
            
        }
        (editor->cursorLine)--;
        editor->cursor = temp->prev;
    }


}


void moveCursorLeft(TextEditor *editor)
{
    Node* temp = editor->cursor;

    /* if left reaches the begining and if a line is above ,control will go to the above line */
    if(editor->cursorPos != 0 )
    {
        (editor->cursorPos)--;
    }
    else if(editor->cursorPos == 0 && temp -> prev != NULL)
    {
        editor->cursor = temp->prev;
        editor->cursorPos = strlen(editor->cursor->line);
        (editor->cursorLine)--;
    }
    
}


void moveCursorRight(TextEditor *editor)
{
    int cur_size = strlen(editor->cursor->line);
    Node* temp = editor -> cursor;

    /* if line is over , goes to next line (if line present , else nothing happens)*/

    if(editor->cursorPos == cur_size )
    {
        if(temp->next != NULL)
        {
            editor->cursor = temp->next;
            editor->cursorPos = 0;
            (editor->cursorLine)++;
        }      
    }
    else
    {
        (editor->cursorPos)++;
    }
}



void insertText(TextEditor *editor, const char *text , DynamicArrayStack* Stack)
{

    // flag used for checcking the validity of open
    flag = 1;

    /* Pusing the action to the stack */
        Action action;
        action.operation = "insert";
        action.text = strdup(text);
        action.cursorLine = editor->cursorLine;
        action.cursorPos = editor->cursorPos;
        pushStack(Stack,action);


    //current line
    Node* temp = editor->cursor;
    char rest[1023];
    strcpy(rest,(temp->line)+(editor->cursorPos));
    strcpy((temp->line)+(editor->cursorPos),text);
    strcat(temp->line,rest);
    editor->cursorPos = editor->cursorPos + strlen(text);
}


void displayText(TextEditor *editor)
{
    printf("\n");
    int l=1;
    Node*temp = editor->head;
    while(temp!=NULL)
    {
        printf("Line %d : %s\n",l++,temp->line);
        temp = temp->next;
    }
    printf("\nCursor position: Line %d, Column %d",editor->cursorLine,editor->cursorPos);
    printf("\n");
}

void deleteCharacters(TextEditor *editor, int length , DynamicArrayStack* Stack)
{
    Node *cur_node = editor->cursor;

    //first we will store the text to be deleted into a temp string to later pass it to undo/redo function
    char temp[length+1];
    //the last length characters from the cur position
    strncpy(temp, cur_node->line + editor->cursorPos , length);
    temp[length] = '\0';

    if(length > strlen(temp))
    {
        printf("\nError: Cannot delete %d characters. Only %ld characters available.\n",length,strlen(temp));
        return;
    }

    if(temp[0] == '\0')
    {
        printf("\nNothing to delete!!!\n");
        return;
    }

    Action action;
    action.operation = "delete";
    action.text = strdup(temp);
    action.cursorLine = editor->cursorLine;
    action.cursorPos = editor->cursorPos;
    pushStack(Stack,action);


    char rest[50];
    strcpy(rest,cur_node->line + editor->cursorPos+length);

    strcpy(cur_node->line + editor->cursorPos , rest);

    printf("\nDeleted %d character(s) successfully✅\n",length);


}


void jumpToStartOfFile(TextEditor *editor)
{
    editor->cursor = editor->head;
    editor->cursorPos = 0;
    editor->cursorLine = 1;
}


void jumpToEndOfFile(TextEditor *editor)
{
    editor->cursor = editor->tail;
    editor->cursorPos = strlen(editor->cursor->line);
    editor->cursorLine = total_line;
}

void jumpToStartOfLine(TextEditor *editor)
{
    editor->cursorPos = 0;
}

void jumpToEndOfLine(TextEditor *editor)
{
    editor->cursorPos = strlen(editor->cursor->line);
}



