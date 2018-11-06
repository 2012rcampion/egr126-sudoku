#include "Board.h"
#include <stdexcept>

Board::Board() {
	for (int i = 0; i < size*size; ++i) {
		numbers[i] = 0;
	}
}

bool Board::solved() {
	
//Board check.
	//Check for sum on each box, column and box:
	if(Sum[row] == 45 && Sum[col] == 45 && Sum[3 * 3] == 45) {
		// do nothing - continue
	}
	else {
		return false;
	}


	//Check duplicate numbers on each row:
	for(int row = 0; row < 9; row++) {
		int flag = 0;

		for(int col = 0; col < 9; col++) {
			if((get(row, col) < 1) || (get(row, col) > 9)) {
				return false;
			}
			if(flag & (1 << get(row, col))) {
				return false;
			}
			else {
				flag |= (1 << get(row, col));
			}
		}
	}

	//Check duplicate numbers on each column:
	for(int col = 0; col < 9; col++) {
		int flag = 0;

		for(int row = 0; row < 9; row++)
			if(flag & (1 << get(row, col)))
				return false;

			else
				flag |= (1 << get(row, col));
	}

	//Check duplicate numbers on each box:
	for(int box = 0; box < 9; box++) {
		for(int ofs = 0; ofs < 9; ofs++);
		int col = (box % 3) * 3;
		int row = ((int) (box / 3)) * 3;

		if(flag & (1 << get(row, col)))
			return false;

		else
			flag |= (1 << get(row, col));
	}

	for(int box_row = 0; box_row < 9; box_row += 3) {
		for(int box_col = 0; box_col < 9; box_col += 3) {
			int flag = 0;
			for(int row = box_row; row < box_row + 3; box_row++) {
				for(int col = box_col; col < box_col + 3; box_col++) {
					// do checks
				}
			}
		}
	}
			
	return true;
}

int Board::row_col_to_index(int row, int col) {
	if (row < 0 || row >= size) {
		throw std::out_of_range("row is out of range");
	}
	if (col < 0 || col >= size) {
		throw std::out_of_range("column is out of range");
	}
	return size * row + col;
}

int Board::get(int row, int col) {
	int index = row_col_to_index(row, col);
	return numbers[index];
}

void Board::set(int row, int col, int value) {
	if (value < 0 || value > size) {
		throw std::out_of_range("value is out of range");
	}
	int index = row_col_to_index(row, col);
	numbers[index] = value;
}

