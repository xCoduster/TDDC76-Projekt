#include "MenuState.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

MenuState::MenuState()
{

}

int MenuState::run(sf::RenderWindow& window)
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
	sf::Time accumulator = sf::seconds(0.0f);
		
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
					return 1;
				}
			}

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

void MenuState::handle(sf::Event event)
{

}

void MenuState::update(const sf::Time& dt)
{
	
}

void MenuState::draw(sf::RenderWindow& window)
{

	window.clear(sf::Color::Black);

// Draw instructions
	sf::Font tech_font;
	tech_font.loadFromFile("ShareTechMono-Regular.ttf");

	sf::Text instruction_text;
	instruction_text.setFont(tech_font);

	instruction_text.setString("press SPACE to start game");

	instruction_text.setCharacterSize(24);

	instruction_text.setFillColor(sf::Color::White);

	instruction_text.setOrigin(instruction_text.getLocalBounds().width/2.0f,instruction_text.getLocalBounds().height/2.0f);

	instruction_text.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 20);

	window.draw(instruction_text);

// Draw title

	sf::Text title_text;
	title_text.setFont(tech_font);

	title_text.setString("Space Craze");

	title_text.setCharacterSize(65);

	title_text.setFillColor(sf::Color::Yellow);

	title_text.setOrigin(title_text.getLocalBounds().width/2.0f,title_text.getLocalBounds().height/2.0f);

	title_text.setPosition(window.getView().getCenter().x, window.getView().getCenter().y -60);

	window.draw(title_text);


    window.display();
}

void MenuState::cleanup()
{
	
}