#include "Player.h"

#include "Projectile.h"
#include "engine/resource/TextureManager.h"

#include <iostream>

Player::Player()
	: active_powerUp(false), m_t_lazer{}, m_t_powerUp{}
{
	TextureManager& texMgr{ TextureManager::instance() };
	m_Texture = *texMgr.load("res/player.png");

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setRotation(90);
	sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);

	m_Tag = Collision::Player;
}

void Player::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
	blast(new_objects);
	if(sf::seconds(clock.getElapsedTime().asSeconds()) > m_t_powerUp + sf::seconds(10))
	{
		active_powerUp = false;
	}

}

void Player::movement(const sf::Time& dt)
{
    m_Speed.x = 0.0f;
	m_Speed.y = 0.0f;

	sf::Vector2f old_position { m_Sprite.getPosition() };

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

	if ( m_Sprite.getPosition().x < 0 || m_Sprite.getPosition().y < 0 || m_Sprite.getPosition().x > 640 || m_Sprite.getPosition().y > 480 )
	{
		m_Sprite.setPosition(old_position);
	}

}

void Player::Collision(const Collidable* other, std::vector<Object*>& new_objects)
{
	if (other->m_Tag & Collision::PowerUp)
		active_powerUp = true;
} 

void Player::blast(std::vector<Object*>& new_objects)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && sf::seconds(clock.getElapsedTime().asSeconds()) > m_t_lazer)
	{
		m_t_lazer = sf::seconds(clock.getElapsedTime().asSeconds()) + sf::seconds(0.4f);
		if(active_powerUp == true)
		{
			sf::Vector2f lazer_pos = m_Sprite.getPosition();
			Projectile* lazer1{new Projectile(m_Sprite.getPosition())};
			lazer_pos.y += 30;
			Projectile* lazer2{new Projectile(lazer_pos)};
			lazer_pos.y -= 60;
			Projectile* lazer3{new Projectile(lazer_pos)};
			new_objects.push_back(lazer1);
			new_objects.push_back(lazer2);
			new_objects.push_back(lazer3);
		}
		else
		{	
			Projectile* lazer{new Projectile(m_Sprite.getPosition())};
			new_objects.push_back(lazer);
		}
	}
}