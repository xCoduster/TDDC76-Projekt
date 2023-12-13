#include "GameBar.h"

#include "engine/resource/TextureManager.h"
#include <string>
#include <iostream>

GameBar::GameBar(Player* player)
    : m_sprites{}, m_images{}, scoreStr{ "" }, Hp{ "" }, player_pointer{ player }, 
    font{}, m_hpText{}, m_scoreText{}
{
    TextureManager& texMgr{ TextureManager::instance() };
    m_images.push_back(*texMgr.load("res/player.png"));

    sf::Sprite sprite {};
    sprite.setTexture(m_images.at(0));
    sprite.setPosition(10.0f, 10.0f);
    m_sprites.push_back(sprite);

    font.loadFromFile("res/fonts/PixeloidSansBold.ttf");

    Hp = std::to_string(player_pointer->getHitpoints());
    
    
    for (int i { 0 }; i < 3; ++i)
    {
        sf::Text tmpText1 {};
        sf::Text tmpText2 {};
    
        tmpText1.setFont(font);
        tmpText1.setString(Hp);
        tmpText1.setCharacterSize(50.0f);
        tmpText1.setPosition(98.0f + 2.0f * i, 8.0f + 2.0f * i);

        tmpText2.setFont(font);
        tmpText2.setString("0000");
        tmpText2.setCharacterSize(50.0f);
        tmpText2.setPosition(448.0f + 2.0f * i, 8.0f + 2.0f * i);

        m_hpText.push_back(tmpText1);
        m_scoreText.push_back(tmpText2);
        
    }

    
    m_scoreText.at(2).setFillColor(sf::Color::Cyan);
    m_scoreText.at(1).setFillColor(sf::Color::White);
    m_scoreText.at(0).setFillColor(sf::Color::Magenta);
    
    m_hpText.at(2).setFillColor(sf::Color::Cyan);
    m_hpText.at(1).setFillColor(sf::Color::White);
    m_hpText.at(0).setFillColor(sf::Color::Magenta);

    std::swap(m_hpText.at(1), m_hpText.back());
    std::swap(m_scoreText.at(1), m_scoreText.back());
     
}

void GameBar::update()
{
    Hp = std::to_string(player_pointer->getHitpoints());
    m_hpText.at(0).setString(Hp);
    m_hpText.at(1).setString(Hp);
    m_hpText.at(2).setString(Hp);
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
    m_scoreText.at(0).setString(temp);
    m_scoreText.at(1).setString(temp);
    m_scoreText.at(2).setString(temp);
}
