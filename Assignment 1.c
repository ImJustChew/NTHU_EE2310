#include <stdio.h>
#include <stdlib.h>

typedef struct maze {
	char **maze;
	int m, n;
} maze_t;

void maze_init (maze_t *maze, const int m, const int n) {
	maze->n = n;
	maze->m = m;
	maze->maze = (char**)malloc((m + 1) * sizeof(char*));
	for (int i = 0; i < m; ++i) {
		maze->maze[i] = (char*)malloc((n + 1) * sizeof(char));
	}
}
typedef struct coord {
	int x, y;
} coord_t;

typedef struct stack {
    coord_t *head;
    int top;
    int max_size;
} stack_arr_t;

void stack_init (stack_arr_t *s, size_t size) {
	s->head = (coord_t *)malloc(sizeof(coord_t) * (size + 1));
	s->top = 0;
	s->max_size = size;
}

void stack_destroy (stack_arr_t *s) {
	free(s->head);
}

void push (const int x, const int y, stack_arr_t *s) {
	/* if over max size, double the size */
	if (s->top == s->max_size) {
		s->max_size *= 2;
		s->head = (coord_t *)realloc(s->head, sizeof(coord_t) * (s->max_size + 1));
	}
	s->head[s->top].x = x;
	s->head[s->top].y = y;
	++s->top;
}

coord_t top (stack_arr_t *s) {
	if (s->top == 0) {
		coord_t temp;
		temp.x = -1;
		temp.y = -1;
		return temp;
	} else {
		return s->head[s->top - 1];
	}
}

coord_t pop (stack_arr_t *s) {
	if (s->top == 0) {
		coord_t temp;
		temp.x = -1;
		temp.y = -1;
		return temp;
	
	} else {
		return s->head[--s->top];
	}
}

int coord_exists (const stack_arr_t *s, const int x, const int y) {
	for (int i = 0; i < s->top; ++i) {
		if (s->head[i].x == x && s->head[i].y == y) return 1;
	}
	return 0;
}


typedef struct sol_stack {
    char **head;
    int top;
    int max_size;
} sol_stack_t;


void sol_stack_init (sol_stack_t *s, size_t max_size) {
	s->head = (char **)malloc(sizeof(char *) * max_size);
	s->top = 0;
	s->max_size = max_size;
}

void add_sol (sol_stack_t *s, char *sol) {
	/* if over max size, double the size */
	if (s->top == s->max_size - 1) {
		s->max_size *= 2;
		s->head = (char **)realloc(s->head, sizeof(char *) * s->max_size);
	}
	s->head[++s->top] = sol;
}

int cmpfunc (const void *a, const void *b) {
	return strcmp(*(const char **)a, *(const char **)b);
}

void sprint_stack (char *string, const maze_t *maze, const stack_arr_t *s) {
	for (int i = 0; i < s->top; ++i) {
		sprintf(string + strlen(string), "(%d, %d)", s->head[i].x+1, maze->m - s->head[i].y);
		if (i != s->top - 1) {
			sprintf(string + strlen(string), "->");
		}
	}
}

int next (const maze_t *maze, stack_arr_t *l, sol_stack_t *solutions, const int pos_x, const int pos_y) {
	/* if the current position is the end, add the solution to the solution stack */
	if (pos_x == (maze->n - 1) && pos_y == 0) {
        char *sol;
		sol = (char*)calloc(l->top * (2 + 2 + 2 + maze->m + maze->n), sizeof(char)); //one coord is at most "(m, n)->" long, which is 2+2+2+digits of n, digits of m
		push(pos_x, pos_y, l);
		sprint_stack(sol, maze, l);
		add_sol(solutions, sol);
		pop(l);
	}
	else {
		/* check if we can move right, and if we haven't been there before */
		if ((pos_x - 1) >= 0 && maze->maze[pos_y][pos_x - 1] == '0' && !coord_exists(l, pos_x - 1, pos_y)) {
			push(pos_x, pos_y, l);
			next(maze, l, solutions, pos_x - 1, pos_y);
			pop(l);
		}
		/* check if we can move up, and if we haven't been there before */
		if ((pos_y + 1) < maze->m && maze->maze[pos_y + 1][pos_x] == '0' && !coord_exists(l, pos_x, pos_y + 1)) {
			push(pos_x, pos_y, l);
			next(maze, l, solutions, pos_x, pos_y + 1);
			pop(l);
		}
		/* check if we can move left, and if we haven't been there before */
		if ((pos_x + 1) < maze->n && maze->maze[pos_y][pos_x + 1] == '0' && !coord_exists(l, pos_x + 1, pos_y)) {
			push(pos_x, pos_y, l);
            next(maze, l, solutions, pos_x + 1, pos_y);
			pop(l);
		}
		/* check if we can move down, and if we haven't been there before */
		if ((pos_y - 1) >= 0 && maze->maze[pos_y - 1][pos_x] == '0' && !coord_exists(l, pos_x, pos_y - 1)) {
			push(pos_x, pos_y, l);
			next(maze, l, solutions, pos_x, pos_y - 1);
			pop(l);
		}
	}
}

int main (void) {
	int m, n;
    maze_t *maze;
    stack_arr_t *list;
    sol_stack_t *sol;
    
	scanf("%d %d\n", &m, &n);
	maze = (maze_t *)malloc(sizeof(maze_t));
	maze_init(maze, m, n);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			char temp;	
			do {scanf("%c", &temp);} while (temp == '\n');
			maze->maze[i][j] = temp;
		}
	}
	/* create a stack to store the current path, and a stack to store the solutions */
	list = (stack_arr_t*)malloc(sizeof(stack_arr_t));
	sol = (sol_stack_t*)malloc(sizeof(sol_stack_t));
	stack_init(list, m*n); 		/* arbitrarily large */
	sol_stack_init(sol, 4); 	/* arbitrary initial size, will be doubled if needed */
	next(maze, list, sol, 0, m - 1);
	if (sol->top == 0) {
		printf("No solution\n");
	} else {
		/* sort the solutions lexographically */
		qsort(sol->head, sol->top, sizeof(char *), cmpfunc);
		for (int i = 0; i < sol->top; ++i) {
			printf("%s\n", sol->head[i]);
		}
	}
    
    /* clean up memory */
    for(int i = 0; i < maze->m; ++i) {
        free(maze->maze[i]);
    }
    free(maze->maze);
    free(maze);
    stack_destroy(list);
    free(list);
    for (int i = 0; i < sol->top; ++i) {
        free(sol->head[i]);
    }
    free(sol->head);
    free(sol);
    return 0;
}