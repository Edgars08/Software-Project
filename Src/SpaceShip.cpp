#include "SpaceShip.h"
#include "GameState.h"
#include "Definations.h"

namespace EdgarSam
{
    SpaceShip::SpaceShip(GameDataPtr data) : _data(data)
    {
        this->initShip();
    }

    void SpaceShip::initShip()
    {
        _data->assets.AddTexture("SpriteSheet", GAMESTATE_SPRITESHEET);
        this->_ship = sf::Sprite(_data->assets.getTexture("SpriteSheet"), sf::IntRect(120, 23, 45, 28));
        float x_pos = _data->window.getSize().x / 2;
        float y_pos = _data->window.getSize().y / 2;
        this->setPosition(x_pos, y_pos);
        this->_rightDirection = false;
    }

    void SpaceShip::update(float dt)
    {
        this->updateDirection();
        float movement = SPACESHIP_SPEED * dt;
        if (_data->inputs.IsDirectionClicked(sf::Keyboard::Right))
        {
            _ship.move(sf::Vector2f(movement, 0)); // move to right
        }
        else if (_data->inputs.IsDirectionClicked(sf::Keyboard::Left))
        {
            _ship.move(sf::Vector2f(-movement, 0)); // move to left
        }
        else if (_data->inputs.IsDirectionClicked(sf::Keyboard::Up))
        {
            _ship.move(sf::Vector2f(0, -movement)); // move UP
        }
        else if (_data->inputs.IsDirectionClicked(sf::Keyboard::Down))
        {
            _ship.move(sf::Vector2f(0, movement)); // move DOWN
        }
        else
        {
            _ship.move(sf::Vector2f(0, 0)); // stop moving
        }
        this->checkWindowCollision();
    }
    void SpaceShip::updateDirection()
    {
        if (_data->inputs.IsDirectionClicked(sf::Keyboard::Left))
        {
            _ship.setScale(1.0f, 2.0f); // Flip the sprite to face left
            this->_rightDirection = false;
        }
        if (_data->inputs.IsDirectionClicked(sf::Keyboard::Right))
        {
            _ship.setScale(-1.0f, 2.0f); // Flip the sprite to face right
            this->_rightDirection = true;
        }
    }
    void SpaceShip::setPosition(float x, float y)
    {
        _ship.setPosition(x, y);
        _ship.setScale(1.0f, 2.0f);
    }
    void SpaceShip::checkWindowCollision()
    {
        sf::Vector2f shipPosition = _ship.getPosition();
        sf::Vector2f shipSize = sf::Vector2f(_ship.getGlobalBounds().width, _ship.getGlobalBounds().height);
        sf::Vector2u windowSize = _data->window.getSize();

        if (shipPosition.x < 0.0f) // LEFT
        {
            shipPosition.x = 10.0f;
        }
        if (shipPosition.x + shipSize.x > windowSize.x) // RIGHT
        {
            shipPosition.x = windowSize.x - shipSize.x;
        }
        if (shipPosition.y < 0) // TOP
        {
            shipPosition.y = 0.0f;
        }
        if (shipPosition.y + shipSize.y > windowSize.y) // BOTTOM
        {
            shipPosition.y = windowSize.y - shipSize.y;
        }
        this->_ship.setPosition(shipPosition);
    }

    sf::Vector2f SpaceShip::getPosition() const
    {
        return _ship.getPosition();
    }
    sf::FloatRect SpaceShip::getBounds() const
    {
        return _ship.getGlobalBounds();
    }
    bool SpaceShip::getDirection() const
    {
        return _rightDirection;
    }
    void SpaceShip::draw()
    {
        this->_data->window.draw(this->_ship);
    }
}