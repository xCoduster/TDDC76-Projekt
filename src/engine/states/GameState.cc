#include "GameState.h"

#include "objects/PowerUp.h"

#include "engine/resource/TextureManager.h"

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

			std::cout << "FPS: " << fps << ", UPS: " << ups << std::endl;
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

	window.draw(gameBar);

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