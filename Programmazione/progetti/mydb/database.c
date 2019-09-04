#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


#include "prompt.h"
#include "metacommand.h"
#include "table.h"

#include "init.h"

//*************INIT*******************
static Mode mode = NORMAL;
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

const char* getModeName(Mode mode) 
{
   switch (mode) 
   {
      case NORMAL: return "NORMAL";
      case DB: return "DB";
      case TABLE: return "TABLE";
   }
}
const char* getModeInputPrompt(Mode mode) 
{
   switch (mode) 
   {
      case NORMAL: return "gbdb >";
      case DB: return "db-mode >";
      case TABLE: return "table-mode >";
   }
}
const char** getModeMetaCommands(Mode mode) 
{
   switch (mode) 
   {
      case NORMAL: return normalModeMetaCommands;
      case DB: return dbModeMetaCommands;
      case TABLE: return tableModeMetaCommands;
   }
}

const int getNumberOfCommands(Mode mode){
    switch (mode)
    {
    case NORMAL: return normalCommands;
      case DB: return dbCommands;
      case TABLE: return tableCommands;
    }
}


static void print_metacommands(){
    for(int i=0; i<getNumberOfCommands(mode); i++){
        printf("%s\n", getModeMetaCommands(mode)[i]);
    }
}

static void print_prompt(){ printf("%s ", getModeInputPrompt(mode)); }

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
    //*********************NORMAL MODE*********************
    if(strcmp(getModeName(mode), "NORMAL") == 0) {
        if(strcmp(inputBuffer->buffer, ".exit") == 0){
            close_input_buffer(inputBuffer);
            return META_COMMAND_EXIT;
        }
        if(strcmp(inputBuffer->buffer, ".help") == 0){
            printf("This is the Normal Mode.\n");
            printf("Here you can switch modes and exit the database.\n");
            print_metacommands();
            return META_COMMAND_SUCCESS;
        }
        if(strcmp(inputBuffer->buffer, ".db-mode") == 0){
            mode = DB;
            return META_COMMAND_SUCCESS;
        }
        if(strcmp(inputBuffer->buffer, ".table-mode") == 0){
            mode = TABLE;
            return META_COMMAND_SUCCESS;
        }
        else {
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
    }
    //*********************NORMAL MODE*********************


    //*********************DB MODE*********************
    else if(strcmp(getModeName(mode), "DB") == 0) {
        
        if(strcmp(inputBuffer->buffer, ".exit") == 0){
            mode = NORMAL;
            return META_COMMAND_SUCCESS;
        }
        if(strcmp(inputBuffer->buffer, ".help") == 0){
            printf("This is the Db Mode.\n");
            printf("First thing first define a working directory, then you can start playing around\n");
            printf("Here you can print, select and create databases.\n");
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
        if(strcmp(inputBuffer->buffer, ".dbs") == 0){
            print_databases();
            return META_COMMAND_SUCCESS;
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
        else {
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
    }
    //*********************DB MODE*********************


    //*********************TABLE MODE*********************
    else if(strcmp(getModeName(mode), "TABLE") == 0) {
        if(strcmp(inputBuffer->buffer, ".exit") == 0){
            mode = NORMAL;
            return META_COMMAND_SUCCESS;
        }
        if(strcmp(inputBuffer->buffer, ".help") == 0){
            printf("This is the Table Mode.\n");
            if(strlen(working_dir)<1 && strlen(database)<1){
                printf("Make sure you've selected a working directory and a database.\n");
            } else {
                printf("Working directory: %s\n", working_dir);
                printf("Database selected: %s\n", database);
            }
            printf("Here you can create tables, make indexes, queries and much more!\n");
            print_metacommands();
            return META_COMMAND_SUCCESS;
        }
        if(strcmp(inputBuffer->buffer, ".table") == 0){
            switch (create_table())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".select") == 0){
            select_table();
        } else {
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
    }
    //*********************TABLE MODE********************* 
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

static void print_databases(){
    if(strlen(working_dir)<2){
        printf("Select a working directory first.\n");
    } else {
        char command[256];
        strcpy(command, "cd ");
        strcat(command, working_dir);
        strcat(command, "/");
        strcat(command, " && ls | grep gbdb* | cut -c6-");
        printf("Databases in working directory %s :\n", working_dir);
        system(command);
    }
}

DatabaseSelection select_database(){
    if(strlen(working_dir)<2){
        printf("Select a working directory first.\n");
        return DATABASE_SELECTION_FAILURE;
    } else {
        char database_name[250];
        char full_path[256];
        printf("Insert database name: ");
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

void select_table(){
    if(strlen(working_dir)<2 || strlen(database)<2){
        printf("Select a working directory and a database first.\n");
    } else {

        //insert file name
        char table_name[32];
        printf("Select from table with name: ");
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
            fp=fopen(full_path, "r+");

            // *************** WHERE *******************
  
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
            char field[32];
            int column_index = 0;
            for(int i=0; i<strlen(first_line); i++){
                c=first_line[i];

                //build column string by dividing per separators and newlines
                if (c != ',' && c!='\n'){
                    field[column_index]=c;
                    column_index++;
                } else {
                    //check if column isn't empty
                    if(strlen(field)>0){       
                        field[column_index]='\0';

                        //add column to record structure
                        strcpy(cursor->field, field);
                        cursor->next = malloc(sizeof(column));
                        cursor = cursor->next;
                        
                        //reset column
                        column_index=0;
                        strcpy(field, "");
                    }
                }
            }

            //init the cursor again to print out columns
            cursor = header;
            int column_counter = 1;

            while(cursor->next!=NULL){
                printf("%d. %s\n",column_counter, cursor->field);
                ++column_counter;
                cursor=cursor->next;
            }

            //selection of the index
            char index[32];
            printf("Select index number [1-%d] ", column_counter-1);
            fgets(index, 32, stdin);
            strtok(index, "\n");
            int index_number = atoi(index);

            //create linked list of the table
            int table_size;
            char record_line[1024];
            record *records_head = NULL;
            records_head = malloc(sizeof(record));

            record *record_cursor;
            record_cursor = records_head;

            while(fgets(record_line, 1024, fp)){
                strcpy(record_cursor->line, record_line);
                record_cursor->next = malloc(sizeof(record));
                record_cursor = record_cursor->next;
                strcpy(record_line, "");
                table_size++;
            }          
            
            //init the cursors back at head
            cursor = header;
            record_cursor=records_head;

            //now from records_head we have a sorted list by index
            int leaves_number = sort_records(records_head, index_number, table_size); 

            int leaves_counter = 0;
            bnode *leaves[leaves_number];

            //build leaves
            record_cursor = records_head;
            while(record_cursor->next != NULL && leaves_counter<leaves_number){

                leaves[leaves_counter] = malloc(sizeof(bnode));
                strcpy(leaves[leaves_counter]->value, record_cursor->line);
                leaves[leaves_counter]->left=NULL;
                leaves[leaves_counter]->right=NULL;
                
                printf("Leaf %d:\n", leaves_counter);
                printf("    Value: %s\n", leaves[leaves_counter]->value);

                leaves_counter++;
                record_cursor=record_cursor->next;
            }
            
            //build tree
            bnode *tree_root;
            tree_root = malloc(sizeof(bnode));
            tree_root=build_tree(leaves, index_number, leaves_number);

            //print tree
            traversalPreorder(tree_root);
                
            } else {
                printf("Do you want to create it? [y/n]\n");
                char answer = getchar();
                if(answer=='y'){ create_table(); select_table();}
            }

        }
}

void traversalPreorder(bnode *node){
    if(node==NULL){ return; }

    printf("%s\n", node->value);
    traversalPreorder(node->left);
    traversalPreorder(node->right);
}

bnode* build_tree(bnode *leaves[], int index_number, int nodes_number){

    bnode *head;
    head = malloc(sizeof(bnode));
    int leaf_indicator = 0;

    if(nodes_number>2 && nodes_number%2==0){
        bnode *new_nodes[(nodes_number/2)-1]; 

        for(int i=0; i<=(nodes_number/2)-1; i++){
            new_nodes[i]=malloc(sizeof(bnode));

            char val1[32];
            char val2[32];
            strcpy(val1, getFieldFromLine(leaves[leaf_indicator]->value, index_number));
            strcpy(val2, getFieldFromLine(leaves[leaf_indicator+1]->value, index_number));
            strcpy(new_nodes[i]->value, findMedianValue(val1, val2));

            new_nodes[i]->left=leaves[leaf_indicator];
            new_nodes[i]->right=leaves[leaf_indicator+1];

            leaf_indicator++;
            leaf_indicator++;
        }
        head = build_tree(new_nodes, -1, (nodes_number/2));

    } 
    else if(nodes_number>2 && nodes_number%2==1) {
        bnode *new_nodes[(nodes_number/2)];
        
        for(int i=0; i<=(nodes_number/2); i++) {
            new_nodes[i]=malloc(sizeof(bnode));

            if(i!=(nodes_number/2)){
                char val1[32];
                char val2[32];
                strcpy(val1, getFieldFromLine(leaves[leaf_indicator]->value, index_number));
                strcpy(val2, getFieldFromLine(leaves[leaf_indicator+1]->value, index_number));
                strcpy(new_nodes[i]->value, findMedianValue(val1, val2));

                new_nodes[i]->left=leaves[leaf_indicator];
                new_nodes[i]->right=leaves[leaf_indicator+1];

                leaf_indicator++;
                leaf_indicator++;

            } else {
                strcpy(new_nodes[i]->value, getFieldFromLine(leaves[leaf_indicator]->value, index_number));
                
                new_nodes[i]->left=leaves[leaf_indicator];
                new_nodes[i]->right=NULL;

                leaf_indicator++;
            }
            
        }
        head = build_tree(new_nodes, -1, (nodes_number/2)+1);

    }
    else if(nodes_number==2)
    {
        char val1[32];
        char val2[32];
        strcpy(val1, getFieldFromLine(leaves[leaf_indicator]->value, index_number));
        strcpy(val2, getFieldFromLine(leaves[leaf_indicator+1]->value, index_number));

        strcpy(head->value, findMedianValue(val1, val2));

        head->left=leaves[leaf_indicator];
        head->right=leaves[leaf_indicator+1];

        return head;
    }
    
}

const char* findMedianValue(const char* val1, const char* val2){
    char field[32];
    char (*p)[32];
    p=&field;

    //printf("Finding median value between: %s and %s\n", val1, val2);

    field[0] = '\0';
    for(int i = 0; i<strlen(val1)-1; i++){
        //printf("Letters found: %c, %c\n", val1[i], val2[i]);
        if(val1[i]==val2[i]){
            field[i]=val1[i];
        } else {
            field[i] = '\0';
            break;
        }
    }


    if(field[0] == '\0') {
        field[0] = (val1[0] + val2[0])/2;
        field[1] = '\0';
    }

        return *p;
}

const char* findMedian(bplusnode* leaf1, bplusnode* leaf2){

    bnode *node;
    node = malloc(sizeof(node));

    char field[32];
    char (*p)[32];
    for(int i = 0; i<strlen(leaf1->value)-1; i++){
            
        if(leaf1->value[i] == leaf2->value[i]){
            field[i]=leaf1->value[i];
        } else {
            field[i] = '\0';
            break;
        }
    }
    if(strlen(field)<1){
        field[0] = (leaf1->value[0] + leaf2->value[0])/2;
        field[1] = '\0';
    }

    p=&field;
    return *p;



}

bplusnode* build_leaf(record* start, int index_number){
    bplusnode *leaf;
    leaf=malloc(sizeof(leaf));
    leaf->n_records=0;
    leaf->start=start;
    strcpy(leaf->value, getFieldFromLine(start->line, index_number));
    
    record *rcursor;
    rcursor=start;
    while(rcursor->next!=NULL){
        if(strcmp(leaf->value, getFieldFromLine(rcursor->line, index_number)) == 0) {
            leaf->n_records++;
            rcursor=rcursor->next;
        } else {
            break;
        }
    }
    return leaf;
}

int sort_records(record *head, int index_number, int n_records){
    char *arr[n_records];
    int arr_counter = 0;

    record *record_cursor1;
    record_cursor1=head;
    
    record_cursor1 = head;
    while(record_cursor1->next!=NULL) {
        arr[arr_counter] = strdup(record_cursor1->line);
        record_cursor1 = record_cursor1->next;
        arr_counter++;
    }

    char field1[32];
    char field2[32];
    char temp[32];
    for(int i = 0; i<arr_counter-1; ++i){
        for(int k = i+1; k<arr_counter; ++k) {
            strcpy(field1, getFieldFromLine(arr[i], index_number));
            strcpy(field2, getFieldFromLine(arr[k], index_number));
            if(strcmp(field1, field2)>0){
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[k]);
                strcpy(arr[k], temp);
            }
        }
    }

    //copy back and find uniques
    record_cursor1=head;
    int uniques=0;
    for(int i = 0; i<arr_counter; i++){
        if(i+1<arr_counter){
            if(strcmp(getFieldFromLine(arr[i], index_number), getFieldFromLine(arr[i+1], index_number)) == 0) {
                uniques++;
            }
        }
        strcpy(record_cursor1->line, arr[i]);

        record_cursor1=record_cursor1->next;
    }

    free(record_cursor1);
    //return uniques;

    return arr_counter;
}

const char* getFieldFromLine(char *line, int index_number){
    int index_counter = 0;
    char c;
    char field[32];
    char (*p)[32] = malloc(sizeof(field));
    int field_index = 0;

    if(index_number != -1) {
        for(int i=0; i<strlen(line); i++){
            c=line[i];

            //build field string by dividing per separators and newlines
            if (c != ',' && c!='\n'){
                field[field_index]=c;
                field_index++;
            } else {      
                field[field_index]='\0';
                index_counter++;

                if(index_counter==index_number){
                    p=&field;
                    break;
                } else {
                    field_index=0;
                    strcpy(field, "");
                }
            }
        }
    return *p;
    } else {
        return line;
    }
}

void sort(column *head, int table_size){
    char *array[table_size];
    int array_counter=0;

    column *sort_cursor;
    sort_cursor=head;
    while(sort_cursor->next!=NULL){
        array[array_counter] = strdup(sort_cursor->field);
        sort_cursor=sort_cursor->next;
        array_counter++;
    }
    
    qsort(array, array_counter, sizeof(char*), stringCompare);
    sort_cursor=head;

    for(int i = 0; i<array_counter; i++){
        strcpy(sort_cursor->field, array[i]);
        sort_cursor=sort_cursor->next;
    }

    free(sort_cursor);
}

static int stringCompare(const void* str1, const void* str2){
    return strcmp(*(const char**)str1, *(const char**)str2); 
}

TableOperationResult create_table() {
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
                strcat(line, table_initializer->field);
                strcat(line, ",");

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
    strcpy(head->field, "id");
    column *current = head;
    
    //the first position of the cursor is the head, so it won't break
    while (current != NULL) {

        //allocate memory for the cursor
        current->next=malloc(sizeof(column));
        //switch to the next position of the list
        current = current->next;
    
        //acquire from stdin
        char field[32];
        printf("Insert next column - (Insert '.exit' to end)\n");
        fgets(field, 32, stdin);
        strtok(field, "\n");

        //check if keyword exit is being pressed
        if(strcmp(field, ".exit") == 0){
            printf("Columns defined.\n");
            //closes the list
            current=NULL;
            break;
        }
        //add new field to the list
        else
        {
            strcpy(current->field, field);
            printf("Column inserted: %s\n", current->field);
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
                printf("Au revoir!\n");
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