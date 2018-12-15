#pragma once

#include "Board.h"
#include <chrono>

class Display {
private:
	Board clues;
	Board guess;
	int cursor_row, cursor_col;
	bool cursor_moved, board_changed, solved;
	typedef std::chrono::steady_clock clock;
	clock::time_point start_time;

public:
	Display();

	void draw();
	bool handle_input(int k);

private:
	void reset();
	void new_game();
};