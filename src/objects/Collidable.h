#pragma once

#include "Object.h"

#include <SFML/Graphics.hpp>

class Collidable : public Object
{
public:
    bool Collides(const Collidable& other);
    virtual void Collision(const Collidable& other, std::vector<Object*>& new_objects) = 0;
protected:
    std::string m_Tag;
};