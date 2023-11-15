#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
    virtual void update(const sf::Time& dt) = 0;
    void move(sf::Vector2f distance)
    {
        m_Sprite.move(distance);
    }

    void setSprite(sf::Sprite& sprite)
    {
        m_Sprite = sprite;
    }

    sf::Sprite m_Sprite;
protected:
    sf::Texture m_Texture;
    bool m_Dead;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_Sprite, states);
    }
};