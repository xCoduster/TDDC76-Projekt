#pragma once

#include "AnimatedObject.h"

#include <SFML/Audio.hpp>

class UFO : public AnimatedObject
{
public:
    UFO();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

private:
    sf::Sound m_deathSound;

    sf::Time m_soundTimer;
};