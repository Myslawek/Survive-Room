#pragma once
#include "Enemies.h"

struct EnemyLinkedList
{
	Enemy currentEnemy;
	EnemyLinkedList *next;
	EnemyLinkedList(Enemy _currentEnemy) : currentEnemy(_currentEnemy), next(nullptr) {};
};

class EnemyContainer
{
public:
	EnemyContainer();
	~EnemyContainer();
	EnemyLinkedList *ReturnHead();
	EnemyLinkedList *ReturnTail();
	void AddNode(ENEMY_TYPE gvnType, unsigned int gvnDifficultyLevel);
	EnemyLinkedList *DeleteNode(EnemyLinkedList *gvnNode);
	void MoveEnemies(sf::Vector2f &gvnDestination, const float gvnFPS);
	void ThrowAttacks(ProjectileContainer &gvnContainer, sf::Vector2f &playerPosition);
	unsigned int ReturnSize();
private:
	EnemyLinkedList *head;
	EnemyLinkedList *tail;
	unsigned int size;
};