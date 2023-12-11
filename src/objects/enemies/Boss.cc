#include "Boss.h"

#include "engine/resource/AudioManager.h"
#include "engine/resource/DataManager.h"

#include "objects/EnemyProjectile.h"

#include "util/Util.h"
#include "util/Constants.h"
#include <cmath>

Boss::Boss()
	: Enemy{}, angle{ 0 }, m_laserTimer{}, m_t_lazer{}, phi{}, fire_rate{}, bossPhase{ BossPhase::firstPhase }
{
	initialize("res/boss.png");
	
	m_Sprite.setScale(3.0f, 3.0f);
	m_Sprite.setPosition(screenWidth, screenHeight/ 2);

	m_Tag = Collision::Enemy;

	m_Velocity.x = -1.0f;
	m_Velocity.y = 0.0f;

	DataManager& dataMgr { DataManager::instance() };
	BossData* data{ dynamic_cast<BossData*>(dataMgr.getData(Data::Type::Boss)) };

	MAX_HP = data->hp;
	m_Hitpoints = MAX_HP;
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
			move(m_Velocity * 120.0f * dt.asSeconds());
			break;
		case BossPhase::secondPhase:
			m_Velocity.x = 0.0f;
			m_Velocity.y = cos(angle);
			angle += pi / 2 * dt.asSeconds();
			move(m_Velocity * 180.0f * dt.asSeconds());
			break;
		case BossPhase::thirdPhase:
			sf::Vector2f center {screenWidth / 2, screenHeight / 2};
		    sf::Vector2f difVec =  center - m_Sprite.getPosition();
			float vecSize = sqrt(difVec.x*difVec.x+ difVec.y*difVec.y);
			m_Velocity = difVec/vecSize;
			move(m_Velocity * 120.0f * dt.asSeconds());
			break;
	}
}

void Boss::set_phase()
{
	switch(bossPhase)
	{
		case BossPhase::firstPhase:
			if (m_Sprite.getPosition().x < screenWidth * 0.85f)
			{
				fire_rate = 0.6f;
				bossPhase = BossPhase::secondPhase;
			}
			break;
		case BossPhase::secondPhase:
			if (m_Hitpoints <= MAX_HP * 2 / 3)
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
			if(m_Hitpoints <= MAX_HP * 1 / 3)
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
		sf::Vector2f lazer_pos{ m_Sprite.getPosition() };
		sf::Vector2u texture_size{ m_Texture.getSize() };
		float radius = texture_size.x / 2.f;

		switch(bossPhase)
		{
			case BossPhase::secondPhase:
			{
				lazer_pos.y += 60.f;
				for(int i { 0 }; i < 3; i++)
				{
					lazer_pos.y -= 30.f;
					EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos, 5.f * pi / 6.f + i * pi / 6.f) };
					new_objects.push_back(lazer);
					lazer_pos.y -= 30.f;
				}
			}
				break;
			case BossPhase::fourthPhase:
			{
				for(int i{ 0 }; i < 4; i++)
				{
					sf::Vector2f bossCircumference{ 3.f * radius * std::cos(phi + (i * pi / 2.f)), 3.f * radius * std::sin(phi + (i * pi / 2.f)) };
					EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos + bossCircumference, phi + (i * pi / 2.f)) };
					new_objects.push_back(lazer);
				}
				phi += 2 * pi * dt.asSeconds();
			}
				break;
			case BossPhase::fifthPhase:
			{
				for(int i{ 0 }; i < 4; i++)
				{
					sf::Vector2f bossCircumference{ 3.f * radius * std::cos(phi + (i * pi / 2.f)), 3.f * radius * std::sin(phi + (i * pi / 2.f)) };
					EnemyProjectile* lazer{ new EnemyProjectile(lazer_pos + bossCircumference, phi + (i * pi / 2.f)) };
					new_objects.push_back(lazer);
				}
				phi++;
			}
				break;
		}
	}
	m_t_lazer += dt;
}
