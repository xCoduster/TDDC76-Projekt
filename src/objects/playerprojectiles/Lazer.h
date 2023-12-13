#pragma once

#include "PlayerProjectile.h"

class Lazer : public PlayerProjectile
{
public:
    Lazer(const sf::Vector2f& cord);

    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
};