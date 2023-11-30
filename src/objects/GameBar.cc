#include "GameBar.h"

#include "engine/resource/TextureManager.h"
#include <string>
#include <iostream>

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

    Hp = std::to_string(player_pointer -> m_Hitpoints);
    
    life.setString(Hp);
    life.setCharacterSize(50.0f);
    life.setFillColor(sf::Color::White);
    life.setPosition(100.0f, 10.0f);

    life_pink.setString(Hp);
    life_pink.setCharacterSize(50.0f);
    life_pink.setFillColor(sf::Color::Magenta);
    life_pink.setPosition(98.0f, 8.0f);

    life_blue.setString(Hp);
    life_blue.setCharacterSize(50.0f);
    life_blue.setFillColor(sf::Color::Cyan);
    life_blue.setPosition(102.0f, 12.0f);

    score.setFont(font);
    score_pink.setFont(font);
    score_blue.setFont(font);

    score.setString(Hp);
    score.setCharacterSize(50.0f);
    score.setFillColor(sf::Color::White);
    score.setPosition(450.0f, 10.0f);

    score_pink.setString(Hp);
    score_pink.setCharacterSize(50.0f);
    score_pink.setFillColor(sf::Color::Magenta);
    score_pink.setPosition(448.0f, 8.0f);

    score_blue.setString(Hp);
    score_blue.setCharacterSize(50.0f);
    score_blue.setFillColor(sf::Color::Cyan);
    score_blue.setPosition(452.0f, 12.0f);    
}

void GameBar::update()
{
    
    Hp = std::to_string(player_pointer -> m_Hitpoints);
    life.setString(Hp);
    life_pink.setString(Hp); 
    life_blue.setString(Hp);  

    std::string temp {};

    for (int i = 0; i < 4 - Hp.length(); i++)
    {
        temp +="0";
    }

    temp += Hp;
    score.setString(temp);
    score_pink.setString(temp);
    score_blue.setString(temp);

}
