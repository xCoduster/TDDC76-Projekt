#include "GameBar.h"

#include "engine/resource/TextureManager.h"
#include <string>
#include <iostream>

GameBar::GameBar(Player* player)
    : m_sprites{}, m_images{}, scoreStr{ "" }, Hp{ "" }, player_pointer{ player }, 
    score_blue{}, score_pink{}, score{}, life_blue{}, life_pink{}, life{}, font{}
{
    TextureManager& texMgr{ TextureManager::instance() };
    m_images.push_back(*texMgr.load("res/player.png"));

    sf::Sprite sprite {};
    sprite.setTexture(m_images.at(0));
    sprite.setPosition(10.0f, 10.0f);
    m_sprites.push_back(sprite);

    font.loadFromFile("res/fonts/PixeloidSansBold.ttf");
    life.setFont(font);
    life_pink.setFont(font);
    life_blue.setFont(font);

    Hp = std::to_string(player_pointer->getHitpoints());
    
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

    score.setString("0000");
    score.setCharacterSize(50.0f);
    score.setFillColor(sf::Color::White);
    score.setPosition(450.0f, 10.0f);

    score_pink.setString("0000");
    score_pink.setCharacterSize(50.0f);
    score_pink.setFillColor(sf::Color::Magenta);
    score_pink.setPosition(448.0f, 8.0f);

    score_blue.setString("0000");
    score_blue.setCharacterSize(50.0f);
    score_blue.setFillColor(sf::Color::Cyan);
    score_blue.setPosition(452.0f, 12.0f);    
}

void GameBar::update()
{
    Hp = std::to_string(player_pointer->getHitpoints());
    life.setString(Hp);
    life_pink.setString(Hp); 
    life_blue.setString(Hp);  
}

void GameBar::showScore(int score)
{
    if (score >= 10000)
        score -= 10000;

    scoreStr = std::to_string(score);

    std::string temp{};

    for (int i{ 0 }; i < 4 - static_cast<int>(scoreStr.length()); i++)
    {
        temp += "0";
    }

    temp += scoreStr;
    this->score.setString(temp);
    score_pink.setString(temp);
    score_blue.setString(temp);
}
