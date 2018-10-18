#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include <string>

enum key {
	nothing = 0,
	quit = 'Q',
	restart = 'R',
	new_game = 'N',
	left = 0x25,
	up = 0x26,
	right = 0x27,
	down = 0x28,
	erase = 0x2E
};

int get_key(int timeout);

void setup_window(const std::string & title, int width, int height);

void move_cursor(int column, int row);

void write_string(const std::string & str, int column, int row);
void write_character(char c, int column, int row);

enum format {
	inverted = 1,
	not_inverted = 2,
	bold = 4,
	not_bold = 8
};

void format_character(int format, int column, int row);

#endif
