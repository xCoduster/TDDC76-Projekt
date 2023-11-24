#pragma once

#include <SFML/Graphics.hpp>

class AnimationManager
{
public:
    AnimationManager(std::vector<sf::Texture> textures, int animSpeed);

    void update(const sf::Time& dt, sf::Sprite sprite);
    
private:
    std::vector<sf::Texture> frames;

    int currentFrame;
    
};