#define MAX_STACK_SIZE 100
#include <malloc.h>

typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} Stack;

Stack *create(){
	Stack *s =(Stack*)malloc(sizeof(Stack));
	s->top = -1;	
	return s; 
}

int is_empty(Stack *s){
	return (s->top == -1);
}

int is_full(Stack *s){
	return (s->top == (MAX_STACK_SIZE-1));
}

void push(Stack *s, element item){
	if(is_full(s)){
		fprintf(stderr, "stack is full\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(Stack *s){
	if(is_empty(s)){
		fprintf(stderr, "stack is empty\n");
		return 0;
	}
	else return s->stack[(s->top)--];
}

