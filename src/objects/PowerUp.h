#pragma once

#include "Collidable.h"

class PowerUp : public Collidable
{
public:
    PowerUp();

    virtual void update(const sf::Time& dt) override;
    virtual void Collision(const Collidable& other) override;

private:
int lifeTime;

};