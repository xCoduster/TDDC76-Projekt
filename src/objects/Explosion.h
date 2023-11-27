#pragma once

#include "Collidable.h"
#include "AnimatedObject.h"

class Explosion : public AnimatedObject 
{
public:
    Explosion(sf::Vector2f start_pos);

    virtual void update(const sf::Time&, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual void Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
};