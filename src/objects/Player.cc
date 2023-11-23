#include "Player.h"
#include "Projectile.h"

#include <iostream>

Player::Player()
{
	m_Texture.loadFromFile("res/player.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setRotation(90);
	sf::Vector2u texture_size { m_Texture.getSize() };
	m_Sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
}

void Player::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    movement(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && clock.getElapsedTime().asSeconds() > 0.4)
	{
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
			//cout << "lever fortfarande" << endl;
			new_objects.push_back(lazer);
		}
		clock.restart();
	}
	//m_BoundingBox

	//std::cout << m_Sprite.getGlobalBounds().left << std::endl;
	
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

		move(m_Speed * 120.0f * dt.asSeconds());
		
	}

	if ( m_Sprite.getPosition().x < 0 || m_Sprite.getPosition().y < 0 || m_Sprite.getPosition().x > 640 || m_Sprite.getPosition().y > 480 )
	{
		m_Sprite.setPosition(old_position);
	}

}

void Player::Collision(const Collidable& other,std::vector<Object*>& new_objects)
{
	active_powerUp = true;
} 