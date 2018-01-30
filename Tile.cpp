#include "Tile.h"

Tile::Tile()
{

}

void Tile::SetSprite(sf::IntRect gvnArea, sf::Texture &gvnTexture)
{
	tileSprite.setTexture(gvnTexture,false);
	tileSprite.setTextureRect(gvnArea);
}

sf::Sprite Tile::ReturnSprite()
{
	return tileSprite;
}