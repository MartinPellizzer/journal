#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

// -------------------------------------------------------------------------
// ;global
// -------------------------------------------------------------------------
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t is_running = 0;

// -------------------------------------------------------------------------
// ;init
// -------------------------------------------------------------------------
void init_sdl()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Ultima", 0, 0, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

// -------------------------------------------------------------------------
// ;input
// -------------------------------------------------------------------------
void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT:
		{
			is_running = 0;
		} break;
	}
}

// -------------------------------------------------------------------------
// ;main
// -------------------------------------------------------------------------
int main()
{
	init_sdl();

	is_running = 1;
	while(is_running)
	{
		process_input();
	}

	return 0;
}
