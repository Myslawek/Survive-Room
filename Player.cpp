#include "Player.h"

Player::Player(std::string uName, float uHealth, float uMovementSpeed, float uAttackSpeed): playerAffectingBlock(GRASS)
{
	entityName = uName;
	entityHealth = uHealth;
	attackSpeed = uAttackSpeed;
	movementSpeed = uMovementSpeed;
	criticalError = false;
	if (!entityTexture.loadFromFile("Textures/Player2.png"))
		criticalError = true;
	entitySprite.setTexture(entityTexture);
	auto playerSize = entitySprite.getTextureRect();
	entitySprite.setOrigin(playerSize.width / 2.f, playerSize.height / 2.f);	//setting the origin of the player in his center
	entitySprite.setPosition(400.f, 300.f);
	entityProjectile.SetDamage(game_nmspc::PLAYER_STARTING_DAMAGE);
	entityProjectile.SetSpeed(game_nmspc::PLAYER_STARTING_PROJECTILE_SPEED);
	entityProjectile.SetProjectileType(BALL);
	//entitySprite.setColor(sf::Color(255, 0, 0));
	/*entitySprite.setPosition(player_nmscp::startingPoint);
	playerMaxHealth = player_nmscp::maxHealth;*/
} 

void Player::SetPlayerAffectingBlock(TILE_TYPE gvnTile)
{
	playerAffectingBlock = gvnTile;
}

sf::Time Player::GetPlayerElapsedTime()
{
	return playerTimer.getElapsedTime();
}

sf::Time Player::RestartPlayerTimer()
{
	return playerTimer.restart();
}

TILE_TYPE Player::ReturnPlayerAffectingBlock() const
{
	return playerAffectingBlock;
}

void Player::MoveSprite(sf::Vector2f entityMoveBy)
{
	entitySprite.move(entityMoveBy);
}

sf::Sprite Player::ReturnSprite()
{
	return entitySprite;
}

void Player::ThrowPlayerAttack(bool _isShootingUp, bool _isShootingDown, bool _isShootingRight, bool _isShootingLeft, ProjectileContainer &gvnContainer)
{
	if (!CheckIfAbleToAttack())
		return;
	sf::Vector2f projectileDirection;
	projectileDirection.x = float(_isShootingRight) - float(_isShootingLeft);	//value true of bool is one, so this one, it is possible to decide which direction should the projectile go
	projectileDirection.y = float(_isShootingDown) - float(_isShootingUp);
	if ((projectileDirection.x == 0) && (projectileDirection.y == 0))
		return;
	gvnContainer.AddNode(Projectile(entityProjectile, projectileDirection, entitySprite.getPosition()));
}