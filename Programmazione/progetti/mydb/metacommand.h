#include "buffer.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_FAILURE,
  META_COMMAND_UNRECOGNIZED_COMMAND,
  META_COMMAND_EXIT
} MetaCommandResult;

const char* metaCommands[] = {".help", ".exit", ".workingdir", ".db", ".table", ".select"};

static void print_metacommands();

MetaCommandResult execute_metacommand(InputBuffer* inputBuffer);
