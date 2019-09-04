#include <stdio.h>


typedef struct S_Column{
    char field[32];
    struct S_Column *next;
} column;

typedef struct S_Record {
    char line[1024];
    struct S_Record *next;
} record;

//***************BTREE**************
typedef struct S_BNode {
    char value[1024];
    struct S_BNode *left;
    struct S_BNode *right;
} bnode;
//***************BTREE**************


typedef enum { TABLE_OPERATION_SUCCESS, TABLE_OPERATION_FAILURE} TableOperationResult;

void print_tables();
TableOperationResult create_table();
TableOperationResult select_table();
TableOperationResult create_index();
TableOperationResult print_index();
column* define_data_structure();



void sort(column *head, int table_size);
int sort_records(record *head, int index_number, int n_records);
static int stringCompare(const void* str1, const void* str2);


bnode* build_tree(bnode *leaves[], int index_number, int nodes_number);
const char* getFieldFromLine(char *line, int index_number);
const char* findMedianValue(const char* val1, const char* val2);
void traversalPreorder(bnode *node);