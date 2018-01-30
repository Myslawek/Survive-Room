#include "Map.h"

Map::Map() : criticalError(false), mapTileContent(nullptr), newMapIsLoaded(false), mapLocalization("Maps/map1.map")
{
	if (!tileTextureSet.loadFromFile("Textures/TileSet.png"))
		criticalError = true;
	InsertTilesIntoVector();
}

Map::~Map()
{
	lastMapTileContent = nullptr;
	while (mapTileContent != nullptr)
	{
		lastMapTileContent = mapTileContent->nextTile;
		delete mapTileContent;
		mapTileContent = lastMapTileContent;
	}
}

bool Map::ReturnErrorState()
{
	return criticalError;
}

void Map::InsertTilesIntoVector()
{
	Tile tempTile;
	for (int i = 0; i < numberOfTiles; ++i)
	{
		sf::IntRect innerTextureRect(i * tileWidth, 0, tileWidth, tileHeight);
		tempTile.SetSprite(innerTextureRect, tileTextureSet);
		tileSet.push_back(tempTile);
		innerTextureRect.left = (i+1)*32;
	}
}

void Map::DrawLevel(sf::RenderWindow &gvnWindow)
{
	sf::Sprite tempTileSprite;
	sf::Vector2f tilePosition(0.f, 0.f);
	CollisionTile tempColisionTile;
	MapTiles *tempMapTileContent = mapTileContent;
	char c;
	if (newMapIsLoaded == true)	//delete previous vector data, if none, then it would change nothing
	{
		collisionTilePos.clear();
	}
	while (tempMapTileContent != nullptr)
	{
		c = tempMapTileContent->currentTile;
		tempTileSprite = GetTile(FileCheckTileType(c));
		if (tilePosition.x + tileWidth > WINDOW_SIZE.x)
		{
			tilePosition.x = 0;
			tilePosition.y += tileHeight;
		}
		tempTileSprite.setPosition(tilePosition);
		gvnWindow.draw(tempTileSprite);
		if (newMapIsLoaded == true)
		{
			if (FileCheckTileType(c) == LAVA || FileCheckTileType(c) == WATER)
			{
				tempColisionTile.tilePosition = tilePosition;
				tempColisionTile.tileType = FileCheckTileType(c);
				collisionTilePos.push_back(tempColisionTile);
			}
		}
		tempMapTileContent = tempMapTileContent->nextTile;
		tilePosition.x += tileWidth;
	}
	newMapIsLoaded = false;
}

sf::Sprite Map::GetTile(TILE_TYPE gvnTileType)
{
	return tileSet[gvnTileType].ReturnSprite();
}

MapTiles *Map::PushBackTile(char c)
{
	MapTiles *tempTileContent = new MapTiles;
	tempTileContent->currentTile = c;
	tempTileContent->nextTile = nullptr;
	return tempTileContent;
}

void Map::LoadNewMap()
{
	std::ifstream sourceFile(mapLocalization);
	char c;
	if (!sourceFile.good())
	{
		criticalError = true;
		return;
	}
	sourceFile >> std::noskipws >> c;
	mapTileContent = new MapTiles;
	mapTileContent->currentTile = c;
	mapTileContent->nextTile=nullptr;
	lastMapTileContent = mapTileContent;
	while (sourceFile >> std::noskipws >> c)
	{
		if (isalpha(c))
		{
			lastMapTileContent->nextTile = PushBackTile(c);
			lastMapTileContent = lastMapTileContent->nextTile;
		}
		else
		{
			//handle future use
		}
	}
	newMapIsLoaded = true;
	sourceFile.close();
}

void Map::ChangeMap(unsigned int gvnMapNumber)
{
	mapLocalization[8] = gvnMapNumber + '0';
	std::ifstream sourceFile(mapLocalization);
	char c;
	if (!sourceFile.good())
	{
		criticalError = true;
		return;
	}
	lastMapTileContent = mapTileContent;
	while (sourceFile >> std::noskipws >> c)
	{
		if (isalpha(c))
		{
			if (lastMapTileContent != nullptr)
			{
				lastMapTileContent->currentTile = c;
				if (lastMapTileContent->nextTile != nullptr)
					lastMapTileContent = lastMapTileContent->nextTile;
			}
		}
	}
	newMapIsLoaded = true;
	sourceFile.close();
}

TILE_TYPE Map::FileCheckTileType(char c)
{
	switch (c)
	{
	case 'G':
		return GRASS;
	case 'W':
		return WATER;
	case 'L':
		return LAVA;
	case 'H':
		return HOLE;
	case 'B':
		return BARRICADE;
	}
	return GRASS;	//in case of wrong letter
}

void Map::CheckPlayerWithTileCollision(Player &gvnPlayer)
{
	sf::Sprite gvnPlayerSprite = gvnPlayer.ReturnSprite();
	sf::FloatRect playerBoundingBox = gvnPlayerSprite.getGlobalBounds();
	sf::FloatRect tileBoundingBox(0.f, 0.f, float(tileWidth), float(tileHeight));
	for (int i = 0; i < collisionTilePos.size(); ++i)
	{
		tileBoundingBox.left = collisionTilePos[i].tilePosition.x;
		tileBoundingBox.top = collisionTilePos[i].tilePosition.y;
		if (playerBoundingBox.intersects(tileBoundingBox))
		{
			gvnPlayer.SetPlayerAffectingBlock(collisionTilePos[i].tileType);
			//std::cout<< collisionTilePos[i].tileType << " TYPE COLLISION!" << std::endl;
			break;
		}
	}
}