#ifndef SPACE_H
#define SPACE_H

#include "Game.h"
#include <vector>

namespace EdgarSam
{
    class Space
    {
    public:
        Space(GameDataPtr data);
        ~Space(){};
        void InitSpace();
        void update(float dt);
        void draw();

    private:
        GameDataPtr _data;
        std::vector<sf::Sprite> _spaceSprites;
        sf::Sprite _background_2;
        sf::Sprite _background;
    };
}
#endif