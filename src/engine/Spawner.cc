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

Spawner::~Spawner()
{
	cleanup();
}

bool Spawner::update(const sf::Time& dt, std::vector<Object*>& new_objects)
{
	m_timer += dt;

	if (m_objects.empty())
		return true;

	if (!m_objects.front().empty())
	{
		if (m_timer.asSeconds() >= m_spawnDelay)
		{
			for (int i{ 1 }; i < random(1, 3); ++i)
			{
				int length = static_cast<int>(m_objects.front().size());
				int index = random(0, length - 1);

				std::swap(m_objects.front().at(index), m_objects.front().back());
				new_objects.push_back(m_objects.front().back());

				m_objects.front().pop_back();
				
				if (m_objects.front().empty())
					break;
			}

			m_timer = sf::Time::Zero;
		}
	}
	else
	{
		if (m_timer.asSeconds() >= m_waveDelay)
		{
			std::swap(m_objects.at(0), m_objects.back());
			m_objects.pop_back();
			m_timer = sf::Time::Zero;
		}
	}

	return false;
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

		if (objects.size() == 0)
			continue;

		m_objects.push_back(objects);
		objects.clear();
	}

	return true;
}

void Spawner::cleanup()
{
	for (int i{ 0 }; i < m_objects.size(); ++i)
	{
		for (int j{ 0 }; j < m_objects.at(i).size(); ++j)
		{
			std::swap(m_objects.at(i).at(j), m_objects.at(i).back());
			delete m_objects.at(i).back();
			m_objects.at(i).pop_back();
			--j;
		}
		std::swap(m_objects.at(i), m_objects.back());
		m_objects.pop_back();
		--i;
	}
}