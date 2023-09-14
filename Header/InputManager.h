#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

namespace EdgarSam
{

    class InputManager
    {
    public:
        InputManager(){};
        ~InputManager(){};
        bool IsDirectionClicked(sf::Keyboard::Key button);
        bool IsClicked(sf::Text text, sf::Mouse::Button button, sf::RenderWindow &window);
        bool IsHovering(sf::Text text, sf::RenderWindow &window);
    };
}
#endif