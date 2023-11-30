#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

class State
{
public:
    virtual int run(std::shared_ptr<sf::RenderWindow> window) = 0;

    virtual void handle(sf::Event event) = 0;
    virtual void update(const sf::Time& dt) = 0;
    virtual void draw() = 0;

    void resize(sf::Event::SizeEvent event, sf::RenderWindow& window)
    {
        sf::Vector2f size{ static_cast<float>(event.width), static_cast<float>(event.height) };

        if (size.x / size.y > 4.f / 3.f)
            m_view.setViewport(sf::FloatRect((1 - (4.f / 3.f * size.y) / size.x) / 2, 0, (4.f / 3.f * size.y) / size.x, 1.0f));
        else
            m_view.setViewport(sf::FloatRect(0, (1 - (3.f / 4.f * size.x) / size.y) / 2, 1.0f, (3.f / 4.f * size.x) / size.y));

        window.setView(m_view);
    }

    virtual void cleanup() = 0;

    enum
    {
        Exit = -1,
        Menu,
        Game,
        Pause
    };

protected:
    sf::View m_view;

    std::shared_ptr<sf::RenderWindow> m_window;

    int m_state;
};