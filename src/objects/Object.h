#pragma once

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
public:
    Object()
        : m_Dead{false}, m_addScore{ false }, m_Texture{}, m_Sprite{}
    {}

    virtual void update(const sf::Time& dt, std::vector<Object*>& new_objects) = 0;

    void move(const sf::Vector2f& distance)
    {
        m_Sprite.move(distance);
    }

    void setSprite(sf::Sprite& sprite)
    {
        m_Sprite = sprite;
    }

    void setPosition(const sf::Vector2f& position)
    {
        m_Sprite.setPosition(position);
    }

    sf::Sprite m_Sprite;
    bool m_Dead;
    bool m_addScore;

protected:
    sf::Texture m_Texture;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_Sprite, states);
    }
};