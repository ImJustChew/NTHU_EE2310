#include <stdio.h>
#include <stdlib.h>

typedef struct maze {
	char **maze;
	int m, n;
} maze_t;

typedef struct coord {
	int x, y;
} coord_t;

typedef struct stack {
    coord_t *head;
    int top;
    int max_size;
} stack_arr_t;

typedef struct sol_stack {
    char **head;
    int top;
    int max_size;
} sol_stack_t;


void stack_init(stack_arr_t *s, int size) {
	s->head = (coord_t *)malloc(sizeof(coord_t) * (size + 1));
	s->top = 0;
	s->max_size = size;
}

void stack_destroy(stack_arr_t *s) {
	free(s->head);
}

void push(int x, int y, stack_arr_t *s) {
	s->head[s->top].x = x;
	s->head[s->top].y = y;
	s->top++;
}

coord_t top(stack_arr_t *s) {
	if (s->top == 0) {
		coord_t temp;
		temp.x = -1;
		temp.y = -1;
		return temp;
	
	} else {
		return s->head[s->top - 1];
	}
}

coord_t pop(stack_arr_t *s) {
	if (s->top == 0) {
		coord_t temp;
		temp.x = -1;
		temp.y = -1;
		return temp;
	
	} else {
		return s->head[--s->top];
	}
}

int coord_exists(stack_arr_t *s, int x, int y) {
	int i;
	for (i = 0; i < s->top; i++) {
		if (s->head[i].x == x && s->head[i].y == y) {
			return 1;
		}
	}
	return 0;
}

void maze_init(maze_t *maze, int m, int n) {
	maze->n = n;
	maze->m = m;
	maze->maze = (char**)malloc((m + 1) * sizeof(char*));
	for (int i = 0; i < m; i++) {
		maze->maze[i] = (char*)malloc((n + 1) * sizeof(char));
	}
}

void sprint_stack(char *string, maze_t *maze, stack_arr_t *s) {
	for (int i = 0; i < s->top; i++) {
		sprintf(string + strlen(string), "(%d, %d)", s->head[i].x+1, maze->m - s->head[i].y);
		if(i != s->top - 1) {
			sprintf(string + strlen(string),"->");
		}
	}
}
int next(maze_t *maze, stack_arr_t *l, int pos_x, int pos_y) {
	// printf("(%d, %d) - (%d, %d) - %c\n", pos_x+1, maze->m - pos_y, pos_x, pos_y, maze->maze[pos_y][pos_x]);
	// printf("top: %d, %d\n", top(l).x, top(l).y);
	if(pos_x == (maze->n - 1) && pos_y == 0) {
		char *sol = (char*)calloc(l->top * (2 + 2 + 2 + maze->m + maze->n), sizeof(char)); //one coord is at most "(m, n)->" long, which is 2+2+2+digits of n, digits of m
		push(pos_x, pos_y, l);
		sprint_stack(sol, maze, l);
		printf("%s\n", sol);
		pop(l);
	}
	else {
		if((pos_x - 1) >= 0 && maze->maze[pos_y][pos_x - 1] == '0' && !coord_exists(l, pos_x - 1, pos_y)) {
			push(pos_x, pos_y, l);
			next(maze, l, pos_x - 1, pos_y);
			pop(l);
		}
		if((pos_y + 1) < maze->m && maze->maze[pos_y + 1][pos_x] == '0' && !coord_exists(l, pos_x, pos_y + 1)) {
			push(pos_x, pos_y, l);
			next(maze, l, pos_x, pos_y + 1);
			pop(l);
		}
		if((pos_x + 1) < maze->n && maze->maze[pos_y][pos_x + 1] == '0' && !coord_exists(l, pos_x + 1, pos_y)) {
			push(pos_x, pos_y, l);
            next(maze, l, pos_x + 1, pos_y);
			pop(l);
		}
		if((pos_y - 1) >= 0 && maze->maze[pos_y - 1][pos_x] == '0' && !coord_exists(l, pos_x, pos_y - 1)) {
			push(pos_x, pos_y, l);
			next(maze, l, pos_x, pos_y - 1);
			pop(l);
		}
	}
}

int main(void) {
	int m, n;
	scanf("%d %d\n", &m, &n);
	maze_t *maze = (maze_t *)malloc(sizeof(maze_t));
	maze_init(maze, m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			char temp;	
			do scanf("%c", &temp);
			while(temp == '\n');
			maze->maze[i][j] = temp;
		}
	}
	stack_arr_t *list = (stack_arr_t*)malloc(sizeof(stack_arr_t));
	stack_init(list, m*n);
	next(maze, list, 0, m - 1);
  return 0;
}