#include "buffer.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_FAILURE,
  META_COMMAND_UNRECOGNIZED_COMMAND,
  META_COMMAND_EXIT
} MetaCommandResult;

typedef enum {NORMAL, DB, TABLE} Mode;

const char* normalModeMetaCommands[] = {".help", ".exit", ".db-mode", ".table-mode"};
const int normalCommands = 4;
const char* dbModeMetaCommands[] = {".help", ".back", ".select-workingdir", ".list", ".select-db"};
const int dbCommands = 5;
const char* tableModeMetaCommands[] = {".help", ".back", ".list", ".create", ".select", ".create-index", ".print-index", ".find" ,".insert"};
const int tableCommands = 9;

const char* get_mode_name(Mode mode);
const char* get_mode_input_prompt(Mode mode);
const char** get_mode_meta_commands(Mode mode);
const int get_number_of_commands(Mode mode);

static void print_metacommands();

MetaCommandResult execute_metacommand(InputBuffer* inputBuffer);
