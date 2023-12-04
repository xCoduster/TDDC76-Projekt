#include "AudioManager.h"

AudioPtr AudioManager::load(const std::string& filePath)
{
    auto bufferIterator = buffers.find(filePath);
    if (bufferIterator != buffers.end())
    {
        return bufferIterator->second;
    }

    AudioPtr buffer{ std::make_shared<sf::SoundBuffer>() };
    buffer->loadFromFile(filePath);

    buffers.insert(std::make_pair(filePath, buffer));

    return buffer;
}

AudioManager::AudioManager()
    : buffers{}
{
}