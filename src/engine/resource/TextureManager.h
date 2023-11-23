#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

typedef std::shared_ptr<sf::Texture> TexturePtr;

class TextureManager
{
public:
	static TextureManager& instance()
	{
		static TextureManager instance;
		return instance;
	}

	TexturePtr load(const std::string& filePath);

private:
	std::map<std::string, TexturePtr> textures;
};