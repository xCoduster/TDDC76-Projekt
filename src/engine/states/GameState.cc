#include "GameState.h"

#include "objects/PowerUp.h"
#include "util/Log.h"

#include <iostream>

GameState::GameState()
{
	player = new Player;
	new_objects.push_back(player);
	sf::Vector2f powerUp_cord {640/2, 480/2};
	PowerUp* powerUp{ new PowerUp(powerUp_cord) };
	new_objects.push_back(powerUp);

	Bomb* bomb{ new Bomb };
	new_objects.push_back(bomb);
}

int GameState::run(sf::RenderWindow& window)
{
	window.setFramerateLimit(60);

	m_View = window.getView();

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
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return -1;

            if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					// Byt skärm till menyn
					return 0;
				}
			}

			if (event.type == sf::Event::Resized)
			{
				sf::Vector2f size{ static_cast<float>(event.size.width), static_cast<float>(event.size.height) };

				if (size.x / size.y > 4 / 3)
					m_View.setViewport(sf::FloatRect((1 - size.y / size.x) / 2, 0, size.y / size.x, 1.0f));
				else
					m_View.setViewport(sf::FloatRect(0, (1 - size.x / size.y) / 2, 1.0f, size.x / size.y));
				
				window.setView(m_View);
			}

		}

		sf::Time now = clock.getElapsedTime();
		sf::Time dt = now - last_update;
		last_update += dt;

        update(dt);
		updates++;
		
		draw(window);
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
	}

    return -1;
}

void GameState::handle(sf::Event event)
{

}

void GameState::update(const sf::Time& dt)
{
	checkCollision();

	for (Object* object : objects)
		object->update(dt, new_objects);
	

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i)->m_Dead)
		{
			std::swap(objects.at(i), objects.back());
			delete objects.back();
			objects.pop_back();
			--i;
		}
	}

	for (int i = 0; i < new_objects.size(); i++)
	{
		objects.push_back(new_objects.at(i));
		std::swap(new_objects.at(i), new_objects.back());
		new_objects.pop_back();
		--i;
	}
}

void GameState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

	for (Object* object : objects)
		window.draw(*object);

    window.display();
}

void GameState::checkCollision()
{
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
}
