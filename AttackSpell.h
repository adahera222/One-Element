#ifndef ATTACKSPELL_H
#define ATTACKSPELL_H
#include "animation.h"
#include "Tile.h"
#include "Enemy.h"
#include <SFML/Audio.hpp>

class AttackSpell
{
    public:
        AttackSpell();

        void draw(sf::RenderWindow &window);
        void initAnim(int framewidth, int frameheight, int totalframewidth, int totalframeheight, float frametime);
        void setType(std::string[2]);
        void move(float, float);
        void setPosition(int, int);
        void init(int, int, int , float, sf::Vector2i, Tile *map[250][500]);
        void update(float);
        void collision(Tile *map[250][500], Enemy dinos[], int&);
        void setCollidable(bool);
        void setActive(bool);
        void setDamage(int);
        void initMusic(std::string);
        void playMusic();
        void loop(bool b);
        void stopMusic();

        bool isCollidable();
        bool isActive();


        virtual ~AttackSpell();

    protected:
        int xCoord;
        int yCoord;
        int damage;

        float actualX;
        float actualY;

        animation spellAnim;

        bool active;
        bool collidable;
        bool soundLoop;

        std::string dir;

        int speed;

        float timeLeft;

        sf::Music sound;



    private:
};

#endif // ATTACKSPELL_H
