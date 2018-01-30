#include "Projectile.h"

Projectile::Projectile()
{
	maxLifeTime = sf::seconds(10.f);
}

//Projectile::Projectile(game_nmspc::Position2f gvnPosition,game_nmspc::Position2f gvnDirection)
//{
//	projectilePos = gvnPosition;
//	projectileDirection = gvnDirection;
//}

Projectile::Projectile(sf::Vector2f _projectileDestination, sf::Vector2f _projectilePosition)
{
	projectileDestination.x = _projectileDestination.x;	
	projectileDestination.y = _projectileDestination.y;
	projectilePosition = _projectilePosition;
}

//Projectile::Projectile(float _projectileSpeed, sf::Vector2f _projectileDestination, float _amountOfDamage, float _maxLifeTime, sf::Vector2f _projectilePosition, PROJECTILE_TYPE _projectileType): projectileSpeed(_projectileSpeed), projectileDestination(_projectileDestination), amountOfDamage(_amountOfDamage), projectilePosition(_projectilePosition), projectileType(_projectileType)
//{
//	maxLifeTime = sf::seconds(_maxLifeTime);
//}
//
//Projectile::Projectile(float _projectileSpeed, sf::Vector2f _projectileDestination, float _amountOfDamage, float _maxLifeTime, sf::Vector2f _projectilePosition, PROJECTILE_TYPE _projectileType, bool _isMovingUp, bool _isMovingDown, bool _isMovingRight, bool _isMovingLeft) : projectileSpeed(_projectileSpeed), projectileDestination(_projectileDestination), amountOfDamage(_amountOfDamage), projectilePosition(_projectilePosition), projectileType(_projectileType)
//{
//	maxLifeTime = sf::seconds(_maxLifeTime);
//}

//Projectile::Projectile(const Projectile &gvnProjectile)
//{
//	projectileSpeed = gvnProjectile.projectileSpeed;
//	amountOfDamage = gvnProjectile.amountOfDamage;
//	maxLifeTime = gvnProjectile.maxLifeTime;
//	projectileLifeTime.restart();
//}

Projectile::Projectile(const Projectile &gvnProjectile, sf::Vector2f _projectileDestination, sf::Vector2f _projectilePosition)
{
	projectileSpeed = gvnProjectile.projectileSpeed;
	amountOfDamage = gvnProjectile.amountOfDamage;
	maxLifeTime = gvnProjectile.maxLifeTime;
	projectileType = gvnProjectile.projectileType;
	projectileLifeTime.restart();
	projectileDestination = _projectileDestination;
	projectilePosition = _projectilePosition;
}

Projectile::~Projectile()
{
}

void Projectile::SetDamage(float _amountOfDamage)
{
	amountOfDamage = _amountOfDamage;
}

void Projectile::SetSpeed(float _projectileSpeed)
{
	projectileSpeed = _projectileSpeed;
}

void Projectile::SetDestination(sf::Vector2f _projectileDestination)
{
	projectileDestination = _projectileDestination;
}

void Projectile::SetLifeTime(float _maxLifeTime)
{
	maxLifeTime = sf::seconds(_maxLifeTime);
	projectileLifeTime.restart();
}

void Projectile::SetParameters(float _amountOfDamage, float _projectileSpeed, float _maxLifeTime)
{
	amountOfDamage = _amountOfDamage;
	projectileSpeed = _projectileSpeed;
	maxLifeTime = sf::seconds(_maxLifeTime);
	projectileLifeTime.restart();
}

void Projectile::SetProjectileType(PROJECTILE_TYPE _projectileType)
{
	projectileType = _projectileType;
}

void Projectile::SetProjectilePosition( sf::Vector2f &_projectilePosition)
{
	projectilePosition = _projectilePosition;
}

void Projectile::SetProjectileVectors( sf::Vector2f &_projectilePosition,  sf::Vector2f &_projectileDestination)
{
	projectilePosition = _projectilePosition;
	projectileDestination = _projectileDestination;
}

float Projectile::ReturnProjectileSpeed()
{
	return projectileSpeed;
}

sf::Vector2f Projectile::ReturnProjectileDestination()
{
	return projectileDestination;
}

float Projectile::ReturnAmountOfDamage()
{
	return amountOfDamage;
}

sf::Vector2f Projectile::ReturnProjectilePosition()
{
	return projectilePosition;
}

PROJECTILE_TYPE Projectile::ReturnProjectileType()
{
	return projectileType;
}

bool Projectile::CheckIfExceededMaxLifeTime()
{
	if (projectileLifeTime.getElapsedTime() > maxLifeTime)
		return true;
	return false;
}

void Projectile::SetBoundingBox(const sf::FloatRect gvnBoundingBox)
{
	projectileBoundingBox = gvnBoundingBox;
}

sf::FloatRect Projectile::ReturnBoundingBox()
{
	return projectileBoundingBox;
}