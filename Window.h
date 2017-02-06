#pragma once
#include <SDL.h>
#include <exception>
#include <iostream>
using namespace std;
class Window
{
	SDL_Window * win;
	SDL_Renderer * ren;
	int width = 1080, height = 640;
	const Uint8* keyBoardState = nullptr;
	Uint32 mouseState = 0;
	int mouseX = 0, mouseY = 0;
	SDL_Event event;
public:
	Window();
	~Window();
	void updateWindowState();
	bool shouldWindowClose();
	void loop();
};

