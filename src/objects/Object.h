#pragma once

#include "engine/resource/TextureManager.h"

#include <SFML/Graphics.hpp>
#include <string>

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

    sf::Vector2f getPosition() const
    {
        return m_Sprite.getPosition();
    }

    bool isDead() const 
    {
        return m_Dead;
    }
    
    sf::Sprite m_Sprite;

    bool m_addScore;

protected:
    sf::Texture m_Texture;
    bool m_Dead;

    void initialize(std::string Path)
    {
        TextureManager& texMgr{ TextureManager::instance() };
        m_Texture = *texMgr.load(Path);

	    m_Sprite.setTexture(m_Texture);
        sf::Vector2u texture_size { m_Texture.getSize() };
        m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    }

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_Sprite, states);
    }
};