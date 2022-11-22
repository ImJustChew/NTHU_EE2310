#include <stdio.h>
#include <stdlib.h>

#define MAX_NEG -1000000000

typedef struct stack {
    int *head;
    int top;
    int max_size;
} stack_arr_t;


void stack_init(stack_arr_t *s, int size) {
	s->head = (int *)malloc(sizeof(int) * (size + 1));
	s->top = 0;
	s->max_size = size;
}

void stack_destroy(stack_arr_t *s) {
	free(s->head);
}

void push(int elem, stack_arr_t *s) {
	s->head[s->top++] = elem;

}

int pop(stack_arr_t *s) {
	if (s->top == 0) {
		return MAX_NEG;
	
	} else {
		return s->head[--s->top];
	}
}

 

void show_stack(stack_arr_t *s) {
/* your code here
 *  if the stack is empty, printf("Stack empty!\n");

 * otherwise, printf("Stack contains %d element(s)\n", ...);

 * and then  printf("top = %d, max_size = %d\n",...);
 */
	if(s->top == 0) {
		printf("Stack empty!\n");
	}
	else {
		printf("Stack contains %d element(s)\n", s->top);
		for(int i = 0; i < s->top; i++) {
			printf("%d", s->head[i]);
			if(i == s->top - 1) printf("\n");
			else printf(" ");
		}
	}
	printf("top = %d, max_size = %d\n", s->top, s->max_size);

}

 

/*  do not change main() !!!  */
int main(){
    stack_arr_t my_stack;
    
    int input_size, temp, max_size, pop_size;

    /* input stack's max size */
    scanf("%d", &max_size);
    stack_init(&my_stack, max_size);

    /* input elements to be pushed */
    scanf("\n%d", &input_size);
    int i;
    for(i=0; i<input_size; ++i){
        scanf("\n%d", &temp);
        push(temp, &my_stack);
    }

    /* input number of elements to be popped */
    scanf("\n%d", &pop_size);
    for(i=0; i < pop_size-1; ++i){
        printf("%d ", pop(&my_stack));
    }
    if (0 != pop_size){
        printf("%d\n", pop(&my_stack));
    }

    show_stack(&my_stack);

    stack_destroy(&my_stack);

    return 0;
}

/* in show_stack(), if the stack is empty, printf("Stack empty!\n"); */

