#include "PowerUp.h"

PowerUp::PowerUp()
{
    m_Texture.loadFromFile("res/powerUp.png");
	m_Sprite.setTexture(m_Texture);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    m_Sprite.setPosition(640 / 2, 480 / 2);
}

void PowerUp::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{

}

void PowerUp::Collision(const Collidable& other, std::vector<Object*>& new_objects)
{
	
}
