#include "buffer.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_FAILURE,
  META_COMMAND_UNRECOGNIZED_COMMAND,
  META_COMMAND_EXIT
} MetaCommandResult;

typedef enum {NORMAL, DB, TABLE} Mode;

//const char* metaCommands[] = {".help", ".exit", ".workingdir", ".db", ".table", ".select"};
const char* normalModeMetaCommands[] = {".help", ".exit", ".db-mode", ".table-mode"};
const char* dbModeMetaCommands[] = {".help", ".exit", ".workingdir", ".dbs", ".db"};
const char* tableModeMetaCommands[] = {".help", ".exit", ".tables", ".table", ".index", ".select"};

const char* getModeName(Mode mode);
const char* getModeInputPrompt(Mode mode);
const char* getModeMetaCommands(Mode mode);

static void print_metacommands();

MetaCommandResult execute_metacommand(InputBuffer* inputBuffer);
