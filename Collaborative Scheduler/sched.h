#ifndef SCHED_H
#define SCHED_H

/*
*pour une fonction:
*3 parametres (3 int de 32) 
* 3 variables locales (3 int de 32)
*de la place pour faire les calculs (128)
*on estime qu'on veut appler 5 fonctions
=> 200 donc 256
*/
#define STACK_SIZE 256

typedef void (*func_t) (void);

typedef enum {NEW, READY, RUNNING, WAITING, TERMINATED} process_state;

struct pcb_s {
	process_state pstate;
	func_t function;
	void * args;
	int* pc;
	int* sp;
	pcb_s * previous;
	pcb_s * next;

};


struct ctx_s* current_ctx;

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size);

void __attribute__ ((naked))switch_to(struct ctx_s* ctx);

int create_process(func_t f, void *args, unsigned int stack_size);
void __attribute__ ((naked)) ctx_switch();


#endif
