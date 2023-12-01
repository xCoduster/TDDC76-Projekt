#include "GameState.h"

#include "engine/resource/AudioManager.h"
#include "engine/resource/TextureManager.h"

#include "util/Log.h"

#include <iostream>

GameState::GameState()
	: m_spawner{ 0.5f, 3.0f }
{
	player = new Player;

	m_spawner.readFile("res/waves.lvl", player);

	for (int i = 0; i < 120; i++)
	{
		Star* star{ new Star };
		stars.push_back(star);
	}

	m_gameBar = new GameBar(player);

	// Ladda in alla ljudfiler från start
	AudioManager& audioMgr{ AudioManager::instance() };

	audioMgr.load("res/audio/explosion.wav");
	audioMgr.load("res/audio/hurt.wav");
	audioMgr.load("res/audio/laser.wav");
	audioMgr.load("res/audio/powerup.wav");
	audioMgr.load("res/audio/ufo.wav");
	
	m_font.loadFromFile("res/fonts/ShareTechMono-Regular.ttf");

	output.setFont(m_font);
	output.setString("");
	output.setCharacterSize(40);
	output.setOrigin(output.getLocalBounds().width / 2.0f, output.getLocalBounds().height / 2.0f);
	output.setPosition(100, 200);
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
			if (event.type == sf::Event::Closed)
				m_state = State::Exit;

            if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					m_state = State::Pause;					// Byt skärm till pausemenyn

				if (event.key.code == sf::Keyboard::G)
					player->m_godMode = !player->m_godMode;

				if (event.key.code == sf::Keyboard::Backspace)
				{
					if (!input.empty())
					{
						input.pop_back();
						output.setString(input);
					}
				}

			}

			if (event.type == sf::Event::TextEntered)
			{
				sf::Uint32 unicode = event.text.unicode;

				if (unicode >= 0x20 && unicode <= 0x7e)
				{
					input += static_cast<char>(unicode);
					output.setFillColor(sf::Color::White);
					output.setString(input);
				}
			}

			if (event.type == sf::Event::Resized)
			{
				resize(event.size, *window);
			}
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

}

void GameState::update(const sf::Time& dt)
{
	for (Star* star : stars)
		star->update(dt, new_objects);

	checkCollision();

	player->update(dt, new_objects);

	for (Object* object : objects)
		object->update(dt, new_objects);
	
	
	if (m_spawner.update(dt, new_objects))
		m_spawner.readFile("res/waves.lvl", player);

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i)->m_Dead)
		{
			if (objects.at(i)->m_addScore)
				m_gameBar->addScore(1);

			std::swap(objects.at(i), objects.back());
			delete objects.back();
			objects.pop_back();
			--i;
		}
	}

	if (player->m_Dead)
	{

	}

	for (int i = 0; i < new_objects.size(); i++)
	{
		objects.push_back(new_objects.at(i));
		std::swap(new_objects.at(i), new_objects.back());
		new_objects.pop_back();
		--i;
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

	//m_window->draw(output);

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

void GameState::cleanup()
{
	for (int i = 0; i < objects.size(); i++)
	{
		std::swap(objects.at(i), objects.back());
       	delete objects.back();
	 	objects.pop_back();
	 	--i;
	}


	for (int i = 0; i < new_objects.size(); i++)
	{
		std::swap(new_objects.at(i), new_objects.back());
       	delete new_objects.back();
	 	new_objects.pop_back();
	 	--i;
	}

	for (int i = 0; i < stars.size(); i++)
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

	player = new Player;

	m_spawner.readFile("res/waves.lvl", player);

	for (int i = 0; i < 120; i++)
	{
		Star* star{ new Star };
		stars.push_back(star);
	}

	m_gameBar = new GameBar(player);
}
