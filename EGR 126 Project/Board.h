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