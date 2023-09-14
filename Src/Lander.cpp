#include "Lander.h"
#include "Definations.h"

namespace EdgarSam
{
    Lander::Lander(GameDataPtr data) : _data(data)
    {
        this->initLander();
    }
    void Lander::initLander()
    {
        _data->assets.AddTexture("SpriteSheet", GAMESTATE_SPRITESHEET);
        this->_lander = sf::Sprite(_data->assets.getTexture("SpriteSheet"), sf::IntRect(200, 170, 25, 20));

        int x_pos = rand() % (_data->window.getSize().x / 2);
        int y_pos = rand() % (_data->window.getSize().y / 2);
        this->setPosition(x_pos, y_pos);
        this->_rightDirection = true;
    }
    void Lander::update(float dt)
    {
        this->updateDirection();
        this->movement = LANDER_SPEED * dt;
        this->updateMovement();
        this->checkCollision();
  
    }
    void Lander::updateDirection()
    {
        if (_lander.getGlobalBounds().left > _data->window.getSize().x)
        {
            _lander.setScale(1.20f, 1.20f); // Flip the sprite to face left
            this->_rightDirection = false;
        }
        if (_lander.getGlobalBounds().left < 0)
        {
            _lander.setScale(-1.20f, 1.20f); // Flip the sprite to face right
            this->_rightDirection = true;
        }
    }
    void Lander::setPosition(float x, float y)
    {
        _lander.setPosition(static_cast<float>(x), static_cast<float>(y));
        _lander.setScale(-1.20f, 1.20f); // Flip the sprite to face right
    }
    void Lander::updateMovement()
    {
        if(this->clock_1.getElapsedTime().asSeconds() > DIRECTION_CHANGETIME)
        {
            // Generate random movement direction (horizontal and vertical)
            this->randomXY = rand() % 3 - 1; // -1, 0, or 1
            this->clock_1.restart();
        }
         // RIGHT MOVEMENTS
        if (this->randomXY == -1 && this->_rightDirection)
        {
            // right-up direction
            this->_lander.move(sf::Vector2f(this->movement, -this->movement));
        }
        if (this->randomXY == 1 && this->_rightDirection)
        {
            // right-down direction
            this->_lander.move(sf::Vector2f(this->movement, this->movement));
        }
        if (this->randomXY == 0 && this->_rightDirection)
        {
            // right-horizontal direction
            this->_lander.move(sf::Vector2f(this->movement, 0));
        }
        // LEFT MOVEMENTS
        if (this->randomXY == -1 && !this->_rightDirection)
        {
            // left-up direction
            this->_lander.move(sf::Vector2f(-this->movement, -this->movement));
        }
        if (this->randomXY == 1 && !this->_rightDirection)
        {
            // left-down direction
            this->_lander.move(sf::Vector2f(-this->movement, this->movement));
        }
        if (this->randomXY == 0 && !this->_rightDirection)
        {
            // left-horizontal direction
            this->_lander.move(sf::Vector2f(-this->movement, 0));
        }
    }
    void Lander::checkCollision()
    {
        sf::Vector2f landerPosition = _lander.getPosition();
        sf::Vector2f landerSize = sf::Vector2f(_lander.getGlobalBounds().width, _lander.getGlobalBounds().height);
        sf::Vector2u windowSize = _data->window.getSize();

        if (landerPosition.y < 0) // TOP
        {
            landerPosition.y = 0.0f;
        }
        if (landerPosition.y + landerSize.y > windowSize.y) // BOTTOM
        {
            landerPosition.y = windowSize.y - landerSize.y;
        }
        this->_lander.setPosition(landerPosition);
    }
    sf::Vector2f Lander::getPosition() const
    {
        return _lander.getPosition();
    }
    sf::FloatRect Lander::getBounds() const
    {
        return _lander.getGlobalBounds();
    }
    bool Lander::getDirection() const
    {
        return _rightDirection;
    }

    void Lander::draw()
    {
        _data->window.draw(_lander);
    }
}
