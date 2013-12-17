#include <iostream>
#include "AttackSpell.h"
#include "Tile.h"

const int MAP_HEIGHT = 250;
const int MAP_LENGTH = 500;

AttackSpell::AttackSpell()
{
    active = false;
    collidable = true;
    damage = 3;
}

void AttackSpell::initAnim(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime)
{
    spellAnim.init(framewidth, frameheight, totalframewidth, totalframeheight, frametime);
}

void AttackSpell::draw(sf::RenderWindow &window)
{
    spellAnim.draw(window);
}

void AttackSpell::setActive(bool b)
{
    active = b;
}

void AttackSpell::setPosition(int x, int y)
{
    actualX = x;
    actualY = y;

    xCoord = x;
    yCoord = y;

    spellAnim.setPosition(x,y);
}

void AttackSpell::setCollidable(bool b)
{
    collidable = b;
}

void AttackSpell::move(float x, float y)
{
    actualX += x;
    actualY += y;

    xCoord = (int)actualX;
    yCoord = (int)actualY;

    spellAnim.setPosition(xCoord, yCoord);
}

void AttackSpell::setType(std::string type[2])
{
    if(type[0] == "fireMage")
    {
        if(type[1] == "attack")
        {
            if(dir == "left")
                spellAnim.setTexture("images/spells/fireballLeft.png");
            else
                spellAnim.setTexture("images/spells/fireball.png");
        }
        else
            spellAnim.setTexture("images/spells/fireWall.png");
    }
    else if(type[0] == "waterMage")
    {
        if(type[1] == "attack")
            spellAnim.setTexture("images/spells/iceBlast.png");
        else
            spellAnim.setTexture("images/spells/icespike.png");
    }
    else if(type[0] == "earthMage")
    {
        if(type[1] == "attack")
            spellAnim.setTexture("images/spells/dirtBlast.png");
        else
            spellAnim.setTexture("images/spells/spikes.png");
    }
    else if(type[0] == "airMage")
    {
        if(type[1] == "attack")
        {
            if(dir == "left")
                spellAnim.setTexture("images/spells/lightningLeft.png");
            else
                spellAnim.setTexture("images/spells/lightning.png");

        }
        else
        {
            if(dir == "left")
                spellAnim.setTexture("images/spells/airPushLeft.png");
            else
                spellAnim.setTexture("images/spells/airPush.png");

        }
    }


}

void AttackSpell::initMusic(std::string path)
{
    sound.openFromFile(path);
    soundLoop = false;
}

void AttackSpell::playMusic()
{
    sound.play();
}

void AttackSpell::loop(bool b)
{
    sound.setLoop(b);
    soundLoop = b;
}

void AttackSpell::stopMusic()
{
    sound.stop();
}


void AttackSpell::init(int x, int y, int spellSpeed, float length, sf::Vector2i position, Tile *map[250][500])
{

    collidable = true;

    if(position.x > 400)
        dir = "right";
    else
        dir = "left";

    active = true;
    speed = spellSpeed;

    if(speed == 0)
    {

        xCoord = x+(position.x-400);
        yCoord = y+(position.y-300);
        actualX = x+(position.x-400);
        actualY = y+(position.y-300);

        int xMap = xCoord / 32;
        for(int i=yCoord/32; i < 250; i++)
        {
            if(i > 0)
            {
                if(map[i][xMap]->isCollidable())
                {
                    xCoord = xMap*32;
                    yCoord = (i-1)*32;
                    actualX = xMap*32;
                    actualY = (i-1)*32;

                    if(map[i-1][xMap]->isCollidable())
                    {
                        active = false;
                    }

                    break;
                }
            }
        }


    }
    else
    {
        xCoord = x;
        yCoord = y;
        actualX = x;
        actualY = y;

    }


    timeLeft = length;

    spellAnim.setPosition(xCoord, yCoord);
}

void AttackSpell::collision(Tile *map[MAP_HEIGHT][MAP_LENGTH], Enemy dinos[], int &XP)
{
    int startY = yCoord/32 - 5;
    int endY = yCoord/32 + 5;

    int startX = xCoord/32 - 5;
    int endX = xCoord/32 + 5;

    if(startY < 0)
        startY = 0;

    if(startX < 0)
        startX = 0;

    if(endX > 500)
        endX = 499;

    if(endY > 250)
        endY = 249;

    if(collidable)
    {
        for(int y=startY; y < endY; y++)
        {
            for(int x=startX; x < endX; x++)
            {
                int xDistance = abs(x*32 - xCoord);
                int yDistance = abs(y*32 - yCoord);

                if(xDistance < 34 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    active = false;
                    stopMusic();
                    break;
                }
            }
        }
    }



    for(int i=0; i < 30; i++)
    {
        if(dinos[i].isActive())
        {

            int dinoX = dinos[i].getX();
            int dinoY = dinos[i].getY();

            int xDistance = abs(dinoX - xCoord);
            int yDistance = abs(dinoY - yCoord);

            if(xDistance < 34 and yDistance < 48)
            {

                if(collidable)
                {
                    active = false;
                }


                if(!dinos[i].isInvuln())
                {
                    dinos[i].hurt(damage);
                    dinos[i].setInvuln(0.2);
                }


                if(dinos[i].getHealth() <= 0)
                {
                    dinos[i].setActive(false);
                    XP += 5;
                }
            }
        }
    }
}

void AttackSpell::update(float dt)
{
    spellAnim.update(dt);
    if(dir == "left")
    {
        move(-speed*dt, 0);
    }
    else if(dir == "right")
    {
        move(speed*dt, 0);
    }

    timeLeft -= dt;
    if(timeLeft <= 0)
    {
        active = false;

        if(soundLoop)
            stopMusic();
    }


}

void AttackSpell::setDamage(int d)
{
    damage = d;
}

bool AttackSpell::isActive()
{
    return active;
}

bool AttackSpell::isCollidable()
{
    return collidable;
}

AttackSpell::~AttackSpell()
{
    //dtor
}
