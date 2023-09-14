#include "Asteroid.h"
#include "Definations.h"
#include <string>

namespace EdgarSam
{
    Asteroid::Asteroid(GameDataPtr data) : _data(data)
    {
        this->SpawnAsteroid();
    }
    void Asteroid::SpawnAsteroid()
    {
        _data->assets.AddTexture("Asteroid", ASTEROID_FILEPATH);
        _asteroid.setTexture(_data->assets.getTexture("Asteroid"));
        _asteroid.setPosition(static_cast<float>(rand() % (_data->window.getSize().x / 2)), 0.0f - _asteroid.getGlobalBounds().height);
        direction = sf::Vector2f(0.0f, 1.0f);
    }
    void Asteroid::Update(float dt)
    {
        _asteroid.move(dt * ASTERIOD_SPEED * direction);
    }

    sf::Vector2f Asteroid::getPosition() const
    {
        return _asteroid.getPosition();
    }
    void Asteroid::draw()
    {
        _data->window.draw(_asteroid);
    }
    sf::FloatRect Asteroid::getBounds() const
    {
        return _asteroid.getGlobalBounds();
    }
}
