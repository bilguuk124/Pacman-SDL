#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define SCROLL_SPEED 300

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdbool.h>

int main(void){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}
	printf("Initialization successful! \n");

	SDL_Window* win = SDL_CreateWindow("Hello, CS50!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT, 0);
	SDL_Delay(100);
	if(!win){
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	if(!rend){
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	SDL_Surface* surface = IMG_Load("resources/hello.png");
	if(!surface){
		printf("Error creating surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		printf("Error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	bool is_running = true;
	SDL_Event event;
	SDL_Rect dest;
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	dest.x = (WINDOW_WIDTH-dest.w) /2;
	float y_pos = WINDOW_HEIGHT;

	while(is_running){
		while(dest.y >= -dest.h && SDL_PollEvent(&event) != 0){
			SDL_RenderClear(rend);
			dest.y = (int) y_pos;
			SDL_RenderCopy(rend, tex, NULL, &dest);
			SDL_RenderPresent(rend);
			if(event.type == SDL_QUIT){
				is_running = false;
			}
			y_pos -= (float) SCROLL_SPEED/60;

		}

	}


	
	SDL_DestroyWindow(win);
	SDL_Quit();
}