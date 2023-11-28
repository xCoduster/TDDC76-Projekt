#include "Player.h"

#include "Projectile.h"

#include "engine/resource/TextureManager.h"
#include "engine/resource/AudioManager.h"

#include "util/Random.h"

#include <iostream>

Player::Player()
	: active_powerUp(false), m_t_lazer{}, m_t_powerUp{}, m_t_invincibility{}, m_godMode(false)
{
	AudioManager& audioMgr{ AudioManager::instance() };
	m_hurtSound.setBuffer(*audioMgr.load("res/audio/hurt.wav"));
	m_pickUpSound.setBuffer(*audioMgr.load("res/audio/powerup.wav"));
	m_laserSound.setBuffer(*audioMgr.load("res/audio/laser.wav"));
	m_laserSound.setVolume(75.0f);

	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/player.png");

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setRotation(90);
	sf::Vector2u texture_size { m_Texture.getSize() };

	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
	m_Sprite.setPosition(texture_size.x, 480 / 2);

	m_Tag = Collision::Player;

	m_Hitpoints = 10;
}

void Player::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
	blast(dt, new_objects);
	
	m_t_powerUp += dt;
	if (m_t_powerUp > sf::seconds(10))
		active_powerUp = false;

	if (m_t_invincibility >= sf::seconds(0.0f))
		m_t_invincibility -= dt;

	if (m_Hitpoints <= 0 && !m_godMode)
		m_Dead = true;
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

	if (position.y - boundingBox.height / 2 < 0 || position.y + boundingBox.height / 2 > 480)
		m_Sprite.setPosition(sf::Vector2f{ position.x, old_position.y });

}

void Player::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->m_Tag & Collision::PowerUp)
	{
		active_powerUp = true;
		m_t_powerUp = sf::seconds(0);
		m_pickUpSound.play();
	}

	if (other->m_Tag & Collision::Explosion)
		hurt();
} 

void Player::blast(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && m_t_lazer > sf::seconds(0.4f))
	{
		m_t_lazer = sf::seconds(0);
		if(active_powerUp == true)
		{
			sf::Vector2f lazer_pos = m_Sprite.getPosition();
			Projectile* lazer1{new Projectile(m_Sprite.getPosition(), false)};
			lazer_pos.y += 30;
			Projectile* lazer2{new Projectile(lazer_pos, false)};
			lazer_pos.y -= 60;
			Projectile* lazer3{new Projectile(lazer_pos, false)};
			new_objects.push_back(lazer1);
			new_objects.push_back(lazer2);
			new_objects.push_back(lazer3);
		}
		else
		{	
			Projectile* lazer{new Projectile(m_Sprite.getPosition(), false)};
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