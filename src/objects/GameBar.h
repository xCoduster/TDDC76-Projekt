#pragma once

#include "Object.h"

#include <SFML/Graphics.hpp>

class GameBar : public sf::Drawable
{
public:
    GameBar();
    void update();
protected:
    std::vector<sf::Sprite> m_sprites;
    std::vector<sf::Texture> m_images;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (int i = 0; i < m_sprites.size(); i++)
            target.draw(m_sprites.at(i), states);
    }
};