#ifndef ENEMY_H
#define ENEMY_H
#include "animation.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        Enemy();
        virtual ~Enemy();

        void setAnim(int, int , int , int , float );
        void setTexture(std::string);
        void setHealth(int);
        void init(int, int, int, std::string);
        void setPosition(int, int);
        void move(float, float);
        void gravity(float, Tile*[250][500]);
        void draw(sf::RenderWindow &window);
        void update(float, Tile *map[250][500]);
        void wander(float);
        void collision(Tile *map[250][500]);
        void hurt(int);
        void setActive(bool);
        void setInvuln(float);
        void checkPlayerClose(int);
        void chase(float);

        bool isActive();
        bool isInvuln();

        int getHealth();
        int getX();
        int getY();
        int getDamage();



    protected:
        animation enemyAnim;
        sf::Sprite healthBar;
        sf::Texture healthTex;

        int health;
        int maxHealth;
        int damage;
        int xCoord;
        int yCoord;
        int speed;

        float actualX;
        float actualY;
        float wanderTimer;
        float invulnTime;

        std::string name;
        std::string dir;
        std::string state;
        std::string prevDir;

        bool climbing;
        bool active;
        bool invuln;



    private:
};

#endif // ENEMY_H
