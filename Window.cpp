#include "Window.h"



Window::Window()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		cerr << "error: init sdl";
		throw exception{};
	}
	SDL_CreateWindowAndRenderer(width, height, SDL_WindowFlags::SDL_WINDOW_RESIZABLE, &win, &ren);
	if (!win || !ren){
		cerr << "window not created";
		throw std::exception{};
	}
	SDL_ShowWindow(win);
}


Window::~Window()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void Window::updateWindowState()
{
	SDL_GetWindowSize(win, &width, &height);
	keyBoardState = SDL_GetKeyboardState(0);
	mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_PollEvent(&event);
	SDL_UpdateWindowSurface(win);
}

bool Window::shouldWindowClose()
{
	return keyBoardState[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT;
}

void Window::loop()
{
	do {
		updateWindowState();
	} while (!shouldWindowClose());
}
