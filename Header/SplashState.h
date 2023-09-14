#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "State.h"
#include "Game.h"
#include "Instructions.h"
#include<SFML/Graphics.hpp>

namespace EdgarSam
{
    class SplashState :public State
    {
    public:
        SplashState(GameDataPtr data);
        ~SplashState();
        void InitState();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataPtr _data;
        sf::Clock _clock;
        sf::Sprite _background;
        Instructions *instruction;
   //     sf::Text _Instruction;
    };
}
#endif