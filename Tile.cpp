#include "Tile.h"
#include <SFML/Graphics.hpp>


Tile::Tile()
{
    collidable = false;
}

void Tile::initTexture(std::string texPath)
{
    tileTexture.loadFromFile(texPath);
    tileSprite.setTexture(tileTexture);
    sf::FloatRect rect = tileSprite.getLocalBounds();
    tileSprite.setOrigin(rect.width/2,rect.height/2);

}

void Tile::rotate(float angle)
{
    tileSprite.rotate(angle);
}

void Tile::draw(sf::RenderWindow &window)
{
    window.draw(tileSprite);
}

void Tile::setPosition(int x, int y)
{
    tileSprite.setPosition(x,y);
}

bool Tile::isCollidable()
{
    return collidable;
}

void Tile::setCollidable(bool c)
{
    collidable = c;
}

Tile::~Tile()
{
    //dtor
}
