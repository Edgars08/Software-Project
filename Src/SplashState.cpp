#include "SplashState.h"
#include "MenuState.h"
#include <iostream>
#include "Definations.h"
namespace EdgarSam
{
    SplashState::SplashState(GameDataPtr data) : _data(data)
    {
    }

    SplashState::~SplashState()
    {
        delete instruction;
    }

    void SplashState::InitState()
    {
        // store them in a map ...then get
        _data->assets.AddTexture("splashbackground", SPLASHSTATE_BACKGROUND);
        _background.setTexture(_data->assets.getTexture("splashbackground"));
        _background.setScale(sf::Vector2f(1.0f, 0.7777778f));

        this->instruction = new Instructions(_data);
        this->_clock.restart();
    }

    void SplashState::HandleInput()
    {
        sf::Event event;
        while (_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                _data->window.close();
            }
        }
    }
    void SplashState::Update(float dt)
    {
        if (_clock.getElapsedTime().asSeconds() > SPLASHSTATE_SHOW_TIME)
        {
            _data->states.PushState(std::unique_ptr<State>(new MenuState(_data)), true, true); // on vector
            this->_clock.restart();
        }
    }
    void SplashState::Draw(float dt)
    {
        _data->window.clear();
        _data->window.draw(_background);
        this->instruction->draw();
        _data->window.display();
    }

}
