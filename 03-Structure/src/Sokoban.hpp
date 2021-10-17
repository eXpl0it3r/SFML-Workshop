#pragma once
#include <SFML/Graphics.hpp>

class Sokoban
{
public:
    Sokoban();

    void run();

private:
    void handle_keyboard_input(sf::Event event);
    void handle_events();
    void update();
    void render();

    const sf::Vector2u m_window_size;
    const float m_distance;
    sf::Vector2i m_direction;
    std::map<sf::Keyboard::Key, bool> m_key_states;
    sf::RenderWindow m_window;
    sf::RectangleShape m_rectangle;
};
