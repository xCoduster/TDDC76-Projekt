#include "UFO.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "Projectile.h"

#include "util/Random.h"
#include <cmath>

UFO::UFO()
	: m_soundTimer{}
{
	m_animTimer = 0;
	m_currentFrame = 0;
	m_frameDuration = 0.1f;
	m_loop = true;

	AudioManager& audioMgr{ AudioManager::instance() };

	m_deathSound.setBuffer(*audioMgr.load("res/audio/ufo.wav"));
	m_deathSound.setVolume(50.0f);
	//m_deathSound.setPitch(1.5f + random(-3, 3) / 10.0f);

	TextureManager& texMgr{ TextureManager::instance() };

	for (int i = 0; i < 3; ++i)
	{
		m_frames.push_back(*texMgr.load("res/ufo/ufo-0" + std::to_string(i) + ".png"));
	}

	m_Texture = m_frames.at(m_currentFrame);

	m_Sprite.setTexture(m_Texture);

	float Y = 200.0f;
	float X = 640.0f;

	sf::Vector2u texture_size{ m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition(X, Y);

	m_Tag = Collision::Enemy | Collision::UFO;

	m_Hitpoints = 1;
}

void UFO::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if (m_Hitpoints <= 0)
	{
		if (m_soundTimer == sf::Time::Zero)
		{
			m_deathSound.play();
			m_Sprite.setColor(sf::Color(0, 0, 0, 0));
		}
		else
		{
			if (m_deathSound.getStatus() == sf::SoundSource::Stopped)
				m_Dead = true;
		}
		m_soundTimer += dt;
	}
	else
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
		
	if (m_Sprite.getPosition().x < 0)
		m_Dead = true;
}

void UFO::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->m_Tag & Collision::PlayerProj)
		m_Hitpoints -= 1;
	
	if (other->m_Tag & Collision::Explosion)
		m_Hitpoints -= 1;

	if (other->m_Tag == m_Tag)
	{
		if (m_Sprite.getPosition().y > other->m_Sprite.getPosition().y)
		{
			move(sf::Vector2f(0.0f, 10.0f));
		}
		else
			move(sf::Vector2f(0.0f, -10.0f));
	}
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