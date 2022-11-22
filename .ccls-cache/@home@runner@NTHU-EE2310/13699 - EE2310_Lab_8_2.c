/*  Please follow our exact rules otherwise you WILL LOSE POINTS */

 

#include <stdio.h>
#include <stdlib.h>

/* DO NOT CHANGE STRUCT */
struct node{
    int data;
    struct node *next;
};
typedef struct node node_t;

typedef struct linked_list{
    node_t *head;
    node_t *tail;
} linked_list_t;

void output_list(linked_list_t *ptr_list){
	node_t *ptr_node;
	ptr_node = ptr_list->head;
	while(ptr_node!= NULL){
		printf("%d", ptr_node->data);
		if(ptr_node->next!= NULL) printf(" ");
		ptr_node = ptr_node->next;
	}
	printf("\n");
}

void add_node(linked_list_t *list_ptr, int data){
	if(list_ptr->head == NULL){
		list_ptr->head = (node_t *)malloc(sizeof(node_t));
		list_ptr->head->data = data;
		list_ptr->head->next = NULL;
		list_ptr->tail = list_ptr->head;
		return;
	}
	else {
		node_t *temp = list_ptr->tail;
		list_ptr->tail->next = (node_t *)malloc(sizeof(node_t));
		list_ptr->tail = list_ptr->tail->next;
		list_ptr->tail->data = data;
		list_ptr->tail->next = NULL;
		return;
	}
}

 

/* DO NOT CHANGE MAIN */

int main(){
    linked_list_t my_list;
    my_list.head = NULL;
    my_list.tail = NULL;
    int data, input_size;
    /* when you add a node, you add it at the tail */
    
    scanf("%d\n", &input_size);
    for(int i=0; i < input_size; ++i){
        scanf("%d", &data);
        add_node(&my_list, data);
    }
    
    output_list(&my_list);
    
    return 0;
}

