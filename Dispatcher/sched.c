
#include "sched.h"
#include "phyAlloc.h"

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size) {
  ctx->pc = f;
  ctx->sp= (int*) phyAlloc_alloc(stack_size)+ (stack_size-1)/sizeof(int);
}

void __attribute__ ((naked)) switch_to(struct ctx_s* ctx) {
	
	//Save the context
	__asm("push {r0-r12}");	
	__asm("mov %0, sp" : "=r"(current_ctx->sp));
	__asm("mov %0, lr" : "=r"(current_ctx->pc));
 

  	//we change the context
  	current_ctx = ctx;

	//restore
	__asm("mov sp, %0" : : "r"(current_ctx->sp));
	__asm("mov lr, %0" : : "r"(current_ctx->pc));
	__asm("pop {r0-r12}");
	__asm("bx lr");
	

 
}
