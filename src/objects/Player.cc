#include "Player.h"

#include <iostream>

void Player::update(const sf::Time& dt)
{
    movement(dt);
}

void Player::movement(const sf::Time& dt)
{
    m_Speed.x = 0.0f;
	m_Speed.y = 0.0f;

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

		move(m_Speed * 120.0f * dt.asSeconds());
	}
}

void Player::Collision(const Collidable& other)
{
	
}