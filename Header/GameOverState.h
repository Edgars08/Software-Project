#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "StateManager.h"
#include "InputManager.h"
#include "Game.h"

namespace EdgarSam
{
    class GameOverState : public State
    {
    public:
        GameOverState(GameDataPtr data);
        ~GameOverState(){};
        void InitState();
        void InitText();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataPtr _data;
        sf::Sprite _background;
        sf::Text gameover_text;
        sf::Text playagain_text;
        sf::Text _Instruction;
        sf::Text title;
        sf::Font fontText;
    };
}
#endif