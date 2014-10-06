
#include "sched.h"
#include "phyAlloc.h"

struct pcb_s * tail = 0;
struct pcb_s * head = 0; 
struct pcb_s * current_process =0;

void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size) {
	//Initialize process state to READY 
	pcb->pstate = READY;
	
	//Assign function and arguments
	pcb->function = f;
	pcb->args =  args;
 
	//PC  & SP
	pcb->pc = f;
  	pcb->sp= (int*) phyAlloc_alloc(stack_size)+ (stack_size -1)/sizeof(int);

	//Next & previous to NULL
	pcb->next = 0;
}
void create_process(func_t f, void* args, unsigned int stack_size){
	struct pcb_s* pcb = (struct pcb_s*)malloc(sizeof(struct pcb_s));
	
	//Insert into linked list
	if (tail == 0)//Empty list
	{
		tail = pcb;
		head=pcb;
	}
	else
	{
		
		tail->next  = pcb;
		tail= pcb;
	}

 	tail->next = head;
	//Initialize PCB
	init_pcb(pcb, f, args, stack_size);
	 	
}
void start_current_process(){
	(current_process->function)();
}
void elect (){
	current_process = current_process->next;
}

void start_sched(){
	current_process = head;
}
void __attribute__ ((naked)) ctx_switch(){

	//Save the context
	__asm("push {r0-r12}");	
	__asm("mov %0, sp" : "=r"(current_process->sp));
	__asm("mov %0, lr" : "=r"(current_process->pc));
 

  	//elect a new process 
	elect();

	//restore the context of the elected process
	__asm("mov sp, %0" : : "r"(current_process->sp));
	__asm("mov lr, %0" : : "r"(current_process->pc));
	__asm("pop {r0-r12}");
	__asm("bx lr");
}

