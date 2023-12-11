#include "Star.h"
#include "util/Constants.h"

#include <cstdlib>

Star::Star()
	: Object{}, m_Color {}, m_Speed{}
{
	initialize("res/star.png");

	m_Sprite.setScale(0.1f ,0.1f);
	
	starAllocation();

	float X = rand() % screenWidth;
	float Y = rand() % screenHeight;

	m_Sprite.setPosition( X , Y);

}

void Star::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    move(m_Speed * 120.0f * dt.asSeconds());
	sf::Vector2f position{ m_Sprite.getPosition() };
	if (position.x < 0)
		starAllocation();
}

void Star::starAllocation()
{
	float X = screenWidth;
	float Y = rand() % screenHeight;
	
	int type = std::rand() % 3;
	switch(type)
	{
		case 0:
			m_Speed.x = -0.05f;
			m_Color = starBlue;
			break;
		case 1:
			m_Speed.x = -0.08f;
			m_Color = starGreen;
			break;
		case 2:
			m_Speed.x = -0.12f;
			m_Color = starRed;
			break;

	}
	m_Sprite.setColor(m_Color);
	m_Sprite.setPosition( X , Y);
}