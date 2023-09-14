#ifndef ASSETLIBRARY_H
#define ASSETLIBRARY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
namespace EdgarSam
{

    class AssetLibrary
    {
    public:
        AssetLibrary(){};
        ~AssetLibrary(){};
        void AddTexture(const std::string &fontName, const std::string &fileName);
        sf::Texture &getTexture(const std::string &fontName);
        void AddFont(const std::string &fontName, const std::string &fileName);
        sf::Font &getFont(const std::string &fontName);

    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
    };
}

#endif