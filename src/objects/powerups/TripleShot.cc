#include "TripleShot.h"

#include <iostream>

#include "engine/resource/DataManager.h"

TripleShot::TripleShot(sf::Vector2f cord)
    : PowerUp{cord}
{
    initialize("res/powerUpTripleShot.png");
    m_Tag = Collision::PowerUp;
}
