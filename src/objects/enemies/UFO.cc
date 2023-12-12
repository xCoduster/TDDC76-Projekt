#include "UFO.h"

#include "engine/resource/AudioManager.h"

#include "objects/EnemyProjectile.h"
#include "objects/powerups/PowerUp.h"

#include "util/Util.h"
#include "util/Constants.h"

#include "engine/resource/DataManager.h"

#include <cmath>

UFO::UFO()
	: Enemy{}, m_laserTimer{}
{
	m_animTimer = 0;
	m_currentFrame = 0;
	m_frameDuration = 0.1f;
	m_loop = true;

	m_Path = "res/ufo/ufo-0";
	initialize(m_Path + "0.png");
	loadFrames(3);

	m_Tag |= Collision::UFO;

	DataManager& dataMgr{ DataManager::instance() };
	EnemyData* data{ dynamic_cast<EnemyData*>(dataMgr.getData(Data::Type::UFO)) };

	m_Hitpoints = data->hp;
	m_Speed = data->speed;
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
	m_Velocity.x = -1.0f;
	m_Velocity.y = 1.f * sin(m_Sprite.getPosition().x / 10);

	move(m_Velocity * m_Speed * dt.asSeconds());
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

		EnemyProjectile* laser{ new EnemyProjectile(sf::Vector2f{ m_Sprite.getPosition().x - 64.f, m_Sprite.getPosition().y }, pi) };
		new_objects.push_back(laser);
	}

	m_laserTimer += dt;
}