#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include "string.h"


class animation
{
    public:
        animation();
        virtual ~animation();

        sf::Sprite sprite;
        sf::Texture texture;
        int currentFrame;
        int row;
        int width;
        int height;
        float frameTime;
        float currentTime;
        int totalWidth;
        int totalHeight;


        void setTexture(std::string filePath);
        void update(float timeBetweenFrames); // IN MILLISECONDS
        void resetOrientation(int scale);
        void setPosition(int x,int y);
        void draw(sf::RenderWindow &window);
        void setIdle();
        void init(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime);





    protected:
    private:
};

#endif // ANIMATION_H
