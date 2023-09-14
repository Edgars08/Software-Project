#ifndef LANDER_H
#define LANDER_H

#include "StateManager.h"
#include "InputManager.h"
#include "Game.h"
namespace EdgarSam
{

    class Lander
    {
    public:
        Lander(GameDataPtr data);
        ~Lander(){};
        void initLander();
        void update(float dt);
        void updateDirection();
        void setPosition(float x, float y);
        void updateMovement();
        void checkCollision();
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        bool getDirection() const;
        void draw();

    private:
        GameDataPtr _data;
        sf::Sprite _lander;
        sf::Clock clock_1;
        float movement;
        bool _rightDirection;
        int randomXY = 0;
    };
}
#endif