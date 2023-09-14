#include "Instructions.h"
#include "Definations.h"

namespace EdgarSam
{
    Instructions::Instructions(GameDataPtr data) : _data(data)
    {
        this->_data->assets.AddFont("InstructionFont", INSTRUCTION_FONT);
        // Setting the font
        this->_Instruction.setFont(_data->assets.getFont("InstructionFont"));
        this->_Instruction.setCharacterSize(20);
        this->_Instruction.setFillColor(sf::Color::Red);

        this->_Instruction_2 = this->_Instruction;
        this->_Instruction_3 = this->_Instruction;
        this->_Instruction_4 = this->_Instruction;

        this->_Instruction.setPosition(_data->window.getSize().x * 0.10f, _data->window.getSize().y * 0.65f);
        this->_Instruction.setString("Left Click Mouse OR use keyboard key 'S' to Shoot");
        this->_Instruction_2.setPosition(_data->window.getSize().x * 0.10f, _data->window.getSize().y * 0.75f);
        this->_Instruction_2.setString("Left Click Mouse on 'Play' OR use keyboard key 'P' to START GAME");
        this->_Instruction_3.setPosition(_data->window.getSize().x * 0.10f, _data->window.getSize().y * 0.85f);
        this->_Instruction_3.setString("Left Click Mouse on 'Quit' OR use keyboard key 'Q' to QUIT GAME");
        this->_Instruction_4.setPosition(_data->window.getSize().x * 0.10f, _data->window.getSize().y * 0.95f);
        this->_Instruction_4.setString("Left Click Mouse on 'Play Again' OR use keyboard key 'P' to RESTART GAME");
    }

    void Instructions::draw()
    {
        _data->window.draw(_Instruction);
        _data->window.draw(_Instruction_2);
        _data->window.draw(_Instruction_3);
        _data->window.draw(_Instruction_4);
    }

}
