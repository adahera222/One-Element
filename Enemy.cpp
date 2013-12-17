#include "Enemy.h"
#include <iostream>

const int TILE_SIZE = 32;

Enemy::Enemy()
{
    state = "wandering";
    dir = "idle";
    wanderTimer = 2;
    climbing = false;
    invulnTime = 0;
}

void Enemy::setAnim(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime)
{
    enemyAnim.init(framewidth, frameheight, totalframewidth, totalframeheight, frametime);
}

void Enemy::setHealth(int h)
{
    health = h;
    float percent = (float)health/maxHealth;
    healthBar.setTextureRect(sf::IntRect(0, 0, percent*64, 64));
}

void Enemy::setPosition(int x, int y)
{
    xCoord = x;
    yCoord = y;
    actualX = x;
    actualY = y;

    enemyAnim.setPosition(x,y);
}

void Enemy::move(float x, float y)
{
    actualX += x;
    actualY += y;

    xCoord = (int)actualX;
    yCoord = (int)actualY;

    enemyAnim.setPosition(xCoord,yCoord);
}

void Enemy::setTexture(std::string path)
{
    enemyAnim.setTexture(path);
}

void Enemy::hurt(int pain)
{
    health -= pain;
    float percent = (float)health/maxHealth;
    healthBar.setTextureRect(sf::IntRect(0, 0, percent*64, 64));
}

void Enemy::setActive(bool b)
{
    active = b;
}

void Enemy::init(int maxH, int dam, int speediness, std::string nam)
{
    maxHealth = maxH;
    health = maxH;
    damage = dam;
    name = nam;
    speed = speediness;

    healthTex.loadFromFile("images/enemies/enemyHealthBar.png");
    healthBar.setTexture(healthTex);
    healthBar.setTextureRect(sf::IntRect(0, 0, 64, 64));
    healthBar.setOrigin(32,32);
}

void Enemy::draw(sf::RenderWindow &window)
{
    enemyAnim.draw(window);
    healthBar.setPosition(xCoord,yCoord);
    window.draw(healthBar);
}

void Enemy::setInvuln(float t)
{
    invulnTime = t;
    invuln = true;
}

void Enemy::wander(float dt)
{
    if(wanderTimer <= 0)
    {

        if(!climbing)
        {
            int chance = rand() % 100 + 1;

            if(chance < 44)
            {

                if(name == "Dino")
                {
                    if(dir == "right")
                        enemyAnim.setTexture("images/enemies/dinoRight.png");
                    else
                        enemyAnim.setTexture("images/enemies/dinoLeft.png");
                }
                else if(name == "Skull")
                {
                    if(dir == "right")
                        enemyAnim.setTexture("images/enemies/skullRight.png");
                    else
                        enemyAnim.setTexture("images/enemies/skullLeft.png");
                }

                dir = "idle";

            }
            else if(chance < 72)
            {
                dir = "left";

                if(name == "Dino")
                {
                    enemyAnim.setTexture("images/enemies/dinoWalkLeft.png");
                }
                else if(name == "Skull")
                {
                    enemyAnim.setTexture("images/enemies/skullWalkLeft.png");
                }
            }

            else
            {
                dir = "right";

                if(name == "Dino")
                {
                    enemyAnim.setTexture("images/enemies/dinoWalkRight.png");
                }
                else if(name == "Skull")
                {
                    enemyAnim.setTexture("images/enemies/skullWalkRight.png");
                }

            }



            wanderTimer = rand() % 3 + 2;
        }
    }

    if(dir == "left")
    {
        move(-speed*dt,0);
    }
    else if(dir == "right")
    {
        move(speed*dt,0);
    }
}

void Enemy::update(float dt, Tile *map[250][500])
{

    enemyAnim.update(dt);
    wanderTimer -= dt;
    invulnTime -= dt;

    if(invulnTime < 0)
        invuln = false;


    if(state == "wandering")
    {
        wander(dt);
    }
    else if(state == "chasing")
    {
        chase(dt);
    }

    collision(map);

}

void Enemy::checkPlayerClose(int x)
{
    if(abs(x-xCoord) < 480)
    {
        state = "chasing";

        if(x > xCoord)
            dir = "right";
        else
            dir = "left";
    }
}

void Enemy::chase(float dt)
{
    if(prevDir != dir)// and !climbing)
    {
        if(name == "Dino")
        {

            if(dir == "right")
            {
                enemyAnim.setTexture("images/enemies/dinoWalkRight.png");
            }
            else if(dir == "left")
            {
                enemyAnim.setTexture("images/enemies/dinoWalkLeft.png");
            }
        }
        else if(name == "Skull")
        {
            if(dir == "right")
            {
                enemyAnim.setTexture("images/enemies/skullWalkRight.png");
            }
            else if(dir == "left")
            {
                enemyAnim.setTexture("images/enemies/skullWalkLeft.png");
            }
        }
    }

    if(dir == "left")
    {
        move(-speed*dt,0);
    }
    else if(dir == "right")
    {
        move(speed*dt,0);
    }

    prevDir = dir;
}

void Enemy::collision(Tile *map[250][500])
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
        endX = 500;

    if(endY > 250)
        endY = 250;

    climbing = false;
    for(int y=startY; y < endY; y++)
    {
        for(int x=startX; x < endX; x++)
        {
            int xDistance = abs(x*TILE_SIZE - xCoord);
            int yDistance = abs(y*TILE_SIZE - yCoord);

            if(dir == "right" and x*32 > xCoord)
            {
                if(xDistance <= 48 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    xCoord = (x)*TILE_SIZE - 48;
                    actualX = (x)*TILE_SIZE - 48;
                    climbing = true;
                    break;
                }

            }
            else if(dir == "left" and x*32 < xCoord)
            {
                if(xDistance < 48 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    xCoord = (x)*TILE_SIZE + 48;
                    actualX = (x)*TILE_SIZE + 48;
                    climbing = true;
                    break;

                }

            }


        }
    }

    enemyAnim.setPosition(xCoord,yCoord);

}

void Enemy::gravity(float dt, Tile *map[250][500])
{

    if(climbing)
    {
        actualY -= 1.75*speed*dt;
    }
    else
    {
        actualY += 3*speed*dt;
    }

    yCoord = (int)actualY;

    int startY = yCoord/32 - 5;
    int endY = yCoord/32 + 5;

    int startX = xCoord/32 - 5;
    int endX = xCoord/32 + 5;

    if(startY < 0)
        startY = 0;

    if(startX < 0)
        startX = 0;

    if(endX > 500)
        endX = 500;

    if(endY > 250)
        endY = 250;

    for(int y=startY; y < endY; y++)
    {
        for(int x=startX; x < endX; x++)
        {
            if(y*TILE_SIZE > yCoord-32)
            {

                int xDistance = abs(x*TILE_SIZE - xCoord);
                int yDistance = abs(y*TILE_SIZE - yCoord);


                if(!climbing)
                {
                    if(dir == "right")
                    {
                        if(xDistance <= 48 and yDistance < 48 and map[y][x]->isCollidable())
                        {
                            yCoord = (y-1)*TILE_SIZE - (TILE_SIZE/2);
                            actualY = (y-1)*TILE_SIZE - (TILE_SIZE/2);
                            break;
                        }
                    }
                    else
                    {
                        if(xDistance < 48 and yDistance < 48 and map[y][x]->isCollidable())
                        {
                            yCoord = (y-1)*TILE_SIZE - (TILE_SIZE/2);
                            actualY = (y-1)*TILE_SIZE - (TILE_SIZE/2);
                            break;
                        }
                    }

                }
            }
            else
            {

                float xDistance = abs(x*TILE_SIZE - actualX);
                float yDistance = abs(y*TILE_SIZE - actualY);



                if(xDistance < 48 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    yCoord = (y+1)*TILE_SIZE + (TILE_SIZE/2);
                    actualY = (y+1)*TILE_SIZE + (TILE_SIZE/2);

                    if(dir == "right")
                    {
                        dir = "left";
                        move(-16,0);
                    }
                    else
                    {
                       dir = "right";
                       move(16,0);
                    }


                    break;
                }


            }

        }
    }


    enemyAnim.setPosition(xCoord,yCoord);
}

int Enemy::getHealth()
{
    return health;
}

int Enemy::getX()
{
    return xCoord;
}

int Enemy::getDamage()
{
    return damage;
}

int Enemy::getY()
{
    return yCoord;
}

bool Enemy::isActive()
{
    return active;
}

bool Enemy::isInvuln()
{
    return invuln;
}




Enemy::~Enemy()
{
    //dtor
}
