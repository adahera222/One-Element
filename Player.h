#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "animation.h"
#include "AttackSpell.h"

using namespace std;

class Player
{
    public:
        Player();
        virtual ~Player();

        void initTexture(std::string[]);
        void draw(sf::RenderWindow &window);
        void setPosition(int, int);
        void gravity(float, Tile*[250][500], Enemy dinos[], int&);
        void move(float, float);
        void initAnim(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime);
        void update(float);
        void spellAttack(sf::RenderWindow &window, Tile* map[250][500]);
        void setDirection(string);
        void setMageType(string);
        void collision(Tile* map[250][500]);
        void setJumping(bool);
        void setIdle();
        void setClimbing(bool);
        void setAnim();
        void spellAlt(sf::RenderWindow &window, Tile* map[250][500]);
        void setHealth(int);
        void cancelSpells();
        void damage(int);
        void setInvuln(float);

        int getX();
        int getY();
        int getHealth();

        bool ableToJump();
        bool isClimbing();
        bool isInvuln();


    protected:
        sf::Texture tex;
        sf::Sprite sprite;
        int xCoord;
        int yCoord;
        int speed;
        int maxHealth;
        float actualX;
        float actualY;
        float invulnTime;
        animation playerAnim;
        animation armAnim;
        float spellAttackTime;
        AttackSpell attackSpells[40];
        string dir;
        string prevDir;
        string climbDir;
        string prevClimbDir;
        string mageType;
        bool jumping;
        float jumpTime;
        bool canJump;
        bool climbing;
        bool canClimb;
        bool invuln;
        int health;
        bool casting;
        bool alreadySet;
        sf::Texture healthTex;
        sf::Sprite healthSprite;

        sf::Texture healthGUITex;
        sf::Sprite healthGUI;

        sf::Texture xpTex;
        sf::Sprite xpSprite;

        sf::Texture xpGUITex;
        sf::Sprite xpGUI;


    private:
};

#endif // PLAYER_H
