#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Enemies.h"
#include "Equipment.h"
#include "Map.h"
#include "Player.h"
#include "Projectile.h"
#include "Constants.h"
#include "ProjectileContainer.h"
#include "EnemyContainer.h"
//namespace game_nmspc	//in future move inside the class 
//{
//	const unsigned int MAX_NUMBER_OF_OPTIONS = 4;	//max number of menu options
//	enum APPLICATION_STATE { MENU, PAUSE, PLAY, TERMINATE, HIGHSCORE, OPTIONS };
//	const float PLAYER_SPEED = 80;
//}



class Game
{
public:
	Game();
	void RunApplication();
	void ShowScoreboard();
private:
	void RunGame();
	sf::RenderWindow gameMainWindow;
	sf::Font gameFont;
	sf::Text menuOptions[game_nmspc::MAX_NUMBER_OF_OPTIONS];
	sf::Clock clock; //it just starts the clock, which is counting the time since invoking it
	sf::Time timeSinceLastUpdate = sf::Time::Zero;	//set time as 0
	sf::Time timePerFrame;
	sf::Sprite projectileSprite;
	Player userPlayer;
	unsigned int indexSelectedMenuOption;
	game_nmspc::APPLICATION_STATE applicationCurrentState;
	bool playerIsMovingUp;
	bool playerIsMovingDown;
	bool playerIsMovingRight;
	bool playerIsMovingLeft;
	bool playerIsShootingUp;
	bool playerIsShootingDown;
	bool playerIsShootingRight;
	bool playerIsShootingLeft;
	Map gameMap;
	unsigned int killedEnemies;
	unsigned int currentMapNumber;
	std::vector<sf::Text> textOfUI;
	std::vector<sf::Texture> projectilesTextures;	//using sprites caused read problem, because sprite basicily is just a pointer tu texture
	std::vector<sf::Texture> enemiesTextures;
	ProjectileContainer existingProjectiles;
	EnemyContainer existingEnemies;
	sf::Clock spawnerClock;
	unsigned int difficultyLevel;
	sf::FloatRect gameBoundingBox;
	unsigned int gameScore;
	/*ProjectileLinkedList *headProjectileLinkedList;
	ProjectileLinkedList *tailProjectileLinkedList;*/
private:
	void ProcessGameEvents();
	void ProcessMenuEvents();
	void HandleGameInput(sf::Keyboard::Key key, bool isPressed);
	void HandleMenuInput(sf::Keyboard::Key key);
	void DrawMenu();
	void UpdatePlayer();
	void PrepareMainMenu();
	void RenderGame();
	void CheckPlayerCollisions();
	void DrawUI();
	void PrepareUI();
	void ProcessPlayerStatuses();
	void DrawGameOver();
	bool LoadProjectileSprite();
	void ProcessProjectiles();
	void DrawProjectiles();
	void ProcessEnemies();
	void DrawEnemies();
	bool LoadEnemyTexture();
	void CheckProjectileWithPlayerCollision();
	void CheckEnemyWithProjectileCollision();
	void CheckPlayerWithEnemyCollision();
	//void AddProjectileNode(const Projectile &gvnProjectile);
};