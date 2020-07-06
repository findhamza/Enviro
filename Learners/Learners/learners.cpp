#include "learners.h"

int main(int argc, const char* argv[]) {

	SDL_Window* window;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(
		"Learner SDL2 Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		576,
		SDL_WINDOW_OPENGL
	);

	if (window == NULL) {
		printf("ERROR CREATING WINDOW: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(3000);

	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}