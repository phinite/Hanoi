#include <iostream>

constexpr int TOWERHEIGHT = 7;


void table_gen(int table[][3])
{
	int i;
	for (i = 0; i < TOWERHEIGHT; i++)
	{
		table[i][0] = i + 1;
	}
	return;
}


void print_table(int table[][3])
{
	std::cout << std::endl;
	int i, j;
	for (i = 0; i < TOWERHEIGHT; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (table[i][j] == 0) {
				std::cout << "." << " ";
			}
			else
			{
				std::cout << table[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	return;
}


int move_piece(int col, int table[][3])
{
	// record the smallest piece and remove it
	int r, rec, stack_height;
	stack_height = rec = 0;
	for (r = 0; r < TOWERHEIGHT; r++)
	{
		if (table[r][col] > 0) {
			rec = table[r][col];
			table[r][col] = 0;
			stack_height = TOWERHEIGHT - r;
			break;
		}
	}

	// if the size of the stack is even or its odd but the middle stack, move it right once, otherwise move it twice
	if (stack_height % 2 == 0) {
		if (col != 1) {
			// move right one, otherwise wraparound
			col = (col + 1) % 3;
		}
		else {
			col = (col + 2) % 3;
		}
	}
	if (stack_height % 2 != 0) {
		if (col != 1) {
			col = (col + 2) % 3;
		}
		else {
			col = (col + 1) % 3;
		}
	}

	// write the new value on the top of the desired stack
	for (r = 0; r < TOWERHEIGHT; r++)
	{

		if ((table[r][col] > 0)) {
			table[r - 1][col] = rec;
			break;
		}
		else if (r == TOWERHEIGHT - 1) {
			table[r][col] = rec;
		}
	}
	return col;
}



void hanoi_solve(int iter, int prev_col, int table[][3])
{

	// get get column with smallest item on top that isnt the item you just moved
	int row_inc, col_inc, smallest_piece, col_num;
	col_num = 0;
	smallest_piece = TOWERHEIGHT;

	for (col_inc = 0; col_inc < 3; col_inc++)
	{
		if (col_inc != prev_col) {
			for (row_inc = 0; row_inc < TOWERHEIGHT; row_inc++)
			{
				if (table[row_inc][col_inc] > 0) {
					if (table[row_inc][col_inc] < smallest_piece) {
						smallest_piece = table[row_inc][col_inc];
						// record the column with the smallest piece
						col_num = col_inc;
						break;
					}
				}
			}
		}
	}
	prev_col = move_piece(col_num, table);
	iter++;

	// if it's been optimal iterations then quit, otherwise continue recursion
	print_table(table);
	if (iter == (1<<TOWERHEIGHT) - 1) {
		return;
	}
	hanoi_solve(iter, prev_col, table);
}



int main()
{
	int table[TOWERHEIGHT][3] = {0};
	table_gen(table);
	print_table(table);
	// set prev_col to 4 because its outside of the column limit, acting like its the first move
	hanoi_solve(0, 4, table);
	return 0;
}



