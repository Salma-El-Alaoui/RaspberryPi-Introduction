
#include "sched.h"
#include "phyAlloc.h"

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size) {
  (*ctx).pc = f;
  (*ctx).sp = phyAlloc_alloc(STACK_SIZE);
}
