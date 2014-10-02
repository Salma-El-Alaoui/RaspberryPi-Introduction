
#include "sched.h"
#include "phyAlloc.h"

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size) {
  (*ctx).pc = f;
  (*ctx).sp = phyAlloc_alloc(STACK_SIZE);
}

void switch_to(struct ctx_s* ctx) {
 int functionSp, functionPc;

//TODO : 
//Save the context
//
  // we save the previous context -> we get the values stored in sp and lr : TODO
  current_ctx->sp = functionSp;
  current_ctx->pc = functionPc;

  //we change the context
  current_ctx = ctx;

  functionSp = current_ctx->sp;
  functionPc = current_ctx->pc;
  //TODO: we should move  functionSp to sp and functionPc to pc

 
}