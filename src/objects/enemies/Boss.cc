#include "Boss.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "objects/EnemyProjectile.h"

#include "util/Util.h"
#include <cmath>

Boss::Boss()
	: m_soundTimer{}, angle{ 0 }, m_t_lazer{}
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/boss.png");

	m_Sprite.setTexture(m_Texture);

	m_Sprite.setScale(3.0f, 3.0f);
    sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition(640, 480 / 2);

	m_Tag = Collision::Enemy;

	m_Hitpoints = 9;

	m_Speed.x = -1.0f;
	m_Speed.y = 0.0f;
	bossPhase = BossPhase::firstPhase; 
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
		case BossPhase::firstPhase:
			move(m_Speed * 120.0f * dt.asSeconds());
			break;
		case BossPhase::secondPhase:
			m_Speed.x = 0.0f;
			m_Speed.y = cos(angle);
			angle += 0.0157f;
			move(m_Speed * 180.0f * dt.asSeconds());
			break;
		case BossPhase::thirdPhase:
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
		case BossPhase::firstPhase:
			if (m_Sprite.getPosition().x < 550)
			{
				fire_rate = 0.6f;
				bossPhase = BossPhase::secondPhase;
			}
			break;
		case BossPhase::secondPhase:
			if (m_Hitpoints <= 6)
				bossPhase = BossPhase::thirdPhase;
			break;
		case BossPhase::thirdPhase:
			if (m_Sprite.getPosition().x < 320)
			{
				fire_rate = 0.2f;
				bossPhase = BossPhase::fourthPhase;
			}
			break;
		case BossPhase::fourthPhase:
			if(m_Hitpoints <= 3)
			{
				fire_rate = 0.4f;
				bossPhase = BossPhase::fifthPhase;
			}
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
	if(m_t_lazer.asSeconds() > fire_rate)
	{
		m_t_lazer = sf::seconds(0);
		sf::Vector2f lazer_pos = m_Sprite.getPosition();
		sf::Vector2u texture_size { m_Texture.getSize() };
		float radius = texture_size.x / 2;
		float pi = 3.14f;
		
		switch(bossPhase)
		{
			case BossPhase::secondPhase:
			{
				lazer_pos.y += 30.f;
				for(int i { 0 }; i < 3; i++)
				{
					lazer_pos.y -= 30.f*i;
					EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos, 5.f * pi / 6.f + i * pi / 6.f) };
					new_objects.push_back(lazer);
				}
			}
				break;
			case BossPhase::fourthPhase:
			{
				for(int i { 0 }; i < 4; i++)
				{
					sf::Vector2f enhetscirkeln{ 3.f * radius * std::cos(phi + (i * pi / 2.f)), 3.f * radius * std::sin(phi + (i * pi / 2.f)) };
					lazer_pos = (m_Sprite.getPosition() + enhetscirkeln);
					EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos, phi + (i * pi / 2.f)) };
					new_objects.push_back(lazer);
				}
				phi += pi*dt.asSeconds();
			}
				break;
			case BossPhase::fifthPhase:
			{
				for(int i { 0 }; i < 4; i++)
				{
					sf::Vector2f enhetscirkeln{ 3.f * radius * std::cos(phi + (i * pi / 2.f)), 3.f * radius * std::sin(phi + (i * pi / 2.f)) };
					lazer_pos = (m_Sprite.getPosition() + enhetscirkeln);
					EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos, phi + (i * pi / 2.f)) };
					new_objects.push_back(lazer);
				}
				phi++;
			}
				break;
		}
	}
	m_t_lazer += dt;
}
