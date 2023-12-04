#pragma once

#include "Enemy.h"

#include <SFML/Audio.hpp>

class Boss : public Enemy
{
public:
    Boss();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;

    void blast(const sf::Time& dt, std::vector<Object*>& new_objects);
private:
    sf::Sound m_deathSound;
    sf::Time m_soundTimer;
    sf::Time m_laserTimer;
    sf::Time m_t_lazer;
    float angle;
    float phi {};
    void set_phase(); 
enum BossPhase
    {
        firstPhase,
        secondPhase,
        thirdPhase,
        fourthPhase
    };
    BossPhase bossPhase; 
};
 