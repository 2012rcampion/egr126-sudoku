#pragma once

#include <array>

using std::array;

//Declaration of class.
class Board {
	//Declaration of variables.
public:
	static constexpr int size = 9;
private:
	array<int, size * size> numbers;

	//Declaration of functions
public:
	Board();

	int get(int row, int col);
	void set(int row, int col, int value);

	bool solved();

private:
	static int row_col_to_index(int row, int col);

};
//
//
//
//
//

//Board check.
	//Check for sum on each box, column and box:
	if (Sum[row] = 45, Sum[col] = 45, Sum[3 * 3] = 45)
		// how to keep going?

	else
		return false;

	//Check duplicate numbers on each row:
	for (int row = 0; row < 9; row++)
		int flag = 0;

	for (int col = 0; col < 9; col++);
		if ((sudoku[row, col] < 1) || (sudoku[row, col] > 9))
			return false;

		if (flag & (1 << sudoku[row, col]))
			return false;

		else
			flag |= (1 << sudoku[row, col]);
					
	//Check duplicate numbers on each column:
	for (int col = 0; col < 9; col++)
		int flag = 0;

	for (int row = 0; row < 9; row++)
		if (flag & (1 << sudoku[row, col])) 
			return false;

		else
			flag |= (1 << sudoku[row, col]);

	//Check duplicate numbers on each box:
	for (int box = 0; box < 9; box++)
		if{
			for (int ofs = 0; ofs < 9; ofs++);
			int col = (box % 3) * 3;
			int row = ((int)(box / 3)) * 3;

			if (flag & (1 << sudoku[row, col]))
				return false;

			else
				flag |= (1 << sudoku[row, col]);
		}
		else //no duplicates detected
			return true;



