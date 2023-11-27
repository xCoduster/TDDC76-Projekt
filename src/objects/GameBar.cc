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

    sf::Sprite sprite {};
    sprite.setTexture(m_images.at(3));
    sprite.setPosition(10.0f, 10.0f);
    m_sprites.push_back(sprite);

    sprite.setTexture(m_images.at(2));
    sprite.setPosition(10.0f, 10.0f);
    m_sprites.push_back(sprite);
}

void GameBar::update()
{

}

