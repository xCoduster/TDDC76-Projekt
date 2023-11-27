#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
    Object()
        : m_Dead(false)
    {}

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) = 0;

    void move(sf::Vector2f distance)
    {
        m_Sprite.move(distance);
    }

    void setSprite(sf::Sprite& sprite)
    {
        m_Sprite = sprite;
    }

    sf::Sprite m_Sprite;
    bool m_Dead;

protected:
    sf::Texture m_Texture;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_Sprite, states);
    }
};