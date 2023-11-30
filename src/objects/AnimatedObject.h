#pragma once

#include "MovingObject.h"

#include <SFML/Graphics.hpp>
#include <string>

class AnimatedObject: public MovingObject
{

protected:
    void animUpdate(const sf::Time& dt);
    void loadFrames(int amountOfFrames);

    std::string m_Path;
    int m_currentFrame;
    float m_animTimer;
    std::vector<sf::Texture> m_frames;
    float m_frameDuration;
    bool m_loop;
};