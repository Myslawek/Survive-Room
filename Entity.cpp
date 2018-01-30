#include "Entity.h"

float Entity::ReturnAttackSpeed() const
{
	return attackSpeed;
}

float Entity::ReturnEntityHealth() const
{
	return entityHealth;
}

float Entity::ReturnMovementSpeed() const
{
	return movementSpeed;
}

bool Entity::ReturnErrorState() const
{
	return criticalError;
}

void Entity::SetAttackSpeed(float uAttackSpeed)
{
	attackSpeed = uAttackSpeed;
	//return attackSpeed;
}

void Entity::SetEntityHealth(float uHealth)
{
	entityHealth = uHealth;
	//return entityHealth;
}


void Entity::SetMovementSpeed(float uMovementSpeed)
{
	movementSpeed = uMovementSpeed;
	//return movementSpeed;
}

void Entity::DecreaseHealth(const float gvnNumber)
{
	entityHealth -= gvnNumber;
}

bool Entity::CheckIfAbleToAttack()
{
	if (attackCooldown.getElapsedTime().asSeconds()>(1/attackSpeed))
	{
		attackCooldown.restart();
		return true;
	}
	return false;
}
