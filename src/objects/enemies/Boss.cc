#include "Boss.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "objects/EnemyProjectile.h"

#include "util/Random.h"
#include <cmath>

Boss::Boss()
	: m_soundTimer{}, angle{0}, m_t_lazer {}
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/bomb.png");

	m_Sprite.setTexture(m_Texture);

	m_Sprite.setScale(3.0f, 3.0f);
    sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition(640, 480 / 2);

	m_Tag = Collision::Enemy;

	m_Hitpoints = 3;

	m_Speed.x = -1.0f;
	m_Speed.y = 0.0f;
	bossPhase = firstPhase; 
}

void Boss::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	Enemy::update(dt, new_objects);
	movement(dt);
	blast(dt, new_objects);
	set_phase();
}

void Boss::movement(const sf::Time& dt)
{	
	switch(bossPhase)
	{
		case firstPhase:
			move(m_Speed * 120.0f * dt.asSeconds());
			break;
		case secondPhase:
			m_Speed.x = 0.0f;
			m_Speed.y = cos(angle);
			angle += 0.0157f;
			move(m_Speed * 180.0f * dt.asSeconds());
			break;
		case thirdPhase:
			sf::Vector2f center {320.0f, 240.0f};
		    sf::Vector2f difVec =  center - m_Sprite.getPosition();
			float vecSize = sqrt(difVec.x*difVec.x+ difVec.y*difVec.y);
			m_Speed = difVec/vecSize;
			move(m_Speed * 120.0f * dt.asSeconds());
			break;
	}
}

void Boss::set_phase()
{
	switch(bossPhase)
	{
		case firstPhase:
			if (m_Sprite.getPosition().x < 550)
				bossPhase = secondPhase;
			break;
		case secondPhase:
			if (m_Hitpoints <= 2)
				bossPhase = thirdPhase;
			break;
		case thirdPhase:
			if (m_Sprite.getPosition().x < 320)
				bossPhase = fourthPhase;
			break;
	}
}

bool Boss::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (Enemy::Collision(other, new_objects))
		return true;
	return false;
}

void Boss::blast(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if(m_t_lazer.asSeconds() > 0.6f)
	{
		m_t_lazer = sf::seconds(0);
		sf::Vector2f lazer_pos = m_Sprite.getPosition();
		sf::Vector2u texture_size { m_Texture.getSize() };
		float radius = texture_size.x / 2;
		float pi = 3.14;
		
		switch(bossPhase)
		{
			case secondPhase:
			{
				EnemyProjectile* lazer1{ new EnemyProjectile(m_Sprite.getPosition(), pi)};
				lazer_pos.y += 30; 
				EnemyProjectile* lazer2{ new EnemyProjectile(lazer_pos, 5 * pi / 6) };
				lazer_pos.y -= 60;
				EnemyProjectile* lazer3{ new EnemyProjectile(lazer_pos, - 5 * pi / 6) };
				new_objects.push_back(lazer1);
				new_objects.push_back(lazer2);
				new_objects.push_back(lazer3);
			}
				break;
			case fourthPhase:
			{
				sf::Vector2f enhetscirkeln = {3.0*radius*cos(phi), 3.0*radius*sin(phi)};
				lazer_pos = (m_Sprite.getPosition() + enhetscirkeln);
				EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos, phi) };
				new_objects.push_back(lazer);
				phi++;
			}
				break;
		}
	}
	m_t_lazer += dt;
}
