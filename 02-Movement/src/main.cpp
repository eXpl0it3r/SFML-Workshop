#include <SFML/Graphics.hpp>

int main()
{
	auto window = sf::RenderWindow{ {800u, 800u}, "02 Movement - SFML Workshop" };
	window.setFramerateLimit(60);

	auto rectangle = sf::RectangleShape{ {100.f, 100.f} };
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setPosition({ 400.f, 400.f });

	const auto distance = 100.f;
	auto direction = sf::Vector2i{};
	auto key_states = std::map<sf::Keyboard::Key, bool>{};

	while (window.isOpen())
	{
		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left && !key_states[sf::Keyboard::Left])
				{
					direction.x = -1;
					key_states[sf::Keyboard::Left] = true;
				}
				else if (event.key.code == sf::Keyboard::Right && !key_states[sf::Keyboard::Right])
				{
					direction.x = 1;
					key_states[sf::Keyboard::Right] = true;
				}
				else if (event.key.code == sf::Keyboard::Up && !key_states[sf::Keyboard::Up])
				{
					direction.y = -1;
					key_states[sf::Keyboard::Up] = true;
				}
				else if (event.key.code == sf::Keyboard::Down && !key_states[sf::Keyboard::Down])
				{
					direction.y = 1;
					key_states[sf::Keyboard::Down] = true;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					direction.x = 0;
					key_states[sf::Keyboard::Left] = false;
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					direction.x = 0;
					key_states[sf::Keyboard::Right] = false;
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					direction.y = 0;
					key_states[sf::Keyboard::Up] = false;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					direction.y = 0;
					key_states[sf::Keyboard::Down] = false;
				}
			}
		}

		auto next_position = rectangle.getPosition() + (sf::Vector2f{ direction } * distance);
		direction = sf::Vector2i{};

		if (next_position.x >= 0.f && next_position.x <= 700.f && next_position.y >= 0.f && next_position.y <= 700.f)
		{
			rectangle.setPosition(next_position);
		}

		window.clear();
		window.draw(rectangle);
		window.display();
	}
}