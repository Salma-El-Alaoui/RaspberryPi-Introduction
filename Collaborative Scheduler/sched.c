
#include "sched.h"
#include "phyAlloc.h"

struct pcb_s * head = (struct pcb_s *)0; 
struct pcb_s * current_process = (struct pcb_s *)0;

void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size)
{
	//Initialize process state to READY 
	pcb->pstate = READY;
	
	//Assign function and arguments
	pcb->function = f;
	pcb->args =  args;
 
	//PC  & SP
	pcb->pc = f;
  	pcb->sp= (int*) phyAlloc_alloc(stack_size)+ (stack_size -1)/sizeof(int);

	//Next to NULL
	pcb->next = 0;
	//how does the function get called ???
}

void create_process(func_t f, void* args, unsigned int stack_size)
{
	struct pcb_s* pcb = (struct pcb_s*)malloc(sizeof(struct pcb_s));
	
	//Insert into linked list
	if (!head)//Empty list
	{
		head = pcb;
	} 
	else
	{		
		pcb->next  = head->next ;
	}
 	head->next = pcb;
	//Initialize PCB
	init_pcb(pcb, f, args, stack_size);
	 	
}

void start_current_process()
{
	current_process->function();
	//current_process->state = TERMINATED;
}

void elect () 
{
	pcb = current_process;
	while (pcb->next->state == TERMINATED) {  
	//all terminated 
    if (pcb->next == pcb) {
    	pcb =0;
    	break;

    } else {
    	//throw it out of the list
    	pcb->next = pcb->next->next;
    	//delete ??
      	pcb = pcb->next;

    }

	if (pcb != 0){
		pcb = pcb->next;
		while(pcb->state == WAITING ){
      		pcb = pcb->next;
		}
		if(pcb->state == WAITING){
      		pcb =0;
		}		
	}

	//TODO: case when it's NULL
	current_process = pcb;
}

void start_sched(){
	current_process = head;
}

void __attribute__ ((naked)) ctx_switch()
{

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

