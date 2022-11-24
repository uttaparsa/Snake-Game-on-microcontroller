#include "stm32f3xx_hal.h"
#include <stdio.h>
#include <string.h>
#include "LiquidCrystal.h"
#include "game.h"
#include "utils.h"
#include <stdlib.h>

GameData game_data;
char const dir_keys[] = DIR_KEYS;
int sbi = 0;
int sll = 0;
unsigned char FILL[] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F
};

unsigned char FOOD[] = {
  0x0A,
  0x0A,
  0x1F,
  0x0A
};

unsigned char EMPTY[] = {
  0x00,
  0x00,
  0x00,
  0x00
};

unsigned char headx;
unsigned char heady;
unsigned char tailx;
unsigned char taily;
unsigned char* snake_head;
unsigned char* snake_tail;


void create_custom_charater(unsigned char* upper_char ,unsigned char* lower_char , int num){
	unsigned char result[8];
	for(int i = 0 ; i < 4 ; ++i){
		result[i] = upper_char[i];
		result[i+4] = lower_char[i];
	}
	createChar(num , result);
}
void init_game_ground(){
	for(int i = 0 ; i < DISPLAY_LENGTH ; ++i){
		for(int j = 0 ; j < DISPLAY_HEIGHT ; ++j){
			game_data.game_ground[i][j] = 'e';
		}
	}
}
void init_snake_body(){
	for(int i = 0 ; i < SNAKE_MAX_LENGTH ; ++i){
		game_data.snake_body[i][0] = 255;
		game_data.snake_body[i][1] = 255;
	}
}
void generate_random_food(){
	
	do{
		game_data.foodx = rand()%DISPLAY_LENGTH;
		game_data.foody = rand()%DISPLAY_HEIGHT;
	}while(game_data.game_ground[game_data.foodx][game_data.foody] != 'e');
	
	game_data.game_ground[game_data.foodx][game_data.foody] = 'f';
	
}

void display_food(){
	setCursor(game_data.foodx , game_data.foody/2);
	if(game_data.foody%2){
		unsigned char other_char = game_data.game_ground[game_data.foodx][game_data.foody-1];
		write(get_custom_character_id(other_char , 'f'));
	}else{
		unsigned char other_char = game_data.game_ground[game_data.foodx][game_data.foody+1];
		write(get_custom_character_id('f' , other_char));
	}
}
void update_snake_place(){
	for(int i =  game_data.length-1 ; i >= 1 ; --i){
		game_data.snake_body[i][0] = game_data.snake_body[i-1][0];
		game_data.snake_body[i][1] = game_data.snake_body[i-1][1];
	}
}

int get_custom_character_id(int upper_char  , int lower_char){
	if(upper_char == 'e' && lower_char  == 'f'){
		return EMPTY_FOOD;
	}else if(upper_char == 'f' && lower_char  == 'e'){
		return FOOD_EMPTY;
	}else if(upper_char == 'f' && lower_char  == 'b'){
		return FOOD_FILL;
	}else if(upper_char == 'b' && lower_char  == 'f'){
		return FILL_FOOD;
	}else if(upper_char == 'b' && lower_char  == 'b'){
		return FILL_FILL;
	}else if(upper_char == 'b' && lower_char  == 'e'){
		return FILL_EMPTY;
	}else if(upper_char == 'e' && lower_char  == 'b'){
		return EMPTY_FILL;
	}else{
		return EMPTY_EMPTY;
	}
}
void write_char(unsigned char x ,unsigned char y){
	setCursor(x , y/2);
	int character_id = EMPTY_EMPTY;
	if(y%2){
		character_id = get_custom_character_id(game_data.game_ground[x][y-1] , game_data.game_ground[x][y]);
	}else{
		character_id = get_custom_character_id(game_data.game_ground[x][y] , game_data.game_ground[x][y+1]);
	}
	
	if(character_id != EMPTY_EMPTY){
		write(character_id);
	}else{
		print(" ");
	}
}

void init_characters(void){
	create_custom_charater(FILL , EMPTY , FILL_EMPTY);
	create_custom_charater(EMPTY , FILL , EMPTY_FILL);
	create_custom_charater(FOOD , FILL , FOOD_FILL);
	create_custom_charater(FILL , FOOD , FILL_FOOD);
	create_custom_charater(FOOD , EMPTY , FOOD_EMPTY);
	create_custom_charater(EMPTY , FOOD , EMPTY_FOOD );
	create_custom_charater(FILL , FILL , FILL_FILL );
}
	


void init_default_game(){
	init_snake_body();
	init_game_ground();
	init_characters();
	game_data.score = 0;
	game_data.move_dir = 'd';
	game_data.speed = 0.5;
	game_data.length = DEFAULT_SNAKE_LENGTH;
	
	game_data.game_ground[4][2] = 'b';
	game_data.game_ground[2][2] = 'b';
	game_data.game_ground[3][2] = 'b';
	game_data.snake_body[0][0] = 4;
	game_data.snake_body[0][1] = 2;
	game_data.snake_body[1][0] = 3;
	game_data.snake_body[1][1] = 2;
	game_data.snake_body[2][0] = 2;
	game_data.snake_body[2][1] = 2;
	game_data.increase_len = 0;
	game_data.counter = 0;
	snake_head = game_data.snake_body[0];
	snake_tail = game_data.snake_body[game_data.length-1];
	
	draw_snake_body();
	generate_random_food();
	display_food();
}

void load_game_from_receive_buffer(){
	init_snake_body();
	init_game_ground();
	int stringLookupLevel = 0; 
	int snake_body_index = 0;
	for (int i = 0; i < strlen((char*)reshte); ++i) {
		if ((int)reshte[i] < 170) {
			int data = (int)reshte[i]-1;
			if (stringLookupLevel == 0) {
				int x = data % DISPLAY_LENGTH;
				int y = data / DISPLAY_LENGTH;
				game_data.game_ground[x][y] = 'b';
				game_data.snake_body[snake_body_index][0] = x;
				game_data.snake_body[snake_body_index][1] = y;
				++snake_body_index;
				sbi = snake_body_index;
			}else if (stringLookupLevel == 1) {
				int x = data % DISPLAY_LENGTH;
				int y = data / DISPLAY_LENGTH;
				game_data.game_ground[x][y] = 'f';
				game_data.foodx = x;
				game_data.foody = y;
				display_food();
			}else if (stringLookupLevel == 2) {
				game_data.move_dir  = (char)data;
			}else if (stringLookupLevel == 3) { // speed
				game_data.speed  = ((float)data)/10.0f;
			}else if (stringLookupLevel == 4) { // score
				game_data.score  = ((int)data)*10.0;
			}
		}
		else {
			stringLookupLevel += 1;
		}
		sll = stringLookupLevel;
	}
	game_data.length = snake_body_index;
	game_data.counter = 0;
	snake_head = game_data.snake_body[0];
	snake_tail = game_data.snake_body[game_data.length-1];
	
	draw_snake_body();
}

void updateSnakePlace(){

	if(( game_data.counter%(int)(TIMER4_FREQUENCY / game_data.speed)) == 0 ){

		snake_head = game_data.snake_body[0];
		snake_tail = game_data.snake_body[game_data.length-1];

		if(!game_data.increase_len){
			game_data.game_ground[snake_tail[0]][snake_tail[1]] = 'e';
			write_char(snake_tail[0] , snake_tail[1]);
		}else{
			game_data.length += 1;
			snake_tail = game_data.snake_body[game_data.length-1];
			game_data.increase_len = 0;
		}
		
		update_snake_place();
		switch(game_data.move_dir){
			case 'w':
				snake_head[1] = (snake_head[1] != 0) ?  snake_head[1] - 1 : DISPLAY_HEIGHT-1;
			break;
			case 'a':
				snake_head[0] = (snake_head[0] != 0) ?  snake_head[0] - 1 : DISPLAY_LENGTH-1;
			break;
			case 's':
				snake_head[1] = (snake_head[1] != DISPLAY_HEIGHT-1) ?  snake_head[1] + 1 : 0;
			break;
			case 'd':
				snake_head[0] = (snake_head[0] != DISPLAY_LENGTH-1) ?  snake_head[0] + 1 : 0;
			break;
		}
		
		if(snake_head_on_food()){
			game_data.increase_len=1;
			HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_9);
			generate_random_food();
			display_food();
			game_data.speed += 0.5;
			game_data.score += game_data.speed * (float)game_data.length;
		}
		if(self_collision()){
			extern TIM_HandleTypeDef htim4;
			HAL_TIM_Base_Stop_IT(&htim4);
			setCursor(0,0);
			char score_text[20];
			print("Game Over! ");
			sprintf(score_text, "Score : %d ",game_data.score);
			setCursor(0,1);
			print(score_text);
			return;
			
		}else{
			light_led();
		}
		game_data.game_ground[snake_head[0]][snake_head[1]] = 'b';
		write_char(snake_head[0] , snake_head[1]);
		
		extern UART_HandleTypeDef huart2;
		unsigned char* str = game_state_string();
		uart_send(&huart2 ,(char*)str );
		free(str);
	}
	++(game_data.counter);

	
}
void light_led(){
	int x = game_data.foodx - snake_head[0];
	int y = game_data.foody - snake_head[1];
	HAL_GPIO_WritePin(GPIOE , GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 , 0);
	if(x == 0){
		if(y > 0){
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_13 , 1);
		}else{
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_9 , 1);
		}
	}else if(y == 0){
		if(x > 0){
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_11 , 1);
		}else{
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_15 , 1);
		}
	}else if(x > 0){
		if(y > 0){
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_12 , 1);
		}else{
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_10 , 1);
		}
	}else{
		if(y > 0){
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_14 , 1);
		}else{
			HAL_GPIO_WritePin(GPIOE , GPIO_PIN_8 , 1);
		}
	}
	
}
void draw_snake_body(){
	for(int i = 0 ; i < game_data.length ; ++i){
		write_char(game_data.snake_body[i][0] , game_data.snake_body[i][1]);
	}

}

unsigned char* game_state_string(){
	unsigned char* result =  malloc(sizeof (char) * SNAKE_MAX_LENGTH);
	int i = 0;
	result[i++] = 201;
	for( ; i <= game_data.length ; ++i){
		result[i] = 1 + game_data.snake_body[i-1][0] + game_data.snake_body[i-1][1]*DISPLAY_LENGTH;
	}
	
	result[i++] = 200;
	result[i++] = 1 + game_data.foodx + game_data.foody*DISPLAY_LENGTH;
	
	result[i++] = 200;
	result[i++] = 1 + game_data.move_dir;
	
	result[i++] = 200;
	result[i++] = 1 + (int)game_data.speed*10;
	
	result[i++] = 200;
	result[i++] = 1 + game_data.score/10;
	
	result[i++] = 202;
	result[i] = '\0';
	return result;
}
int self_collision(){
	return game_data.game_ground[snake_head[0]][snake_head[1]] == 'b';
}

int get_snake_length(){
	return game_data.length;
}

float get_snake_speed(){
	return game_data.speed;
}
void set_snake_speed(float input){
	game_data.speed = input;
}
void set_snake_max_speed(float input){
	game_data.max_speed = input;
}
int snake_head_on_food(){
	return (snake_head[0] == game_data.foodx) && (snake_head[1] == game_data.foody);
}
void setMovDir(unsigned char input ){
	if(abs(strchr(dir_keys, input) -  strchr(dir_keys, game_data.move_dir)) != 2 ){
		game_data.move_dir = input;
	}
}

