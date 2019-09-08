
typedef enum {DIRECTORY_SELECTION_SUCCESS, DIRECTORY_SELECTION_FAILURE} DirectorySelection;
typedef enum {DATABASE_CREATED, DATABASE_SELECTED, DATABASE_SELECTION_FAILURE} DatabaseSelection;

DirectorySelection define_working_dir();

DatabaseSelection select_database();

static void print_databases();

