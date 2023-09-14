#include "AssetLibrary.h"
#include <algorithm>

namespace EdgarSam
{
    void AssetLibrary::AddTexture(const std::string &textureName, const std::string &fileName)
    {
        sf::Texture texture;
        if (texture.loadFromFile(fileName))
        {
            // Use the textureName as the key to store the loaded texture.
            this->textures[textureName] = texture;
        }
        else
        {
            // Handle the case where the file failed to load.
            std::cerr << "Error loading texture: " << fileName << std::endl;
        }
    }

    sf::Texture &AssetLibrary::getTexture(const std::string &textureName)
    {
        // Check if the textureName exists in the map before returning it.
        if (this->textures.find(textureName) != this->textures.end())
        {
            return this->textures.at(textureName);
        }
        else
        {
            // Handle the case where the requested texture is not found
            throw std::runtime_error("Texture not found: " + textureName);
        }
    }

    void AssetLibrary::AddFont(const std::string &fontName, const std::string &fileName)
    {
        sf::Font font;
        if (font.loadFromFile(fileName))
        {
            // Use the fontName as the key to store the loaded font.
            this->fonts[fontName] = font;
        }
        else
        {
            // Handle the case where the file failed to load
            std::cerr << "Error loading font: " << fileName << std::endl;
        }
    }

    sf::Font &AssetLibrary::getFont(const std::string &fontName)
    {
        // Check if the fontName exists in the map before returning it.
        if (this->fonts.find(fontName) != this->fonts.end())
        {
            return this->fonts.at(fontName);
        }
        else
        {
            // Handle the case where the requested font is not found
            throw std::runtime_error("Font not found: " + fontName);
        }
    }
}
