#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "StateManager.h"
#include "InputManager.h"
#include "Game.h"
namespace EdgarSam
{

    class SpaceShip
    {
    public:
        SpaceShip(GameDataPtr data);
        ~SpaceShip(){};
        void initShip();
        void update(float dt);
        void updateDirection();
        void setPosition(float x, float y);
        void checkWindowCollision();
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        bool getDirection() const;
        void draw();

    private:
        GameDataPtr _data;
        sf::Sprite _ship;
        bool _rightDirection;
    };
}
#endif