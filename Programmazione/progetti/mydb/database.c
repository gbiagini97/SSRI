#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "prompt.h"
#include "metacommand.h"
#include "table.h"

#include "init.h"

//*************INIT*******************
static char working_dir[1024];
static char database[256];
const char prefix[] = "gbdb-\0";
struct stat st = {0};
//*************INIT*******************

static void print_startup_prompt(){

printf("Welcome to Gabriele Biagini database\n");
printf("*******************************\n");
printf("*         _         _ _       *\n");
printf("*        | |       | | |      *\n");
printf("*    __ _| |__   __| | |__    *\n");
printf("*   / _` | '_ \\ / _` | '_ \\   *\n");
printf("*  | (_| | |_) | (_| | |_) |  *\n");
printf("*   \\__, |_.__/ \\__,_|_.__/   *\n");
printf("*    __/ |                    *\n");
printf("*   |___/                     *\n");
printf("*                             *\n");
printf("*******************************\n");
printf("Insert .help to see avaible metacommands\n");
printf("\n\n");
}

static void print_metacommands(){

    printf("Avaible metacommands: \n");
    size_t metaCommandsNumber = sizeof(metaCommands)/sizeof(metaCommands[0]);
    for(int i = 0; i<metaCommandsNumber; i++){
        printf("%s\n", metaCommands[i]);
    }
}

static void print_prompt(){ printf("gbdb > "); }

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void read_input_buffer(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  // Ignore newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

MetaCommandResult execute_metacommand(InputBuffer* inputBuffer){
    if(strcmp(inputBuffer->buffer, ".exit") == 0){
        close_input_buffer(inputBuffer);
        return META_COMMAND_EXIT;
    }
    if(strcmp(inputBuffer->buffer, ".help") == 0){
        print_metacommands();
        return META_COMMAND_SUCCESS;
    }
    if(strcmp(inputBuffer->buffer, ".workingdir") == 0){
        switch (define_working_dir())
        {
        case (DIRECTORY_SELECTION_SUCCESS):
            return META_COMMAND_SUCCESS;
        case (DIRECTORY_SELECTION_FAILURE):
            return META_COMMAND_FAILURE;
        }
    }
    if(strcmp(inputBuffer->buffer, ".db") == 0){
        switch (select_database())
        {
        case (DATABASE_SELECTED):
            return META_COMMAND_SUCCESS;
        case (DATABASE_CREATED):
            return META_COMMAND_SUCCESS;
        case (DATABASE_SELECTION_FAILURE):
            return META_COMMAND_FAILURE;
        }
    }
    if(strcmp(inputBuffer->buffer, ".table") == 0){
        switch (create_table())
        {
            case (TABLE_OPERATION_SUCCESS):
                return META_COMMAND_SUCCESS;
            case (TABLE_OPERATION_FAILURE):
                return META_COMMAND_FAILURE;
        }
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    } 
}

DirectorySelection define_working_dir(){
    
    printf("Insert your working directory (press enter to use current one): ");
    fgets(working_dir, 1024, stdin);
    if(working_dir[0]=='\n'){
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL && stat(cwd, &st) == 0) {
            strcpy(working_dir, cwd);
            strcat(working_dir, "/");
            printf("Current working directory selected: %s\n", working_dir);
            return(DIRECTORY_SELECTION_SUCCESS);
        } else {
            perror("Error while selecting current working directory.\n");
            return(DIRECTORY_SELECTION_FAILURE);
        }

    }
    else{
        strtok(working_dir, "\n");
        if(working_dir[strlen(working_dir)-1] != '/'){
            strcat(working_dir, "/");
        }
        if (stat(working_dir, &st) == 0) {
            printf("Working directory selected: %s\n", working_dir);
            return(DIRECTORY_SELECTION_SUCCESS);
        } else {
            printf("You may not have permissions to write here.\n");
            return(DIRECTORY_SELECTION_FAILURE);
        }
        
    }
}

DatabaseSelection select_database(){
    if(strlen(working_dir)<2){
        printf("Select a working directory first.\n");
        return DATABASE_SELECTION_FAILURE;
    } else {
        char database_name[250];
        char full_path[256];
        printf("Insert your database name: ");
        fgets(database_name, 250, stdin);
        strcpy(database, "");
        strcat(database, prefix);
        strcat(database, database_name);
        strtok(database, "\n");

        strcpy(full_path, working_dir);
        strcat(full_path, database);
        strcat(full_path, "/");

        if (stat(full_path, &st) == 0){
            printf("Database selected: %s\n", database);
            return DATABASE_SELECTED;
        }
        else if (stat(full_path, &st) == -1){
            mkdir(full_path, 0777);
            printf("Database created and selected: %s\n", database);
            return DATABASE_CREATED;
        }
        else {
            printf("Error while creating or selecting database: %s\n", database);
            strcpy(database, "");
            return DATABASE_SELECTION_FAILURE;
        }
    }
}

FILE* select_table(){
    if(strlen(working_dir)<2 || strlen(database)<2){
        printf("Select a working directory and a database first.\n");
        return NULL;
    } else {

        //insert file name
        char table_name[32];
        printf("Select table with name: ");
        fgets(table_name, 32, stdin);
        strtok(table_name, "\n");

        //build path for file location
        char full_path[1024];
        strcpy(full_path, working_dir);
        strcat(full_path, database);
        strcat(full_path, "/");
        strcat(full_path, table_name);
        strcat(full_path, ".csv");

        //check if table exists
        if (stat(full_path, &st) == 0) {
            FILE *fp;
            fp=fopen(full_path, "a+");

            //load first line, containing record structure
            char first_line[1024];
            fgets(first_line, 1024, fp);

            //keep head of record structure
            column *header = NULL;
            header = malloc(sizeof(column));

            // record structure builder
            column *cursor;
            cursor = header;

            //scan first line
            char c;
            char column[32];
            int column_index = 0;
            for(int i=0; i<strlen(first_line); i++){
                c=first_line[i];

                //build column string by dividing per separators and newlines
                if (c != ';' && c!='\n'){
                    column[column_index]=c;
                    column_index++;
                } else {
                    //check if column isn't empty
                    if(strlen(column)>0){       
                        column[column_index]='\0';

                        //add column to record structure
                        strcpy(cursor->column_name, column);
                        cursor->next = malloc(sizeof(column));
                        cursor = cursor->next;
                        
                        //reset column
                        column_index=0;
                        strcpy(column, "");
                    }
                }
            }

            //init the cursor again to print out columns
            cursor = header;
            int column_counter = 1;

            while(cursor->next!=NULL){
                printf("%d. %s\n",column_counter, cursor->column_name);
                ++column_counter;
                cursor=cursor->next;
            }

            //selection of the index
            char index[32];
            printf("Select index number [1-%d] ", column_counter);
            fgets(index, 32, stdin);
            strtok(index, "\n");
            int index_number = atol(index);
        
            
        } else {
            printf("Do you want to create it? [y/n]\n");
            char answer = getchar();
            if(answer=='y'){ create_table(); select_table();}
            else{return NULL;}
        }

    }
}

TableOperationResult create_table(){
    if(strlen(working_dir)<2 || strlen(database)<2){
        printf("Select a working directory and a database first.\n");
        return TABLE_OPERATION_FAILURE;
    } else {
        //insert file name
        char table_name[32];
        printf("Create table with name: ");
        fgets(table_name, 32, stdin);
        strtok(table_name, "\n");

        //build path for file location
        char full_path[1024];
        strcpy(full_path, working_dir);
        strcat(full_path, database);
        strcat(full_path, "/");
        strcat(full_path, table_name);
        strcat(full_path, ".csv");

        //check if table already exists
        if (stat(full_path, &st) == 0) {
            printf("A table with this name already exists.\n");
            return TABLE_OPERATION_FAILURE;
        } else {
            //create table
            FILE *fp;
            fp=fopen(full_path, "a+");

            //define data structure invocation
            column *table_initializer;
            table_initializer=malloc(sizeof(column));
            table_initializer=define_data_structure();

            //compose first line of file with data structure
            char line[1024];
            strcpy(line, "");

            while(table_initializer->next != NULL){
                strcat(line, table_initializer->column_name);
                strcat(line, ";");

                table_initializer=table_initializer->next;
            }
            line[strlen(line)] = '\n';

            //write first line of file with column names
            fprintf(fp, line);
            printf("Table %s created.\n", table_name);
            printf("Data structure of the table: %s\n\n", line);

            //close file
            fclose(fp);

            //deallocate memory
            free(table_initializer);

            return TABLE_OPERATION_SUCCESS;
        }

    }

}
column* define_data_structure(){

    //initialize head of the list
    column *head = NULL;
    head=malloc(sizeof(column));

    //initialize first field of the list with id
    strcpy(head->column_name, "id");
    column *current = head;
    
    //the first position of the cursor is the head, so it won't break
    while (current != NULL) {

        //allocate memory for the cursor
        current->next=malloc(sizeof(column));
        //switch to the next position of the list
        current = current->next;
    
        //acquire from stdin
        char column_name[32];
        printf("Insert next column - (Insert '.exit' to end)\n");
        fgets(column_name, 32, stdin);
        strtok(column_name, "\n");

        //check if keyword exit is being pressed
        if(strcmp(column_name, ".exit") == 0){
            printf("Columns defined.\n");
            //closes the list
            current=NULL;
            break;
        }
        //add new field to the list
        else
        {
            strcpy(current->column_name, column_name);
            printf("Column inserted: %s\n", current->column_name);
        }
    }
    return head;
}


int main() {
    print_startup_prompt();

    InputBuffer* input_buffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input_buffer(input_buffer);

      
        if(input_buffer->buffer[0] == '.') {
            switch (execute_metacommand(input_buffer))
            {
            case (META_COMMAND_EXIT):
                printf("au_revoir!\n");
                exit(EXIT_SUCCESS);
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized metacommand '%s'\n", input_buffer->buffer);
                continue;
            }
        } else {
            printf("BUFFER: %s\n", input_buffer->buffer);
        }
    }

    return 0;
}