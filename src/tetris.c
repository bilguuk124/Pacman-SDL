#include "tetris.h"

// Главный механизм игры: контроллирует рендером и фигурой

void draw_playing_field(){
	int i;

	//Установить цвет рендеринга
	//Это устанавливает «цвет фона»
	SDL_SetRenderDrawColor(render, 204, 192, 179, 255);

	// Очистить рендер
	//'установить' цвет фона, определенный в SDL_SetRenderDrawColor(...)
	SDL_RenderClear(render);

	i = PLAYFIELD_WIDTH * PLAYFIELD_HEIGHT;
	while(i --> 0)
		set_playfield( i % PLAYFIELD_WIDTH, i /PLAYFIELD_WIDTH, playfield[i]);

	//Обновить экран
	setRenderChanged();
}

Uint32 auto_drop_timer (Uint32 interval, void* param){
	SDL_Event event;
	SDL_UserEvent userEvent;

	userEvent.type = SDL_USEREVENT;
	userEvent.code = 0;
	userEvent.data1 = NULL;
	userEvent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userEvent;

	SDL_PushEvent(&event);
	return interval;
}

//Инициализация игрвого механизма
void initTetris(){

	// Установить таймер
	if(cb_timer != 0){
		SDL_RemoveTimer(cb_timer);
	}
	cb_timer = 0;

	SHAPE_ACTION = NONE;


	// Очистить игровую площадку
	int i = PLAYFIELD_HEIGHT * PLAYFIELD_WIDTH;
	while(i --> 0){
		playfield[i] = EMPTY;
	}

	//Создать очередь фигур
	current_queue_index = 0;
	i = shape_queue_size;
	int n = 0;
	while(i --> 0){
		if((i+1) % 4 == 0){
			n++;
		}
		shape_queue[i] = n;
	}

	// Перетасываем очередь фигур
	shuffle(shape_queue, shape_queue_size, sizeof(uint8_t));

	draw_playing_field();

	spawn_shape();

}

// Функция зафиксирование фигуры на место
void lockShape(){
	lock_delay_count = 0;
	int i = 4;
	while( i--> 0){
		uint8_t x_coord = i * 2;
		uint8_t y_coord = x_coord + 1;
		uint8_t _x = CURRENT_SHAPE_COORDS[x_coord];
		uint8_t _y = CURRENT_SHAPE_COORDS[y_coord];

		CURRENT_SHAPE_COORDS[x_coord] = 0;
		CURRENT_SHAPE_COORDS[y_coord] = 0;

		set_playfield(_x,_y,CURRENT_SHAPE.type.color);
	}

	// Очищаем строку если строка полно
	uint8_t row = PLAYFIELD_HEIGHT;
	int8_t row_to_copy_to = -1;

	uint8_t completed_lines = 0;

	while(row --> 0){
		uint8_t col;
		bool complete_line = true;

		//Проверить полон ли строка
		for(col = 0; col < PLAYFIELD_WIDTH; col++){
			if(get_playfield(col, row) == EMPTY){
				complete_line = false;
				break;
			}
		}
		//Сама очистка
		if(complete_line){

			completed_lines++;

			if(row_to_copy_to < row){
				row_to_copy_to = row;
			}

			for(col = 0; col < PLAYFIELD_WIDTH; col++){
				set_playfield(col, row, EMPTY);
			}

		} else if(row_to_copy_to > row){
			for(col = 0; col < PLAYFIELD_WIDTH; col ++){
				set_playfield(col, row_to_copy_to, get_playfield(col, row));
			}

			row_to_copy_to--;
		}
	}

	// Добавляем количество очков
	if(completed_lines > 0){
		// Сразу 4 строк
		score += completed_lines/4 * 800;
		completed_lines = completed_lines % 4;
		// 3 строки
		score += completed_lines/3 * 500;
		completed_lines = completed_lines %3;
		// 2 строк
		score += completed_lines/2 * 300;
		completed_lines = completed_lines % 2;
		// 1 строк
		score += completed_lines * 100;
	}

	spawn_shape();
}

//Функция рендера кол-во очков
void render_score(){

	SDL_Color textColor = { 0x11, 0x1F, 0X3F};
	sds string_score = printfcomma(score);

	SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, string_score, textColor);
	sdsfree(string_score);

	if(textSurface == NULL){
		fprintf(stderr, "\nОшибка вывода текста на экран: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Texture* mTexture = SDL_CreateTextureFromSurface(render, textSurface);

	if(mTexture == NULL){
		fprintf(stderr, "\nОшибка создание текстур от текста: %s\n" , SDL_GetError());
		exit(1);
	}
	int mWidth = textSurface->w;
	int mHeight = textSurface->h;

	// Сам рендеринг
	SDL_Rect renderQuad = {WINDOW_WIDTH - mWidth - 10, 10 ,mWidth, mHeight};

	SDL_RenderCopy(render, mTexture,NULL,&renderQuad);

	SDL_DestroyTexture(mTexture);
	SDL_FreeSurface(textSurface);
}

// Функция обновление игры
void updateTetris(){
	if(cb_timer == 0){
		cb_timer = SDL_AddTimer(500, auto_drop_timer, NULL);
	}
	int i = 4;
	bool on_score_area = false;
	while (i --> 0){
		uint8_t x_coord = i*2;
		uint8_t y_coord = x_coord + 1;

		uint8_t _y = CURRENT_SHAPE_COORDS[y_coord];

		if(_y <= 2){
			on_score_area = true;
			break;
		}
	}
	if (on_score_area){
		int n = PLAYFIELD_WIDTH * 2 - 1;
		while( n--> 0 ) {
			int x = n % PLAYFIELD_WIDTH;
			int y = n / PLAYFIELD_WIDTH;

			set_playfield(x, y, get_playfield(x, y));
		}
		draw_playing_field();
		render_current_shape(CURRENT_SHAPE);
		render_score();
	}

	Shape_Movement  request = CURRENT_SHAPE;

	switch(SHAPE_ACTION){
	case NONE:
		break;

	case ROTATE:
		request.rotation = (request.rotation + 1) % 4;
		render_current_shape(request);
		break;

	case LEFT:
		request.x -= 1;
		render_current_shape(request);
		break;
	case RIGHT:
		request.x += 1;
		render_current_shape(request);
		break;
	case DROP:
		request.y += 1;
		while(render_current_shape(request)) request.y += 1;
		lockShape();
	case DOWN:
		request.y += 1;
		if(!render_current_shape(request)){
			lock_delay_count++;
		} else lock_delay_count = 0;
		break;

	case RESTART:
		initTetris();
		break;
	case AUTO_DROP:
		request.y += 1;
		if(!render_current_shape(request)){
			lock_delay_count++;
		} else{
			lock_delay_count = 0;
		}
		if(lock_delay_count >= lock_delay_threshold){
			lockShape();
		}
		break;
	}
	SHAPE_ACTION = NONE;
}

void spawn_shape(){
	current_queue_index++;
	if(current_queue_index >= shape_queue_size){
		current_queue_index = 0;
		shuffle (shape_queue, shape_queue_size, sizeof(uint8_t));
	}

	Shape type;
	switch(shape_queue[current_queue_index]){
	case 1:
		type = SHAPE_I;
		break;
	case 2:
		type = SHAPE_J;
		break;
	case 3:
		type = SHAPE_L;
		break;
	case 4:
		type = SHAPE_O;
		break;
	case 5:
		type = SHAPE_S;
		break;
	case 6:
		type = SHAPE_T;
		break;
	case 7:
		type = SHAPE_Z;
		break;
	}
	Shape_Movement shape_request = {
		type,
		0,
		3,0
	};
	if(!render_current_shape(shape_request)){
		initTetris();
	}
}

bool can_render_shape( Shape_Movement shape_request, uint8_t block_render_queue[]){
	uint16_t bit, piece;
	uint8_t row = 0, col = 0;

	piece = shape_request.type.rotation[shape_request.rotation];
	uint8_t x = shape_request.x;
	uint8_t y = shape_request.y;

	int i = 0;
	for(bit = 0x8000; bit > 0 && i < 8; bit = bit >> 1){
		if(piece & bit){
			uint8_t _x = x + col;
			uint8_t _y = y + row;
			if((_x < 0) || (_x >= PLAYFIELD_WIDTH) || (_y < 0) || (_y >= PLAYFIELD_HEIGHT) || get_playfield(_x, _y) != EMPTY){
				return false;
				break;
			} else {
				if(block_render_queue != NULL){
					block_render_queue[i * 2] = _x;
					block_render_queue[i * 2 + 1] = _y;
				}
				i++;
			}
		}
		col++;
		col = col % 4;
		if (col == 0){
			row++;
		}
	}
	return true;
}

bool render_current_shape(Shape_Movement shape_request){
	Shape ghost = shape_request.type;
	ghost.color = ghost.color & 0x00FFFFFF;
	ghost.color = ghost.color | 0x66000000;

	Shape_Movement ghost_request = shape_request;
	ghost_request.type = ghost;

	while(render_shape(ghost_request, GHOST_SHAPE_COORDS)) ghost_request.y += 1;
	shape_request.type.color = shape_request.type.color & 0x00FFFFFF;
	shape_request.type.color = shape_request.type.color | 0xE5000000;
	if(render_shape(shape_request, CURRENT_SHAPE_COORDS)){
		CURRENT_SHAPE = shape_request;

		return true;
	}
	return false;

}

bool render_shape(Shape_Movement shape_request, uint8_t current_coords[]){
	uint8_t block_render_queue[8] = {0};
	if(!can_render_shape(shape_request, block_render_queue)) return false;
	int i = 4;
	while(i --> 0){
		uint8_t x_coord = i * 2;
		uint8_t y_coord = x_coord + 1;

		uint8_t _x = current_coords[x_coord];
		uint8_t _y = current_coords[y_coord];

		draw_block(_x, _y, EMPTY);
	}

	 i = 4;
	while(i-->0){
		uint8_t x_coord = i * 2;
		uint8_t y_coord = x_coord + 1;

		uint8_t _x = block_render_queue[x_coord];
		uint8_t _y = block_render_queue[y_coord];

		current_coords[x_coord] = _x;
		current_coords[y_coord] = _y;

		draw_block(_x, _y, shape_request.type.color);

	}
	return true;
}
Color_Block get_playfield (uint8_t x, uint8_t y){
	return playfield[(y * PLAYFIELD_WIDTH) + x];
}

void set_playfield(uint8_t x, uint8_t y, Color_Block color){
	playfield[(y*PLAYFIELD_WIDTH) + x] = color;
	draw_block(x, y, color);
}