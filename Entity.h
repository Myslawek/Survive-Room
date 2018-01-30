#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
//#include "Projectile.h"
#include "Constants.h"
#include "ProjectileContainer.h"


class Entity
{
public:
	float ReturnEntityHealth() const;
	float ReturnMovementSpeed() const;
	float ReturnAttackSpeed() const;
	bool ReturnErrorState() const;
	void SetEntityHealth(float uHealth);
	void SetMovementSpeed(float uMovementSpeed);
	void SetAttackSpeed(float uAttackSpeed);
	 //function which takes care of moving sprites
	void DecreaseHealth(const float gvnNumber);
	bool CheckIfAbleToAttack();
	//sound
protected:
	std::string entityName;
	Projectile entityProjectile;
	float entityHealth;
	float movementSpeed;	//movement per frame
	float attackSpeed;
	sf::Clock attackCooldown;
	bool criticalError;
};