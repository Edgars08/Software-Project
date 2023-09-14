#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace EdgarSam
{
    class Instructions
    {
    public:
        Instructions(GameDataPtr data);
        ~Instructions(){};
        void draw();

    private:
        GameDataPtr _data;
        sf::Text _Instruction;
        sf::Text _Instruction_2;
        sf::Text _Instruction_3;
        sf::Text _Instruction_4;
    };
}
#endif