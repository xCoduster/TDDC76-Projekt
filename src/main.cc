#include <vector>

#include <SFML/Graphics.hpp>

#include "engine/states/State.h"
#include "engine/states/GameState.h"
#include "engine/states/MenuState.h"

#include <iostream>

int main(int argc, char* argv[])
{
    std::vector<State*> states;
    int state = 0;
    // TODO: Lägg till variabler på fönsterstorleken
    sf::RenderWindow window{sf::VideoMode(640, 480), "Space Craze", sf::Style::Titlebar | sf::Style::Close};

    MenuState menuState;
    states.push_back(&menuState);
    GameState gameState;
    states.push_back(&gameState);

    while (state >= 0)
    {
        state = states[state]->run(window);
    }

    window.close();

    for (State* state : states)
        state->cleanup();

    return 0;
}