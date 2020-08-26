#include <stdio.h> 		  /* printf, size_t */
#include <stdbool.h> 	  /* true, false    */
#include <setjmp.h>
#include "knights_tour_hiuristic.h" /* API function   */

jmp_buf buf;

enum status
{
	FINISH = 1
};
/*----------------------------------------------------------------------------*/
/*
static int col_size = 8;
static int row_size = 8;
*/
static int col_size = 8;
static int row_size = 8;

#define BOARD_SIZE 64
#define NUM_OF_OPTIONS 8
/*
static int result_board[BOARD_SIZE] = {0};
*/
/*
static int row_move[NUM_OF_OPTIONS] = {-2, -2, -1, 1, 2,  2,  1, -1};
static int col_move[NUM_OF_OPTIONS] = {-1,  1,  2, 2, 1, -1, -2, -2};
*/
/*----------------------------------------------------------------------------*/
/* Utility functions decleration */
/*----------------------------------------------------------------------------*/

static int AvialableMove(int row,
						 int col,
						 int move_counter,
						 int *row_move,
						 int *col_move,
						 int *result_board);

static int IsValidMove(int row_index,
					   int col_index,
					   int last_move_number,
					   int *result_board);

static int IsNotVisited(int row_index,
					    int col_index,
						int last_move_number, 
						int *result_board);

static int IsRowOnBord(int row);
static int IsColOnBord(int col);
static int GetIndex(int row_index, int col_index);
static void PrintTour(int *result_board);
int FindMin(int *arr, int size);

/*----------------------------------------------------------------------------*/

void KnightTour(int row_index, int col_index)
{
	int row_move[NUM_OF_OPTIONS] = {-2, -2, -1, 1, 2,  2,  1, -1};
	int col_move[NUM_OF_OPTIONS] = {-1,  1,  2, 2, 1, -1, -2, -2};
	int result_board[BOARD_SIZE] = {0};
	

	printf("\n\n");

	if (AvialableMove(col_index, row_index, 0, row_move, col_move, result_board))
	{
		PrintTour(result_board);
	}
	else
	{
		printf("Has no solution\n");
	}

	setjmp(buf);
}

/*----------------------------------------------------------------------------*/

static int AvialableMove(int row,
						 int col,
						 int move_counter,
						 int *row_move,
						 int *col_move,
						 int *result_board)
{
	static int terminator_counter = 0;
	int index = GetIndex(row ,col);
	int r = 0;
	int c = 0;
	int i = 0;
	int k = 0;
	int potential_r = 0;
	int potential_c = 0;
	int best_index = 0;
	int min_lut[8] = {0};
	
	++terminator_counter;
	result_board[move_counter] = index;

	if (terminator_counter >= 10000)
	{
		terminator_counter = 0;
		longjmp(buf, 1);
	}
	
	/* max available steps reached */
	if (move_counter == BOARD_SIZE - 1)
	{
		return (true);
	}
	
	/* generates data for each possible step */  
	for (i = 0; i < NUM_OF_OPTIONS; ++i)
	{
		r = row + row_move[i];
		c = col + col_move[i];

#ifdef NDEBUG
		if (IsValidMove(r, c, move_counter, result_board))
		{
			int cnt = 0;
			int j = 0;
				
			/* this loop check for the next move with the least amount of steps */
			for	(j = 0; j < NUM_OF_OPTIONS; ++j)
			{
				potential_r = r + row_move[j];
				potential_c = c + col_move[j];

				/* counts number of available next moves */
				cnt += IsValidMove(potential_r,
								   potential_c,
								   move_counter,
								   result_board);				
			}

			min_lut[i] = cnt;			
		}
	}

	best_index = FindMin(min_lut, 8);
		
	for (k = 0; k < 8 && min_lut[best_index] < 9; ++k, best_index = FindMin(min_lut, 8))
	{
		r = row + row_move[best_index];
		c = col + col_move[best_index];

		/* rules out current index for the next iteration */
		min_lut[best_index] = 9;
#endif

		if (IsValidMove(r, c, move_counter, result_board))
		{
			if (AvialableMove(r, c, move_counter + 1, row_move, col_move, result_board))
			{
				return (true);
			}
		}
	}

	return (false);
}

/*----------------------------------------------------------------------------*/

static int IsValidMove(int row_index, int col_index,
					   int move_counter, int *result_board)
{
	return (IsRowOnBord(row_index) && IsColOnBord(col_index) &&
			IsNotVisited(row_index, col_index, move_counter, result_board));
}
/*----------------------------------------------------------------------------*/
static int IsRowOnBord(int row)
{
	return (row >= 0 && row < col_size);
}

/*----------------------------------------------------------------------------*/

static int IsColOnBord(int col)
{
	return (col >= 0 && col < row_size);
}

/*----------------------------------------------------------------------------*/

static int IsNotVisited(int row_index, int col_index,
						int move_counter, int *result_board)
{
	int index = GetIndex(row_index ,col_index);
	int is_not_visited = 1;

	for (; move_counter >= 0 && is_not_visited; --move_counter)
	{
		is_not_visited = result_board[move_counter] != index;
	}

	return (is_not_visited);
}

/*----------------------------------------------------------------------------*/

static int GetIndex(int row_index, int col_index)
{
	return (row_index * row_size + col_index);
}

/*----------------------------------------------------------------------------*/

static void PrintTour(int *result_board)
{
	int i = 0;

	printf("Printing Tour:\n");

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		printf("Step %d at index: %d\n",  i + 1, result_board[i]);
	}
}

int FindMin(int *arr, int size)
{
	int i = 0;
	int min_index = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] < arr[min_index])
		{			
			min_index = i;			
		} 
	}

	return (min_index);
}	

/*----------------------------------------------------------------------------*/
