#pragma once

#include "objects/Collidable.h"

class PowerUp : public Collidable
{
public:
    PowerUp(const sf::Vector2f& cord);
    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

private:
    sf::Time lifeTime;
    float life;
};