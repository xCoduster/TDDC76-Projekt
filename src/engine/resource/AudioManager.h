#pragma once

#include <memory>
#include <map>

#include <SFML/Audio.hpp>

typedef std::shared_ptr<sf::SoundBuffer> AudioPtr;

class AudioManager
{
public:
	static AudioManager& instance()
	{
		static AudioManager instance;
		return instance;
	}

	AudioPtr load(const std::string& filePath);

private:
	AudioManager();

	std::map<std::string, AudioPtr> buffers;
};