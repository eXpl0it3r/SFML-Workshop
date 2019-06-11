#include "Sokoban.hpp"

Sokoban::Sokoban() :
	m_window_size{ 640u, 640u },
	m_distance{ 64.f },
	m_tile_size{ m_distance, m_distance },
	m_window{ sf::VideoMode{m_window_size.x, m_window_size.y}, "08 - Text - SFML Workshop" }
{
	m_window.setFramerateLimit(60);

	m_texture_holder.load("tilesheet", "assets/tilesheet.png");

	init_player();
	init_map();
	init_boxes();
	init_music();
	init_sound();
	init_text();
}

void Sokoban::run()
{
	m_music.play();

	while (m_window.isOpen())
	{
		handle_events();

		if (!check_win_condition())
		{
			update();
		}

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
	const std::set<int> collision_set = { TileTypes::Empty, TileTypes::BrickWall, TileTypes::FloorBrown };

	const auto boxes_allow_movement = update_boxes(next_position, collision_set);

	if (!are_equal(m_player.getPosition(), next_position)
		&& check_window_bounds(next_position)
		&& !m_map.check_collision(next_position, collision_set)
		&& boxes_allow_movement)
	{
		m_sound_step.play();
		m_player.setPosition(next_position);
	}

	update_box_visuals();

	m_direction = sf::Vector2i{};
}

void Sokoban::render()
{
	m_window.clear(sf::Color{ 0xAA733CFF });
	m_window.draw(m_map);
	for (auto& box : m_boxes)
	{
		m_window.draw(box);
	}
	m_window.draw(m_player);

	if (check_win_condition())
	{
		m_window.draw(m_text);
	}

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

void Sokoban::init_map()
{
	std::vector<int> data =
	{
		90,  90,  90,  85,  85,  85,  85,  85,  90,  90,
		90,  85,  85,  85,  89,  89,  89,  85,  90,  90,
		90,  85, 102,  89,  89,  89,  89,  85,  90,  90,
		90,  85,  85,  85,  89,  89, 102,  85,  90,  90,
		90,  85, 102,  85,  85,  89,  89,  85,  90,  90,
		90,  85,  89,  85,  89, 102,  89,  85,  85,  90,
		90,  85,  89,  89, 102,  89,  89, 102,  85,  90,
		90,  85,  89,  89,  89, 102,  89,  89,  85,  90,
		90,  85,  85,  85,  85,  85,  85,  85,  85,  90,
		90,  90,  90,  90,  90,  90,  90,  90,  90,  90,
	};
	m_map.load(m_texture_holder.get("tilesheet"), { 64u, 64u }, data.data(), { 10u, 10u });
}

void Sokoban::init_boxes()
{
	auto& tilesheet = m_texture_holder.get("tilesheet");

	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 4.f, m_tile_size.y * 2.f });
	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 5.f, m_tile_size.y * 3.f });
	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 5.f, m_tile_size.y * 4.f });
	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 5.f, m_tile_size.y * 6.f });
	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 4.f, m_tile_size.y * 6.f });
	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 2.f, m_tile_size.y * 6.f });
	m_boxes.emplace_back(tilesheet, sf::Vector2f{ m_tile_size.x * 6.f, m_tile_size.y * 6.f });

	update_box_visuals();
}

void Sokoban::init_music()
{
	if (!m_music.openFromFile("assets/music.ogg"))
	{
		throw std::runtime_error{ "Unable to open asset 'assets/music.ogg'" };
	}
	m_music.setLoop(true);
	m_music.setVolume(60.f);
}

void Sokoban::init_sound()
{
	m_sound_holder.load("step", "assets/step.ogg");
	m_sound_step.setBuffer(m_sound_holder.get("step"));

	m_sound_holder.load("box", "assets/box.ogg");
	m_sound_box.setBuffer(m_sound_holder.get("box"));
}

void Sokoban::init_text()
{
	m_font_holder.load("DejaVu", "assets/DejaVuSansCondensed-Bold.ttf");

	m_text.setFont(m_font_holder.get("DejaVu"));
	m_text.setString("You Won!");
	m_text.setCharacterSize(80u);
	m_text.setOrigin({ std::round(m_text.getGlobalBounds().width / 2.f), std::round(m_text.getGlobalBounds().height / 2.f) });
	m_text.setPosition(sf::Vector2f{ m_window_size } / 2.f);
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
	return next_position.x >= 0.f && next_position.x <= m_window_size.x - m_distance
		&& next_position.y >= 0.f && next_position.y <= m_window_size.y - m_distance;
}

bool Sokoban::check_win_condition() const
{
	for (auto& box : m_boxes)
	{
		if (box.get_state() == Box::State::OnNormalTile)
		{
			return false;
		}
	}

	return true;
}

bool Sokoban::update_boxes(const sf::Vector2<float> next_position, const std::set<int>& collision_set)
{
	for (auto& next_box : m_boxes)
	{
		if (are_equal(next_position, next_box.get_position()))
		{
			const auto next_position_plus_one = m_player.getPosition() + (sf::Vector2f{ m_direction } *m_distance * 2.f);
			for (auto& next_box_plus_one : m_boxes)
			{
				if (are_equal(next_position_plus_one, next_box_plus_one.get_position())
					|| m_map.check_collision(next_position_plus_one, collision_set))
				{
					return false;
				}
			}

			m_sound_box.play();
			next_box.set_position(next_position_plus_one);
		}
	}

	return true;
}

void Sokoban::update_box_visuals()
{
	for (auto& box : m_boxes)
	{
		const auto& position = box.get_position();
		const auto tile_position = sf::Vector2<std::size_t>{
			static_cast<std::size_t>(position.x / m_tile_size.x),
			static_cast<std::size_t>(position.y / m_tile_size.x)
		};
		const auto tile_number = m_map.get_tile_number(tile_position);

		if (tile_number == TileTypes::TargetGrey)
		{
			box.set_state(Box::State::OnTargetTile);
		}
		else
		{
			box.set_state(Box::State::OnNormalTile);
		}
	}
}

bool Sokoban::are_equal(const sf::Vector2<float> vector_one, const sf::Vector2<float> vector_two) const
{
	return std::abs(vector_one.x - vector_two.x) <= std::numeric_limits<float>::epsilon()
		&& std::abs(vector_one.y - vector_two.y) <= std::numeric_limits<float>::epsilon();
}