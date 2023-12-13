#include "HpUp.h"

#include <iostream>

#include "engine/resource/DataManager.h"

HpUp::HpUp(const sf::Vector2f& cord)
    : PowerUp{cord}
{
    initialize("res/hpUp.png");
    m_Tag = Collision::HpUp;
}
