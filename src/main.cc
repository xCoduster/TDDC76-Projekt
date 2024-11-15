#include <vector>

#include <SFML/Graphics.hpp>

#include "engine/states/State.h"
#include "engine/states/GameState.h"
#include "engine/states/MenuState.h"
#include "engine/states/PauseState.h"

#include "util/Constants.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <memory>

void config(const std::string& filePath);

int main(int argc, char* argv[])
{
    std::vector<State*> states;
    int state = State::Menu;
    std::shared_ptr<sf::RenderWindow> window{ std::make_shared<sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), 
        "Space Craze", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize)};

    window->setFramerateLimit(fps);

    config("res/config.txt");

    MenuState menuState;
    states.push_back(&menuState);
    GameState gameState;
    states.push_back(&gameState);
    PauseState pauseState;
    states.push_back(&pauseState);

    while (state != State::Exit)
    {
        if (state == State::Menu)
            gameState.reset();

        state = states[state]->run(window);
    }

    window->close();

    for (State* state : states)
        state->cleanup();

    return 0;
}

void config(const std::string& filePath)
{
    std::ifstream ifs{ filePath };
    std::string line{};
    std::string word{};

    if (!ifs.is_open())
        return;

    while (std::getline(ifs, line))
    {
        std::istringstream iss{ line };
        std::vector<std::string> words;

        while (std::getline(iss, word, '='))
            words.push_back(word);
        
        if (words.at(0) == "seed")
        {
            if (words.size() == 1)
                std::srand(std::time(nullptr));
            else
                std::srand(stoi(words.at(1)));
        }
    }
}