#include "EnemyProjectile.h"

#include "engine/resource/TextureManager.h"
#include <cmath>

EnemyProjectile::EnemyProjectile(sf::Vector2f cord, float angle)
{
    TextureManager& texMgr{ TextureManager::instance() };
    m_Texture = *texMgr.load("res/lazer.v2.png");

	m_Sprite.setTexture(m_Texture);
    sf::Vector2u texture_size { m_Texture.getSize() };
    m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
    m_Sprite.setPosition(cord.x + texture_size.x, cord.y);

    m_Speed.x = cos(angle);
    m_Speed.y = sin(angle);
    m_Tag = Collision::EnemyProj;
} 

void EnemyProjectile::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void EnemyProjectile::movement(const sf::Time& dt)
{
    move(m_Speed * 150.0f * dt.asSeconds());

    sf::Vector2f position{ m_Sprite.getPosition() };

	if (position.x < 0 || position.x > 640)
        m_Dead = true;

	if (position.y < 0 || position.y > 480)
		m_Dead = true;
}


bool EnemyProjectile::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
    if (other->m_Tag & Collision::Player)
    {
        m_Dead = true;

        return true;
    }
    return false;
}
