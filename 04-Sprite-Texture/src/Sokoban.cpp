#include "Sokoban.hpp"

Sokoban::Sokoban() :
	m_window_size{ 640, 640 },
	m_distance{ 64.f },
	m_tile_size{ m_distance, m_distance },
	m_window{ sf::VideoMode{m_window_size.x, m_window_size.y}, "04 - Sprite & Texture - SFML Workshop" }
{
	m_window.setFramerateLimit(60);

	m_texture_holder.load("tilesheet", "assets/tilesheet.png");

	init_player();
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
	const auto next_position = m_player.getPosition() + (sf::Vector2f{ m_direction } *m_distance);
	m_direction = sf::Vector2i{};

	if (check_window_bounds(next_position))
	{
		m_player.setPosition(next_position);
	}
}

void Sokoban::render()
{
	m_window.clear();
	m_window.draw(m_player);
	m_window.display();
}

void Sokoban::init_player()
{
	m_player.setTexture(m_texture_holder.get("tilesheet"));
	m_player.setPosition(m_tile_size * 2.f);
	m_player.setTextureRect({
		0,
		5 * static_cast<int>(m_tile_size.y),
		static_cast<int>(m_tile_size.x),
		static_cast<int>(m_tile_size.y)
		});
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

bool Sokoban::check_window_bounds(const sf::Vector2<float> next_position) const
{
	return next_position.x >= 0.f && next_position.x <= m_window_size.x - m_tile_size.x
		&& next_position.y >= 0.f && next_position.y <= m_window_size.y - m_tile_size.y;
}