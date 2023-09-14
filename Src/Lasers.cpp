#include "Lasers.h"

namespace EdgarSam
{
    Lasers::Lasers(GameDataPtr data, sf::Vector2f position, bool right_Dir, bool isShip) : _data(data)
    {
        this->SpawnLasers(position, right_Dir);
        this->_isShip = isShip;
        this->_isLander = !this->_isShip;
    }
    void Lasers::SpawnLasers(sf::Vector2f position, bool right_Dir)
    {
        if (this->_isShip)
        {
            _data->assets.AddTexture("Shiplasers", SHIPLASER_FILEPATH);
            _laser.setTexture(_data->assets.getTexture("Shiplasers"));
            _laser.setPosition(position);
            _laser.setScale(0.30f, 0.50f);
        }
        if (this->_isLander)
        {
            _data->assets.AddTexture("Landerlasers", LANDERLASER_FILEPATH);
            _laser_1.setTexture(_data->assets.getTexture("Landerlasers"));
            _laser_1.setPosition(position);
            _laser_1.setScale(0.40f, 0.50f);
        }

        if (right_Dir)
        {
            direction = sf::Vector2f(1.0f, 0.0f); // Flip the sprite to face right
        }
        else
        {
            direction = sf::Vector2f(-1.0f, 0.0f); // Flip the sprite to face left
        }
    }
    void Lasers::Update(float dt)
    {
        if (this->_isShip)
        {
            _laser.move(dt * LASER_SPEED * direction);
        }
        else
        {
            _laser_1.move(dt * LASER_SPEED * direction * 0.5f);
        }
    }
    void Lasers::updateDirection()
    {
    }
    void Lasers::draw()
    {
        if (this->_isShip)
        {
            _data->window.draw(_laser);
        }
        else
        {
            _data->window.draw(_laser_1);
        }
    }
    sf::FloatRect Lasers::getBounds() const
    {
        if (this->_isShip)
        {
            return _laser.getGlobalBounds();
        }
        else
        {
            return _laser_1.getGlobalBounds();
        }
    }
}