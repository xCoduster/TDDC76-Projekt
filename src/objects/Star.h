#pragma once

#include "Object.h"

class Star : public Object
{
public:
    Star();

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) override;

private:
    void starAllocation();
    sf::Vector2f m_Speed;
    sf::Color m_Color;
    float greenSpeed;
    float blueSpeed;
    float redSpeed;


};