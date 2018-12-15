#include "Board.h"
#include <stdexcept>
#include <array>
#include <numeric>
#include <algorithm>
#include <random>


Board::Board() : numbers{} {
	std::fill(numbers.begin(), numbers.end(), 0);
}

int bit(int b) {
	return (1 << b) >> 1;
}

bool Board::solved() const {

	//Check all cells are filled:
	for(int row = 0; row < size; row++) {
		for(int col = 0; col < size; col++) {
			if(get(row, col) == 0) {
				return false;
			}
		}
	}

	//Check duplicate numbers on each row:
	for(int row = 0; row < size; row++) {
		if(check_row(row) == false) {
			return false;
		}
	}

	//Check duplicate numbers on each column:
	for(int col = 0; col < size; col++) {
		if(check_col(col) == false) {
			return false;
		}
	}

	//Check duplicate numbers on each box:
	for(int box = 0; box < size; ++box) {
		if(check_box(box) == false) {
			return false;
		}
	}

	return true;
}

bool Board::check_row(int row) const {
	int flag = 0;

	for (int col = 0; col < size; col++) {
		if (flag & bit(get(row, col))) {
			return false;
		}
		else {
			flag |= bit(get(row, col));
		}
	}
	return true;
}

bool Board::check_col(int col) const {
	int flag = 0;

	for (int row = 0; row < size; row++) {
		if (flag & bit(get(row, col))) {
			return false;
		}
		else {
			flag |= bit(get(row, col));
		}
	}
	return true;
}

bool Board::check_box(int box) const {
	int flag = 0;
	for (int boxnum = 0; boxnum < size; boxnum++) {
			if (flag & bit(get_box(box, boxnum))) {
				return false;
			}
			else {
				flag |= bit(get_box(box, boxnum));
			}
	}
	return true;
}

static auto random_generator = std::default_random_engine{ std::random_device{}() };

Board Board::random() {
	Board b{};
	b.fill_board();
	std::array<int, max_index> idxs;
	std::iota(idxs.begin(), idxs.end(), 0);
	std::shuffle(idxs.begin(), idxs.end(), random_generator);
	for(auto i : idxs) {
		int x = b.get(i);
		b.set(i, 0);
		int count = b.solution_count();
		if(count > 1) {
			b.set(i, x);
		}
	}
	return b;
}

bool Board::fill_board(int i) {
	if(i == max_index) {
		return true;
	}
	if(get(i)) {
		return fill_board(i + 1);
	}
	int taken = 0;
	auto rowcol = index_to_row_col(i);
	auto row = rowcol.first;
	auto col = rowcol.second;
	auto boxnums = index_to_box_number(i);
	auto box = boxnums.first;
	for(int j = 0; j < size; ++j) {
		taken |= bit(get(row, j));
		taken |= bit(get(j, col));
		taken |= bit(get_box(box, j));
	}
	std::array<int, size> xs;
	auto x = xs.begin();
	for(int j = 1; j <= size; ++j) {
		if(!(taken & bit(j))) {
			*x++ = j;
		}
	}
	auto xend = x;
	std::shuffle(xs.begin(), xend, random_generator);
	for(auto x = xs.cbegin(); x != xend; ++x) {
		set(i, *x);
		if(fill_board(i + 1)) return true;
	}
	set(i, 0);
	return false;
}

int Board::solution_count(int i, int count) {
	if(i == max_index) {
		return count + 1;
	}
	if(get(i)) {
		return solution_count(i + 1, count);
	}
	int taken = 0;
	auto rowcol = index_to_row_col(i);
	auto row = rowcol.first;
	auto col = rowcol.second;
	auto boxnums = index_to_box_number(i);
	auto box = boxnums.first;
	for(int j = 0; j < size; ++j) {
		taken |= bit(get(row, j));
		taken |= bit(get(j, col));
		taken |= bit(get_box(box, j));
	}
	for(int x = 1; x <= size; ++x) {
		if(taken & bit(x)) {
			continue;
		}
		set(i, x);
		count = solution_count(i + 1, count);
		if(count > 1) break;
	}
	set(i, 0);
	return count;
}

int Board::row_col_to_index(int row, int col) {
	if(row < 0 || row >= size) {
		throw std::out_of_range("row is out of range");
	}
	if(col < 0 || col >= size) {
		throw std::out_of_range("column is out of range");
	}
	return size * row + col;
}

std::pair<int, int> Board::index_to_row_col(int index) {
	if(index < 0 || index >= max_index) {
		throw std::out_of_range("index is out of range");
	}
	return { index / size, index % size };
}

int Board::box_number_to_index(int box, int box_idx) {
	if(box < 0 || box >= size) {
		throw std::out_of_range("box is out of range");
	}
	if(box_idx < 0 || box_idx >= size) {
		throw std::out_of_range("box index is out of range");
	}
	int box_row = box / box_size;
	int box_col = box % box_size;
	int row = box_size * box_row + (box_idx / box_size);
	int col = box_size * box_col + (box_idx % box_size);
	return row_col_to_index(row, col);
}

std::pair<int, int> Board::index_to_box_number(int index) {
	auto rowcol = index_to_row_col(index);
	int row = rowcol.first;
	int col = rowcol.second;
	int box_row = row / box_size;
	int box_col = col / box_size;
	row %= box_size;
	col %= box_size;
	int box = box_size * box_row + box_col;
	int box_idx = box_size * row + col;
	return { box, box_idx };
}

int Board::row_col_to_box_number(int row, int col) {
	return index_to_box_number(row_col_to_index(row, col)).first;
}

int Board::get(int index) const {
	return numbers.at(index);
}

int Board::get(int row, int col) const {
	int index = row_col_to_index(row, col);
	return numbers.at(index);
}

int Board::get_box(int box, int box_idx) const {
	int index = box_number_to_index(box, box_idx);
	return numbers.at(index);
}

void Board::set(int index, int value) {
	if(value < 0 || value > size) {
		throw std::out_of_range("value is out of range");
	}
	numbers.at(index) = value;
}

void Board::set(int row, int col, int value) {
	int index = row_col_to_index(row, col);
	set(index, value);
}

void Board::set_box(int box, int box_idx, int value) {
	int index = box_number_to_index(box, box_idx);
	set(index, value);
}

