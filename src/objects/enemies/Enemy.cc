#include "Enemy.h"

#include "engine/resource/AudioManager.h"
#include "objects/PowerUp.h"

#include "util/Util.h"

Enemy::Enemy()
	: AnimatedObject{}, m_soundTimer {}, m_deathSound{}
{
	AudioManager& audioMgr{ AudioManager::instance() };

	m_deathSound.setBuffer(*audioMgr.load("res/audio/ufo.wav"));
	m_deathSound.setVolume(50.0f);

	m_Tag = Collision::Enemy;
}

void Enemy::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if (m_Hitpoints <= 0)
	{
		if (m_soundTimer == sf::Time::Zero)
		{
			m_deathSound.play();
			m_Sprite.setColor(sf::Color(0, 0, 0, 0));

			if (random(2, 1) == 0)
				new_objects.push_back(new PowerUp{ m_Sprite.getPosition() ,  random(1, 3)});
		}
		else
		{
			if (m_deathSound.getStatus() == sf::SoundSource::Stopped)
			{
				m_Dead = true;
				m_addScore = true;
			}
		}
		m_soundTimer += dt;
	}
	else
	{
		if (m_Sprite.getPosition().x < 0)
			m_Dead = true;
	}
}

bool Enemy::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->getTag() & Collision::PlayerProj)
	{
		m_Hitpoints -= 1;
		return true;
	}

	if (other->getTag() & Collision::Explosion)
	{
		m_Hitpoints -= 1;
		return true;
	}

	if (other->getTag() == m_Tag)
	{
		if (m_Sprite.getPosition().y > other->getPosition().y)
		{
			move(sf::Vector2f(0.0f, 10.0f));
		}
		else
			move(sf::Vector2f(0.0f, -10.0f));

		return true;
	}

	return false;
}