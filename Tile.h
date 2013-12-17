#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    public:
        Tile();
        virtual ~Tile();
        sf::Sprite tileSprite;
        sf::Texture tileTexture;
        bool collidable;

        void initTexture(std::string texPath);
        void draw(sf::RenderWindow &window);
        void setPosition(int x, int y);
        void rotate(float angle);
        void setCollidable(bool c);

        bool isCollidable();


    protected:
    private:
};

#endif // TILE_H
