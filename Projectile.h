#pragma once
#include <SFML\Graphics.hpp>
#include "Constants.h"



class Projectile
{
public:
	Projectile();
	Projectile(game_nmspc::Position2f gvnPosition, game_nmspc::Position2f gvnDirection);
	Projectile(sf::Vector2f _projectileDestination, sf::Vector2f _projectilePosition);
	/*Projectile(float _projectileSpeed, sf::Vector2f _projectileDestination, float _amountOfDamage, float _maxLifeTime, sf::Vector2f _projectilePosition, PROJECTILE_TYPE _projectileType);
	Projectile(float _projectileSpeed, sf::Vector2f _projectileDestination, float _amountOfDamage, float _maxLifeTime, sf::Vector2f _projectilePosition, PROJECTILE_TYPE _projectileType, bool _isMovingUp, bool _isMovingDown, bool _isMovingRight, bool _isMovingLeft);*/
	Projectile(const Projectile &gvnProjectile, sf::Vector2f _projectileDestination, sf::Vector2f _projectilePosition);
	~Projectile();
	void SetDamage(float _amountOfDamage);
	void SetSpeed(float _projectileSpeed);
	void SetDestination(sf::Vector2f _projectileDestination);
	void SetLifeTime(float _maxLifeTime);
	void SetParameters(float _amountOfDamage, float _projectileSpeed, float _maxLifeTime);
	void SetProjectileType(PROJECTILE_TYPE _projectileType);
	void SetProjectilePosition( sf::Vector2f &_projectilePosition);
	void SetProjectileVectors( sf::Vector2f &_projectilePosition,  sf::Vector2f &_projectileDestination);
	float ReturnProjectileSpeed();
	sf::Vector2f ReturnProjectileDestination();
	float ReturnAmountOfDamage();
	sf::Vector2f ReturnProjectilePosition();
	PROJECTILE_TYPE ReturnProjectileType();
	bool CheckIfExceededMaxLifeTime();
	void SetBoundingBox(const sf::FloatRect gvnBoundingBox);
	sf::FloatRect ReturnBoundingBox();
private:
	float projectileSpeed;	//pixels per frame
	sf::Vector2f projectileDestination;
	sf::FloatRect projectileBoundingBox;
	float amountOfDamage;
	sf::Time maxLifeTime;	//denotes how long the projectile should last (game has no bounds)
	sf::Clock projectileLifeTime;
	sf::Vector2f projectilePosition;
	PROJECTILE_TYPE projectileType;
};