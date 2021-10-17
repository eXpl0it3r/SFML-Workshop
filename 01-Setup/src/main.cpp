#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 1280u, 720u }, "01 Setup - SFML Workshop" };
    window.setFramerateLimit(60);

    auto rectangle = sf::RectangleShape{ { 100.f, 100.f } };
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition({ 50.f, 50.f });

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }
}
