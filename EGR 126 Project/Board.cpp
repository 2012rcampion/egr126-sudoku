#include "Board.h"
#include <stdexcept>

Board::Board() {
	for (int i = 0; i < size*size; ++i) {
		numbers[i] = 0;
	}
}

bool Board::solved() {
	// loop over all the boxes
	for (int j = 0; j < size; ++j) { // loop over rows
		for (int i = 0; i < size; ++i) { // loop over columns in a row
			get(j, i);
		}
	}
	return false;
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

