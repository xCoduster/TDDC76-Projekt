#pragma once

#include "Collidable.h"

class Explosion : public Collidable
{
public:
    Explosion(sf::Vector2f start_pos);

    virtual void update(const sf::Time&, std::vector<Object*>& new_objects) override;
   
    virtual void Collision(const Collidable& other, std::vector<Object*>& new_objects) override;
};