#ifndef ASTEROID_H
#define ASTEROID_H

#include "StateManager.h"
#include "InputManager.h"
#include "Game.h"
#include "Definations.h"
#include <SFML/Graphics.hpp>

namespace EdgarSam
{

    class Asteroid
    {
    public:
        Asteroid(GameDataPtr data);
        ~Asteroid(){};
        void SpawnAsteroid();
        void Update(float dt);
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        void draw();

    private:
        GameDataPtr _data;
        sf::Sprite _asteroid;
        sf::Vector2f direction;
    };
}
#endif