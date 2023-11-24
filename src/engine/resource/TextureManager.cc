#include "TextureManager.h"

TexturePtr TextureManager::load(const std::string& filePath)
{
    auto texIterator = textures.find(filePath);
    if (texIterator != textures.end())
    {
        return texIterator->second;
    }

    TexturePtr texture{ std::make_shared<sf::Texture>() };
    texture->loadFromFile(filePath);

    textures.insert(std::make_pair(filePath, texture));

    return texture;
}