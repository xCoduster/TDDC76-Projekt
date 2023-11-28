#pragma once

#include "Object.h"

class Star : public Object
{
public:
    Star();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;

private:
    void initialize();
    sf::Vector2f m_Speed;

};