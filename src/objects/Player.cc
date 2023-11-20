#include "Player.h"

#include <iostream>

Player::Player()
{
	m_Texture.loadFromFile("res/tmp.png");
	m_Sprite.setTexture(m_Texture);
}

void Player::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);

	//m_BoundingBox

	//std::cout << m_Sprite.getGlobalBounds().left << std::endl;
	
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

void Player::Collision(const Collidable& other,std::vector<Object*>& new_objects)
{
	
}