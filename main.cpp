#include <iostream>
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>



using namespace std;

const int MAP_LENGTH = 500;
const int MAP_HEIGHT = 250;
const int numBlocks = 11;
const int maxSpawn = 70;


void spawnCreatures(Enemy dinos[], int num, bool newWorld)
{
    if(num > maxSpawn)
        num = maxSpawn;

    for(int i=0; i < num; i++)
    {
        if(newWorld)
        {

            int chance = rand() % 100 + 1;

            if(chance < 50)
            {
                dinos[i].init(10,3, 200,"Dino");
                dinos[i].setAnim(64,64,256,64,0.1);
                dinos[i].setTexture("images/enemies/dinoRight.png");
                dinos[i].setActive(true);
                int xPos = rand() % 15400 + 400;
                int yPos = 70;

                dinos[i].setPosition(xPos ,yPos);
            }
            else
            {
                dinos[i].init(15,5, 150,"Skull");
                dinos[i].setAnim(64,64,256,64,0.1);
                dinos[i].setTexture("images/enemies/skullRight.png");
                dinos[i].setActive(true);
                int xPos = rand() % 15400 + 400;
                int yPos = 70;

                dinos[i].setPosition(xPos ,yPos);
            }

        }
        else if(!dinos[i].isActive())
        {

            int chance = rand() % 100 + 1;

            if(chance < 50)
            {
                dinos[i].init(10,3, 200,"Dino");
                dinos[i].setAnim(64,64,256,64,0.1);
                dinos[i].setTexture("images/enemies/dinoRight.png");
                dinos[i].setActive(true);
                int xPos = rand() % 15400 + 400;
                int yPos = 70;

                dinos[i].setPosition(xPos ,yPos);
            }
            else
            {
                dinos[i].init(15,5, 150,"Skull");
                dinos[i].setAnim(64,64,256,64,0.1);
                dinos[i].setTexture("images/enemies/skullRight.png");
                dinos[i].setActive(true);
                int xPos = rand() % 15400 + 400;
                int yPos = 70;

                dinos[i].setPosition(xPos ,yPos);
            }
        }

    }
}

void generateMap(Tile *map[MAP_HEIGHT][MAP_LENGTH], Tile blocks[numBlocks])
{

    for(int y =0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_LENGTH; x++)
        {
            if(y < 1)
            {
                map[y][x] = &blocks[4];
            }
            else if((x <= 5) or (x > 494))
            {
                map[y][x] = &blocks[0]; //Dirtblock
            }
            else if(y > 245)
            {
                if(y == 246)
                    map[y][x] = &blocks[3];
                else
                    map[y][x] = &blocks[0]; //Dirtblock
            }
            else
            {
                map[y][x] = &blocks[1]; //Skyblock
            }
        }
    }

    int choiceY = 100;
    string type = "";

    int numStrips = 0;
    int sizeOfStrip = 0;
    bool makeStone = false;
    int stoneLength = 0;
    int startPoint = 0;
    int nextStartPoint = 0;
    int endPoint = 0;

    int blockCount = 0;
    for(int x =0; x < MAP_LENGTH; x++)
    {



        if(blockCount == 0)
        {
            type = "";
            int terrainType = rand() % 100 + 1;
            if(terrainType < 40 and type == "")
            {
                type = "flat";
            }
            if(terrainType < 50 and choiceY > 50 and type == "")
            {
                type = "cliff";
            }
            else if(terrainType < 60 and choiceY < 200 and type == "")
            {
                type = "cave";
            }
            else if(terrainType < 80 and choiceY < 200 and type == "")
            {
                type = "descent";
            }
            else if(terrainType <= 100 and choiceY > 50 and type == "")
            {
                type = "hill";
            }

            if(type == "")
            {
                if(choiceY > 200)
                    type = "cliff";
                else if(choiceY < 50)
                    type = "cave";
                else
                    type = "flat";
            }

            blockCount = rand() % 15 + 15;
        }

        if(type == "cliff")
        {
            int chance = rand() % 100 + 1;
            if(chance < 45)
            {
                choiceY -= rand() % 4 + 3;
            }

            if(choiceY < 7)
            {
                choiceY = 7;
                type = "";
            }


        }
        else if(type == "cave")
        {
            int chance = rand() % 100 + 1;
            if(chance < 45)
            {
                choiceY += rand() % 4 + 3;
            }

            if(choiceY > 243)
            {
                choiceY = 243;
                type = "";
            }

        }
        else if(type == "descent")
        {
            int chance = rand() % 100 + 1;
            if(chance < 25)
            {
                choiceY += rand() % 2 + 1;

            }

            if(choiceY > 243)
            {
                choiceY = 243;
                type = "";
            }

        }
        else if(type == "hill")
        {

            int chance = rand() % 100 + 1;
            if(chance < 25)
            {
                choiceY -= rand() % 2 + 1;
            }

            if(choiceY < 7)
            {
                choiceY = 7;
                type = "";
            }

        }
        else if(type == "flat")
        {
            int chance = rand() % 100 + 1;
            if(chance < 10)
            {
                choiceY += 1;
            }
            else if(chance < 20)
            {
                choiceY -= 1;
            }

            if(choiceY < 7)
            {
                choiceY = 7;
                type = "";
            }
            else if(choiceY > 243)
            {
                choiceY = 243;
                type = "";
            }
        }

        blockCount--;

        if(!makeStone)
        {
            int chanceOfStone = rand() % 100 + 1;
            if(chanceOfStone < 25)
            {
                makeStone = true;
                numStrips = rand() % 3 + 2;
                startPoint = rand() % 10 + (choiceY+1);
            }
            else
                makeStone = false;

        }

        if(makeStone)
        {

            int chance = rand() % 100 + 1;

            if(chance < 50)
                nextStartPoint = startPoint + (rand() % 2 + 2);
            else
                nextStartPoint = startPoint - (rand() % 2 + 2);

            stoneLength = rand() % 5 + 4;
            endPoint = nextStartPoint + stoneLength;

        }

        for(int y = 0; y < MAP_HEIGHT; y++)
        {
            if(makeStone and y > nextStartPoint and y < endPoint)
            {
                map[y][x] = &blocks[2];
            }
            else if(y == choiceY and x > 5 and x <= 494)
            {
                map[y][x] = &blocks[3];
            }
            else if(y > choiceY)
            {
                map[y][x] = &blocks[0];
            }
        }


        numStrips--;
        startPoint = nextStartPoint;

        if(numStrips == 0)
            makeStone = false;
    }


    for(int y=1; y < MAP_HEIGHT; y++)
    {
        for(int x=0; x < MAP_LENGTH; x++)
        {
            if(map[y][x] == &blocks[3])
            {

                int chance = rand() % 100 + 1;

                if(chance < 3)
                    map[y-1][x] = &blocks[5];
                else if(chance < 6)
                    map[y-1][x] = &blocks[6];
                else if(chance < 9)
                    map[y-1][x] = &blocks[7];
                else if(chance < 12)
                    map[y-1][x] = &blocks[8];
                else if(chance < 15)
                    map[y-1][x] = &blocks[9];
                else if(chance < 18)
                    map[y-1][x] = &blocks[10];

            }
        }
    }
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow mainWindow(sf::VideoMode(800,600),"One Element!",sf::Style::Close);

    const int MAP_LENGTH = 500;
    const int MAP_HEIGHT = 250;
    int XP = 400;

    int speed = 350;
    float spawnTimer = 10;

    sf::View camera;
    camera.reset(sf::FloatRect(0,0,800,600));

    sf::Clock dtClock;
    sf::Time dt;

    sf::Font defaultFont;
    defaultFont.loadFromFile("images/fonts/font.ttf");

    Tile blocks[numBlocks];
    blocks[0].initTexture("images/tiles/dirtBlock.png");
    blocks[0].setCollidable(true);

    blocks[1].initTexture("images/tiles/skyBlock.png");

    blocks[2].initTexture("images/tiles/stoneBlock.png");
    blocks[2].setCollidable(true);

    blocks[3].initTexture("images/tiles/grassBlock.png");
    blocks[3].setCollidable(true);

    blocks[4].initTexture("images/tiles/cloudBlock.png");
    blocks[4].setCollidable(true);

    //Background blocks
    blocks[5].initTexture("images/tiles/grass.png");
    blocks[6].initTexture("images/tiles/tree.png");
    blocks[7].initTexture("images/tiles/mushrooms.png");
    blocks[8].initTexture("images/tiles/rock1.png");
    blocks[9].initTexture("images/tiles/rock2.png");
    blocks[10].initTexture("images/tiles/rock3.png");

    Enemy dinos[maxSpawn];





    //Menu screen setup
    animation fireMageStatic;
    fireMageStatic.setTexture("images/characters/fireMageStatic.png");
    fireMageStatic.init(64,64,64,64,1);
    fireMageStatic.setIdle();
    fireMageStatic.setPosition(200,200);

    animation waterMageStatic;

    if(XP < 100)
    {
        waterMageStatic.setTexture("images/tiles/lock.png");
    }
    else
    {
        waterMageStatic.setTexture("images/characters/waterMageStatic.png");
    }

    waterMageStatic.init(64,64,64,64,1);
    waterMageStatic.setIdle();
    waterMageStatic.setPosition(200,290);

    animation airMageStatic;

    if(XP < 200)
    {
        airMageStatic.setTexture("images/tiles/lock.png");
    }
    else
    {
        airMageStatic.setTexture("images/characters/airMageStatic.png");
    }

    airMageStatic.init(64,64,64,64,1);
    airMageStatic.setIdle();
    airMageStatic.setPosition(200,380);

    animation earthMageStatic;

    if(XP < 300)
    {
        earthMageStatic.setTexture("images/tiles/lock.png");
    }
    else
    {
        earthMageStatic.setTexture("images/characters/earthMageStatic.png");
    }

    earthMageStatic.init(64,64,64,64,1);
    earthMageStatic.setIdle();
    earthMageStatic.setPosition(200,470);

    sf::Text title;
    title.setString("ONE ELEMENT \n\n    CHOOSE YOUR MAGE");
    title.setFont(defaultFont);
    title.setCharacterSize(30);
    title.setPosition(10,20);
    title.setColor(sf::Color::White);

    sf::Text fireName;
    fireName.setString("FIRE MAGE");
    fireName.setFont(defaultFont);
    fireName.setCharacterSize(20);
    fireName.setPosition(300,220);
    fireName.setColor(sf::Color::White);

    sf::Text waterName;

    if(XP < 100)
        waterName.setString("MORE XP NEEDED");
    else
        waterName.setString("WATER MAGE");

    waterName.setFont(defaultFont);
    waterName.setCharacterSize(20);
    waterName.setPosition(300,310);
    waterName.setColor(sf::Color::White);

    sf::Text airName;

    if(XP < 200)
        airName.setString("MORE XP NEEDED");
    else
        airName.setString("AIR MAGE");

    airName.setFont(defaultFont);
    airName.setCharacterSize(20);
    airName.setPosition(300,400);
    airName.setColor(sf::Color::White);

    sf::Text earthName;

    if(XP < 300)
        earthName.setString("MORE XP NEEDED");
    else
        earthName.setString("EARTH MAGE");

    earthName.setFont(defaultFont);
    earthName.setCharacterSize(20);
    earthName.setPosition(300,490);
    earthName.setColor(sf::Color::White);

    //Death Screen Setup
    sf::Text deathTitle;
    deathTitle.setString("YOU DIED");
    deathTitle.setFont(defaultFont);
    deathTitle.setCharacterSize(50);
    deathTitle.setPosition(260,130);
    deathTitle.setColor(sf::Color::White);

    sf::Text buttonText;
    buttonText.setString("CHOOSE YOUR MAGE");
    buttonText.setFont(defaultFont);
    buttonText.setCharacterSize(30);
    buttonText.setPosition(210,390);
    buttonText.setColor(sf::Color::White);


    Player playerChar;
    playerChar.initAnim(64,64,256,64,0.1);
    string paths[] = {"images/characters/fireMageWalkRight.png","images/characters/fireCastRight.png"};
    playerChar.initTexture(paths);
    playerChar.setMageType("fireMage");

    string mageChoice = "";

    string gameState = "menu";

    Tile* map[MAP_HEIGHT][MAP_LENGTH];





    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    mainWindow.close();
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    if(gameState == "dead")
                    {
                         if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i position = sf::Mouse::getPosition(mainWindow);
                            if(position.x > 210 and position.x < 460 and position.y > 390 and position.y < 420)
                            {
                                gameState = "menu";
                                playerChar.setHealth(100);
                            }
                        }
                    }
                    else if(gameState == "game")
                    {



                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            playerChar.spellAttack(mainWindow, map);
                        }
                        else if(event.mouseButton.button == sf::Mouse::Right)
                        {
                            playerChar.spellAlt(mainWindow, map);

                        }
                    }
                    else if(gameState == "menu")
                    {
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2i position = sf::Mouse::getPosition(mainWindow);
                            if(position.x > 100 and position.x < 460)
                            {
                                if(position.y > 220 and position.y < 280)
                                {
                                    cout << "Fire Mage" << endl;
                                    mageChoice = "fireMage";
                                    string paths[] = {"images/characters/fireMageWalkRight.png","images/characters/fireCastRight.png"};
                                    playerChar.initTexture(paths);
                                    playerChar.setMageType("fireMage");
                                }
                                else if(position.y > 310 and position.y < 370 and XP >= 100)
                                {
                                    cout << "Water Mage" << endl;
                                    mageChoice = "waterMage";
                                    string paths[] = {"images/characters/waterMageWalkRight.png","images/characters/waterCastRight.png"};
                                    playerChar.initTexture(paths);
                                    playerChar.setMageType("waterMage");
                                }
                                else if(position.y > 400 and position.y < 460 and XP >= 200)
                                {
                                    cout << "Air Mage" << endl;
                                    mageChoice = "airMage";
                                    string paths[] = {"images/characters/airMageWalkRight.png","images/characters/airCastRight.png"};
                                    playerChar.initTexture(paths);
                                    playerChar.setMageType("airMage");
                                }
                                else if(position.y > 490 and position.y < 550 and XP >= 300)
                                {
                                    cout << "Earth Mage" << endl;
                                    mageChoice = "earthMage";
                                    string paths[] = {"images/characters/earthMageWalkRight.png","images/characters/earthCastRight.png"};
                                    playerChar.initTexture(paths);
                                    playerChar.setMageType("earthMage");
                                }

                                if(mageChoice != "")
                                {
                                    gameState = "game";
                                    generateMap(map, blocks);
                                    spawnCreatures(dinos, 30, true);

                                    bool found = false;
                                    playerChar.setPosition(640,640);
                                    for(int y=0; y < MAP_HEIGHT-3; y++)
                                    {
                                        for(int x=0; x < MAP_LENGTH-3; x++)
                                        {
                                            if(map[y][x] == &blocks[1] and map[y][x+1] == &blocks[1] and
                                               map[y+1][x] == &blocks[1] and map[y+1][x+1] == &blocks[1] and
                                               map[y+2][x] == &blocks[3] and map[y+2][x+1] == &blocks[3])
                                            {
                                                playerChar.setPosition((x*32)+16, (y*32)+16);
                                                found = true;
                                                break;
                                            }
                                        }

                                        if(found)
                                            break;
                                    }

                                    dtClock.restart();
                                }

                            }
                        }

                    }

                    break;
                }
                case sf::Event::KeyPressed:
                {
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        if(playerChar.ableToJump())
                            playerChar.setJumping(true);


                    }

                }

                default:
                    break;
            }

        }

        if(gameState == "dead")
        {
            mainWindow.clear();

            mainWindow.draw(deathTitle);

            mainWindow.draw(buttonText);

            mainWindow.display();
        }
        else if(gameState == "menu")
        {
            mainWindow.clear();

            mainWindow.draw(title);

            fireMageStatic.draw(mainWindow);
            mainWindow.draw(fireName);

            waterMageStatic.draw(mainWindow);
            mainWindow.draw(waterName);

            airMageStatic.draw(mainWindow);
            mainWindow.draw(airName);


            earthMageStatic.draw(mainWindow);
            mainWindow.draw(earthName);

            mainWindow.display();
        }
        else if(gameState == "game")
        {
            dt = dtClock.restart();
            playerChar.gravity(dt.asSeconds(), map, dinos, XP);
            playerChar.update(dt.asSeconds());
            spawnTimer -= dt.asSeconds();

            if(spawnTimer <= 0)
            {
                spawnTimer = 10;
                spawnCreatures(dinos, 5, false);
            }


            for(int i=0; i < maxSpawn; i++)
            {
                if(dinos[i].isActive())
                {
                    dinos[i].checkPlayerClose(playerChar.getX());
                    dinos[i].gravity(dt.asSeconds(), map);
                    dinos[i].update(dt.asSeconds(), map);
                }

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                playerChar.move(speed*dt.asSeconds(), 0);
                playerChar.setDirection("right");
                playerChar.collision(map);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                playerChar.move(-speed*dt.asSeconds(), 0);
                playerChar.setDirection("left");
                playerChar.collision(map);
            }
            else
            {
                playerChar.setIdle();
                playerChar.setDirection("idle");
            }


            playerChar.setAnim();

            //Make sure the player is always the centre of the camera
            camera.setCenter(playerChar.getX(), playerChar.getY());

            mainWindow.setView(camera);

            mainWindow.clear();

            int startX = playerChar.getX()/32 - 14;
            int startY = playerChar.getY()/32 - 12;

            int endX = playerChar.getX()/32 + 14;
            int endY = playerChar.getY()/32 + 12;


            if(startX < 0)
                startX = 0;

            if(startY < 0)
                startY = 0;

            if(endX > MAP_LENGTH)
                endX = MAP_LENGTH - 1;

            if(endY > MAP_HEIGHT)
                endY = MAP_HEIGHT - 1;


            for(int y=startY; y < endY; y++)
            {
                for(int x=startX; x < endX; x++)
                {

                    map[y][x]->setPosition(x*32, y*32);
                    map[y][x]->draw(mainWindow);
                }
            }


            for(int i=0; i < 30; i++)
            {
                if(dinos[i].isActive())
                {
                    dinos[i].draw(mainWindow);
                }
            }

            playerChar.draw(mainWindow);



            mainWindow.display();

            if(playerChar.getHealth() <= 0)
            {
                gameState = "dead";
                playerChar.cancelSpells();
                mageChoice = "";
                camera.setCenter(400, 300);
                mainWindow.setView(camera);

                if(XP < 100)
                {
                    waterMageStatic.setTexture("images/tiles/lock.png");
                }
                else
                {
                    waterMageStatic.setTexture("images/characters/waterMageStatic.png");
                    waterName.setString("WATER MAGE");
                }

                if(XP < 200)
                {
                    airMageStatic.setTexture("images/tiles/lock.png");
                }
                else
                {
                    airMageStatic.setTexture("images/characters/airMageStatic.png");
                    airName.setString("AIR MAGE");
                }

                if(XP < 300)
                {
                    earthMageStatic.setTexture("images/tiles/lock.png");
                }
                else
                {
                    earthMageStatic.setTexture("images/characters/earthMageStatic.png");
                    earthName.setString("EARTH MAGE");
                }

                waterMageStatic.setPosition(232,322);

                airMageStatic.setPosition(232,412);

                earthMageStatic.setPosition(232,502);

            }
        }

    }
    return 0;
}
