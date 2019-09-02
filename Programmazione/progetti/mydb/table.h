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
    char value[32];
    struct S_BNode *left;
    struct S_BNode *right;
} bnode;
//***************BTREE**************


//***************B+TREE**************
typedef struct S_BPlusNode {
    char value[32];
    struct S_Record *start;
    int n_records;
} bplusnode;
//***************B+TREE**************

typedef enum { TABLE_OPERATION_SUCCESS, TABLE_OPERATION_FAILURE} TableOperationResult;

void select_table();
TableOperationResult create_table();
column* define_data_structure();

void sort(column *head, int table_size);
int sort_records(record *head, int index_number, int n_records);
const char* getFieldFromLine(char *line, int index_number);
static int stringCompare(const void* str1, const void* str2);

bplusnode* build_leaf(record* start, int index_number);
const char* findMedian(bplusnode* leaf1, bplusnode* leaf2);
