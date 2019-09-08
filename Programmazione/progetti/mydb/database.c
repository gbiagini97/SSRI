#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <time.h> 

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
const char prefix[] = "gbdb-\0";
static char working_dir[1024];
static char database[256];
static char table[32];
static bnode *tree = NULL;
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

const char* get_mode_name(Mode mode) 
{
   switch (mode) 
   {
      case NORMAL: return "NORMAL";
      case DB: return "DB";
      case TABLE: return "TABLE";
      default: return "NORMAL";
   }
}
const char* get_mode_input_prompt(Mode mode) 
{
   switch (mode) 
   {
        case NORMAL: return "gbdb >";
        case DB: {
            if(strlen(database)>2){
                char db_prompt[36];
                char (*p)[36] = NULL;
                strcpy(db_prompt, "db-");
                strcat(db_prompt ,database);
                strcat(db_prompt, " >");
                p=&db_prompt;
                return *p;
            } else {
            return "db-mode >";
            }
        }
        case TABLE: {
            if(strlen(table)>2){
                char table_prompt[36];
                char (*p)[36] = NULL;
                strcpy(table_prompt, "table-");
                strcat(table_prompt, table);
                strcat(table_prompt, " >");
                p=&table_prompt;
                return *p;
            } else {
                return "table-mode >";
            }
        }
        default: return "gbdb >";
   }
}
const char** get_mode_meta_commands(Mode mode) 
{
   switch (mode) 
   {
        case NORMAL: return normalModeMetaCommands;
        case DB: return dbModeMetaCommands;
        case TABLE: return tableModeMetaCommands;
        default: return normalModeMetaCommands;
   }
}

int get_number_of_commands(Mode mode){
    switch (mode)
    {
        case NORMAL: return normalCommands;
        case DB: return dbCommands;
        case TABLE: return tableCommands;
        default: return normalCommands;
    }
}


static void print_metacommands(){
    for(int i=0; i<get_number_of_commands(mode); i++){
        printf("%s\n", get_mode_meta_commands(mode)[i]);
    }
}

static void print_prompt(){ printf("%s ", get_mode_input_prompt(mode)); }

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
    printf("Error reading input.\n");
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
    if(strcmp(get_mode_name(mode), "NORMAL") == 0) {
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
    else if(strcmp(get_mode_name(mode), "DB") == 0) {
        
        if(strcmp(inputBuffer->buffer, ".back") == 0){
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
        if(strcmp(inputBuffer->buffer, ".select-workingdir") == 0){
            switch (define_working_dir())
            {
            case (DIRECTORY_SELECTION_SUCCESS):
                return META_COMMAND_SUCCESS;
            case (DIRECTORY_SELECTION_FAILURE):
                return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".list") == 0){
            print_databases();
            return META_COMMAND_SUCCESS;
        }
        if(strcmp(inputBuffer->buffer, ".select-db") == 0){
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
    else if(strcmp(get_mode_name(mode), "TABLE") == 0) {
        if(strcmp(inputBuffer->buffer, ".back") == 0){
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
        if(strcmp(inputBuffer->buffer, ".list") == 0){
            switch (print_tables())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".create") == 0){
            switch (create_table())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".select") == 0){
            switch (select_table())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".create-index") == 0){
            switch(create_index())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".print-index") == 0){
            switch(print_index())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".find") == 0){
            switch (find())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        if(strcmp(inputBuffer->buffer, ".insert") == 0){
            switch(insert())
            {
                case (TABLE_OPERATION_SUCCESS):
                    return META_COMMAND_SUCCESS;
                case (TABLE_OPERATION_FAILURE):
                    return META_COMMAND_FAILURE;
            }
        }
        else {
            return META_COMMAND_UNRECOGNIZED_COMMAND;
        }
    }
    //*********************TABLE MODE********************* 
    return META_COMMAND_FAILURE;
}

TableOperationResult find(){
    if(strlen(table)<2 || strlen(database)<2 || strlen(working_dir)<2){
        printf("Make sure you've selected a table within your database.\n");
        return TABLE_OPERATION_FAILURE;
    } else {
        
        FILE *fp = NULL;
        fp = open_table("r+");
        record *table = NULL;  
        int n_columns = 0;
        double time_taken_to_execute = 0;
        clock_t time;

        if(fp==NULL){
            fclose(fp);
            return TABLE_OPERATION_FAILURE;
        } else {
            
            n_columns = print_table_structure(fp);    

            //apply WHERE condition?
            char index_number_input[10];
            index_number_input[0]='\0';
            printf("Press any button to print the entire table, or insert a column number to apply a WHERE condition [1-%d]: ", n_columns-1);
            fgets(index_number_input, 10, stdin);
            strtok(index_number_input, "\n");
            int index_number = atoi(index_number_input);
            //create linked list of the table
            table = build_list_from_table(fp);                     

            //find all
            if(index_number == 0){
                printf("Query results:\n");
                time = clock();
                while(table->next!=NULL){ printf("%s\n", table->line); table=table->next;}
                time=clock()-time;
                time_taken_to_execute = (double)time/CLOCKS_PER_SEC;
                printf("Query executed in %f seconds.\n", time_taken_to_execute);
                fclose(fp);
                return TABLE_OPERATION_SUCCESS;
            }
            
            //insert WHERE condition
            else {
                char where_condition[32];
                where_condition[0]='\0';
                printf("Insert the value you are looking for: ");
                fgets(where_condition, 32, stdin);
                strtok(where_condition, "\n");

                if(index_number==1){
                    if(atoi(where_condition) == 0) {
                        printf("Have you ever found a DMBS that counts records starting by 0?\n");
                        fclose(fp);
                        return TABLE_OPERATION_FAILURE;
                    } else if(atoi(where_condition)>count_records(table)){
                        printf("There are %d records in this table.\n", count_records(table));
                        fclose(fp);
                        return TABLE_OPERATION_FAILURE;
                    } else {
                        printf("Query results:\n");
                        time = clock();
                        for (int i = 1; i!=atoi(where_condition); i++){
                            table=table->next;
                        }
                        printf("%s\n", table->line);
                        time=clock()-time;
                        time_taken_to_execute = (double)time/CLOCKS_PER_SEC;
                        printf("Query executed in %f seconds.\n", time_taken_to_execute);
                        fclose(fp);
                        return TABLE_OPERATION_SUCCESS;
                    }
                }
                else if( index_number>1 && index_number<n_columns ) {
                    //index already in place
                    if(tree!=NULL){
                        printf("Query results:\n");
                        time = clock();
                        bnode* tree_cursor = NULL;
                        tree_cursor=malloc(sizeof(bnode));
                        tree_cursor=tree;
                        traversal_preorder_search(tree_cursor, where_condition, index_number);
                        time=clock()-time;
                        time_taken_to_execute = (double)time/CLOCKS_PER_SEC;
                        printf("Query executed in %f seconds.\n", time_taken_to_execute);
                        fclose(fp);
                        return TABLE_OPERATION_SUCCESS;
                    } 
                    //create new index on queried field
                    else {
                        build_tree_from_list(table, index_number);

                        printf("Query results:\n");
                        time = clock();
                        bnode* tree_cursor = NULL;
                        tree_cursor=malloc(sizeof(bnode));
                        tree_cursor=tree;
                        traversal_preorder_search(tree_cursor, where_condition, index_number);
                        time=clock()-time;
                        time_taken_to_execute = (double)time/CLOCKS_PER_SEC;
                        printf("Query executed in %f seconds.\n", time_taken_to_execute);
                        fclose(fp);
                        return TABLE_OPERATION_SUCCESS;
                    }
                }
            }
        }
    }
    return TABLE_OPERATION_FAILURE;
}

int print_table_structure(FILE *fp){
    //load first line, containing record structure
    char first_line[1024];
    first_line[0]='\0';
    fgets(first_line, 1024, fp);
    int column_counter = 1;

    char c = '\0';
    char field[32];
    field[0]='\0';
    int column_index = 0;
    for(int i=0; i<(int)strlen(first_line); i++){
        c=first_line[i];

        if( (c >='a' && c<='z') || (c>='0' && c<='9') || (c=='@') || (c=='_') || (c=='.')){
            field[column_index]=c;
            column_index++;
        } 
        else if(c == ','){
            field[column_index]='\0';
            printf("%d. %s\n",column_counter, field);
            column_index=0;
            strcpy(field, "");
            column_counter++;
        }
        else {
            column_index++;
        }
    }
    return column_counter;
    
}

int count_records(record *head){
    int table_size = 0;
    while(head->next!=NULL){
        table_size++;
        head=head->next;
    }
    return table_size;
}

record* build_list_from_table(FILE *fp){

    char record_line[1024];
    record_line[0]='\0';
    record *records_head = NULL;
    records_head = malloc(sizeof(record));

    record *record_cursor = NULL;
    record_cursor = malloc(sizeof(record));
    record_cursor = records_head;

    while(fgets(record_line, 1024, fp)){
        if(record_line[0]!='\n'){
            strcpy(record_cursor->line, record_line);
            strtok(record_cursor->line, "\n");
            record_cursor->next = malloc(sizeof(record));
            record_cursor = record_cursor->next;
            strcpy(record_line, "");
        }
    }
    free(record_cursor);
    return records_head;
}

FILE* open_table(char open_mode[3]){
    char full_path[1024];
    full_path[0]='\0';
    strcpy(full_path, working_dir);
    strcat(full_path, database);
    strcat(full_path, "/");
    strcat(full_path, table);
    strcat(full_path, ".csv");

    //check if table exists
    if (stat(full_path, &st) == 0) {
        FILE *file = NULL;
        file=fopen(full_path, open_mode);
        return file;
    } else {
        return NULL;
    }
}

void build_leaves(bnode *leaves[], record *sorted_list, int leaves_number){
    int leaves_counter = 0;

    //build leaves
    while(sorted_list->next != NULL && leaves_counter<leaves_number){

        leaves[leaves_counter] = malloc(sizeof(bnode));
        strcpy(leaves[leaves_counter]->value, sorted_list->line);
        leaves[leaves_counter]->left=NULL;
        leaves[leaves_counter]->right=NULL;
        
        leaves_counter++;
        sorted_list=sorted_list->next;
    }
}

TableOperationResult insert(){
    if(strlen(table)<2 || strlen(database)<2 || strlen(working_dir)<2){
        printf("Make sure you've selected a table within your database");
        return TABLE_OPERATION_FAILURE;
    } else {
        FILE *fp=NULL;
        fp = open_table("a+");

        if(fp==NULL){
            fclose(fp);
            printf("Table not found\n");
            return TABLE_OPERATION_FAILURE;
        } else {

            column *table_structure = NULL;
            table_structure = get_table_structure(fp);

            char record[1024];
            record[0]='\0';
            sprintf(record, "%d,", generate_id());
            while (table_structure->next!=NULL) {
                if(strcmp(table_structure->field, "id")!=0){
                    char field[32];
                    field[0]='\0';
                    printf("Insert value for column %s: ", table_structure->field);
                    fgets(field, 32, stdin);
                    while(strlen(field)<2){
                        if(strlen(field)<2){
                            printf("Please insert a valid value for column %s: ", table_structure->field);
                            fgets(field, 32, stdin);
                        }
                    }
                    strtok(field, "\n");
                    strcat(record, field);
                    strcat(record, ",");
                }
                table_structure=table_structure->next;
            }

            record[strlen(record)] = '\0';
            fprintf(fp, "\n");
            fprintf(fp, record);
            printf("Record inserted %s\n", record);
        }
        fclose(fp);
        return TABLE_OPERATION_SUCCESS;
    }
}

column* get_table_structure(FILE *file){
    //read first line
    char line[1024];
    line[0]='\0';
    fgets(line, 1024, file);

    column *structure = NULL;
    structure=malloc(sizeof(column));

    column *structure_cursor = NULL;
    structure_cursor=malloc(sizeof(column));
    structure_cursor=structure;

    //scan line
    char c = '\0';
    char column[32];
    column[0]='\0';
    int column_index = 0;
    for(int i=0; i<(int)strlen(line); i++){
        c=line[i];

        //build column string by dividing per separators and newlines
        if (c != ',' && c!='\n'){
            column[column_index]=c;
            column_index++;
        } else {
            //check if column isn't empty
            if(strlen(column)>0){       
                column[column_index]='\0';

                //add column to data structure
                strcpy(structure_cursor->field, column);
                structure_cursor->next = malloc(sizeof(column));
                structure_cursor = structure_cursor->next;
                
                //reset column
                column_index=0;
                strcpy(column, "");
            }
        }
    }
    return structure;
}

int generate_id(){
    FILE *fp = NULL;
    fp=open_table("r+");
    char line[1024];
    line[0]='\0';
    char last_id[32];
    last_id[0]='\0';

    while(fgets(line, 1024, fp)){
        strcpy(last_id, get_field_from_line(line, 1));
    }

    fclose(fp);
    return atoi(last_id)+1;
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
        strcat(command, " && ls | grep gbdb | cut -c6-");
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

TableOperationResult print_tables(){
    if(strlen(working_dir)<2 && strlen(database)<2){
        printf("Select a working directory and a database first.\n");
        return TABLE_OPERATION_FAILURE;
    } else {
        char command[256];
        strcpy(command, "cd ");
        strcat(command, working_dir);
        strcat(command, database);
        strcat(command, "/");
        strcat(command, " && ls | rev | cut -c5- | rev");
        printf("Tables in database %s :\n", database);
        system(command);
        return TABLE_OPERATION_SUCCESS;
    }

}

TableOperationResult create_index(){
    if(strlen(working_dir)<2 || strlen(database)<2 || strlen(table)<2){
        printf("Select a working directory,a database and a table first.\n");
        return TABLE_OPERATION_FAILURE;
    } else {

        FILE *fp;
        fp = open_table("r+");
        int n_columns;
        record *table;

        if(fp==NULL){
            fclose(fp);
            return TABLE_OPERATION_FAILURE;
        } else {
            n_columns = print_table_structure(fp);

            //selection of the index
            char index[32];
            printf("Select index number [1-%d] ", n_columns-1);
            fgets(index, 32, stdin);
            strtok(index, "\n");
            int index_number = atoi(index);
            if(index_number<1 || index_number>n_columns){
                printf("Creating an index on the column %d was impossible, selection has been changed to 1.\n", index_number);
                index_number = 1;
            }

            //create linked list of the table
            table = build_list_from_table(fp);                     
            build_tree_from_list(table, index_number);
        }
        if(tree != NULL){
            printf("Index successfully created.\n");
            fclose(fp);
            return TABLE_OPERATION_SUCCESS;
        } else {
            free(tree);
            fclose(fp);
            printf("Couldn't create index.\n");
            return TABLE_OPERATION_FAILURE;
        }
    }
    return TABLE_OPERATION_FAILURE;
}

void build_tree_from_list(record *list, int index_number){
    int leaves_number = sort_records(list, index_number, count_records(list));

    if(tree!=NULL){ 
        free_tree(tree);
    }

    bnode *leaves[leaves_number];
    *leaves=calloc(leaves_number, sizeof(bnode));
    build_leaves(leaves, list, leaves_number);

    tree = malloc(sizeof(bnode));
    tree = build_tree(leaves, index_number, leaves_number);
}

void free_tree(bnode *node){
    if(node==NULL){ return; }

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

TableOperationResult print_index(){
    if(tree==NULL){
        printf("Create an index first.\n");
        return TABLE_OPERATION_FAILURE;
    } else {

        bnode* tree_cursor;
        tree_cursor=malloc(sizeof(bnode));
        tree_cursor=tree;
        print_2d_traversal_preorder(tree_cursor, 0);
        //print_traversal_preorder(tree_cursor);
        return TABLE_OPERATION_SUCCESS;
    }
}

void print_traversal_preorder(bnode *node){
    if(node==NULL){ return; }

    strlen(node->value)>1 ? printf("%s\n", node->value) : printf("%c\n", node->value[0]);
    print_traversal_preorder(node->left);
    print_traversal_preorder(node->right);
}

void print_2d_traversal_preorder(bnode *node, int space) { 
    if (node == NULL) {return;} 

    space += 10; 
  
    print_2d_traversal_preorder(node->right, space); 
  
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    strlen(node->value)>1 ? printf("%s\n", node->value) : printf("%c\n", node->value[0]);
  
    print_2d_traversal_preorder(node->left, space); 
} 

void traversal_preorder_search(bnode *node, char key[32], int index_number){
    if(node==NULL){ return; }
    if(strcmp(key, get_field_from_line(node->value, index_number)) == 0 && node->left==NULL && node->right==NULL){
        printf("%s\n", node->value);
    } 
    traversal_preorder_search(node->left, key, index_number);
    traversal_preorder_search(node->right, key, index_number);
    

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
            strcpy(val1, get_field_from_line(leaves[leaf_indicator]->value, index_number));
            strcpy(val2, get_field_from_line(leaves[leaf_indicator+1]->value, index_number));
            strcpy(new_nodes[i]->value, find_median_value(val1, val2));

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
                strcpy(val1, get_field_from_line(leaves[leaf_indicator]->value, index_number));
                strcpy(val2, get_field_from_line(leaves[leaf_indicator+1]->value, index_number));
                strcpy(new_nodes[i]->value, find_median_value(val1, val2));

                new_nodes[i]->left=leaves[leaf_indicator];
                new_nodes[i]->right=leaves[leaf_indicator+1];

                leaf_indicator++;
                leaf_indicator++;

            } else {
                strcpy(new_nodes[i]->value, get_field_from_line(leaves[leaf_indicator]->value, index_number));
                
                new_nodes[i]->right=leaves[leaf_indicator];
                new_nodes[i]->left=NULL;

                leaf_indicator++;
            }
            
        }
        head = build_tree(new_nodes, -1, (nodes_number/2)+1);

    }
    else if(nodes_number==2) {
        char val1[32];
        char val2[32];
        strcpy(val1, get_field_from_line(leaves[leaf_indicator]->value, index_number));
        strcpy(val2, get_field_from_line(leaves[leaf_indicator+1]->value, index_number));

        head = malloc(sizeof(bnode));

        strcpy(head->value, find_median_value(val1, val2));

        head->left=leaves[leaf_indicator];
        head->right=leaves[leaf_indicator+1];

        //if(strlen(head->value)>=1  || (int)atoi(head->value) != 0){
            return head;
        //} else {
        //    printf("An error occurred while creating the index.\n");
        //    return NULL;
        //}
    }
}

const char* find_median_value(const char* val1, const char* val2){
    char field[32];
    field[0]='\0';
    char (*p)[32] = NULL;
    
    if(atoi(val1)!=0 && atoi(val2)!=0){
        sprintf(field, "%d", (atoi(val1)+atoi(val2))/2);
        p=&field;
        return *p;
    } else {

        int length = 0;
        if(strlen(val1)<strlen(val2)) {length=(int)strlen(val1);} else { length=(int)strlen(val2); }
        for(int i = 0; i<length; i++){
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
        p=&field;
        return *p;
    }
}

int sort_records(record *head, int index_number, int n_records){

    char arr[n_records][1024];
    int arr_counter = 0;
    record *record_cursor1 = NULL;
    record_cursor1=malloc(sizeof(record));
    record_cursor1=head;
    
    while(record_cursor1->next!=NULL) {
        strcpy(arr[arr_counter], record_cursor1->line);
        record_cursor1 = record_cursor1->next;
        arr_counter++;
    }

    char field1[1024];
    char field2[1024];
    char temp[1024];
    for(int i = 0; i<arr_counter-1; ++i){
        for(int k = i+1; k<arr_counter; ++k) {
            strcpy(field1, get_field_from_line(arr[i], index_number));
            strcpy(field2, get_field_from_line(arr[k], index_number));
            if(strcmp(field1, field2)>0){
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[k]);
                strcpy(arr[k], temp);
                temp[0]='\0';
                field1[0]='\0';
                field2[0]='\0';
            }
        }
    }

    record_cursor1=head;
    for(int i = 0; i<arr_counter; i++){
        strcpy(record_cursor1->line, arr[i]);
        record_cursor1=record_cursor1->next;
    }

    free(record_cursor1);

    return arr_counter;

}

const char* get_field_from_line(char *line, int index_number){

    if(line==NULL) {
        return "\0";
    }
    else if(line != NULL && index_number==-1){
        strcat(line, "\0");
        return line;
    }
    else if(line != NULL && index_number==1){
        char id[32];
        for(int i=0; i<(int)strlen(line); i++){
            if(line[i]>='0' && line[i]<='9'){
                id[i]=line[i];
            } else{
                break;
            }
        }
        char (*p)[32] = NULL;
        p=malloc(sizeof(id));
        p=&id;
        return *p;
    }
    else{
        char c = '\0';
        char field[32];
        field[0]='\0';
        char (*p)[32] = NULL;
        p=malloc(sizeof(field));
        
        int field_index=0;
        int index_counter=0;

        for(int i = 0; i<(int)strlen(line); i++){
            c=line[i];
           
            if((c >='a' && c<='z') || (c>='0' && c<='9') || (c=='@') || (c=='_') || (c=='.')){
                field[field_index]=c;
                field_index++;
            }
            else if(c == ','){
                field[field_index]='\0';
                index_counter++;
                if(index_counter==index_number){
                    p=&field;
                    break;
                }
                else{
                    field[0]='\0';
                    field_index=0;
                }
            }
            
        }
        if(index_counter==0){
            return get_field_from_line(line, -1);
        } else {
            return *p;
        }

    }








    //if(line == NULL){
    //    return "\0";
    //} else {
//
    //    int index_counter = 0;
    //    char c;
    //    char field[1024];
    //    char (*p)[1024] = malloc(sizeof(field));
    //    int field_index = 0;
//
    //    if(index_number != -1) {
    //        for(int i=0; i<(int)strlen(line); i++){
    //            c=line[i];
//
    //            //build field string by dividing per separators and newlines
    //            if (c != ',' && c!='\n'){
    //                field[field_index]=c;
    //                field_index++;
    //            } else {      
    //                field[field_index]='\0';
    //                index_counter++;
//
    //                if(index_counter==index_number){
    //                    p=&field;
    //                    break;
    //                } else {
    //                    field_index=0;
    //                    strcpy(field, "");
    //                }
    //            }
    //        }
    //        if(strlen(field)<2){ return get_field_from_line(line, -1);} 
    //        else {return *p;}
    //    } else {
    //        strcat(line, "\0");
    //        return line;
    //    }
    //}
}

TableOperationResult select_table(){

    if(strlen(working_dir)<2 || strlen(database)<2){
        printf("Select a working directory and a database first.\n");
        return TABLE_OPERATION_FAILURE;
    } else {
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

        //check if table already exists
        if (stat(full_path, &st) == 0) {
            strcpy(table, table_name);
            printf("Table %s selected.\n", table_name);
            return TABLE_OPERATION_SUCCESS;
        } else {
            printf("Table %s doesn't exist.\n", table_name);
            return TABLE_OPERATION_FAILURE;
        }
    }
    return TABLE_OPERATION_FAILURE;
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
            line[0]='\0';

            while(table_initializer->next != NULL){
                strcat(line, table_initializer->field);
                strcat(line, ",");

                table_initializer=table_initializer->next;
            }
            //line[strlen(line)] = '\n';

            //write first line of file with column names
            fprintf(fp, line);
            fprintf(fp, "\n");
            printf("Table %s created.\n", table_name);
            printf("Data structure of the table: %s\n", line);

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

    column *current = malloc(sizeof(column));
    current = head;
    
    //the first position of the cursor is the head, so it won't break
    while (current != NULL) {
      
        //allocate memory for the cursor
        current->next=malloc(sizeof(column));
        //switch to the next position of the list
        current = current->next;

        //acquire from stdin
        char field[32];
        field[0]='\0';
        printf("Insert next column - (Insert '.end' to end): ");
        fgets(field, 32, stdin);
        strtok(field, "\n");

        //check if keyword exit is being pressed
        if(strcmp(field, ".end") == 0){
            printf("Columns defined.\n");
            //closes the list
            current=NULL;
            field[0]='\0';
            break;
        }
        else
        {
            //add new field to the list
            strcpy(current->field, field);
            printf("Column inserted: %s\n", current->field);
        }
    }
    return head;
}


int main() {
    print_startup_prompt();

    //MOCK
    //strcpy(working_dir, "/home/eai/Documents/private/SSRI/Programmazione/progetti/mydb/");
    //strcpy(working_dir, "/home/gab/SSRI/Programmazione/progetti/mydb/");
    //strcpy(database, "gbdb-prova");
    //strcpy(table, "small_dataset");
    //mode = TABLE;

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
            case (META_COMMAND_FAILURE):
                printf("An error occurred while executing metacommand '%s'\n", input_buffer->buffer);
                continue;
            }
        } else {
            printf("BUFFER: %s\n", input_buffer->buffer);
        }
    }

    return 0;
}