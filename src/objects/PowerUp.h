#pragma once

#include "Collidable.h"

class PowerUp : public Collidable
{
public:
    PowerUp(sf::Vector2f cord, int type);
    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

private:
    sf::Time lifeTime;
    float life;
};