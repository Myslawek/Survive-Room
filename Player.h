#pragma once
//#include <iostream>
#include "Entity.h"
#include "Equipment.h"
#include "Constants.h"

class Player: public Entity
{
public:
	//Player();
	Player(std::string uName, float uHealth, float uMovementSpeed, float uAttackSpeed);
	void SetPlayerAffectingBlock(TILE_TYPE gvnTile);
	sf::Time GetPlayerElapsedTime();
	sf::Time RestartPlayerTimer();	//restarting clock returns some value, might be usefull
	TILE_TYPE ReturnPlayerAffectingBlock() const;
	void MoveSprite(sf::Vector2f entityMoveBy);
	sf::Sprite ReturnSprite();
	void ThrowPlayerAttack(bool _isShootingUp, bool _isShootingDown, bool _isShootingRight, bool _isShootingLeft, ProjectileContainer &gvnContainter);
private:
	float playerMaxHealth;
	TILE_TYPE playerAffectingBlock;
	sf::Clock playerTimer;
	sf::Sprite entitySprite;
	sf::Texture entityTexture;
};