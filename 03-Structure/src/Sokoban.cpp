#include "Sokoban.hpp"

Sokoban::Sokoban() :
	m_window_size{ 700u, 700u },
	m_distance{ 100.f },
	m_window{ sf::VideoMode{m_window_size.x, m_window_size.y}, "03 - Structure - SFML Workshop" },
	m_rectangle{ {100.f, 100.f} }
{
	m_window.setFramerateLimit(60);

	m_rectangle.setFillColor(sf::Color::Green);
	m_rectangle.setPosition({ 300.f, 600.f });
}

void Sokoban::run()
{
	while (m_window.isOpen())
	{
		handle_events();
		update();
		render();
	}
}

void Sokoban::handle_events()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		handle_keyboard_input(event);
	}
}

void Sokoban::update()
{
	const auto next_position = m_rectangle.getPosition() + (sf::Vector2f{ m_direction } *m_distance);
	m_direction = sf::Vector2i{};

	if (next_position.x >= 0.f && next_position.x <= m_window_size.x - 100.f && next_position.y >= 0.f && next_position.y <= m_window_size.y - 100.f)
	{
		m_rectangle.setPosition(next_position);
	}
}

void Sokoban::render()
{
	m_window.clear();
	m_window.draw(m_rectangle);
	m_window.display();
}

void Sokoban::handle_keyboard_input(const sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left && !m_key_states[sf::Keyboard::Left])
		{
			m_direction.x = -1;
			m_key_states[sf::Keyboard::Left] = true;
		}
		else if (event.key.code == sf::Keyboard::Right && !m_key_states[sf::Keyboard::Right])
		{
			m_direction.x = 1;
			m_key_states[sf::Keyboard::Right] = true;
		}
		else if (event.key.code == sf::Keyboard::Up && !m_key_states[sf::Keyboard::Up])
		{
			m_direction.y = -1;
			m_key_states[sf::Keyboard::Up] = true;
		}
		else if (event.key.code == sf::Keyboard::Down && !m_key_states[sf::Keyboard::Down])
		{
			m_direction.y = 1;
			m_key_states[sf::Keyboard::Down] = true;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			m_direction.x = 0;
			m_key_states[sf::Keyboard::Left] = false;
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			m_direction.x = 0;
			m_key_states[sf::Keyboard::Right] = false;
		}
		else if (event.key.code == sf::Keyboard::Up)
		{
			m_direction.y = 0;
			m_key_states[sf::Keyboard::Up] = false;
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			m_direction.y = 0;
			m_key_states[sf::Keyboard::Down] = false;
		}
	}
}
