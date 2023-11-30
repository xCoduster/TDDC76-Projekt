#include "MenuState.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "util/Log.h"

MenuState::MenuState()
	: m_playButton(), m_exitButton()
{
	m_font.loadFromFile("res/fonts/ShareTechMono-Regular.ttf");

	for (int i = 0; i < 120; i++)
	{
		Star* star{ new Star };
		stars.push_back(star);
	}
}

int MenuState::run(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;
	m_state = State::Menu;

	title_text.setFont(m_font);
	title_text.setString("Space Craze");
	title_text.setCharacterSize(65);
	title_text.setFillColor(sf::Color::Yellow);
	title_text.setOrigin(title_text.getLocalBounds().width / 2.0f, title_text.getLocalBounds().height / 2.0f);
	title_text.setPosition(m_window->getView().getCenter().x, 80);

	m_playButton.setSize(sf::Vector2f{ 200.f, 50.f });
	m_playButton.setColor(sf::Color(0x939393ff), sf::Color(0xadadadff), sf::Color(0xcececeff));
	m_playButton.setText("Play", m_font);
	m_playButton.setPosition(sf::Vector2f{ m_window->getView().getCenter().x, 200.f });

	m_exitButton.setSize(sf::Vector2f{ 200.f, 50.f });
	m_exitButton.setColor(sf::Color(0x939393ff), sf::Color(0xadadadff), sf::Color(0xcececeff));
	m_exitButton.setText("Exit", m_font);
	m_exitButton.setPosition(sf::Vector2f{ m_window->getView().getCenter().x, 260.f });

	m_view = m_window->getView();

    bool running = true;
    unsigned int fps = 0;
    unsigned int ups = 0;

    sf::Clock clock;

	const sf::Time deltatime = sf::seconds(1 / 60.0f);
	float timer = 0.0f;
	unsigned int frames = 0;
	unsigned int updates = 0;

	sf::Time last_update = clock.getElapsedTime();
	sf::Time accumulator = sf::seconds(0.0f);
		
	while (running)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_state = State::Exit;

			if (event.type == sf::Event::Resized)
				resize(event.size, *window);
		}

		sf::Time now = clock.getElapsedTime();
		sf::Time dt = now - last_update;
		last_update += dt;

		accumulator += dt;

		while (accumulator >= deltatime)
		{
			updates++;
			accumulator -= deltatime;

            update(dt);
		}

		
		draw();
		frames++;

		if (clock.getElapsedTime().asSeconds() - timer > 1.0f)
		{
			timer += 1.0f;
			fps = frames;
			ups = updates;
			frames = 0;
			updates = 0;

			// Every second

			LOG_INFO("FPS: " << fps << ", UPS: " << ups);
		}

		if (m_state != State::Menu)
			return m_state;
	}

    return State::Exit;
}

void MenuState::handle(sf::Event event)
{

}

void MenuState::update(const sf::Time& dt)
{
	sf::Vector2i mousePos{ sf::Mouse::getPosition(*m_window) };

	if (m_playButton.update(mousePos))
		m_state = State::Game;

	if (m_exitButton.update(mousePos))
		m_state = State::Exit;

	for (Star* star : stars)
		star->update(dt, std::vector<Object*>{});
}

void MenuState::draw()
{
	m_window->clear(sf::Color::Black);

	for (Star* star : stars)
		m_window->draw(*star);

	m_window->draw(title_text);
	m_window->draw(m_playButton);
	m_window->draw(m_exitButton);

	m_window->display();
}

void MenuState::cleanup()
{
	for (int i = 0; i < stars.size(); i++)
	{
		std::swap(stars.at(i), stars.back());
		delete stars.back();
		stars.pop_back();
		--i;
	}
}