#include "Star.h"
#include "util/Constants.h"
#include "engine/resource/DataManager.h"

#include <cstdlib>

Star::Star()
	: Object{}, m_Color {}, m_Speed{}, greenSpeed{}, redSpeed{}, blueSpeed{}
{
	initialize("res/star.png");

	DataManager& dataMgr { DataManager::instance() };
	StarData* data{ dynamic_cast<StarData*>(dataMgr.getData(Data::Type::Star)) };

	greenSpeed = data -> greenSpeed;
	redSpeed = data -> redSpeed;
	blueSpeed = data -> blueSpeed;

	float scale { data -> scale };
	m_Sprite.setScale( scale, scale);
	
	starAllocation();

	float X = rand() % screenWidth;
	float Y = rand() % screenHeight;

	m_Sprite.setPosition( X , Y);

}

void Star::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
    move(m_Speed * dt.asSeconds());
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
			m_Speed.x = blueSpeed;
			m_Color = starBlue;
			break;
		case 1:
			m_Speed.x = greenSpeed;
			m_Color = starGreen;
			break;
		case 2:
			m_Speed.x = redSpeed;
			m_Color = starRed;
			break;

	}
	m_Sprite.setColor(m_Color);
	m_Sprite.setPosition( X , Y);
}