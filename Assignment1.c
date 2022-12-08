/**
 * \file            main.c
 * \brief           Assignment 1 - EECS 2310 Course - Maze
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * \brief                   This struct represents a maze, with its dimensions.
 * \note                    Should be used with maze_init()
 */
typedef struct maze {
	char **maze;
	int m, n;
} maze_t;

/**
 * \brief                   This function initializes a maze.
 * \param[in]               m: The number of rows in the maze.
 * \param[in]               n: The number of columns in the maze.
 * \return                  A pointer to the maze.
 */
void 
maze_init (maze_t *maze, const int m, const int n) {
	maze->n = n;
	maze->m = m;
    /* Initialize the 2D array for the maze */
	maze->maze = (char**)malloc((m + 1) * sizeof(char*));
	for (int i = 0; i < m; ++i) {
		maze->maze[i] = (char*)malloc((n + 1) * sizeof(char));
	}
}


/**
 * \brief                   This is a struct representing a x,y coordinate
 */
typedef struct coord {
	int x, y;
} coord_t;

/**
 * \brief                   This is a struct representing a stack of coordinates which is the solution
 */
typedef struct stack {
    coord_t *head;
    int top;
    int max_size;
} stack_arr_t;

/**
 * \brief                   This function initializes a stack
 * \param[in]               stack: The stack to be initialized
 * \param[in]               max_size: The maximum size of the stack
 */
void 
stack_init (stack_arr_t *s, size_t size) {
	s->head = (coord_t *)malloc(sizeof(coord_t) * (size + 1));
	s->top = 0;
	s->max_size = size;
}

/**
 * \brief This function destroys the stack, freeing each element
 * 
 * \param[in] s 
 */
void 
stack_destroy (stack_arr_t *s) {
	free(s->head);
}

/**
 * \brief                   This function pushes a coordinate onto the stack
 * 
 * \param[in]               x: The x coordinate
 * \param[in]               y: The y coordinate 
 * \param[in]               s: The stack to push onto
 */
void 
push (const int x, const int y, stack_arr_t *s) {
	/* if over max size, double the size */
	if (s->top == s->max_size) {
		s->max_size *= 2;
		s->head = (coord_t *)realloc(s->head, sizeof(coord_t) * (s->max_size + 1));
	}
    /* set the new head with new coordinates, and inc. top */
	s->head[s->top].x = x;
	s->head[s->top].y = y;
	++s->top;
}

/**
 * \brief                   This function returns the top coordinate on the stack
 * 
 * \param[in]               s: The stack to get top from
 * \return                  The coordinate on top of the stack or (-1, -1), (-1, -1) if stack is empty
 */
coord_t 
top (stack_arr_t *s) {
	if (s->top == 0) {
		coord_t temp;
		temp.x = -1;
		temp.y = -1;
		return temp;
	} else {
		return s->head[s->top - 1];
	}
}

/**
 * \brief                   This function pops the top coordinate off the stack
 * 
 * \param[in]               s: The stack to pop from
 * \return                  The coordinate that was popped or (-1, -1), (-1, -1) if stack is empty
 */
coord_t 
pop (stack_arr_t *s) {
	if (s->top == 0) {
		coord_t temp;
		temp.x = -1;
		temp.y = -1;
		return temp;
	
	} else {
        /* move the top back by 1 to overwrite the stack later*/
		return s->head[--s->top];
	}
}

/**
 * \brief                   This function checks if coordinate exists in the stack
 * 
 * \param[in]               s: The stack to check
 * \param[in]               x: The x coordinate to check
 * \param[in]               y: The y coordinate to check
 * \return                  1 if the coordinate exists in the stack, 0 otherwise 
 */
int 
coord_exists (const stack_arr_t *s, const int x, const int y) {
	for (int i = 0; i < s->top; ++i) {
		if (s->head[i].x == x && s->head[i].y == y) { /* if the coordinate exists in the stack */
            return 1;
        }
	}
	return 0;
}

/**
 * \brief                  struct representing the solutions strings
 * 
 */
typedef struct sol_stack {
    char **head;
    int top;
    int max_size;
} sol_stack_t;

/**
 * \brief                   This function initializes a solution stack
 * 
 * \param[in]               s: The stack to initialize
 * \param[in]               max_size: The maximum size of the stack
 */
void 
sol_stack_init (sol_stack_t *s, size_t max_size) {
    /* initialize head with a max_size arr, begin with top = 0*/
	s->head = (char **)malloc(sizeof(char *) * max_size); 
	s->top = 0;
	s->max_size = max_size;
}

/**
 * \brief                   This function compares two strings using strcmp
 * 
 * \param[in]               a: The first string
 * \param[in]               b: The second string 
 * \return                  int 
 */
int 
cmpfunc (const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

/**
 * \brief                   This function puts the solution into the given string (sprint)
 * 
 * \param[in]               sol_stack_t: The string to put the solution into
 * \param[in]               maze: The maze to solve
 * \param[in]               s: The stack of coordinates that is the solution
 */
void 
sprint_stack (sol_stack_t *sol_stack, const maze_t *maze, const stack_arr_t *coords) {
    int anslen; /* length of the answer string */

	/* if over max size, double the size */
	if (sol_stack->top == sol_stack->max_size - 1) {
		sol_stack->max_size *= 2;
		sol_stack->head = (char **)realloc(sol_stack->head, sizeof(char *) * sol_stack->max_size);
	}
    /* one coord is at most "(m, n)->" long, which is 2+2+2+digits of n, digits of m */
	sol_stack->head[sol_stack->top] = (char*)malloc(coords->top * (2 + 2 + 2 + log10(maze->m) + 1 + log10(maze->n) + 1) * sizeof(char)); 
     
    anslen = 0; 
	for (int i = 0; i < coords->top; ++i) {
        /* use sprintf to add to string offsetted by the length of answer */
		anslen += sprintf(sol_stack->head[sol_stack->top] + anslen, "(%d,%d)", coords->head[i].x+1, maze->m - coords->head[i].y);
		if (i != coords->top - 1) { /* if not last coord, add "->" */
			anslen += sprintf(sol_stack->head[sol_stack->top] + anslen, "->");
		}
	}
	++sol_stack->top; /* increment top */
}

/**
 * \brief                 This function solves the maze by recursively checking each direction
 * \note                  This function is recursive, and will call itself for all possible paths, paths to dead ends will be popped off the stack
 * 
 * \param[in]               maze: The maze to solve
 * \param[in]               l: The stack to push coordinates onto
 * \param[in]               solutions: The stack to push solutions onto
 * \param[in]               pos_x: The x coordinate of the current position
 * \param[in]               pos_y: The y coordinate of the current position
 */
void 
next (const maze_t *maze, stack_arr_t *l, sol_stack_t *solutions, const int pos_x, const int pos_y) {
    /* first add the current pos to the stack, will pop when this ends */
    push(pos_x, pos_y, l);
	if (pos_x == (maze->n - 1) && pos_y == 0) {	/* if the current position is the end, add the solution to the solution stack */
		sprint_stack(solutions, maze, l);
	} else {
		/* check if we can move right, and if we haven't been there before */
		if ((pos_x - 1) >= 0 && maze->maze[pos_y][pos_x - 1] == '0' && !coord_exists(l, pos_x - 1, pos_y)) {
			next(maze, l, solutions, pos_x - 1, pos_y);
		}
		/* check if we can move up, and if we haven't been there before */
		if ((pos_y + 1) < maze->m && maze->maze[pos_y + 1][pos_x] == '0' && !coord_exists(l, pos_x, pos_y + 1)) {
			next(maze, l, solutions, pos_x, pos_y + 1);
		}
		/* check if we can move left, and if we haven't been there before */
		if ((pos_x + 1) < maze->n && maze->maze[pos_y][pos_x + 1] == '0' && !coord_exists(l, pos_x + 1, pos_y)) {
            next(maze, l, solutions, pos_x + 1, pos_y);
		}
		/* check if we can move down, and if we haven't been there before */
		if ((pos_y - 1) >= 0 && maze->maze[pos_y - 1][pos_x] == '0' && !coord_exists(l, pos_x, pos_y - 1)) {
			next(maze, l, solutions, pos_x, pos_y - 1);
		}
	}
    pop(l);
}

int main (void) {
	int m, n;           /* the dimensions of the maze */
    maze_t *maze;       /* the maze struct*/
    stack_arr_t *list;  /* the stack of coordinates */
    sol_stack_t *sol;   /* the stack of solutions */
    
	scanf("%d %d\n", &m, &n);
    /* allocate memory for the maze struct */
	maze = (maze_t *)malloc(sizeof(maze_t)); 
	maze_init(maze, m, n);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			char temp;	
			do {scanf("%c", &temp);} while (temp == '\n' && temp != '0' && temp != '1'); /* read in the maze, only accepting 1 and 0 */
			maze->maze[i][j] = temp;
		}
	}
	/* create a stack to store the current path, and a stack to store the solutions */
	list = (stack_arr_t*)malloc(sizeof(stack_arr_t));
	sol = (sol_stack_t*)malloc(sizeof(sol_stack_t));

	stack_init(list, m*n); 		/* largest possible path without infinite loops would be m*n long, will be doubled if needed */
	sol_stack_init(sol, 4); 	/* arbitrary initial size, will be doubled if needed */

    /* solve the maze, by recursive func. */
	next(maze, list, sol, 0, m - 1);    

	if (sol->top == 0) {                /* check if there are answers in the solution stack */
		printf("No way\n");
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