#pragma once

#include "Enemy.h"
#include "objects/Player.h"


class Seeker : public Enemy
{
public:
    Seeker(Player* player);

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

private:
    Player* m_playerPtr;
};