#include "EnemyContainer.h"
//#include <iostream>

EnemyContainer::EnemyContainer() : head(nullptr), tail(nullptr), size(0)
{
}

EnemyContainer::~EnemyContainer()
{
	while (head != nullptr)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
	size = 0;
}

EnemyLinkedList *EnemyContainer::ReturnHead()
{
	return head;
}

EnemyLinkedList *EnemyContainer::ReturnTail()
{
	return tail;
}

void EnemyContainer::AddNode(ENEMY_TYPE gvnType, unsigned int gvnDifficultyLevel)
{
	++size;
	Enemy tempEnemy;
	switch (gvnType)
	{
	case BALLER:
		tempEnemy = Baller(gvnDifficultyLevel);
		break;
	default:
		tempEnemy = Baller(gvnDifficultyLevel); //in case of programmer error
		break;
	}
	if (head == nullptr)
	{
		head = new EnemyLinkedList(tempEnemy);
		tail = head;
	}
	else
	{
		tail->next = new EnemyLinkedList(tempEnemy);
		tail = tail->next;
	}
}

EnemyLinkedList *EnemyContainer::DeleteNode(EnemyLinkedList *gvnNode)
{
	EnemyLinkedList *temp = nullptr;
	if (head == gvnNode)
	{
		temp = head;
		head = head->next;
		delete temp;
		--size;
		return head;
	}
	else
	{
		temp = head;
		while (temp->next != nullptr)
		{
			if (temp->next == gvnNode)
			{
				EnemyLinkedList *temp2 = temp->next;
				temp->next = temp->next->next;
				delete temp2;
				--size;
				return temp->next;
			}
			temp = temp->next;
		}
	}
	return nullptr;
}

unsigned int EnemyContainer::ReturnSize()
{
	return size;
}

void EnemyContainer::MoveEnemies(sf::Vector2f &gvnDestination, const float gvnFPS)
{
	EnemyLinkedList *temp = head;
	sf::Vector2f unitVector;
	sf::Vector2f deltaMove;
	float vectorNorm;
	while (temp != nullptr)
	{
		unitVector = gvnDestination - temp->currentEnemy.ReturnEnemyPosition();
		vectorNorm = std::sqrt(unitVector.x * unitVector.x + unitVector.y * unitVector.y);
		if (vectorNorm<1)
		{
			temp = temp->next;
			continue;
		}
		unitVector = unitVector / vectorNorm;	//true unit vector
		deltaMove = unitVector * temp->currentEnemy.ReturnMovementSpeed() * gvnFPS;
		temp->currentEnemy.SetEnemyPosition(temp->currentEnemy.ReturnEnemyPosition() + deltaMove);
		//std::cout << "x: " << temp->currentEnemy.ReturnEnemyPosition().x << "\ny: " << temp->currentEnemy.ReturnEnemyPosition().y << std::endl;
		temp = temp->next;
	}
}

void EnemyContainer::ThrowAttacks(ProjectileContainer &gvnContainer, sf::Vector2f &playerPosition)
{
	EnemyLinkedList *tempEnemy = head;
	while (tempEnemy != nullptr)
	{
		tempEnemy->currentEnemy.ThrowAttack(gvnContainer, playerPosition);
		tempEnemy = tempEnemy->next;
	}
}

