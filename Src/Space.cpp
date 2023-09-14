#include "Space.h"
#include "Definations.h"

namespace EdgarSam
{
    Space::Space(GameDataPtr data) : _data(data)
    {
        this->InitSpace();
    }

    void Space::InitSpace()
    {
        _data->assets.AddTexture("gamestateBackground", GAMESTATE_BACKGROUND);

        this->_background.setTexture(_data->assets.getTexture("gamestateBackground"));
        _background.setScale(0.902998f, 0.981767f);

        this->_background_2 = this->_background;

        _background.setPosition(sf::Vector2f(0.0f, 0.0f));
        _background_2.setPosition(sf::Vector2f(0.0f - _background_2.getGlobalBounds().width, 0.0f));

        _spaceSprites.push_back(_background);
        _spaceSprites.push_back(_background_2);
    }
    void Space::update(float dt)
    {
        float movement = SPACE_SPEED * dt;

        for (unsigned int i = 0; i < _spaceSprites.size(); i++)
        {
            _spaceSprites[i].move(movement, 0.0f);
            if (_spaceSprites[i].getGlobalBounds().left > _data->window.getSize().x)
            {
                _spaceSprites[i].setPosition(sf::Vector2f(0.0f - _spaceSprites[i].getGlobalBounds().width, 0.0f));
            }
        }
    }
    void Space::draw()
    {
        for (unsigned int i = 0; i < _spaceSprites.size(); i++)
        {
            _data->window.draw(_spaceSprites[i]);
        }
    }
}