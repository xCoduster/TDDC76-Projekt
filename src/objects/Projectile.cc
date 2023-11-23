#include "Projectile.h"

Projectile::Projectile(sf::Vector2f cord)
{
    m_Texture.loadFromFile("res/lazer.png");
	m_Sprite.setTexture(m_Texture);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    m_Sprite.setPosition(cord.x + texture_size.x, cord.y);

    m_Tag = Collision::Projectile;
} 

void Projectile::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Projectile::movement(const sf::Time& dt)
{
    m_Speed.x = 1.0f;
    move(m_Speed * 250.0f * dt.asSeconds());

    if ( m_Sprite.getPosition().x > 640 )
	{
		m_Dead = true;
	}
}

void Projectile::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{

}
