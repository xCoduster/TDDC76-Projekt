#pragma once

#include <SFML/Graphics.hpp>

class AnimationManager
{
public:
    AnimationManager();

    bool update(const sf::Time& dt, sf::Sprite& sprite,const std::vector<sf::Texture>& textures, const float frameDuration);

private:
    int currentFrame;
    float animTimer;
};