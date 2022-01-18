#include "input.h"

void getInput(){
	SDL_Event event;

	while (SDL_PollEvent(&event)){
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				exit(0);
				break;
			case SDLK_s:
			case SDLK_DOWN:
				SHAPE_ACTION = DOWN;
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				SHAPE_ACTION = RIGHT;
				break;

			case SDLK_a:
			case SDLK_LEFT:
				SHAPE_ACTION = LEFT;
				break;

			case SDLK_w:
			case SDLK_UP:
				SHAPE_ACTION = ROTATE;
				break;

			case SDLK_r:
				SHAPE_ACTION = RESTART;
				break;

			case SDLK_SPACE:
				SHAPE_ACTION = DROP;
				break;

			default:
				break;
			}
			break;

		case SDL_KEYUP:
			SHAPE_ACTION = NONE;
			break;
		case SDL_USEREVENT:
			SHAPE_ACTION = AUTO_DROP;
			break;
		default:
			break;
		}
	}
}
