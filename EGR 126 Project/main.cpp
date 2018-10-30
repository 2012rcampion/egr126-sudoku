#include "console_io.h"
#include "drawing.h"
#include <string>
#include <fstream>
#include <chrono>
#include "Board.h"

const int height = 25;
const int width = 39;

int main(int argc, char* argv[]) {

	Board b;
	if (b.solved()) {
		// you win
	}
	else {
		// try again
	}

	setup_window("Sudoku", width, height);

	draw_board();
	
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

}