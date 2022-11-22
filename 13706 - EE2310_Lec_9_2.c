/* ---    DO NOT SUBMIT main() !!!   --- */

/* --- submit EVERYTHING ELSE except main() --- */

/* --- containing the #include directives and struct definition --- */

 

#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *next;
};
typedef struct node node_t;

typedef struct linked_list {
    node_t *head;
    node_t *tail;
} linked_list_t;

void initialize(linked_list_t *list_ptr) {
    list_ptr->head = NULL;
    list_ptr->tail = NULL;
}

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

node_t* find_middle(linked_list_t *list_ptr) {
	//get index and then middle
	node_t *ptr_node;
	int index = 0;
	ptr_node = list_ptr->head;
	while(ptr_node->next!= NULL){
		index++;
		ptr_node = ptr_node->next;
	}
	index = (int) (float)index/2.0 +0.5;
	ptr_node = list_ptr->head;
	while(index > 0){
		index--;
		ptr_node = ptr_node->next;
	}
	return ptr_node;
}

void free_list(linked_list_t *ptr_list) {
	node_t *ptr_node;
	ptr_node = ptr_list->head;
	while(ptr_node!= NULL){
		node_t *temp = ptr_node;
		ptr_node = temp->next;
		free(temp);
	}
}

void reverse_list(linked_list_t *list_ptr) {
	node_t *current, *next, *prev;
	current = list_ptr->head;
	prev = NULL;
	while(current!= NULL){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list_ptr->tail = list_ptr->head;
	list_ptr->head = prev;
}

 


int main() {
    linked_list_t my_list;
    initialize(&my_list);
    node_t *middle_ptr;
    
    int data, input_size;
    /* when you add a node, you add it at the tail */
    
    scanf("%d\n", &input_size);
    for(int i=0; i < input_size; ++i) {
        scanf("%d", &data);
        add_node(&my_list, data);
    }
    
    reverse_list(&my_list);
    output_list(&my_list);
    free_list(&my_list);
    
    return 0;
}

