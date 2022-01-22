#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "sds.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL2_gfxPrimitives.h"

#ifndef _GLOBAL_CONSTANTS
#define _GLOBAL_CONSTANTS

#define WINDOW_TITLE "Tetris_by_Bilguun.P"

#define BLOCK_SIZE 20

#define PLAYFIELD_HEIGHT 22
#define PLAYFIELD_WIDTH 12

#define WINDOW_HEIGHT PLAYFIELD_HEIGHT * (BLOCK_SIZE+1) +1
#define WINDOW_WIDTH PLAYFIELD_WIDTH * (BLOCK_SIZE+1) +1

#endif