#ifndef SCHED_H
#define SCHED_H

#define STACK_SIZE 512 

typedef void (*func_t) (void);

struct ctx_s {
  void* pc;
  void* sp;
};

struct ctx_s* current_ctx;

void init_ctx(struct ctx_s* ctx, func_t f, int stack_size);

void switch_to(struct ctx_s* ctx);

#endif
