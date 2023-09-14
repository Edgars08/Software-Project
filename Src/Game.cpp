#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include "Definations.h"
#include "SplashState.h"

namespace EdgarSam
{
    Game::Game()
    {
        srand(time(NULL));
        _data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Titlebar);
        _data->states.PushState(std::unique_ptr<State>(new SplashState(this->_data)));
        this->Run();
    }

    void Game::Run()
    {
        const float maxFrameTime = MAXFRAMETIME;
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (this->_data->window.isOpen())
        {
            this->_data->states.UpdateState();

            float newTime = this->_clock.getElapsedTime().asSeconds();
            float frameTime = std::min(newTime - currentTime, maxFrameTime); // Limit frame time
            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= dt)
            {
                this->_data->states.getActiveState()->HandleInput();
                this->_data->states.getActiveState()->Update(dt);
                accumulator -= dt;
            }

            float interpolation = accumulator / dt;
            this->_data->states.getActiveState()->Draw(interpolation);
        }
    }
}
