#include "Projectile.h"

Projectile::Projectile()
{
    m_Texture.loadFromFile("res/temp_lazer.png");
	m_Sprite.setTexture(m_Texture);
    m_Sprite.setRotation(90);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    m_Sprite.setPosition(640 / 2, 480 / 2);


} 

void Projectile::update(const sf::Time& dt)
{
    movement(dt);
}

void Projectile::movement(const sf::Time& dt)
{
    m_Speed.x = 1.0f;
    move(m_Speed * 120.0f * dt.asSeconds());
}

void Projectile::Collision(const Collidable& other)
{
	
}
