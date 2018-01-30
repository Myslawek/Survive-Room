#pragma once
#include "Projectile.h"
#include <math.h>

struct ProjectileLinkedList
{
	Projectile currentProjectile;
	ProjectileLinkedList *next;
	ProjectileLinkedList(Projectile _currentProjectile) : currentProjectile(_currentProjectile), next(nullptr) {};
};

class ProjectileContainer
{
public:
	ProjectileContainer();
	~ProjectileContainer();
	ProjectileLinkedList *ReturnHead();
	ProjectileLinkedList *ReturnTail();
	void AddNode(Projectile &gvnProjectile);
	ProjectileLinkedList *DeleteNode(ProjectileLinkedList *gvnPointer);
	unsigned int ReturnSize();
	void DeleteOutdatedNodes();
	void MoveProjectiles(const float gvnFPS);
private:
	ProjectileLinkedList *head;
	ProjectileLinkedList *tail;
	unsigned int size;
};