#pragma once

#include "objects/Object.h"
#include "objects/Player.h"
#include "objects/enemies/Boss.h"

#include <vector>

#include <SFML/System/Clock.hpp>

class Spawner
{
public:
	Spawner(float spawnDelay = 0.5f, float waveDelay = 3.0f);
	~Spawner();

	bool update(const sf::Time& dt, std::vector<Object*>& new_objects, bool bossFight);

	bool readFile(const std::string& filePath, Player* playerObject);

	void cleanup();

private:
	std::vector<std::vector<Object*>> m_objects;

	Boss* m_boss;

	sf::Time m_timer;

	float m_spawnDelay;
	float m_waveDelay;
};

