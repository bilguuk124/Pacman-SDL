#include "defs.h"
#include "utility.h"
#include "shuffle.h"
#include "graphics.h"

#ifndef _TETRIS_CONSTANTS
#define _TETRIS_CONSTANTS

typedef struct{
	uint16_t rotation[4];
	uint32_t color;
}Shape;

typedef struct {
	Shape type;

	uint8_t rotation;
	uint8_t x;
	uint8_t y;
}Shape_Movement;

typedef enum{
	NONE,
	DOWN,
	LEFT,
	RIGHT,
	DROP,
	ROTATE,
	AUTO_DROP,
	RESTART
}Tetris_Action;

typedef enum{
	EMPTY = 0xFFB3C0CC,
	TEAL = 0xFFFFDB7F,
	BLUE = 0xFFD97400,
	ORANGE = 0xFF1B85FF,
	YELLOW = 0xFF00DCFF,
	GREEN = 0xFF40CC2E,
	PURPLE = 0xFF4B1485,
	RED = 0xFF4B59F2
} Color_Block;

extern Tetris_Action SHAPE_ACTION;

const static Shape SHAPE_I = {
	{0x0F00, 0x2222, 0x00F0, 0x4444},
	TEAL
};

const static Shape SHAPE_J = {
	{0x8E00, 0x6440, 0x0E20, 0x44C0},
	BLUE
};

const static Shape SHAPE_L = {
	{0x2E00, 0x4460, 0x0E80, 0xC440},
	ORANGE
};
const static Shape SHAPE_O = {
	{0x6600, 0x6600, 0x6600, 0x6600},
	YELLOW
};
const static Shape SHAPE_S = {
	{0x6C00, 0x4620, 0x06C0, 0x8c40},
	GREEN
};

const static Shape SHAPE_T = {
	{0x4E00, 0x4640, 0x0E40, 0x4C40},
	PURPLE
};

const static Shape SHAPE_Z = {
	{0xC600, 0x2640, 0x0C60, 0x4C80},
	RED
};

static uint8_t CURRENT_SHAPE_COORDS[8] = {0};
static uint8_t GHOST_SHAPE_COORDS[8] = {0};

static Shape_Movement  CURRENT_SHAPE;

static Color_Block playfield[PLAYFIELD_HEIGHT*PLAYFIELD_WIDTH];

const static uint8_t lock_delay_threshold = 2;
static uint8_t lock_delay_count = 0;

static uint8_t shape_queue[7 * 4];
static uint8_t shape_queue_size = 7*4;
static uint8_t current_queue_index = 0;

static SDL_TimerID cb_timer = 0;

static int score = 0;

#endif

void draw_playing_field();
Color_Block get_playfield(uint8_t x, uint8_t y);
void set_playfield(uint8_t x, uint8_t y, Color_Block color);

void initTetris();
void updateTetris();
void lockShape();

void spawn_shape();
bool render_shape(Shape_Movement tetra_request, uint8_t current_coords[]);
bool render_current_shape(Shape_Movement tetra_request);
