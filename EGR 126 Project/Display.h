#pragma once

#include "Board.h"
#include "drawing.h"
#include "console_io.h"

class Display {
private:
	Board clues;
	Board guess;
	int cursor_row, cursor_col;

public:
	Display();

	void draw();
	bool handle_input(int k);

private:
	void reset();
	void new_game();
};