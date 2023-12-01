#pragma once

#include "objects/AnimatedObject.h"

#include <SFML/Audio.hpp>

#include <vector>

class Enemy : public AnimatedObject
{
public:
    Enemy();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

private:
    sf::Sound m_deathSound;

    sf::Time m_soundTimer;
};