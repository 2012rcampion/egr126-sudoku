#include "drawing.h"
#include "console_io.h"
#include <utility>
#include <fstream>
#include <sstream>

std::pair<int, int> get_screen_coordinates(int row, int column) {
	return { 3 + 4 * column, 4 + 2 * row };
}

void draw_board() {
	std::string line;
	std::ifstream template_file("template.txt");
	for(int row = 0; template_file; ++row) {
		line.clear();
		std::getline(template_file, line);
		write_string(line, 0, row);
	}
}

void draw_time(int seconds) {
	const int max_seconds = 100 * 60 - 1;
	if(seconds > max_seconds) {
		seconds = max_seconds;
	}
	int minutes = seconds / 60;
	seconds = seconds % 60;
	std::stringstream output;
	output.width(2);
	output << minutes;
	output << ':';
	output.width(2);
	output.fill('0');
	output << seconds;
	write_string(output.str(), 17, 1);
}

void draw_cell(char c, int row, int col, bool emphasize) {
	auto xy = get_screen_coordinates(row, col);
	int x = xy.first;
	int y = xy.second;
	write_character(c, x, y);
	int format = emphasize ? format::bold : format::not_bold;
	format_character(format, x - 1, y);
	format_character(format, x + 0, y);
	format_character(format, x + 1, y);
}

void highlight_cell(int row, int col, bool highlight) {
	auto xy = get_screen_coordinates(row, col);
	int x = xy.first;
	int y = xy.second;
	write_character(highlight ? 221 : ' ', x - 1, y);
	write_character(highlight ? 222 : ' ', x + 1, y);
	int format = highlight ? format::inverted : format::not_inverted;
	format_character(format, x - 1, y);
	format_character(format, x + 0, y);
	format_character(format, x + 1, y);
}

void draw_cursor(int row, int col) {
	auto xy = get_screen_coordinates(row, col);
	int x = xy.first;
	int y = xy.second;
	move_cursor(x, y);
}
