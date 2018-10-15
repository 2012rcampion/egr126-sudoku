#include "console_io.h"
#include <Windows.h>
#include <assert.h>

static HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE);
static HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

int get_key(int timeout) {
	if(timeout < 0) {
		timeout = INFINITE;
	}
	if(WaitForSingleObjectEx(input_handle, timeout, true) != WAIT_OBJECT_0) {
		return key::nothing;
	}
	DWORD number_of_inputs;
	GetNumberOfConsoleInputEvents(input_handle, &number_of_inputs);
	if(!number_of_inputs) {
		return key::nothing;
	}
	INPUT_RECORD input;
	ReadConsoleInput(input_handle, &input, 1, &number_of_inputs);
	assert(number_of_inputs == 1);
	if(input.EventType != KEY_EVENT || !input.Event.KeyEvent.bKeyDown) {
		return key::nothing;
	}
	switch(input.Event.KeyEvent.wVirtualKeyCode) {
		case VK_ESCAPE:
		case 'Q':
			return key::quit;
		case 'R':
			return key::restart;
		case 'N':
			return key::new_game;
		case VK_BACK:
		case VK_DELETE:
		case VK_SPACE:
			return key::erase;
		case VK_LEFT:
			return key::left;
		case VK_RIGHT:
			return key::right;
		case VK_DOWN:
			return key::down;
		case VK_UP:
			return key::up;
		default:
			return input.Event.KeyEvent.wVirtualKeyCode;
	}
}

void setup_window(const std::string & title, int width, int height) {
	// prevent autoscrolling
	DWORD mode;
	GetConsoleMode(output_handle, &mode);
	mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(output_handle, mode);
	// set title
	SetConsoleTitle(title.c_str());
	// set window size
	SMALL_RECT window_size = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(output_handle, TRUE, &window_size);
	COORD buffer_size = { width, height };
	SetConsoleScreenBufferSize(output_handle, buffer_size);
}

void move_cursor(int column, int row) {
	COORD position;
	position.X = column;
	position.Y = row;
	SetConsoleCursorPosition(output_handle, position);
}

void write_string(const std::string & str, int column, int row) {
	COORD position;
	position.X = column;
	position.Y = row;
	DWORD chars_written;
	WriteConsoleOutputCharacter(output_handle, str.c_str(), str.size(), position, &chars_written);
}

void write_character(char c, int column, int row) {
	COORD position;
	position.X = column;
	position.Y = row;
	DWORD chars_written;
	WriteConsoleOutputCharacter(output_handle, &c, 1, position, &chars_written);
}
