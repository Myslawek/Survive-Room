#pragma once
#include <SFML\Graphics.hpp>
//default tile size is 32x32 px
class Tile
{
public:
	Tile();
	void SetSprite(sf::IntRect gvnArea, sf::Texture &gvnTexture);
	sf::Sprite ReturnSprite();
private:
	sf::Sprite tileSprite;
};