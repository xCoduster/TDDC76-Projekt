#pragma once

#include "objects/Object.h"

#include <vector>
#include <stack>

#include <SFML/System/Clock.hpp>

class Spawner
{
public:
	Spawner(float spawnDelay = 0.5f, float waveDelay = 3.0f);
	~Spawner();

	bool update(const sf::Time& dt, std::vector<Object*>& new_objects);

	bool readFile(const std::string& filePath);

private:
	std::stack<std::vector<Object*>> m_objects;

	sf::Time m_timer;

	float m_spawnDelay;
	float m_waveDelay;
};

