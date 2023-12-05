#include "Button.h"

#include "util/Log.h"

Button::Button()
	: m_rect{}, m_text{}, m_held{ false }, m_activeColor{}, m_hoverColor{}, m_color{}
{
	m_text.setString("");
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_rect.setPosition(position);
	m_text.setPosition(position);
}

void Button::setSize(const sf::Vector2f& size)
{
	m_rect.setSize(size);
	m_rect.setOrigin(size / 2.f);
}

void Button::setText(const std::string& text, const sf::Font& font, const sf::Color& color)
{
	m_text.setString(text);
	m_text.setFont(font);
	m_text.setCharacterSize(24);
	m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height * 0.8f);
}

void Button::setColor(const sf::Color& color, const sf::Color& hoverColor, const sf::Color& activeColor)
{
	m_color = color;
	m_hoverColor = hoverColor;
	m_activeColor = activeColor;
}

bool Button::update(const sf::Vector2f& mousePos)
{
	if (m_rect.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_rect.setFillColor(m_activeColor);
			m_held = true;
		}
		else
		{
			m_rect.setFillColor(m_hoverColor);
			if (m_held)
			{
				m_held = false;
				return true;
			}
		}
	}
	else
		m_rect.setFillColor(m_color);

	return false;
}
