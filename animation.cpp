#include "animation.h"
#include <SFML/Graphics.hpp>

animation::animation()
{
}

void animation::init(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime)
{
    currentFrame = 0;
    width = framewidth;
    height = frameheight;
    totalWidth = totalframewidth;
    totalHeight = totalframeheight;
    frameTime = frametime;
    currentTime = 0;
    row = 0;
}

void animation::setTexture(std::string filePath)
{
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setOrigin(width/2,height/2);

}

void animation::resetOrientation(int scale)
{
    sprite.setScale(scale,scale);
}

void animation::update(float timeBetweenFrames) // IN MILLISECONDS
{
    currentTime += timeBetweenFrames;
    if (currentTime >= frameTime)
    {



        if (currentFrame*width == totalWidth)
        {
            currentFrame = 0;
            row++;
        }

        if (row*height == totalHeight)
            row = 0;


        sprite.setTextureRect(sf::IntRect(currentFrame*width, row*height, width, height));
        currentFrame++;

        currentTime = 0;
    }


}

void animation::setPosition(int x, int y)
{
    sprite.setPosition(x,y);
}

void animation::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void animation::setIdle() //DO THIS
{

    currentFrame = 0;
    row = 0;
    sprite.setTextureRect(sf::IntRect(currentFrame*width, row*height, width, height));

}

animation::~animation()
{
    //dtor
}
