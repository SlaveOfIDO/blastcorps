#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

// TODO: This is 99% a library function
// Maybe it is alSeqpGetState and this file is seqpgetstate.c
s32 alSeqpGetState(ALSeqPlayer* arg0) {
  return arg0->state;
}

