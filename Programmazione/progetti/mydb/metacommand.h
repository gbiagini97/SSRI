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
const char* dbModeMetaCommands[] = {".help", ".exit", ".workingdir", ".dbs", ".db"};
const int dbCommands = 5;
const char* tableModeMetaCommands[] = {".help", ".exit", ".tables", ".table", ".index", ".select"};
const int tableCommands = 6;

const char* getModeName(Mode mode);
const char* getModeInputPrompt(Mode mode);
const char** getModeMetaCommands(Mode mode);
const int getNumberOfCommands(Mode mode);

static void print_metacommands();

MetaCommandResult execute_metacommand(InputBuffer* inputBuffer);
