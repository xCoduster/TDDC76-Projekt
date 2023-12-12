#include "Player.h"

#include "PlayerProjectile.h"
#include "Lazer.h"
#include "Missile.h"

#include "engine/resource/AudioManager.h"
#include "engine/resource/DataManager.h"

#include "util/Util.h"
#include "util/Constants.h"


Player::Player()
	: MovingObject{}, active_tripleshot { false }, active_missile{ false }, m_t_lazer{}, m_t_tripleshot{},
	m_t_invincibility{}, m_godMode{ false }, m_pickUpSound{}, m_t_missile{},  
	m_laserSound{}, m_hurtSound{}, m_fireRate{}
{
	AudioManager& audioMgr{ AudioManager::instance() };
	m_hurtSound.setBuffer(*audioMgr.load("res/audio/hurt.wav"));
	m_pickUpSound.setBuffer(*audioMgr.load("res/audio/powerup.wav"));
	m_laserSound.setBuffer(*audioMgr.load("res/audio/laser.wav"));
	m_laserSound.setVolume(75.0f);

	initialize("res/player.png");

	sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setPosition(texture_size.x, screenHeight / 2);

	m_Tag = Collision::Player;

	DataManager& dataMgr{ DataManager::instance() };
	PlayerData* data{ dynamic_cast<PlayerData*>(dataMgr.getData(Data::Type::Player)) };

	m_fireRate = data->fireRate;
	m_Hitpoints = data->hp;
	m_Speed = data->speed;
}

void Player::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	m_t_tripleshot += dt;
	m_t_missile +=dt;

	if (m_t_tripleshot > sf::seconds(10))
		active_tripleshot = false;

	if (m_t_missile > sf::seconds(10))
		active_missile = false;

	if (m_t_invincibility >= sf::seconds(0.0f))
		m_t_invincibility -= dt;

	if (m_Hitpoints > 0)
	{
		movement(dt);
		blast(dt, new_objects);
	}
	else
	{
		m_Sprite.setColor(sf::Color{ 0 });
		m_Dead = true;
	}
}

void Player::movement(const sf::Time& dt)
{
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;

	sf::Vector2f old_position{ m_Sprite.getPosition() };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_Velocity.x = -1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_Velocity.x = 1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_Velocity.y = -1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_Velocity.y = 1.0f;

	if (m_Velocity.x != 0.0f || m_Velocity.y != 0.0f)
	{
		if (m_Velocity.x != 0.0f && m_Velocity.y != 0.0f)
			m_Velocity /= root2;

		move(m_Velocity * m_Speed * dt.asSeconds());
	}

	sf::Vector2f position{ m_Sprite.getPosition() };
	sf::FloatRect boundingBox{ m_Sprite.getGlobalBounds() };

	if (position.x - boundingBox.width / 2 < 0 || position.x + boundingBox.width / 2 > screenWidth)
		position.x = old_position.x;

	if (position.y - boundingBox.height / 2 < 0 || position.y + boundingBox.height / 2 > screenHeight)
		position.y = old_position.y;

	m_Sprite.setPosition(position);
}		

bool Player::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (m_Hitpoints <= 0)
		return false;

	if (other->getTag() & Collision::PowerUp)
	{
		active_tripleshot = true;
		m_t_tripleshot = sf::seconds(0);
		m_pickUpSound.play();

		return true;
	}

	if (other->getTag() & Collision::HpUp)
	{
		m_Hitpoints += 1;
		m_pickUpSound.play();

		return true;
	}

	if (other->getTag() & Collision::MissileUp)
	{
		active_missile = true;
		m_t_missile = sf::seconds(0);
		m_pickUpSound.play();

		return true;
	}

	if (other->getTag() & (Collision::Explosion | Collision::Enemy | Collision::EnemyProj))
	{
		hurt();
		return true;
	}

	return false;
} 

void Player::blast(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_t_lazer.asSeconds() > m_fireRate)
	{
		m_t_lazer = sf::seconds(0);

		if(active_tripleshot == true && active_missile == true)
		{
			sf::Vector2f lazer_pos = m_Sprite.getPosition();
			lazer_pos.y += 60.f;
			for(int i { 0 }; i < 3; i++)
			{
				lazer_pos.y -= 30.f;
				Missile* rocket{ new Missile(lazer_pos)};
				new_objects.push_back(rocket);
			}
		}

		else if(active_tripleshot == true && active_missile == false)
		{
			sf::Vector2f lazer_pos = m_Sprite.getPosition();
			lazer_pos.y += 60.f;
			for(int i { 0 }; i < 3; i++)
			{
				lazer_pos.y -= 30.f;
				Lazer* lazer{ new Lazer(lazer_pos)};
				new_objects.push_back(lazer);
			}
		}

		else if(active_missile == true && active_tripleshot == false)
		{
			Missile* rocket{ new Missile(m_Sprite.getPosition())};
			new_objects.push_back(rocket);
		}

		else
		{	
			Lazer* lazer{ new Lazer(m_Sprite.getPosition()) };
			new_objects.push_back(lazer);
		}

		m_laserSound.setPitch(1.0f + random(0, 15) / 10.0f);
		m_laserSound.play();
	}
	m_t_lazer += dt;
}

void Player::hurt(int amount)
{
	if (!m_godMode)
	{
		if (m_t_invincibility <= sf::seconds(0.0f))
		{
			m_t_invincibility = sf::seconds(1.0f);
			m_Hitpoints -= 1;
			m_hurtSound.play();
		}
	}
}