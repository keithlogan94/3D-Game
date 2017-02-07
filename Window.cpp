#include "Window.h"



Window::Window()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "error init sdl";
		abort();
	}
	win = SDL_CreateWindow(
		"3D Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1366,
		768,
		SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	if (!win) {
		cerr << "error creating window";
		abort();
	}
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ALPHA_SIZE, 8);

	context = SDL_GL_CreateContext(win);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cerr << "error init glew";
		abort();
	}
	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, 512, 512);

	GLfloat vertices[] = {
	   -0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f,  0.5f, 0.0f  // Top   
	};

	glGenVertexArrays(1, &object.vertexArrayObject);
	glGenBuffers(1, &object.vertexBufferObject);

	glBindVertexArray(object.vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, object.vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glBindVertexArray(0);

	object.shader = new Shader("vert.fs", "frag.fs");
}


Window::~Window()
{
	delete object.shader;
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
		draw();
	} while (!shouldWindowClose());
}

void Window::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	object.shader->use();
	glBindVertexArray(object.vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	SDL_GL_SwapWindow(win);
}
