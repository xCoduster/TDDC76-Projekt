#pragma once

#include <SFML/Graphics.hpp>

class AnimationManager
{
public:
    AnimationManager(std::vector<sf::Texture> textures, float frameDuration);

    void update(const sf::Time& dt, sf::Sprite& sprite);

private:
    std::vector<sf::Texture> frames;

    int currentFrame;
    float animTimer;
    float animSpeed;

};