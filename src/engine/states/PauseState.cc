#include "PauseState.h"

#include "util/Log.h"

PauseState::PauseState()
	: m_gameTex(), m_gameSprite(), m_continueButton(), m_menuButton(), m_font(), m_windowView()
{
	m_font.loadFromFile("res/fonts/ShareTechMono-Regular.ttf");

	init();
}

int PauseState::run(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;
	m_view = m_window->getView();
	m_state = State::Pause;

	resizeTexture();

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

		if (m_state != State::Pause)
		{
			m_window->setView(m_view);
			return m_state;
		}
	}

	return State::Exit;
}

void PauseState::handle(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		m_state = State::Exit;

	if (event.type == sf::Event::Resized)
	{
		resize(event.size, m_view);
		resize(event.size, m_windowView);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			m_state = State::Game;					// Byt skärm till spelet
	}
}

void PauseState::update(const sf::Time& dt)
{
	sf::Vector2f mousePos{ m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)) };

	if (m_continueButton.update(mousePos))
		m_state = State::Game;

	if (m_menuButton.update(mousePos))
		m_state = State::Menu;
}

void PauseState::draw()
{
	m_window->clear(sf::Color::Black);

	m_window->setView(m_windowView);

	m_window->draw(m_gameSprite);

	m_window->setView(m_view);

	m_window->draw(m_continueButton);
	m_window->draw(m_menuButton);

	m_window->display();
}

void PauseState::init()
{
	m_continueButton.setSize(sf::Vector2f{ 200.f, 50.f });
	m_continueButton.setColor(sf::Color(0x939393ff), sf::Color(0xadadadff), sf::Color(0xcececeff));
	m_continueButton.setText("Continue", m_font);
	m_continueButton.setPosition(sf::Vector2f{ 640.f / 2.f, 200.f });

	m_menuButton.setSize(sf::Vector2f{ 200.f, 50.f });
	m_menuButton.setColor(sf::Color(0x939393ff), sf::Color(0xadadadff), sf::Color(0xcececeff));
	m_menuButton.setText("Exit to menu", m_font);
	m_menuButton.setPosition(sf::Vector2f{ 640.f / 2.f, 260.f });
}

void PauseState::cleanup()
{

}

void PauseState::resizeTexture()
{
	sf::Vector2u size{ m_window->getSize() };

	m_windowView.reset(sf::FloatRect(0.f, 0.f, size.x, size.y));
	m_windowView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	m_gameTex.create(size.x, size.y);

	m_gameTex.update(*m_window);
	m_gameSprite.setTexture(m_gameTex, true);
}
