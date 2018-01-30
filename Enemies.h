#pragma once
#include <ctime>
#include <cstdlib>
#include "Entity.h"


class Enemy: public Entity
{
public:
	Enemy();
	~Enemy();
	void ThrowAttack(ProjectileContainer &gvnContainer, const sf::Vector2f &gvnDestination);
	void SetEnemyPosition(const sf::Vector2f &gvnPosition);
	sf::Vector2f ReturnEnemyPosition();
	ENEMY_TYPE ReturnEnemyType();
	void SetBoundingBox(const sf::FloatRect gvnBoundingBox);
	sf::FloatRect ReturnBoundingBox();
protected:
	ENEMY_TYPE enemyType;	//just to avoid runtime cast checks
	sf::Vector2f enemyPosition;
	sf::FloatRect enemyBoundingBox;
};

class Baller : public Enemy
{
public:
	Baller(const unsigned int difficultyLevel);
};

class Cloud : public Enemy
{

};

class Slime : public Enemy
{

};

class Boss : public Enemy
{
public:
	Boss(std::string uName, float uHealth, float uMovementSpeed, float uAttackSpeed)
	{
		entityName = uName;
		entityHealth = uHealth;
		movementSpeed = uMovementSpeed;
		attackSpeed = uAttackSpeed;
	}
private:
	std::string sth;
};