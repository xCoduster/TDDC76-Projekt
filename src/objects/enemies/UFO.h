#pragma once

#include "Enemy.h"

#include <SFML/Audio.hpp>

class UFO : public Enemy
{
public:
    UFO();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

    void blast(const sf::Time& dt, std::vector<Object*>& new_objects);

private:
    sf::Time m_laserTimer;
};