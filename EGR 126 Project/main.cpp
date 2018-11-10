#include <string>
#include <fstream>
#include <chrono>
#include "Board.h"
#include "Display.h"


int main(int argc, char* argv[]) {
	Display d;

	bool exit = false;
	while(exit == false) {
		exit = d.handle_input(get_key(100));
		d.draw();
	}

	return 0;
}