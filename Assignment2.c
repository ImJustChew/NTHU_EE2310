/**
 * \file            main.c
 * \brief           Assg#2 The K-Queen Problem
 * \note            Write a program that finds all possible ways to place K queens on an K×K chessboard so
                    that no two queens threaten each other. Thus, a solution requires that no two queens share
                    the same row, column, or diagonal,
                    The result is simply represented as the x-coordinate of the queen as an array of integers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
sprint_sol (sol_stack_t *sol_stack, int k, int **board) {
    int anslen;
	/* if over max size, double the size */
	if (sol_stack->top == sol_stack->max_size - 1) {
		sol_stack->max_size *= 2;
		sol_stack->head = (char **)realloc(sol_stack->head, sizeof(char *) * sol_stack->max_size);
	}
    /* one coord is at most "(m, n)->" long, which is 2+2+2+digits of n, digits of m */
	sol_stack->head[sol_stack->top] = (char*)malloc(k * 2 * sizeof(char)); 
     
    anslen = 0; 
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < k; ++j) {
            if(board[i][j] == 1) {
                anslen += sprintf(sol_stack->head[sol_stack->top] + anslen, "%d ", j + 1);
            }
        }
    }
	++sol_stack->top; /* increment top */
}

/**
 * \brief                   This function checks if the given coordinate is valid to put a queen
 * 
 * \param[in]               k: The size of the board
 * \param[in]               board: The board to check 
 * \param[in]               row: The row to check 
 * \param[in]               col: The column to check 
 * \return int              1 if valid, 0 if not
 */
int 
is_safe(int k, int **board, int row, int col) {
    for (int i = 0; i < col; ++i) {
        if (board[row][i]) {
            return 0;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j]) {
            return 0;
        }
    }
    for (int i = row, j = col; j >= 0 && i < k; ++i, --j) {
        if (board[i][j]) {
            return 0;
        }
    }
    return 1;
}

/**
 * \brief                   This function solves the maze using backtracking
 * 
 * \param[in]               k: The size of the board
 * \param[in]               board: The board to solve
 * \param[in]               col: The column to check
 * \param[in]               sol_stack: The stack of coordinates that is the solution
 * \return int 
 */
int 
solve(int k, int **board, int col, sol_stack_t *sol_stack) {
    if (col >= k) {
        return 1;
    }
    for (int i = 0; i < k; i++) {
        if (is_safe(k, board, i, col)) {
            board[i][col] = 1;
            if (solve(k, board, col + 1, sol_stack)) {
                sprint_sol(sol_stack, k, board);
            }
            board[i][col] = 0;
        }
    }
    return 0;
}

int main() {
    int k;
    sol_stack_t *sol;   /* the stack of solutions */

    scanf("%d", &k); /* trivial */
    
    int **queens = (int**)malloc(k * sizeof(int*));
    for(int i = 0; i < k; i++) {
        queens[i] = (int*)malloc(k * sizeof(int));
        for(int j = 0; j < k; j++) {
            queens[i][j] = 0;
        }
    }


	sol = (sol_stack_t*)malloc(sizeof(sol_stack_t));
	sol_stack_init(sol, 4); 	/* arbitrary initial size, will be doubled if needed */

    solve(k, queens, 0, sol);
    
    qsort(sol->head, sol->top, sizeof(char *), cmpfunc);
    for (int i = 0; i < sol->top; ++i) {
        printf("%s\n", sol->head[i]);
    }
    printf("%d solution(s) for the %d-Queen problem.\n", sol->top, k);

}