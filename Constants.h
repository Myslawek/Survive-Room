#pragma once
namespace game_nmspc	//in future move inside the class 
{
	const unsigned int MAX_NUMBER_OF_OPTIONS = 4;	//max number of menu options
	enum APPLICATION_STATE { MENU, PAUSE, PLAY, TERMINATE, HIGHSCORE, OPTIONS, GAME_OVER };
	const float PLAYER_SPEED = 160;
	const float PLAYER_LAVA_HP_DECREASE = 3.f;
	const float PLAYER_STARTING_HP = 100;	//starting health points
	const float PLAYER_STARTING_AS = 1;	//starting attack speed
	const float ENEMY_DIFFICULTY_SCALAR = 1;
	const float PLAYER_STARTING_DAMAGE = 10;
	const float PLAYER_STARTING_PROJECTILE_SPEED = 100;
	const float FRAMES_PER_SECOND = 60.f;
	const float SPAWNER_BASIC_TIME = 5.f; //value in seconds
	const int MAX_NUMBER_OF_ENEMIES = 10;//just for safety, too many enemies might cause too much computations or consume to much RAM
	struct Position2f
	{
		float x;
		float y;
		Position2f() {};
		Position2f(float _x, float _y) : x(_x), y(_y) {};
	};
}
enum TILE_TYPE { GRASS, WATER, LAVA, HOLE, BARRICADE };
enum PROJECTILE_TYPE { BALL, ENEMY_BALL, NO_PROJECTILE };
enum ENEMY_TYPE { BALLER, NO_ENEMY };
const sf::Vector2f WINDOW_SIZE(800.f, 600.f);	//800x600 screen