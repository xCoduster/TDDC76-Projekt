#pragma once

#include "objects/Player.h"
#include <string>
#include <SFML/Graphics.hpp>

class GameBar : public sf::Drawable
{
public:
    GameBar(Player* player);
    
    GameBar(const GameBar&) = delete;
    GameBar operator=(const GameBar&) = delete;

    void update();
    void showScore(int score);

private:
    std::vector<sf::Sprite> m_sprites;
    std::vector<sf::Texture> m_images;
    
    std::vector<sf::Text> m_hpText;
    std::vector<sf::Text> m_scoreText;

    sf::Font font;

   
    
    Player* player_pointer;

    std::string Hp;
    std::string scoreStr;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (std::size_t i { 0 }; i < m_sprites.size(); ++i)
            target.draw(m_sprites.at(i), states);
        
        for (std::size_t i { 0 }; i < m_hpText.size(); ++i)
        {
            target.draw(m_hpText.at(i), states);
            target.draw(m_scoreText.at(i), states);
        }
    
    }
};