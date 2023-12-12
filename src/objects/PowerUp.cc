#include "PowerUp.h"

#include <iostream>

#include "engine/resource/DataManager.h"

PowerUp::PowerUp(sf::Vector2f cord, int type)
    : Collidable{}, lifeTime{}, life{}
{
    if ( type == 1 )
    {
        initialize("res/powerUpTripleShot.png");
        m_Tag = Collision::PowerUp;
    }
    if ( type == 2 )
    {
        initialize("res/hpUp.png");
        m_Tag = Collision::HpUp;
    }
    if ( type == 3 )
    {
        initialize("res/missile.png");
        m_Tag = Collision::missile;
    }

    m_Sprite.setPosition(cord.x, cord.y);

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
