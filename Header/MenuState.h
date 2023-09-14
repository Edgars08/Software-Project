#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "StateManager.h"
#include "Game.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>

namespace EdgarSam
{
    class MenuState : public State
    {
    public:
        MenuState(GameDataPtr data);
        ~MenuState(){};
        void InitState();
        void InitText();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataPtr _data;
        sf::Sprite _background;
        sf::Text play_text;
        sf::Text quit_text;
        sf::Text title;
        sf::Font fontText;
    };
}

#endif
