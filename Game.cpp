#include "Game.h"

Game::Game() : gameMainWindow(sf::VideoMode(800, 600), "Survive Room"), userPlayer("test", game_nmspc::PLAYER_STARTING_HP, game_nmspc::PLAYER_SPEED, game_nmspc::PLAYER_STARTING_AS), playerIsMovingUp(false), playerIsMovingDown(false), playerIsMovingRight(false), playerIsMovingLeft(false), killedEnemies(0), currentMapNumber(1), playerIsShootingUp(0), playerIsShootingDown(0), playerIsShootingRight(0), playerIsShootingLeft(0), difficultyLevel(1), gameBoundingBox(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y), gameScore(0)	//it does not work without initialization list, but why?
{
	gameMainWindow.setMouseCursorVisible(false);
	gameMainWindow.setVerticalSyncEnabled(false);
	timePerFrame = sf::seconds(1.f / game_nmspc::FRAMES_PER_SECOND); //60 frames per second
	applicationCurrentState = game_nmspc::MENU;
	if (!gameFont.loadFromFile("Fonts/arial.ttf"))
	{
		std::cout << "Error loading font!" << std::endl;
		applicationCurrentState = game_nmspc::TERMINATE;
	}
	if (userPlayer.ReturnErrorState())
	{
		std::cout << "Error loading player model!" << std::endl;
		applicationCurrentState = game_nmspc::TERMINATE;
	}
	if (gameMap.ReturnErrorState())
	{
		std::cout << "Error loading tile texture set!" << std::endl;
		applicationCurrentState = game_nmspc::TERMINATE;
	}
	if (!LoadProjectileSprite())
	{
		std::cout << "Error loading projectiles!" << std::endl;
		applicationCurrentState = game_nmspc::TERMINATE;
	}
	if (!LoadEnemyTexture())
	{
		std::cout << "Error loading enemies!" << std::endl;
		applicationCurrentState = game_nmspc::TERMINATE;
	}
	gameMap.LoadNewMap();
	PrepareMainMenu();
	PrepareUI();
}


void Game::RunApplication()
{
	 //std::cout << "Time Per Frame: " << TimePerFrame.asSeconds() << std::endl;
	while (gameMainWindow.isOpen())
	{
		//std::cout << "MAIN LOOP" << std::endl;
		switch (applicationCurrentState)
		{
		case game_nmspc::PLAY:
			RunGame();
			break;
		case game_nmspc::PAUSE:
			break;
		case game_nmspc::MENU:
			DrawMenu();
			break;
		case game_nmspc::HIGHSCORE:
			break;
		case game_nmspc::OPTIONS:
			break;
		case game_nmspc::GAME_OVER:
			DrawGameOver();
			break;
		case game_nmspc::TERMINATE:
			gameMainWindow.close();
			break;
		}
		//ProcessEvents();
	}

}

void Game::RunGame()	//main function for the game
{
	ProcessGameEvents();
	timeSinceLastUpdate += clock.restart();	//returns the value since the last clock.restart()
	while (timeSinceLastUpdate > timePerFrame)
	{
		timeSinceLastUpdate -= timePerFrame;
		ProcessGameEvents();
		CheckPlayerCollisions();
		ProcessPlayerStatuses();	//it can also be in render game function which will make more frequent calls (but why)
		UpdatePlayer();
		ProcessEnemies();
		ProcessProjectiles();
		//std::cout << "x: " << userPlayer.ReturnSprite().getPosition().x << "y: " << userPlayer.ReturnSprite().getPosition().y << std::endl;
	}
	RenderGame();
}

void Game::UpdatePlayer()
{
	sf::Vector2f movement(0.f, 0.f);
	if (playerIsMovingUp)
		movement.y -= userPlayer.ReturnMovementSpeed();
	if (playerIsMovingDown)
		movement.y += userPlayer.ReturnMovementSpeed();
	if (playerIsMovingRight)
		movement.x += userPlayer.ReturnMovementSpeed();
	if (playerIsMovingLeft)
		movement.x -= userPlayer.ReturnMovementSpeed();
	

	userPlayer.MoveSprite(movement*timePerFrame.asSeconds());

	if (playerIsShootingDown || playerIsShootingLeft || playerIsShootingRight || playerIsShootingUp)
		userPlayer.ThrowPlayerAttack(playerIsShootingUp, playerIsShootingDown, playerIsShootingRight, playerIsShootingLeft, existingProjectiles);

}

void Game::ProcessGameEvents()
{
	sf::Event applicationEvent;
	while (gameMainWindow.pollEvent(applicationEvent))	//check for events in queue
	{
		switch (applicationEvent.type)
		{
		case sf::Event::KeyPressed:
			HandleGameInput(applicationEvent.key.code, true);
			break;
		case sf::Event::KeyReleased:
			HandleGameInput(applicationEvent.key.code, false);
			break;
		case sf::Event::Closed:
			gameMainWindow.close();
			break;
		default:
			break;
		}
	}
	if (gameScore / 100 > difficultyLevel)
	{
		++difficultyLevel;
		std::cout << "difficulty level: " << difficultyLevel << std::endl;
	}
	if (difficultyLevel/3>(currentMapNumber-1))
	{
		++currentMapNumber;
		gameMap.ChangeMap(currentMapNumber);
		std::cout << "current map number: " << currentMapNumber << std::endl;
	}
		
		
}

void Game::HandleGameInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::W:
		playerIsMovingUp = isPressed;
		break;
	case sf::Keyboard::S:
		playerIsMovingDown = isPressed;
		break;
	case sf::Keyboard::D:
		playerIsMovingRight = isPressed;
		break;
	case sf::Keyboard::A:
		playerIsMovingLeft = isPressed;
		break;
	case sf::Keyboard::Up:
		playerIsShootingUp = isPressed;
		break;
	case sf::Keyboard::Down:
		playerIsShootingDown = isPressed;
		break;
	case sf::Keyboard::Right:
		playerIsShootingRight = isPressed;
		break;
	case sf::Keyboard::Left:
		playerIsShootingLeft = isPressed;
		break;
	case sf::Keyboard::P:
		//for future implementation 
		//applicationCurrentState = game_nmspc::PAUSE;
		//system("PAUSE");
		break;
	case sf::Keyboard::Space:
		//player shooting
		break;
	case sf::Keyboard::N:
		++currentMapNumber;
		gameMap.ChangeMap(currentMapNumber);
		break;
	case sf::Keyboard::Escape:
		applicationCurrentState = game_nmspc::MENU;
		break;
	default:
		break;
	}
}

void Game::PrepareMainMenu()
{
	for (int i = 0; i < game_nmspc::MAX_NUMBER_OF_OPTIONS; ++i)
	{
		menuOptions[i].setFont(gameFont);
		menuOptions[i].setFillColor(sf::Color::White);
		menuOptions[i].setPosition(10.f, 100.f*i + 5);
	}
	menuOptions[0].setFillColor(sf::Color::Red);
	menuOptions[0].setString("Play");
	menuOptions[1].setString("Highscores (not implemented yet)");
	menuOptions[2].setString("Options (not implemented yet)");
	menuOptions[game_nmspc::MAX_NUMBER_OF_OPTIONS - 1].setString("Exit");
	indexSelectedMenuOption = 0;
}

void Game::DrawMenu()
{
	//std::cout << "MENU LOOP" << std::endl;
	ProcessMenuEvents();
	gameMainWindow.clear(sf::Color(37, 37, 38, 255));
	for (int i = 0; i < game_nmspc::MAX_NUMBER_OF_OPTIONS; ++i)
		gameMainWindow.draw(menuOptions[i]);
	gameMainWindow.display();
	
}

void Game::ProcessMenuEvents()
{
	sf::Event menuEvent;
	while (gameMainWindow.pollEvent(menuEvent))
	{
		switch (menuEvent.type)
		{
		case sf::Event::KeyPressed:
			HandleMenuInput(menuEvent.key.code);
			break;
		case sf::Event::Closed:
			gameMainWindow.close();
			break;
		default:
			break;
		}
	}
}

void Game::HandleMenuInput(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::W:
		if (indexSelectedMenuOption > 0)
		{
			menuOptions[indexSelectedMenuOption].setFillColor(sf::Color::White);
			--indexSelectedMenuOption;
			menuOptions[indexSelectedMenuOption].setFillColor(sf::Color::Red);
		}
		break;
	case sf::Keyboard::S:
		if (indexSelectedMenuOption < game_nmspc::MAX_NUMBER_OF_OPTIONS-1)
		{
			menuOptions[indexSelectedMenuOption].setFillColor(sf::Color::White);
			++indexSelectedMenuOption;
			menuOptions[indexSelectedMenuOption].setFillColor(sf::Color::Red);
		}
		break;
	case sf::Keyboard::Return:
		switch (indexSelectedMenuOption)
		{
		case 0: 
			applicationCurrentState = game_nmspc::PLAY;
			break;
		case 1: 
			applicationCurrentState = game_nmspc::HIGHSCORE;
			break;
		case 2:
			applicationCurrentState = game_nmspc::OPTIONS;
			break;
		case 3:
			applicationCurrentState = game_nmspc::TERMINATE;
			break;
		}
		break;
	default:
		break;
	}
}

void Game::RenderGame()
{
	gameMainWindow.clear();
	gameMap.DrawLevel(gameMainWindow);
	gameMainWindow.draw(userPlayer.ReturnSprite());	//must be last! (as object)
	DrawEnemies();
	DrawProjectiles();
	DrawUI();
	gameMainWindow.display();
}

void Game::CheckPlayerCollisions()
{
	gameMap.CheckPlayerWithTileCollision(userPlayer);
	if (!gameBoundingBox.intersects(userPlayer.ReturnSprite().getGlobalBounds()))
		difficultyLevel = 100;
	CheckPlayerWithEnemyCollision();
	CheckProjectileWithPlayerCollision();
	CheckEnemyWithProjectileCollision();
}

void Game::DrawUI()
{
	textOfUI[0].setString("Health: "+std::to_string(userPlayer.ReturnEntityHealth()));
	textOfUI[1].setString("Points: " + std::to_string(gameScore));
	for (int i = 0; i < textOfUI.size(); ++i)
	{
		gameMainWindow.draw(textOfUI[i]);
	}
	//gameMainWindow.draw
}

void Game::PrepareUI()
{
	sf::Text tempUIData("Health: ", gameFont, 20);
	tempUIData.setFillColor(sf::Color(255, 255, 255));
	tempUIData.setPosition(5.f, 5.f);
	textOfUI.push_back(tempUIData);
	tempUIData.setString("Points: ");
	tempUIData.setPosition(WINDOW_SIZE.x - 180.f, 5.f);
	textOfUI.push_back(tempUIData);
}
//1. Player health
//2. 

void Game::ProcessPlayerStatuses()
{

	if (userPlayer.ReturnPlayerAffectingBlock() == LAVA)
	{
		textOfUI[0].setFillColor(sf::Color(255, 0, 0));
		if (userPlayer.GetPlayerElapsedTime() > sf::seconds(game_nmspc::PLAYER_LAVA_HP_DECREASE))	//if time is greater that 5 seconds
		{
			userPlayer.DecreaseHealth(5);
			userPlayer.RestartPlayerTimer();
		}
	}
	else
	{
		textOfUI[0].setFillColor(sf::Color(255, 255, 255));
	}
	if (userPlayer.ReturnEntityHealth() <= 0)
	{
		applicationCurrentState = game_nmspc::GAME_OVER;
	}
}

void Game::DrawGameOver()
{
	gameMainWindow.clear(sf::Color(0,0,0));
	sf::Text gameOverText("GAME OVER", gameFont, 50);
	sf::FloatRect boundingBox(gameOverText.getGlobalBounds());
	sf::Vector2f globalBox(gameMainWindow.getSize());
	gameOverText.setOrigin(boundingBox.left + boundingBox.width / 2, boundingBox.top + boundingBox.height / 2);
	gameOverText.setPosition(globalBox.x/2 ,globalBox.y/2);
	gameOverText.setFillColor(sf::Color(255, 0, 0));
	gameMainWindow.draw(gameOverText);
	gameOverText.setString("Your score: " + std::to_string(gameScore));
	gameOverText.setPosition(300, 100);
	gameOverText.setCharacterSize(20);
	gameMainWindow.draw(gameOverText);
	gameMainWindow.display();
	sf::Event gameOverEvent;
	gameMainWindow.pollEvent(gameOverEvent);
	if (gameOverEvent.KeyPressed&&gameOverEvent.key.code==sf::Keyboard::Escape)
	{
		applicationCurrentState = game_nmspc::TERMINATE;
	}
}

bool Game::LoadProjectileSprite()
{
	sf::Texture tempProjectileTexture;
	if (!tempProjectileTexture.loadFromFile("Textures/PlayerProjectile.png"))
		return false;
	projectilesTextures.push_back(tempProjectileTexture);
	if (!tempProjectileTexture.loadFromFile("Textures/EnemyProjectile.png"))
		return false;
	projectilesTextures.push_back(tempProjectileTexture);
	return true;
}

void Game::ProcessProjectiles()
{
	existingProjectiles.DeleteOutdatedNodes();
	existingProjectiles.MoveProjectiles(timePerFrame.asSeconds());
}

void Game::DrawProjectiles()
{
	sf::Vector2f tempProjectilePosition;
	sf::Sprite tempProjectileSprite;
	PROJECTILE_TYPE tempProjectileType = NO_PROJECTILE;
	sf::FloatRect projectileBoundingBox;
	ProjectileLinkedList *tempNode = existingProjectiles.ReturnHead();
	while (tempNode != nullptr)
	{
		//tempProjectilePosition = tempNode->currentProjectile.ReturnProjectilePosition();
		tempProjectileSprite.setPosition(tempNode->currentProjectile.ReturnProjectilePosition());
		if (tempProjectileType != tempNode->currentProjectile.ReturnProjectileType())
		{
			tempProjectileType = tempNode->currentProjectile.ReturnProjectileType();
			tempProjectileSprite.setTexture(projectilesTextures[tempProjectileType]);
			projectileBoundingBox = tempProjectileSprite.getGlobalBounds();
			tempProjectileSprite.setOrigin(projectileBoundingBox.width / 2.f, projectileBoundingBox.height / 2.f);
		}
		tempNode->currentProjectile.SetBoundingBox(tempProjectileSprite.getGlobalBounds());	//set new location and possible transformations of object
		gameMainWindow.draw(tempProjectileSprite);
		tempNode = tempNode->next;
	}
}

void Game::ProcessEnemies()
{
	if (existingEnemies.ReturnSize() < (game_nmspc::MAX_NUMBER_OF_ENEMIES + 2*difficultyLevel))
	{
		if (spawnerClock.getElapsedTime().asSeconds() >= (game_nmspc::SPAWNER_BASIC_TIME - game_nmspc::SPAWNER_BASIC_TIME*difficultyLevel / (10 + difficultyLevel)))	//some custom formula, to spawn more enemies for higher difficulty levels
		{
			//std::cout << "ENEMY SPAWNED!" << std::endl;
			existingEnemies.AddNode(BALLER, difficultyLevel);
			spawnerClock.restart();
		}
	}
	sf::Vector2f tempEnemyDestination(userPlayer.ReturnSprite().getPosition().x, userPlayer.ReturnSprite().getPosition().y);
	existingEnemies.MoveEnemies(tempEnemyDestination,timePerFrame.asSeconds());
	existingEnemies.ThrowAttacks(existingProjectiles, tempEnemyDestination);
}

void Game::DrawEnemies()
{
	EnemyLinkedList *temp = existingEnemies.ReturnHead();
	sf::Sprite tempSprite;
	ENEMY_TYPE tempEnemyType = NO_ENEMY;
	sf::FloatRect tempBoundingBox;
	while (temp != nullptr)
	{
		tempSprite.setPosition(temp->currentEnemy.ReturnEnemyPosition());
		if (tempEnemyType != temp->currentEnemy.ReturnEnemyType())
		{
			tempEnemyType = temp->currentEnemy.ReturnEnemyType();
			tempSprite.setTexture(enemiesTextures[tempEnemyType]);
			tempBoundingBox = tempSprite.getGlobalBounds();
			tempSprite.setOrigin(tempBoundingBox.width / 2.f, tempBoundingBox.height / 2.f);
			//tempProjectileSprite.setTexture(projectilesTextures[tempProjectileType]);
		}
		temp->currentEnemy.SetBoundingBox(tempSprite.getGlobalBounds());
		gameMainWindow.draw(tempSprite);
		temp = temp->next;
	}
}

bool Game::LoadEnemyTexture()
{
	sf::Texture tempEnemyTexture;
	if (!tempEnemyTexture.loadFromFile("Textures/Baller.png"))
		return false;
	enemiesTextures.push_back(tempEnemyTexture);
	return true;
}

void Game::CheckProjectileWithPlayerCollision()
{
	ProjectileLinkedList *temp = existingProjectiles.ReturnHead();
	sf::FloatRect playerBoundingBox = userPlayer.ReturnSprite().getGlobalBounds();
	while (temp != nullptr)
	{
		
		if (playerBoundingBox.intersects(temp->currentProjectile.ReturnBoundingBox())&&(temp->currentProjectile.ReturnProjectileType() != BALL))
		{
				userPlayer.DecreaseHealth(temp->currentProjectile.ReturnAmountOfDamage());
				temp = existingProjectiles.DeleteNode(temp);	//new node applied
		}
		else
			temp = temp->next;
	}
}

void Game::CheckEnemyWithProjectileCollision()
{
	EnemyLinkedList *tempEnemy = existingEnemies.ReturnHead();
	//ProjectileLinkedList *tempProjectileHead = existingProjectiles.ReturnHead();
	ProjectileLinkedList *tempProjectile = nullptr;
	sf::FloatRect enemyBoundingBox;
	sf::FloatRect projectileBoundingBox;
	bool enemyWasDeleted;
	while (tempEnemy != nullptr)
	{
		enemyWasDeleted = false;	//new loop, set flag to default value (the enemy might be deleted later, but not before this point)
		tempProjectile = existingProjectiles.ReturnHead();
		enemyBoundingBox = tempEnemy->currentEnemy.ReturnBoundingBox();
		while (tempProjectile != nullptr)
		{
			projectileBoundingBox = tempProjectile->currentProjectile.ReturnBoundingBox();
			if ((tempProjectile->currentProjectile.ReturnProjectileType() == BALL) && projectileBoundingBox.intersects(enemyBoundingBox))
			{
				tempEnemy->currentEnemy.DecreaseHealth(tempProjectile->currentProjectile.ReturnAmountOfDamage());
				tempProjectile = existingProjectiles.DeleteNode(tempProjectile);
				if (tempEnemy->currentEnemy.ReturnEntityHealth() <= 0)
				{
					tempEnemy = existingEnemies.DeleteNode(tempEnemy);
					enemyWasDeleted = true;
					gameScore = gameScore + 10 * difficultyLevel;
					break;
				}
			}
			else
				tempProjectile = tempProjectile->next;
		}
		if (enemyWasDeleted == false)	//if enemy was not deleted in this loop, the loop has to be iterated
			tempEnemy = tempEnemy->next;
	}
}

void Game::CheckPlayerWithEnemyCollision()
{
	EnemyLinkedList *temp = existingEnemies.ReturnHead();
	sf::FloatRect enemyBoundingBox;
	sf::FloatRect playerBoundingBox = userPlayer.ReturnSprite().getGlobalBounds();
	while (temp != nullptr)
	{
		enemyBoundingBox = temp->currentEnemy.ReturnBoundingBox();
		if (playerBoundingBox.intersects(enemyBoundingBox))
		{
			userPlayer.DecreaseHealth(1000000);
			return;
		}
			
		temp = temp->next;
	}
}