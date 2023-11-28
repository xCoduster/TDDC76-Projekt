#include "Spawner.h"

#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>

#include "objects/Bomb.h"
#include "objects/UFO.h"
#include "util/Log.h"
#include "util/Random.h"

Spawner::Spawner(float spawnDelay, float waveDelay)
	: m_timer{}, m_spawnDelay(spawnDelay), m_waveDelay(waveDelay)
{
}

void Spawner::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	m_timer += dt;

	if (m_objects.empty())
		return;

	if (!m_objects.top().empty())
	{
		if (m_timer.asSeconds() >= m_spawnDelay)
		{
			for (int i{ 1 }; i < random(1, 3); ++i)
			{
				int length = static_cast<int>(m_objects.top().size());
				int index = random(0, length - 1);

				std::swap(m_objects.top().at(index), m_objects.top().back());
				new_objects.push_back(m_objects.top().back());

				m_objects.top().pop_back();
				
				if (m_objects.top().empty())
					break;
			}

			m_timer = sf::Time::Zero;
		}
	}
	else
	{
		if (m_timer.asSeconds() >= m_waveDelay)
		{
			m_objects.pop();
			m_timer = sf::Time::Zero;
		}
	}
}

bool Spawner::readFile(const std::string& filePath)
{
	std::ifstream ifs{ filePath };

	std::string line{};
	std::string word{};

	char type{};
	unsigned int amount{};

	if (!ifs.is_open())
		return false;

	while (std::getline(ifs, line))
	{
		std::istringstream iss{ line };
		std::vector<Object*> objects{};

		if (line[0] == '#')
			continue;

		while (std::getline(iss, word, ';'))
		{
			std::stringstream ss{ word };

			if (ss >> amount >> type)
			{
				for (int i{ 0 }; i < amount; ++i)
				{
					switch (type)
					{
					case 'b':
						objects.push_back(new Bomb{});
						objects.back()->setPosition(sf::Vector2f(640 + random(0, 32), random(32, 448)));
						break;
					case 's':
						break;
					case 'u':
						objects.push_back(new UFO{});
						objects.back()->setPosition(sf::Vector2f(640 + random(0, 32), random(32, 448)));
						break;
					}
				}
			}
		}
		
		m_objects.push(objects);
	}

	return true;
}
