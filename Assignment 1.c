#include <stdio.h>
#include <stdlib.h>

typedef struct maze {
	char **maze;
	int m, n;
} maze_t;

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
void print(list_t *l) {
	node_t *p = l->head;
	while (p!= NULL) {
		printf("(%d,%d)", p->x, p->y);
		if(p->next!= NULL) printf("->");
		p = p->next;
	}
	printf("\n");
}

int next(maze_t *maze, list_t *l, int pos_x, int pos_y) {
	if(pos_x - 1 >= 0 && maze.maze[pos_x - 1][pos_y] == '0') return next(matrix, l, pos_x - 1, pos_y) == 0)
}

int main(void) {
	int m, n;
	scanf("%d %d\n", &m, &n);
	maze_t *maze = (maze_t *)malloc(sizeof(maze_t));
	maze->m = m;
	maze->n = n;
	char** matrix = (char**)malloc(m * sizeof(char*));
	maze->maze = matrix;
	for (int i = 0; i < m; i++) {
		matrix[i] = (char*)malloc(n * sizeof(char));
		for (int j = 0; j < n; j++) {
			char temp;	
			do {
				scanf("%c", &temp);
			}
			while(temp == '\n');
			matrix[i][j] = temp;
		}
	}

	int pos_x = 0, pos_y = 0;
	list_t *list = (list_t*)malloc(sizeof(list_t));
	next(matrix, list, pos_x, pos_y);
  return 0;
}