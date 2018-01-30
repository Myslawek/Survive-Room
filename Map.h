#pragma once
#include <SFML\Graphics.hpp>
//#include <iostream>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "Constants.h"
#include "Player.h"



struct CollisionTile
{
	sf::Vector2f tilePosition;
	TILE_TYPE tileType;
};

struct MapTiles
{
	char currentTile;
	MapTiles *nextTile;
};

class Map
{
public:
	Map();
	~Map();
	void DrawLevel(sf::RenderWindow &gvnWindow);
	void LoadNewMap();
	void ChangeMap(unsigned int gvnMapNumber);
	void CheckPlayerWithTileCollision( Player &gvnPlayer);
	void SetObstacles();
	void SpawnItems();
	void SpawnEnemies();
	void CountScore();
	bool ReturnErrorState();
private:
	bool newMapIsLoaded;
	const int tileWidth = 32;
	const int tileHeight = 32;
	const int numberOfTiles = 5;
	//const int mapWidth = 640 / tileHeight;
	//const int mapHeight = 480 / tileHeight;
	std::vector<Tile> tileSet;
	std::vector<CollisionTile> collisionTilePos;
	sf::Texture tileTextureSet;
	bool criticalError;
	MapTiles *mapTileContent;
	MapTiles *lastMapTileContent;
	std::string mapLocalization;
private:
	void InsertTilesIntoVector();
	sf::Sprite GetTile(TILE_TYPE gvnTileType);
	MapTiles *PushBackTile(char c);
	TILE_TYPE FileCheckTileType(char c);
	
	//void SetCollisionTilePos(char c, sf::Vector2f);
};