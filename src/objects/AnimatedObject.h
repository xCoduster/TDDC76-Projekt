#pragma once

#include "MovingObject.h"

#include <SFML/Graphics.hpp>

class AnimatedObject: public MovingObject
{

protected:
    void animUpdate(const sf::Time& dt);

    int m_currentFrame;
    float m_animTimer;
    std::vector<sf::Texture> m_frames;
    float m_frameDuration;
};