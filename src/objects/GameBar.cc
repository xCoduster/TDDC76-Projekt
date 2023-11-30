#include "GameBar.h"

#include "engine/resource/TextureManager.h"
#include <string>

GameBar::GameBar(Player* player)
    :m_sprites{}, m_images{}
{
    TextureManager& texMgr{ TextureManager::instance() };
    m_images.push_back(*texMgr.load("res/player.v2.png"));

    sf::Sprite sprite {};
    sprite.setTexture(m_images.at(0));
    sprite.setPosition(10.0f, 10.0f);
    m_sprites.push_back(sprite);

    font.loadFromFile("res/PixeloidSansBold.ttf");
    life.setFont(font);
    life_pink.setFont(font);
    life_blue.setFont(font);

    player_pointer = player;
    
    life.setString(std::to_string(player_pointer -> m_Hitpoints));
    life.setCharacterSize(50.0f);
    life.setFillColor(sf::Color::White);
    life.setPosition(100.0f, 10.0f);

    life_pink.setString(std::to_string(player_pointer -> m_Hitpoints));
    life_pink.setCharacterSize(50.0f);
    life_pink.setFillColor(sf::Color::Magenta);
    life_pink.setPosition(98.0f, 8.0f);

    life_blue.setString(std::to_string(player_pointer -> m_Hitpoints));
    life_blue.setCharacterSize(50.0f);
    life_blue.setFillColor(sf::Color::Cyan);
    life_blue.setPosition(102.0f, 12.0f);
}

void GameBar::update()
{
    life.setString(std::to_string(player_pointer -> m_Hitpoints));
    life_pink.setString(std::to_string(player_pointer -> m_Hitpoints)); 
    life_blue.setString(std::to_string(player_pointer -> m_Hitpoints));  
}
