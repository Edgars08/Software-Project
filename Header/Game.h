#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "AssetLibrary.h"
#include "InputManager.h"

namespace EdgarSam
{
    struct GameData
    {
        StateManager states;
        AssetLibrary assets;
        InputManager inputs;
        sf::RenderWindow window;
    };
    // use a smart pointer to access the struct
    // creating alias for shared pointer
    typedef std::shared_ptr<GameData> GameDataPtr;

    class Game
    {
    public:
        Game();

    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock _clock;
        GameDataPtr _data = std::make_shared<GameData>(); // use _data to access GameData
        void Run();
    };
}
#endif