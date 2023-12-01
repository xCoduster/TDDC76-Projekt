#include "Boss.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "Projectile.h"

#include "util/Random.h"
#include <cmath>

Boss::Boss()
	: m_soundTimer{}
{
}

void Boss::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{

}

void Boss::movement(const sf::Time& dt)
{

}

bool Boss::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{

}

void Boss::blast(const sf::Time& dt, std::vector<Object*>& new_objects)
{

}