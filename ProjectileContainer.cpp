#include "ProjectileContainer.h"
#include <iostream>

ProjectileContainer::ProjectileContainer() : head(nullptr), tail(nullptr), size(0)
{
}

ProjectileContainer::~ProjectileContainer()
{
	while (head != nullptr)
	{
		tail = head->next;
		delete head;
		head = tail;
	}
	size = 0;
}

ProjectileLinkedList *ProjectileContainer::ReturnHead()
{
	return head;
}

ProjectileLinkedList *ProjectileContainer::ReturnTail()
{
	return tail;
}

void ProjectileContainer::AddNode(Projectile &gvnProjectile)
{
	float vectorNorm = std::sqrt(gvnProjectile.ReturnProjectileDestination().x*gvnProjectile.ReturnProjectileDestination().x + gvnProjectile.ReturnProjectileDestination().y*gvnProjectile.ReturnProjectileDestination().y);
	if (vectorNorm <= 0)
		return;
	std::cout << "NODE IS BEING ADDED!" << "\tsize: " << size << std::endl;
	++size;
	if (head == nullptr)
	{
		head = new ProjectileLinkedList(gvnProjectile);
		//float vectorNorm = std::sqrt(head->currentProjectile.ReturnProjectileDestination().x*head->currentProjectile.ReturnProjectileDestination().x + head->currentProjectile.ReturnProjectileDestination().y*head->currentProjectile.ReturnProjectileDestination().y);
		//vectorNorm is needed to create unit vector, in order to avoid different speeds for different projectile angles
		head->currentProjectile.SetDestination(head->currentProjectile.ReturnProjectileDestination() / vectorNorm);
		tail = head;
	}
	else
	{
		tail->next = new ProjectileLinkedList(gvnProjectile);
		tail = tail->next;
		//float vectorNorm = std::sqrt(tail->currentProjectile.ReturnProjectileDestination().x*tail->currentProjectile.ReturnProjectileDestination().x + tail->currentProjectile.ReturnProjectileDestination().y*tail->currentProjectile.ReturnProjectileDestination().y);
		
		tail->currentProjectile.SetDestination(tail->currentProjectile.ReturnProjectileDestination() / vectorNorm);
	}
}

ProjectileLinkedList *ProjectileContainer::DeleteNode(ProjectileLinkedList *gvnPointer)
{
	ProjectileLinkedList *temp = nullptr;
	if (head == nullptr)
		return nullptr;
	if (head == gvnPointer)
	{
		//if (head == tail)	//in case of one element
		//	tail = tail->next;
		//code given above is not need, because in case of nullptr head, tail is changed when adding new node;
		temp = head;
		head = head->next;
		delete temp;
		--size;
		return head;	//element found and deleted
	}
	else
	{
		temp = head;
		while (temp->next != nullptr)
		{
			if (temp->next == gvnPointer)
			{
				ProjectileLinkedList *temp2 = temp->next;
				temp->next = temp->next->next;
				delete temp2;
				--size;
				return temp->next; //element found and deleted, so pass pointer to next element
			}
			temp = temp->next;
		}
	}
	return nullptr;	//element not found
}

unsigned int ProjectileContainer::ReturnSize()
{
	return size;
}

void ProjectileContainer::DeleteOutdatedNodes()
{
	if (head == nullptr)
	{
		//std::cout << "Head is nullptr!" << std::endl;
		return;
	}
		
	ProjectileLinkedList *temp = nullptr;//head->next;
	ProjectileLinkedList *tempPrevious = nullptr;//head;
	ProjectileLinkedList *tempToDelete = nullptr;
	while (head->currentProjectile.CheckIfExceededMaxLifeTime())
	{
		tempToDelete = head;
		head = head->next;
		delete tempToDelete;
		--size;
		//std::cout << "Deleted head!" << std::endl;
		//std::cout << "Size: " << size << std::endl;
		if (head == nullptr)
			return;
	}
	tempPrevious = head;
	temp = tempPrevious->next;
	while (temp != nullptr)
	{
		if (temp->currentProjectile.CheckIfExceededMaxLifeTime())
		{
			tempToDelete = temp;
			temp = temp->next;
			tempPrevious->next = temp;
			delete tempToDelete;
			--size;
			//std::cout << "Deleted inside!";
		}
		else
		{
			tempPrevious = tempPrevious->next;
			temp = tempPrevious->next;
		}
	}
}

void ProjectileContainer::MoveProjectiles(const float gvnFPS)
{
	ProjectileLinkedList *temp = head;
	while (temp != nullptr)
	{
		temp->currentProjectile.SetProjectilePosition(temp->currentProjectile.ReturnProjectilePosition() + temp->currentProjectile.ReturnProjectileDestination()*temp->currentProjectile.ReturnProjectileSpeed()*gvnFPS);
		//std::cout << "x: " << temp->currentProjectile.ReturnProjectilePosition().x << "\ny: " << temp->currentProjectile.ReturnProjectilePosition().y << std::endl;
		temp = temp->next;
	}
}