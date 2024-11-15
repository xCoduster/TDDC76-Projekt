#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

class State
{
public:
    virtual ~State() = default;

    virtual int run(std::shared_ptr<sf::RenderWindow> window) = 0;

    virtual void handle(sf::Event event) = 0;
    virtual void update(const sf::Time& dt) = 0;
    virtual void draw() = 0;

    void resize(sf::Event::SizeEvent event, sf::View& view)
    {
        sf::Vector2f size{ static_cast<float>(event.width), static_cast<float>(event.height) };

        float ratio = view.getSize().x / view.getSize().y;

        if (size.x / size.y > ratio)
            view.setViewport(sf::FloatRect((1 - (ratio * size.y) / size.x) / 2, 0, (ratio * size.y) / size.x, 1.0f));
        else
            view.setViewport(sf::FloatRect(0, (1 - (1 / ratio * size.x) / size.y) / 2, 1.0f, (1 / ratio * size.x) / size.y));
    }

    virtual void init() = 0;
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

    State() : m_view{}, m_window{ nullptr }, m_state{ State::Exit } {}
};