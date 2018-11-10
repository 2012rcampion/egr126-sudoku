#include "Display.h"

Display::Display() : cursor_row(0), cursor_col(0) {
	const int height = 25;
	const int width = 39;
	setup_window("Sudoku", width, height);
	draw_board();

	new_game();
}

void Display::draw() {
	draw_cursor(cursor_row, cursor_col);
	for(int row = 0; row < Board::size; ++row) {
		for(int col = 0; col < Board::size; ++col) {
			int value = guess.get(row, col);
			char c = ' ';
			if(value > 0) {
				c = value + '0';
			}
			draw_cell(c, row, col);
		}
	}
}

bool Display::handle_input(int k) {
	switch(k) {
		case key::quit:
			return true;
		case key::up:
			if(cursor_row > 0) { --cursor_row; }
			break;
		case key::down:
			if(cursor_row < Board::size - 1) { ++cursor_row; }
			break;
		case key::left:
			if(cursor_col > 0) { --cursor_col; }
			break;
		case key::right:
			if(cursor_col < Board::size - 1) { ++cursor_col; }
			break;
		case key::erase:
			guess.set(cursor_row, cursor_col, 0);
			break;
		case key::restart:
			reset();
			break;
		case key::new_game:
			new_game();
			break;
		default:
			if('1' <= k && k <= '9') {
				guess.set(cursor_row, cursor_col, k - '0');
			}
			break;
	}
	return false;
}

void Display::reset() {
	guess = clues;
}

void Display::new_game() {
	Board empty;
	clues = empty;
	reset();
}

/*
int col = 0;
	int row = 0;
	bool move = true;
	bool quit = false;
	bool highlight = false;

	const int grid_width = 9;
	const int grid_height = 9;

	auto start = std::chrono::steady_clock::now();

	while(!quit) {
		const int k = get_key(100);
		switch(k) {
			case key::nothing:
				break;
			case key::quit:
				quit = true;
				break;
			case key::left:
				if(col > 0) --col;
				move = true;
				break;
			case key::right:
				if(col < grid_width - 1) ++col;
				move = true;
				break;
			case key::up:
				if(row > 0) --row;
				move = true;
				break;
			case key::down:
				if(row < grid_height - 1) ++row;
				move = true;
				break;
			case key::erase:
				draw_cell(' ', row, col);
				break;
			case 'H':
				highlight_cell(row, col, highlight);
				break;
			case 'X':
				highlight = !highlight;
				break;
			default:
				if('1' <= k && k <= '9') {
					draw_cell(static_cast<char>(k), row, col, highlight);
				}
				break;
		}
		if(move) {
			draw_cursor(row, col);
			move = false;
		}
		int seconds = std::chrono::ceil<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
		draw_time(seconds);
	}
*/
