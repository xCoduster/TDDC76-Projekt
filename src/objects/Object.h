#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable, public sf::Transformable
{
public:
    virtual void update(const sf::Time& dt) = 0;

    void setSprite(sf::Sprite& sprite)
    {
        m_Sprite = sprite;
    }

protected:
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;
    bool m_Dead;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(m_Sprite, states);
    }
};