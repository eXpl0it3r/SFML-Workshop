#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Box.hpp"

class Sokoban
{
public:
	enum TileTypes
	{
		Empty = 0,
		BoxNormal = 1,
		BoxHighlighted = 14,
		BrickWall = 85,
		FloorGrey = 89,
		FloorBrown = 90,
		TargetGrey = 102,
	};

	Sokoban();

	void run();

private:
	void handle_events();
	void update();
	void render();

	void init_player();
	void init_map();
	void init_boxes();

	void handle_keyboard_input(sf::Event event);
	bool check_window_bounds(sf::Vector2<float> next_position) const;
	bool update_boxes(sf::Vector2<float> next_position, const std::set<int>& collision_set);
	void update_box_visuals();
	bool are_equal(sf::Vector2<float> vector_one, const sf::Vector2<float> vector_two) const;

	const sf::Vector2u m_window_size;
	const float m_distance;
	sf::Vector2i m_direction;
	sf::Vector2f m_tile_size;
	std::map<sf::Keyboard::Key, bool> m_key_states;
	sf::RenderWindow m_window;
	sf::Texture m_tilesheet;
	sf::Sprite m_player;
	Map m_map;
	std::vector<Box> m_boxes;
};
