#ifndef LASERS_H
#define LASERS_H

#include "StateManager.h"
#include "InputManager.h"
#include "Game.h"
#include "Definations.h"
#include <SFML/Graphics.hpp>

namespace EdgarSam
{

    class Lasers
    {
    public:
        Lasers(GameDataPtr data, sf::Vector2f position, bool right_Dir, bool isShip = true);
        ~Lasers(){};
        void SpawnLasers(sf::Vector2f position, bool right_Dir);
        void Update(float dt);
        void updateDirection();
        sf::FloatRect getBounds() const;
        void draw();

    private:
        GameDataPtr _data;
        sf::Sprite _laser;
        sf::Sprite _laser_1;
        sf::Vector2f direction;
        bool _isShip;
        bool _isLander;
    };
}
#endif