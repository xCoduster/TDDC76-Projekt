#include "GameState.h"

#include <iostream>

GameState::GameState()
{

}

int GameState::run(sf::RenderWindow& window)
{
	Projectile lazer;
	PowerUp powerUp;

	objects.push_back(&lazer);
	objects.push_back(&powerUp);

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
    player.update(dt);
	for (Object* object : objects)
		object->update(dt);
}

void GameState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    window.draw(player);

	for (Object* object : objects)
		window.draw(*object);

    window.display();
}