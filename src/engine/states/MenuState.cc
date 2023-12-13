#include "MenuState.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

#include "util/Log.h"
#include "util/Util.h"

MenuState::MenuState()
	: m_buttons{}, m_titleText{}, m_stars{}, m_objects{}, m_font{}, m_toggleScore{ false }, m_scoreText{}, m_scoreList{}, m_scores{}
{
	m_font.loadFromFile("res/fonts/ShareTechMono-Regular.ttf");

	init();

	for (int i = 0; i < 120; i++)
	{
		Star* star{ new Star };
		m_stars.push_back(star);
	}
}

int MenuState::run(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;
	m_state = State::Menu;

	m_view = m_window->getView();

	m_scores = readScore("highscore.csv");

	std::stringstream scoreString;
	for (auto& element : m_scores)
	{
		scoreString << element.first << ": " << element.second << std::endl;
	}
	m_scoreList.setString(scoreString.str());
	m_scoreList.setOrigin(m_scoreList.getLocalBounds().width / 2.0f, m_scoreList.getLocalBounds().height / 2.0f);

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
			handle(event);
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
	if (event.type == sf::Event::Closed)
		m_state = State::Exit;

	if (event.type == sf::Event::Resized)
	{
		resize(event.size, m_view);
		m_window->setView(m_view);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (m_toggleScore)
		{
			if (event.key.code == sf::Keyboard::Escape)
				m_toggleScore = false;
		}
	}
}

void MenuState::update(const sf::Time& dt)
{
	sf::Vector2f mousePos{ m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)) };
	
	if (!m_toggleScore)
	{
		if (m_buttons.at(0).update(mousePos))
			m_state = State::Game;

		if (m_buttons.at(1).update(mousePos))
			m_toggleScore = true;

		if (m_buttons.at(2).update(mousePos))
			m_state = State::Exit;
	}
	else
	{
		if (m_buttons.at(3).update(mousePos))
			m_toggleScore = false;
	}

	for (Star* star : m_stars)
		star->update(dt, m_objects);
}

void MenuState::draw()
{
	m_window->clear(sf::Color::Black);

	for (Star* star : m_stars)
		m_window->draw(*star);

	if (!m_toggleScore)
	{
		m_window->draw(m_titleText);
		m_window->draw(m_buttons.at(0));
		m_window->draw(m_buttons.at(1));
		m_window->draw(m_buttons.at(2));
	}
	else
	{
		m_window->draw(m_scoreText);
		m_window->draw(m_scoreList);
		m_window->draw(m_buttons.at(3));
	}

	m_window->display();
}

void MenuState::init()
{
	m_titleText.setFont(m_font);
	m_titleText.setString("Space Craze");
	m_titleText.setCharacterSize(65);
	m_titleText.setFillColor(sf::Color::Yellow);
	m_titleText.setOrigin(m_titleText.getLocalBounds().width / 2.0f, m_titleText.getLocalBounds().height / 2.0f);
	m_titleText.setPosition(640.f / 2.f, 80.f);

	m_scoreText.setFont(m_font);
	m_scoreText.setString("Scoreboard");
	m_scoreText.setCharacterSize(42);
	m_scoreText.setFillColor(sf::Color::Yellow);
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2.0f, m_scoreText.getLocalBounds().height / 2.0f);
	m_scoreText.setPosition(640.f / 2.f, 40.f);

	m_scoreList.setFont(m_font);
	m_scoreList.setCharacterSize(42);
	m_scoreList.setFillColor(sf::Color::White);
	m_scoreList.setOrigin(m_scoreList.getLocalBounds().width / 2.0f, m_scoreList.getLocalBounds().height / 2.0f);
	m_scoreList.setPosition(640.f / 2.f, 220.f);

	for (int i{ 0 }; i < 4; ++i)
	{
		m_buttons.push_back(Button{});

		m_buttons.at(i).setSize(sf::Vector2f{ 200.f, 50.f });
		m_buttons.at(i).setColor(sf::Color(0x939393ff), sf::Color(0xadadadff), sf::Color(0xcececeff));
	}

	
	m_buttons.at(0).setText("Play", m_font);
	m_buttons.at(0).setPosition(sf::Vector2f{ 640.f / 2.f, 200.f });

	m_buttons.at(1).setText("Highscore", m_font);
	m_buttons.at(1).setPosition(sf::Vector2f{ 640.f / 2.f, 260.f });

	m_buttons.at(2).setText("Exit", m_font);
	m_buttons.at(2).setPosition(sf::Vector2f{ 640.f / 2.f, 320.f });

	m_buttons.at(3).setText("Back", m_font);
	m_buttons.at(3).setPosition(sf::Vector2f{ 640.f / 2.f, 380.f });
}

void MenuState::cleanup()
{
	for (std::size_t i = 0; i < m_stars.size(); i++)
	{
		std::swap(m_stars.at(i), m_stars.back());
		delete m_stars.back();
		m_stars.pop_back();
		--i;
	}
}