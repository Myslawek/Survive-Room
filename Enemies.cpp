#include "Enemies.h"

Enemy::Enemy()
{
	srand(time(NULL));
	sf::Vector2f spawningPoint[4] = { sf::Vector2f(0,0),sf::Vector2f(WINDOW_SIZE.x,0),sf::Vector2f(0,WINDOW_SIZE.y),sf::Vector2f(WINDOW_SIZE.x,WINDOW_SIZE.y) };
	enemyPosition = spawningPoint[rand() % (4)];
	//enemyPosition = sf::Vector2f(400.f, 300.001);
}

Enemy::~Enemy()
{
}

void Enemy::ThrowAttack(ProjectileContainer &gvnContainer, const sf::Vector2f &gvnDestination)
{
	if (!CheckIfAbleToAttack())
		return;
	sf::Vector2f projectileDirection;
	projectileDirection = gvnDestination - enemyPosition;
	gvnContainer.AddNode(Projectile(entityProjectile, projectileDirection, enemyPosition));
	//projectileDirection
}

void Enemy::SetEnemyPosition(const sf::Vector2f &gvnPosition)
{
	enemyPosition = gvnPosition;
}

sf::Vector2f Enemy::ReturnEnemyPosition()
{
	return enemyPosition;
}

ENEMY_TYPE Enemy::ReturnEnemyType()
{
	return enemyType;
}

void Enemy::SetBoundingBox(const sf::FloatRect gvnBoundingBox)
{
	enemyBoundingBox = gvnBoundingBox;
}

sf::FloatRect Enemy::ReturnBoundingBox()
{
	return enemyBoundingBox;
}

Baller::Baller(const unsigned int difficultyLevel)
{
	//entityName = "Baller";
	entityHealth = 15.f + 1.f * difficultyLevel;		//3 is about 33% of basic health
	movementSpeed = 60 + 7 * difficultyLevel;	//16.67 is about 6% of basic speed
	attackSpeed = 0.5 + 0.5 * (difficultyLevel - 1);			//2 is 50% 
	entityProjectile.SetDamage(15 + 1 * (difficultyLevel - 1));	//0.1 is 10%
	entityProjectile.SetSpeed(80 + 15 * (difficultyLevel - 1));	//0.05 is 5%
	entityProjectile.SetProjectileType(ENEMY_BALL);
	entityProjectile.SetSpeed(80.f + 3.f * (difficultyLevel - 1));
	enemyType = BALLER;
}

