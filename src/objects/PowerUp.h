#pragma once

#include "Collidable.h"

class PowerUp : public Collidable
{
public:
    PowerUp();
    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

private:
    sf::Time lifeTime;
};