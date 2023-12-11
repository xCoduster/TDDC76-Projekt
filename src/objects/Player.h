#pragma once

#include "MovingObject.h"

#include <SFML/Audio.hpp>

class Player : public MovingObject
{
public:
    Player();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

    void blast(const sf::Time& dt, std::vector<Object*>& new_objects);
    void hurt(int amount = 1);

    void setgodMode()
    {
        m_godMode = !m_godMode;
    }

private:
    bool active_powerUp;
    bool m_godMode;

    sf::Time m_t_lazer;
    sf::Time m_t_powerUp;
    sf::Time m_t_invincibility;

    sf::Sound m_hurtSound;
    sf::Sound m_laserSound;
    sf::Sound m_pickUpSound;
};