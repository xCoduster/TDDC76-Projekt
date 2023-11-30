#pragma once

#include "Object.h"
#include "Player.h"
#include <string>
#include <SFML/Graphics.hpp>

class GameBar : public sf::Drawable
{
public:
    GameBar(Player* player);
    void update();
protected:
    std::vector<sf::Sprite> m_sprites;
    std::vector<sf::Texture> m_images;
    sf::Font font;
    sf::Text life;
    sf::Text life_pink;
    sf::Text life_blue;
    
    Player* player_pointer;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (int i = 0; i < m_sprites.size(); i++)
            target.draw(m_sprites.at(i), states);
        
        target.draw(life_pink, states);
        target.draw(life_blue, states);
        target.draw(life, states);


    }
};