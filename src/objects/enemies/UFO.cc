#include "UFO.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "objects/Projectile.h"
#include "objects/PowerUp.h"

#include "util/Util.h"

#include <cmath>

UFO::UFO()
	: Enemy{}, m_laserTimer{}
{
	m_animTimer = 0;
	m_currentFrame = 0;
	m_frameDuration = 0.1f;
	m_loop = true;

	m_Path = "res/ufo/ufo-0";
	loadFrames(3);

	sf::Vector2u texture_size{ m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);

	m_Tag |= Collision::UFO;

	m_Hitpoints = 1;
}

void UFO::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	Enemy::update(dt, new_objects);

	if (m_Hitpoints > 0)
	{
		movement(dt);
		animUpdate(dt);
		blast(dt, new_objects);
	}
}

void UFO::movement(const sf::Time& dt)
{
	m_Speed.x = -1.0f;
	m_Speed.y = 1.f * sin(m_Sprite.getPosition().x / 10);

	move(m_Speed * 75.0f * dt.asSeconds());
}

bool UFO::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (Enemy::Collision(other, new_objects))
		return true;
	
	return false;
}

void UFO::blast(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if (m_laserTimer > sf::seconds(1.0f))
	{
		m_laserTimer = sf::seconds(0);
		
		if (random(1, 3) != 1)
			return;

		Projectile* laser{ new Projectile(sf::Vector2f{ m_Sprite.getPosition().x - 64.f, m_Sprite.getPosition().y }, true) };
		new_objects.push_back(laser);

		//m_laserSound.setPitch(1.0f + random(0, 15) / 10.0f);
		//m_laserSound.play();
	}

	m_laserTimer += dt;
}