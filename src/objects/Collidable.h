#pragma once

#include "Object.h"

#include <SFML/Graphics.hpp>

class Collidable : public Object
{
public:
    sf::Rect m_BoundingBox;

    bool Collides(const Collidable& other);
    virtual void Collision(const Collidable& other) = 0;
private:
    std::string m_Tag;
};