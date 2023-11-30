#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable
{
public:
	Button();

	void setSize(const sf::Vector2f& size);
	void setPosition(const sf::Vector2f& position);
	void setText(const std::string& text, const sf::Font& font, const sf::Color& color = sf::Color::White);
	void setColor(const sf::Color& color, const sf::Color& hoverColor, const sf::Color& activeColor);

	bool update(const sf::Vector2f& mousePos);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_rect, states);
		target.draw(m_text, states);
	}

	bool m_held;

	sf::RectangleShape m_rect;
	sf::Text m_text;

	sf::Color m_color;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;
};