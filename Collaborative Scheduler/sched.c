
#include "sched.h"
#include "phyAlloc.h"

struct pcb_s * current_pcb = NULL;

void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size) {
	//Initialize process state to READY 
	pcb->pstate = process_state.READY;
	
	//Assign function and arguments
	pcb->function = f;
	pcb->args =  args;
 
	//PC  & SP
	pcb->pc = f;
  	pcb->sp= (int*) phyAlloc_alloc(stack_size)+ (stack_size -1)/sizeof(int);

	//Next & previous to NULL
	pcb->next = NULL;
	pcb->previous = NULL;
}

void create_process(func_t f, void* args, unsigned int stack_size){
	pcb_s* pcb = malloc(sizeof(pcb_s));
	
	//Insert into linked list
	if (current_pcb == NULL)//Empty list
	{
		current_pcb = pcb;
		pcb->next = pcb;
		pcb->previous = pcb;
	}
	else
	{
		
		pcb_s->next= current_pcb->next;
		pcb_s->previous=current_pcb;
		current_pcb->next = pcb_s;
		current_pc= pcb_s;
	}
 
	//Initialize PCB
	init_pcb(pcb_s, f, args, stack_size);
	 
	

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
