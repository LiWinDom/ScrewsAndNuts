#include <algorithm>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <string>
#include <Windows.h>

#include "Config.h"
#include "ScrewsAndNuts/Game.h"
#include "ScrewsAndNuts/Human.h"

sf::RenderWindow* window;
sf::Font font;

Game* game;

void init() {
    std::srand(std::time(nullptr));

    window = new sf::RenderWindow(sf::VideoMode(CELL_SIZE * FIELD_WIDTH, CELL_SIZE * (FIELD_HEIGHT + 1)), "Screws & Nuts [0.22]", sf::Style::Close);
    window->setVerticalSyncEnabled(true);
    window->setActive(true);

    if (!font.loadFromFile("resourses/Consolas.ttf")) {
        throw std::runtime_error("Cannot load font: \"resourses/Consolas.ttf\"");
    }

    //sf::Image icon;
    //icon.loadFromFile("resourses/icon.png");
    //window->setIcon(52, 52, icon.getPixelsPtr());

    game = new Game(FIELD_WIDTH, FIELD_HEIGHT, new Human(1, "Player 1"), new Human(2, "Player 2"));
    return;
}

void display() {
    window->clear(sf::Color(BACKGROUND_COLOR));

    // Preinit rectangle, circle
    sf::RectangleShape rect;
    sf::CircleShape cir;
    cir.setRadius(CELL_SIZE / 3.0);
    cir.setOutlineThickness(CELL_SIZE / 30.0);

    // Winner highlight
    for (uint8_t i = 0; i < game->getWinCombination().size(); ++i) {
        rect.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        rect.setFillColor(sf::Color(WIN_HIGHLIGHT_COLOR));
        rect.setOutlineThickness(0);
        rect.setPosition(game->getWinCombination()[i].first * CELL_SIZE, game->getWinCombination()[i].second * CELL_SIZE);
        window->draw(rect);
    }

    // Board drawing
    rect.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    rect.setFillColor(sf::Color(0));
    rect.setOutlineColor(sf::Color(BORDER_COLOR));
    rect.setOutlineThickness(BORDER_SIZE / 2.0);
    for (uint8_t i = 0; i < FIELD_WIDTH; ++i) {
        for (uint8_t j = 0; j < FIELD_HEIGHT; ++j) {
            rect.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            window->draw(rect);

            if (game->getField()[i][j] != 0) {
                cir.setFillColor(sf::Color(game->getField()[i][j] == 1 ? PLAYER1_COLOR : PLAYER2_COLOR));
                cir.setOutlineColor(sf::Color(game->getField()[i][j] == 1 ? PLAYER2_COLOR : PLAYER1_COLOR));
                cir.setPosition(i * CELL_SIZE + CELL_SIZE / 2.0 - CELL_SIZE / 3.0, j * CELL_SIZE + CELL_SIZE / 2.0 - CELL_SIZE / 3.0);
                window->draw(cir);
            }
        }
    }

    // Board outline
    rect.setSize(sf::Vector2f(FIELD_WIDTH * CELL_SIZE - BORDER_SIZE, FIELD_HEIGHT * CELL_SIZE - BORDER_SIZE));
    rect.setPosition(BORDER_SIZE / 2.0, BORDER_SIZE / 2.0);
    window->draw(rect);

    // Highlight cell
    if (window->hasFocus()) {
        // Highlight hovered cell
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < CELL_SIZE * FIELD_WIDTH && mousePos.y < CELL_SIZE * FIELD_HEIGHT) {
            rect.setSize(sf::Vector2f(CELL_SIZE - BORDER_SIZE, CELL_SIZE - BORDER_SIZE));
            rect.setFillColor(sf::Color(MOUSE_HIGHLIGHT_COLOR));
            rect.setOutlineThickness(0);
            rect.setPosition(mousePos.x - mousePos.x % CELL_SIZE + BORDER_SIZE / 2.0, mousePos.y - mousePos.y % CELL_SIZE + BORDER_SIZE / 2.0);
            window->draw(rect);
        }
    }

    // Game info
    IPlayer* curPlayer = game->getCurPlayer();

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(TEXT_SIZE);
    text.setPosition(CELL_SIZE + CELL_SIZE / 2.0 - CELL_SIZE / 3.0, FIELD_HEIGHT * CELL_SIZE + CELL_SIZE / 2.0 - CELL_SIZE / 3.0);
    text.setFillColor(sf::Color(TEXT_COLOR));
    text.setString("Current move: " + curPlayer->getName());
    
    if (game->getWinner() != nullptr) {
        curPlayer = game->getWinner();
        text.setString("Winner: " + curPlayer->getName());
    }
    else if (game->getPossibleMoves().size() < 1) {
        text.setString("Tie!");
    }
    window->draw(text);

    cir.setFillColor(sf::Color(curPlayer->getNumber() == 1 ? PLAYER1_COLOR : PLAYER2_COLOR));
    cir.setOutlineColor(sf::Color(curPlayer->getNumber() == 1 ? PLAYER2_COLOR : PLAYER1_COLOR));
    cir.setPosition(CELL_SIZE / 2.0 - CELL_SIZE / 3.0, FIELD_HEIGHT * CELL_SIZE + CELL_SIZE / 2.0 - CELL_SIZE / 3.0);
    window->draw(cir);

    window->display();
    return;
}

void eventProcessing() {
    static int8_t mouseButton = -1;
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();

        if (!window->hasFocus()) continue;

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                delete game;
                game = new Game(FIELD_WIDTH, FIELD_HEIGHT, new Human(1, "Player 1"), new Human(2, "Player 2"));
            }
            if (event.key.code == sf::Keyboard::U) {
                game->undo();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseButton == -1) {
            mouseButton = sf::Mouse::Left;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouseButton == -1) {
            mouseButton = sf::Mouse::Right;
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (mouseButton == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                game->think(mousePos.x / CELL_SIZE, mousePos.y / CELL_SIZE);
            }
            mouseButton = -1;
        }
    }
    return;
}

int main() {
#if !_DEBUG
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // !_DEBUG

    try {
        init();

        while (window->isOpen()) {
            eventProcessing();
            game->think();
            display();
        }
    }
    catch (const std::exception& ex) {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        std::cerr << "Something went wrong. We are sorry about that :(" << std::endl;
        std::cerr << "Error info: " << ex.what() << std::endl;
        system("pause");
        return 1;
    }
    return 0;
}