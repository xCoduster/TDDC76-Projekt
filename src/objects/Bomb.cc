#include "Bomb.h"

#include "engine/resource/DataManager.h"

Bomb::Bomb()
	: MovingObject{}
{
	initialize("res/bomb.png");

	m_Velocity.x = -1.0f;
	m_Velocity.y = 0.0f;

	m_Tag = Collision::Enemy | Collision::Bomb;

	DataManager& dataMgr{ DataManager::instance() };
	EnemyData* data{ dynamic_cast<EnemyData*>(dataMgr.getData(Data::Type::Bomb)) };

	m_Speed = data->speed;
}

void Bomb::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
}

void Bomb::movement(const sf::Time& dt)
{
	move(m_Velocity * m_Speed * dt.asSeconds());

	if ( m_Sprite.getPosition().x < 0 )
	{
		m_Dead = true;
	}

}

bool Bomb::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->getTag() & (Collision::PlayerProj |Collision::Explosion) )
	{
		Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);

		m_Dead = true;

		m_addScore = true;

		return true;
	}

	if (other->getTag() & Collision::Player)
	{
		Explosion* ex{ new Explosion{ m_Sprite.getPosition() } };
		new_objects.push_back(ex);

		m_Dead = true;

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