#include "Star.h"

#include "engine/resource/TextureManager.h"

Star::Star()
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/star.png");

	m_Sprite.setTexture(m_Texture);

	float Y = 200.0f;
	float X = 640.0f;

    sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition( X , Y);

}

void Star::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    move(m_Speed * 120.0f * dt.asSeconds());
}

void Star::initialize()
{
    m_Speed.x = -1.0f;
	m_Speed.y = 0.0f;
	
}