#include "GameBar.h"

#include "engine/resource/TextureManager.h"

#include <string>

GameBar::GameBar()
    :m_sprites{}, m_images{}
{
    for (int i = 1; i < 4; i++)
    {
        TextureManager& texMgr{ TextureManager::instance() };
	    m_images.push_back(*texMgr.load("res/numbers/"+ std::to_string(i) +".png"));
    }
    TextureManager& texMgr{ TextureManager::instance() };
    m_images.push_back(*texMgr.load("res/player.v2.png"));

    sf::Sprite sprite1 {};
    sprite1.setTexture(m_images.at(3));
    sprite1.setPosition(10.0f, 10.0f);
    m_sprites.push_back(sprite1);

    sf::Sprite sprite2 {};
    sprite2.setTexture(m_images.at(2));
    sprite2.setPosition(70.0f, 10.0f);
    m_sprites.push_back(sprite2);
}

void GameBar::update()
{
    int HP = 3;
    //m_sprites.at(1).setTexture(m_images.at(HP-1));    
}
