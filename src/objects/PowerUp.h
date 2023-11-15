#pragma once

#include "Collidable.h"

class PowerUp : public Collidable
{
public:
    PowerUp() {}

    virtual void update(const sf::Time& dt) override;
    virtual void movement(const sf::Time& dt);
    virtual void Collision(const Collidable& other) override;

private:
int powerUpType;
int lifeTime;

};