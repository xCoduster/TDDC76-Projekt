#pragma once

#include "State.h"

#include "objects/Player.h"
#include "objects/Star.h"
#include "objects/GameBar.h"

#include "engine/Spawner.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{
public:
    GameState();

    GameState(const GameState&) = delete;
    GameState operator=(const GameState&) = delete;

    virtual int run(std::shared_ptr<sf::RenderWindow> window) override;
    virtual void handle(sf::Event event) override;
    virtual void update(const sf::Time& dt) override;
    virtual void draw() override;

    void checkCollision();

    void saveScore();

    void init();
    void reset();
    virtual void cleanup() override;
private:
    Player* player;
    GameBar* m_gameBar;
    std::vector<Object*> objects;
    std::vector<Object*> new_objects;

    std::vector<Star*> stars;

    Spawner m_spawner;

    sf::Font m_font;
    std::string m_nameInput;
    sf::Text m_textBox;
    sf::Text m_gameOverText;

    int m_score;
    bool m_bossFight;
    bool m_gameOver;
};