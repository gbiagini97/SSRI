#include <stdio.h>
typedef struct Column{
    char column_name[32];
    struct Column *next;
} column;

typedef enum { TABLE_OPERATION_SUCCESS, TABLE_OPERATION_FAILURE} TableOperationResult;

FILE* select_table();
TableOperationResult create_table();
column* define_data_structure();

