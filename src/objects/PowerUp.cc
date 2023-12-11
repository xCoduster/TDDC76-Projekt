#include "PowerUp.h"

#include <iostream>

#include "engine/resource/DataManager.h"

PowerUp::PowerUp(sf::Vector2f cord)
    : Collidable{}, lifeTime{}, life{}
{
    initialize("res/powerUp.png");

    m_Sprite.setPosition(cord.x, cord.y);

    m_Tag = Collision::PowerUp;

    DataManager& dataMgr{ DataManager::instance() };
    PowerUpData* data{ dynamic_cast<PowerUpData*>(dataMgr.getData(Data::Type::PowerUp)) };

    life = data->lifeTime;
}

void PowerUp::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    lifeTime += dt;
    if (lifeTime.asSeconds() > life)
    {   
        m_Dead = true;        
    }
}

bool PowerUp::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->getTag() & Collision::Player)
    {
        m_Dead = true;
        return true;
    }

    return false;
}
