#include "MissileUp.h"

#include <iostream>

#include "engine/resource/DataManager.h"

MissileUp::MissileUp(sf::Vector2f cord)
    : PowerUp{cord}
{
    initialize("res/powerUpMissile.png");
    m_Tag = Collision::MissileUp;
}
