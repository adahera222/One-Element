#include "Player.h"

const int MAP_HEIGHT = 250;
const int MAP_LENGTH = 500;
const int TILE_SIZE = 32;

float abs(float a)
{
    if(a < 0)
        return a*-1;
    else
        return a;
}

Player::Player()
{
    spellAttackTime = 0;
    dir = "right";
    prevDir = "right";
    jumping = false;
    jumpTime = 0;
    canJump = true;
    canClimb = false;
    maxHealth = 100;
    health = maxHealth;
    prevClimbDir = "";
}

int Player::getX()
{
    return xCoord;
}

int Player::getY()
{
    return yCoord;
}

int Player::getHealth()
{
    return health;
}

void Player::setHealth(int h)
{
    health = h;
    float percent = (float)health/maxHealth;
    healthSprite.setTextureRect(sf::IntRect(0, 0, percent*256, 64));
}

void Player::setJumping(bool b)
{
    canJump = false;
    jumping = b;
    jumpTime = 0.35;
}

bool Player::ableToJump()
{
    return canJump;
}

void Player::initTexture(std::string str[])
{
    playerAnim.setTexture(str[0]);
    armAnim.setTexture(str[1]);
    speed = 200;

    healthGUITex.loadFromFile("images/tiles/healthGUI.png");
    healthGUI.setTexture(healthGUITex);

    xpGUITex.loadFromFile("images/tiles/xpGUI.png");
    xpGUI.setTexture(xpGUITex);

    healthTex.loadFromFile("images/tiles/healthBar.png");
    healthSprite.setTexture(healthTex);

    xpTex.loadFromFile("images/tiles/xpBar.png");
    xpSprite.setTexture(xpTex);

    healthSprite.setTextureRect(sf::IntRect(0, 0, 256, 64));
    healthSprite.setOrigin(128,32);

    xpSprite.setTextureRect(sf::IntRect(0, 0, 256, 64));
    xpSprite.setOrigin(128,32);

    healthGUI.setOrigin(128,32);
    xpGUI.setOrigin(128,32);
}

void Player::initAnim(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime)
{
    playerAnim.init(framewidth, frameheight, totalframewidth, totalframeheight, frametime);
    armAnim.init(framewidth, frameheight, totalframewidth, totalframeheight, frametime);
}

void Player::draw(sf::RenderWindow &window)
{
    playerAnim.draw(window);
    armAnim.draw(window);

    xpSprite.setPosition(getX()-250, getY()-190);
    healthSprite.setPosition(getX()-250, getY()-260);

    xpGUI.setPosition(getX()-250, getY()-190);
    healthGUI.setPosition(getX()-250, getY()-260);


    window.draw(healthGUI);
    window.draw(xpGUI);

    window.draw(xpSprite);
    window.draw(healthSprite);

    for(int i=0; i < 40; i++)
    {
        if(attackSpells[i].isActive())
        {
            attackSpells[i].draw(window);
        }
    }
}

void Player::move(float X, float Y)
{
    actualX += X;
    actualY += Y;

    xCoord = (int)actualX;
    yCoord = (int)actualY;

    playerAnim.setPosition(xCoord, yCoord);
    armAnim.setPosition(xCoord, yCoord);


}

void Player::collision(Tile* map[MAP_HEIGHT][MAP_LENGTH])
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
            float xDistance = abs(x*TILE_SIZE - actualX);
            float yDistance = abs(y*TILE_SIZE - actualY);

            if(dir == "right") //and x*32 > xCoord)
            {
                if(xDistance < 32 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    xCoord = (x)*TILE_SIZE - 32;
                    actualX = (x)*TILE_SIZE - 32;


                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        climbing = true;
                        jumping = false;
                        jumpTime = 0.2;
                        climbDir = dir;
                    }


                    break;
                }

            }
            else if(dir == "left")// and x*32 < xCoord)
            {
                if(xDistance < 32 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    xCoord = (x)*TILE_SIZE + 32;
                    actualX = (x)*TILE_SIZE + 32;

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        climbing = true;
                        jumping = false;
                        jumpTime = 0.2;
                        climbDir = dir;
                    }
                    /*else
                    {
                        if(y > 0)
                        {
                            if(!map[y-1][x]->isCollidable())
                            {
                                climbing = true;
                                jumping = false;
                                jumpTime = 0.2;
                                climbDir = dir;
                            }
                        }

                    }*/

                    break;

                }

            }


        }
    }

    playerAnim.setPosition(xCoord,yCoord);
    armAnim.setPosition(xCoord,yCoord);





}

bool Player::isClimbing()
{
    return climbing;
}

bool Player::isInvuln()
{
    return invuln;
}

void Player::setInvuln(float t)
{
    invulnTime = t;
    invuln = true;
}

void Player::setClimbing(bool b)
{
    climbing = b;
}

void Player::setAnim()
{
    if(dir == "none")
        dir = prevDir;

    if(!casting and !climbing)
        armAnim.setIdle();




    if(!climbing)
    {

        prevClimbDir = "";
        climbDir = "";


        if(prevDir != dir or (!climbing and !alreadySet))
        {
            alreadySet = true;
            if(dir == "left")
            {

                if(mageType == "fireMage")
                {
                    playerAnim.setTexture("images/characters/fireMageWalkLeft.png");
                    armAnim.setTexture("images/characters/fireCastLeft.png");
                }
                else if(mageType == "airMage")
                {
                    playerAnim.setTexture("images/characters/airMageWalkLeft.png");
                    armAnim.setTexture("images/characters/airCastLeft.png");
                }
                else if(mageType == "waterMage")
                {
                    playerAnim.setTexture("images/characters/waterMageWalkLeft.png");
                    armAnim.setTexture("images/characters/waterCastLeft.png");
                }
                else if(mageType == "earthMage")
                {
                    playerAnim.setTexture("images/characters/earthMageWalkLeft.png");
                    armAnim.setTexture("images/characters/earthCastLeft.png");
                }

            }
            else if(dir == "right")
            {
                if(mageType == "fireMage")
                {
                    playerAnim.setTexture("images/characters/fireMageWalkRight.png");
                    armAnim.setTexture("images/characters/fireCastRight.png");
                }
                else if(mageType == "airMage")
                {
                    playerAnim.setTexture("images/characters/airMageWalkRight.png");
                    armAnim.setTexture("images/characters/airCastRight.png");
                }
                else if(mageType == "waterMage")
                {
                    playerAnim.setTexture("images/characters/waterMageWalkRight.png");
                    armAnim.setTexture("images/characters/waterCastRight.png");
                }
                else if(mageType == "earthMage")
                {
                    playerAnim.setTexture("images/characters/earthMageWalkRight.png");
                    armAnim.setTexture("images/characters/earthCastRight.png");
                }
            }
        }
    }
    else
    {
        alreadySet = false;
        if(prevDir != dir)
        {
            if(dir == "left")
            {

                if(mageType == "fireMage")
                {
                    playerAnim.setTexture("images/characters/fireMageWalkLeft.png");
                }
                else if(mageType == "airMage")
                {
                    playerAnim.setTexture("images/characters/airMageWalkLeft.png");
                }
                else if(mageType == "waterMage")
                {
                    playerAnim.setTexture("images/characters/waterMageWalkLeft.png");
                }
                else if(mageType == "earthMage")
                {
                    playerAnim.setTexture("images/characters/earthMageWalkLeft.png");
                }

            }
            else if(dir == "right")
            {
                if(mageType == "fireMage")
                {
                    playerAnim.setTexture("images/characters/fireMageWalkRight.png");
                }
                else if(mageType == "airMage")
                {
                    playerAnim.setTexture("images/characters/airMageWalkRight.png");
                }
                else if(mageType == "waterMage")
                {
                    playerAnim.setTexture("images/characters/waterMageWalkRight.png");
                }
                else if(mageType == "earthMage")
                {
                    playerAnim.setTexture("images/characters/earthMageWalkRight.png");
                }
            }
        }

        if(prevClimbDir.compare(climbDir) != 0)
        {

            if(climbDir == "left")
            {

                if(mageType == "fireMage")
                {
                    armAnim.setTexture("images/characters/fireClimbLeft.png");
                }
                else if(mageType == "airMage")
                {
                    armAnim.setTexture("images/characters/airClimbLeft.png");
                }
                else if(mageType == "waterMage")
                {
                    armAnim.setTexture("images/characters/waterClimbLeft.png");
                }
                else if(mageType == "earthMage")
                {
                    armAnim.setTexture("images/characters/earthClimbLeft.png");
                }

            }
            else if(climbDir == "right")
            {
                if(mageType == "fireMage")
                {
                    armAnim.setTexture("images/characters/fireClimbRight.png");
                }
                else if(mageType == "airMage")
                {
                    armAnim.setTexture("images/characters/airClimbRight.png");
                }
                else if(mageType == "waterMage")
                {
                    armAnim.setTexture("images/characters/waterClimbRight.png");
                }
                else if(mageType == "earthMage")
                {
                    armAnim.setTexture("images/characters/earthClimbRight.png");
                }
            }
        }


    }

    prevDir = dir;
    prevClimbDir = climbDir;


}



void Player::setPosition(int X, int Y)
{
    playerAnim.setPosition(X,Y);
    armAnim.setPosition(X,Y);
    xCoord = X;
    yCoord = Y;

    actualX = X;
    actualY = Y;
}

void Player::damage(int d)
{
    health -= d;
    float percent = (float)health/maxHealth;
    healthSprite.setTextureRect(sf::IntRect(0, 0, percent*256, 64));
}

void Player::gravity(float dt, Tile* map[MAP_HEIGHT][MAP_LENGTH], Enemy dinos[], int &XP)
{


    float percent = (float)(XP%100)/100;
    xpSprite.setTextureRect(sf::IntRect(0, 0, percent*256, 64));

    for(int i=0; i < 40; i++)
    {
        if(attackSpells[i].isActive())
            attackSpells[i].collision(map, dinos, XP);
    }

     if(climbing or jumping)
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


    climbing = false;
    for(int y=startY; y < endY; y++)
    {
        for(int x=startX; x < endX; x++)
        {
            if(y*TILE_SIZE > yCoord-32)
            {

                float xDistance = abs(x*TILE_SIZE - actualX);
                float yDistance = abs(y*TILE_SIZE - actualY);



                if(xDistance < 32 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    yCoord = (y-1)*TILE_SIZE - (TILE_SIZE/2);
                    actualY = (y-1)*TILE_SIZE - (TILE_SIZE/2);

                    if(jumpTime <= 0)
                        canJump = true;

                    break;
                }


                int playerX = actualX/32;
                int playerY = actualY/32;



            }
            else
            {

                float xDistance = abs(x*TILE_SIZE - actualX);
                float yDistance = abs(y*TILE_SIZE - actualY);



                if(xDistance < 32 and yDistance < 48 and map[y][x]->isCollidable())
                {
                    yCoord = (y+1)*TILE_SIZE + (TILE_SIZE/2);
                    actualY = (y+1)*TILE_SIZE + (TILE_SIZE/2);

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

                if(!isInvuln())
                {
                    damage(dinos[i].getDamage());
                    setInvuln(0.2);
                }
            }
        }
    }


    playerAnim.setPosition(xCoord,yCoord);
    armAnim.setPosition(xCoord,yCoord);

}

void Player::spellAttack(sf::RenderWindow &window, Tile *map[250][500])
{
    if(spellAttackTime == 0)
    {
        for(int i=0; i < 40; i++)
        {
            if(!attackSpells[i].isActive())
            {

                string types[2];
                types[0] = mageType;
                types[1] = "attack";

                sf::Vector2i position = sf::Mouse::getPosition(window);
                if(position.x > 400)
                    dir = "right";
                else
                    dir = "left";

                if(mageType == "fireMage")
                {

                    attackSpells[i].initAnim(32,32,128,32,0.1);
                    attackSpells[i].init(xCoord, yCoord, 500, 5, position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setDamage(5);
                    attackSpells[i].initMusic("sounds/fireball.wav");
                    attackSpells[i].playMusic();
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/fireCastRight.png");
                    else
                        armAnim.setTexture("images/characters/fireCastLeft.png");

                    break;
                }
                else if(mageType == "airMage")
                {
                    attackSpells[i].initAnim(64,32,256,32,0.1);
                    attackSpells[i].init(xCoord, yCoord, 500, 5, position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setDamage(5);
                    attackSpells[i].initMusic("sounds/lightning.wav");
                    attackSpells[i].playMusic();
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/airCastRight.png");
                    else
                        armAnim.setTexture("images/characters/airCastLeft.png");

                    break;
                }
                else if(mageType == "waterMage")
                {
                    attackSpells[i].initAnim(32,32,32,32,0.1);
                    attackSpells[i].init(xCoord, yCoord, 500, 5, position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setDamage(5);
                    attackSpells[i].initMusic("sounds/iceball.wav");
                    attackSpells[i].playMusic();
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/waterCastRight.png");
                    else
                        armAnim.setTexture("images/characters/waterCastLeft.png");

                    break;
                }
                else if(mageType == "earthMage")
                {
                    attackSpells[i].initAnim(32,32,32,32,0.1);
                    attackSpells[i].init(xCoord, yCoord, 500, 5,position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setDamage(5);
                    attackSpells[i].initMusic("sounds/earthball.wav");
                    attackSpells[i].playMusic();
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/earthCastRight.png");
                    else
                        armAnim.setTexture("images/characters/earthCastLeft.png");

                    break;
                }
            }
        }

    }

}

void Player::spellAlt(sf::RenderWindow &window, Tile *map[250][500])
{
    if(spellAttackTime == 0)
    {
        for(int i=0; i < 40; i++)
        {
            if(!attackSpells[i].isActive())
            {

                string types[2];
                types[0] = mageType;
                types[1] = "alt";

                sf::Vector2i position = sf::Mouse::getPosition(window);
                if(position.x > 400)
                    dir = "right";
                else
                    dir = "left";

                if(mageType == "fireMage")
                {

                    attackSpells[i].initAnim(32,32,128,32,0.05);
                    attackSpells[i].init(xCoord, yCoord, 0, 10, position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setCollidable(false);
                    attackSpells[i].setDamage(1);
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/fireCastRight.png");
                    else
                        armAnim.setTexture("images/characters/fireCastLeft.png");

                    break;
                }
                else if(mageType == "airMage")
                {
                    attackSpells[i].initAnim(32,96,256,96,0.03);
                    attackSpells[i].init(xCoord, yCoord, 500, 0.2, position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setDamage(7);
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/airCastRight.png");
                    else
                        armAnim.setTexture("images/characters/airCastLeft.png");


                    break;
                }
                else if(mageType == "waterMage")
                {
                    attackSpells[i].initAnim(32,32,128,32,0.1);
                    attackSpells[i].init(xCoord, yCoord, 0, 10, position, map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setCollidable(false);
                    attackSpells[i].setDamage(1);
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/waterCastRight.png");
                    else
                        armAnim.setTexture("images/characters/waterCastLeft.png");

                    break;
                }
                else if(mageType == "earthMage")
                {
                    attackSpells[i].initAnim(32,32,128,32,0.1);
                    attackSpells[i].init(xCoord, yCoord, 0, 10, position , map);
                    attackSpells[i].setType(types);
                    attackSpells[i].setCollidable(false);
                    attackSpells[i].setDamage(1);
                    spellAttackTime = 0.25;
                    casting = true;

                    if(dir == "right")
                        armAnim.setTexture("images/characters/earthCastRight.png");
                    else
                        armAnim.setTexture("images/characters/earthCastLeft.png");

                    break;
                }
            }
        }

    }

}

void Player::setMageType(std::string type)
{
    mageType = type;
}

void Player::setDirection(std::string direction)
{

     dir = direction;
}

void Player::setIdle()
{
    playerAnim.setIdle();
}

void Player::update(float dt)
{
    playerAnim.update(dt);
    armAnim.update(dt);
    spellAttackTime -= dt;
    jumpTime -= dt;
    invulnTime -= dt;

    if(invulnTime < 0)
        invuln = false;

    if(spellAttackTime < 0)
    {
        spellAttackTime = 0;
        casting = false;
    }


    if(jumpTime < 0)
        jumping = false;

    for(int i=0; i < 40; i++)
    {
        if(attackSpells[i].isActive())
            attackSpells[i].update(dt);
    }


}

void Player::cancelSpells()
{
    for(int i=0; i < 40; i++)
    {
        attackSpells[i].setActive(false);
    }
}

Player::~Player()
{



    //dtor
}
