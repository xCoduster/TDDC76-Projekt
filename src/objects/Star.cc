#include "Star.h"

#include <cstdlib>

#include "engine/resource/TextureManager.h"

Star::Star()
	: m_Color{}, m_Speed{}
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/star.png");

	m_Sprite.setTexture(m_Texture);

	sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);

	m_Sprite.setScale(0.1f ,0.1f);
	
	starAllocation();

	float X = rand() % 640;
	float Y = rand() % 480;

	m_Sprite.setPosition( X , Y);

}

void Star::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    move(m_Speed * 120.0f * dt.asSeconds());
	sf::Vector2f position{ m_Sprite.getPosition() };
	if (position.x < 0)
		starAllocation();
}

void Star::starAllocation()
{
	float X = 642.0f;
	float Y = rand() % 480;
	
	int type = std::rand() % 3;
	switch(type)
	{
		case 0:
			m_Speed.x = -0.05f;
			m_Color = sf::Color(108,108,255,255);
			break;
		case 1:
			m_Speed.x = -0.08f;
			m_Color = sf::Color(158,255,158,255);
			break;
		case 2:
			m_Speed.x = -0.12f;
			m_Color = sf::Color(255,200,200,255);
			break;

	}
	m_Sprite.setColor(m_Color);
	m_Sprite.setPosition( X , Y);
}