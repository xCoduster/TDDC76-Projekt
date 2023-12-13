#pragma once

#include "Collidable.h"
#include "AnimatedObject.h"

#include <SFML/Audio.hpp>

class Explosion : public AnimatedObject 
{
public:
    Explosion(const sf::Vector2f start_pos);

    virtual void update(const sf::Time&, std::vector<Object*>& new_objects) override;
    virtual void movement(const sf::Time& dt) override;
    virtual bool Collision(const Collidable* other, std::vector<Object*>& new_objects) override;
private:
    sf::Sound m_explosionSound;
};