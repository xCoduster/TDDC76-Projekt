#include "GameState.h"

#include "engine/resource/AudioManager.h"
#include "engine/resource/TextureManager.h"
#include "objects/enemies/Boss.h"

#include "util/Log.h"
#include "util/Util.h"

#include <iostream>
#include <fstream>
#include <string>

GameState::GameState()
	: m_spawner{ 1.0f, 5.0f }, m_nameInput{}, m_score{ 0 }, m_gameOver{ false }, m_gameOverText{}, m_textBox{}, m_font{},
	stars{}, new_objects{}, objects{}, m_gameBar{ nullptr }, player{ nullptr }, m_bossFight{ false }
{
	// Ladda in alla ljudfiler från start
	AudioManager& audioMgr{ AudioManager::instance() };

	audioMgr.load("res/audio/explosion.wav");
	audioMgr.load("res/audio/hurt.wav");
	audioMgr.load("res/audio/laser.wav");
	audioMgr.load("res/audio/powerup.wav");
	audioMgr.load("res/audio/ufo.wav");
	
	m_font.loadFromFile("res/fonts/ShareTechMono-Regular.ttf");

	m_textBox.setFont(m_font);
	m_textBox.setString("");
	m_textBox.setCharacterSize(40);
	m_textBox.setOrigin(m_textBox.getLocalBounds().width / 2.0f, m_textBox.getLocalBounds().height / 2.0f);
	m_textBox.setPosition(640 / 2, 480 / 2);

	m_gameOverText.setFont(m_font);
	m_gameOverText.setString("  Game over! Skriv in ditt\nnamn och spara ditt resultat");
	m_gameOverText.setCharacterSize(38);
	m_gameOverText.setFillColor(sf::Color::Yellow);
	m_gameOverText.setOrigin(m_gameOverText.getLocalBounds().width / 2.0f, m_gameOverText.getLocalBounds().height / 2.0f);
	m_gameOverText.setPosition(640 / 2, 100 );

	init();
}

int GameState::run(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;
	m_state = State::Game;

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

        update(dt);
		updates++;
		
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

		if (m_state != State::Game)
			return m_state;
	}

	// Bör inte komma hit
    return State::Exit;
}

void GameState::handle(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		m_state = State::Exit;

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			m_state = State::Pause;					// Byt skärm till pausemenyn

		if (event.key.code == sf::Keyboard::G)
			player->m_godMode = !player->m_godMode;

		if (m_gameOver)
		{
			if (event.key.code == sf::Keyboard::Backspace)
			{
				if (!m_nameInput.empty())
				{
					m_nameInput.pop_back();
					m_textBox.setString(m_nameInput);
					m_textBox.setOrigin(m_textBox.getLocalBounds().width / 2.0f, m_textBox.getLocalBounds().height / 2.0f);
				}
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				saveScore();
				m_state = State::Menu;
			}
		}

	}

	if (m_gameOver)
	{
		if (event.type == sf::Event::TextEntered)
		{
			sf::Uint32 unicode = event.text.unicode;

			if (unicode >= 0x20 && unicode <= 0x7e)
			{
				m_nameInput += static_cast<char>(unicode);
				m_textBox.setString(m_nameInput);
				m_textBox.setOrigin(m_textBox.getLocalBounds().width / 2.0f, m_textBox.getLocalBounds().height / 2.0f);
			}
		}
	}

	if (event.type == sf::Event::Resized)
	{
		resize(event.size, m_view);
		m_window->setView(m_view);
	}
}

void GameState::update(const sf::Time& dt)
{
	for (Star* star : stars)
		star->update(dt, new_objects);

	checkCollision();

	player->update(dt, new_objects);

	for (Object* object : objects)
		object->update(dt, new_objects);
	
	for (int i = 0; i < static_cast<int>(objects.size()); i++)
	{
		if (objects.at(i)->m_Dead)
		{
			if (objects.at(i)->m_addScore)
			{
				m_score += 1;
				m_gameBar->showScore(m_score);
			}

			if (dynamic_cast<Boss*>(objects.at(i)) != nullptr)		// Kolla om bossen är död
			{
				m_bossFight = false;
				player->m_Hitpoints += 1;
			}

			std::swap(objects.at(i), objects.back());
			delete objects.back();
			objects.pop_back();
			--i;
		}
	}

	if (player->m_Dead)
	{
		m_gameOver = true;
	}

	for (int i = 0; i < static_cast<int>(new_objects.size()); i++)
	{
		objects.push_back(new_objects.at(i));
		std::swap(new_objects.at(i), new_objects.back());
		new_objects.pop_back();
		--i;
	}

	if (!m_bossFight && m_score % 20 == 0 && m_score != 0)		// Spawna en boss om spelaren har nått multiplar av 20 poäng
	{
		for (int i = 0; i < static_cast<int>(objects.size()); i++)
		{
			std::swap(objects.at(i), objects.back());
			delete objects.back();
			objects.pop_back();
			--i;
		}
	
		objects.push_back(new Boss{});
		m_bossFight = true;
	}

	if (!m_bossFight)
	{
		if (m_spawner.update(dt, new_objects))
			m_spawner.readFile("res/waves.lvl", player);
	}

	m_gameBar->update();

}

void GameState::draw()
{
    m_window->clear(sf::Color::Black);

	for (Star* star : stars)
		m_window->draw(*star);

	for (Object* object : objects)
		m_window->draw(*object);

	m_window->draw(*player);

	m_window->draw(*m_gameBar);

	if (m_gameOver)
	{
		m_window->draw(m_textBox);
		m_window->draw(m_gameOverText);
	}

    m_window->display();
}

void GameState::checkCollision()
{
	objects.push_back(player);

	for (unsigned i{ 0 }; i < objects.size(); ++i)
	{
		for (unsigned j{ i + 1 }; j < objects.size(); ++j)
		{
			Collidable* collidable1{ dynamic_cast<Collidable*>(objects.at(i)) };
			Collidable* collidable2{ dynamic_cast<Collidable*>(objects.at(j)) };

			if (collidable1 != nullptr && collidable2 != nullptr)
			{
				if (collidable1->Collides(collidable2))
				{
					collidable1->Collision(collidable2, new_objects);
					collidable2->Collision(collidable1, new_objects);
				}
			}
		}
	}

	objects.pop_back();
}

void GameState::saveScore()
{
	std::vector<std::pair<std::string, int>> scores{ readScore("highscore.csv") };
	
	scores.push_back(std::make_pair(m_nameInput, m_score));
	std::sort(scores.begin(), scores.end(), compareScore);
	
	std::ofstream outFile{ "highscore.csv", std::ios::trunc };

	for (int i{ 0 }; i < 5; ++i)
	{
		if (i >= static_cast<int>(scores.size()))
			break;

		int index = scores.size() - 1 - i;

		outFile << scores[index].first << "," << scores[index].second << std::endl;
	}

}

void GameState::init()
{
	player = new Player;

	m_spawner.readFile("res/waves.lvl", player);

	for (int i = 0; i < 120; i++)
	{
		Star* star{ new Star };
		stars.push_back(star);
	}

	m_gameBar = new GameBar(player);

	m_score = 0;
	m_nameInput = "";
	m_textBox.setString(m_nameInput);
	m_gameOver = false;
}

void GameState::cleanup()
{
	for (int i = 0; i < static_cast<int>(objects.size()); i++)
	{
		std::swap(objects.at(i), objects.back());
       	delete objects.back();
	 	objects.pop_back();
	 	--i;
	}


	for (int i = 0; i < static_cast<int>(new_objects.size()); i++)
	{
		std::swap(new_objects.at(i), new_objects.back());
       	delete new_objects.back();
	 	new_objects.pop_back();
	 	--i;
	}

	for (int i = 0; i < static_cast<int>(stars.size()); i++)
	{
		std::swap(stars.at(i), stars.back());
		delete stars.back();
		stars.pop_back();
		--i;
	}

	m_spawner.cleanup();
	
	delete m_gameBar;
	delete player;
}

void GameState::reset()
{
	cleanup();
	init();
}