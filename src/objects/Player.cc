#include "Player.h"

#include "Projectile.h"

#include "engine/resource/AudioManager.h"

#include "util/Util.h"

#include <iostream>

Player::Player()
	: active_powerUp{ false }, m_t_lazer{}, m_t_powerUp{}, 
	m_t_invincibility{}, m_godMode{ false }, m_pickUpSound{}, 
	m_laserSound{}, m_hurtSound{}
{
	AudioManager& audioMgr{ AudioManager::instance() };
	m_hurtSound.setBuffer(*audioMgr.load("res/audio/hurt.wav"));
	m_pickUpSound.setBuffer(*audioMgr.load("res/audio/powerup.wav"));
	m_laserSound.setBuffer(*audioMgr.load("res/audio/laser.wav"));
	m_laserSound.setVolume(75.0f);

	initialize("res/player.v2.png");

	sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setPosition(texture_size.x, 480 / 2);

	m_Tag = Collision::Player;

	m_Hitpoints = 5;
}

void Player::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	m_t_powerUp += dt;

	if (m_t_powerUp > sf::seconds(10))
		active_powerUp = false;

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
	m_Speed.x = 0.0f;
	m_Speed.y = 0.0f;

	sf::Vector2f old_position{ m_Sprite.getPosition() };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_Speed.x = -1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_Speed.x = 1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_Speed.y = -1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_Speed.y = 1.0f;

	if (m_Speed.x != 0.0f || m_Speed.y != 0.0f)
	{
		if (m_Speed.x != 0.0f && m_Speed.y != 0.0f)
			m_Speed *= 0.70710678f;

		move(m_Speed * 150.0f * dt.asSeconds());
	}

	sf::Vector2f position{ m_Sprite.getPosition() };
	sf::FloatRect boundingBox{ m_Sprite.getGlobalBounds() };

	if (position.x - boundingBox.width / 2 < 0 || position.x + boundingBox.width / 2 > 640)
		m_Sprite.setPosition(sf::Vector2f{ old_position.x, position.y });

	position = m_Sprite.getPosition();

	if (position.y - boundingBox.height / 2 < 0 || position.y + boundingBox.height / 2 > 480)
		m_Sprite.setPosition(sf::Vector2f{ position.x, old_position.y });
}

bool Player::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (m_Hitpoints <= 0)
		return false;

	if (other->m_Tag & Collision::PowerUp)
	{
		active_powerUp = true;
		m_t_powerUp = sf::seconds(0);
		m_pickUpSound.play();

		return true;
	}

	if (other->m_Tag & (Collision::Explosion | Collision::Enemy | Collision::EnemyProj))
	{
		hurt();
		return true;
	}

	return false;
} 

void Player::blast(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_t_lazer > sf::seconds(0.4f))
	{
		m_t_lazer = sf::seconds(0);
		if(active_powerUp == true)
		{
			sf::Vector2f lazer_pos = m_Sprite.getPosition();
			lazer_pos.y += 60.f;
			for(int i { 0 }; i < 3; i++)
			{
				lazer_pos.y -= 30.f;
				Projectile* lazer{ new Projectile(lazer_pos)};
				new_objects.push_back(lazer);
			}
		}
		else
		{	
			Projectile* lazer{ new Projectile(m_Sprite.getPosition()) };
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

sf::Vector2f Player::getPosition()
{
 return m_Sprite.getPosition();
}