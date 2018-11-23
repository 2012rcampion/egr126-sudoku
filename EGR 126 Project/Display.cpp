#include "Display.h"

Display::Display() : cursor_row(0), cursor_col(0), board_changed(true), cursor_moved(true), solved(false) {
	const int height = 25;
	const int width = 39;
	setup_window("Sudoku", width, height);
	new_game();
}

void Display::draw() {
	if(board_changed) {
		solved = guess.solved();
	}
	if(cursor_moved) {
		draw_cursor(cursor_row, cursor_col);
	}
	if(board_changed || cursor_moved) {
		int selection = guess.get(cursor_row, cursor_col);
		for(int row = 0; row < Board::size; ++row) {
			for(int col = 0; col < Board::size; ++col) {
				int value = guess.get(row, col);
				char c = ' ';
				if(value > 0) {
					c = value + '0';
				}
				draw_cell(c, row, col, clues.get(row, col) != 0);
				highlight_cell(row, col, selection != 0 && value == selection && !solved);
			}
		}
	}
	cursor_moved = false;
	board_changed = false;
	if(solved) {
		draw_win();
	}
	else {
		int seconds = std::chrono::floor<std::chrono::seconds>(clock::now() - start_time).count();
		draw_time(seconds);
	}
}

bool Display::handle_input(int k) {
	switch(k) {
		case key::quit:
			return true;
		case key::up:
			if(cursor_row > 0) {
				--cursor_row;
				cursor_moved = true;
			}
			break;
		case key::down:
			if(cursor_row < Board::size - 1) {
				++cursor_row;
				cursor_moved = true;
			}
			break;
		case key::left:
			if(cursor_col > 0) {
				--cursor_col;
				cursor_moved = true;
			}
			break;
		case key::right:
			if(cursor_col < Board::size - 1) {
				++cursor_col;
				cursor_moved = true;
			}
			break;
		case key::erase:
			if(clues.get(cursor_row, cursor_col) == 0 && !solved) {
				guess.set(cursor_row, cursor_col, 0);
				board_changed = true;
			}
			break;
		case key::restart:
			reset();
			break;
		case key::new_game:
			new_game();
			break;
		default:
			if('1' <= k && k <= '9') {
				if(clues.get(cursor_row, cursor_col) == 0 && !solved) {
					int previous_guess = guess.get(cursor_row, cursor_col);
					guess.set(cursor_row, cursor_col, k - '0');
					if(guess.check_row(cursor_row) &&
					   guess.check_col(cursor_col) &&
					   guess.check_box(Board::row_col_to_box_number(cursor_row, cursor_col))) {
						board_changed = true;
					}
					else {
						guess.set(cursor_row, cursor_col, previous_guess);
					}
				}
			}
			break;
	}
	return false;
}

void Display::reset() {
	guess = clues;
	board_changed = true;
	solved = false;
	draw_board();
}

void Display::new_game() {
	clues = Board::random();
	start_time = clock::now();
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

	}
*/
