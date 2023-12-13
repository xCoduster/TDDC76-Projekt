#pragma once

#include "PlayerProjectile.h"
#include "objects/Explosion.h"

class Missile : public PlayerProjectile
{
public:
    Missile(const sf::Vector2f cord);

    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
};