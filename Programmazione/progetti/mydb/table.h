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

TableOperationResult print_tables();
TableOperationResult create_table();
TableOperationResult select_table();
TableOperationResult create_index();
TableOperationResult print_index();
TableOperationResult find();
TableOperationResult insert();


column* define_data_structure();
column* get_table_structure(FILE *file);
void build_tree_from_list(record *list, int index_number);
int generate_id();
int print_table_structure(FILE *fp);
int count_records(record *head);
record* build_list_from_table(FILE *fp);
FILE* open_table(char open_mode[3]);
int sort_records(record *head, int index_number, int n_records);
void build_leaves(bnode *leaves[], record *sorted_list, int leaves_number);
void traversal_preorder_search(bnode *node, char key[32], int index_number);

bnode* build_tree(bnode *leaves[], int index_number, int nodes_number);
const char* get_field_from_line(char *line, int index_number);
const char* find_median_value(const char* val1, const char* val2);
void print_traversal_preorder(bnode *node);