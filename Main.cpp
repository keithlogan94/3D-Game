#include "Window.h"
#include <iostream>
int main(int argc, char ** argv) {
	Window win;
	win.loop();

	std::cout << "all done!";
	return 0;
}