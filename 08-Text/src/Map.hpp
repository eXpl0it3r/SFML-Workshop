#pragma once

#include <SFML/Graphics.hpp>
#include <set>

class Map final : public sf::Drawable
{
public:
	void load(const sf::Texture& tilesheet, sf::Vector2u tile_size,
		const int* tile_map, sf::Vector2<std::size_t> map_size);
	bool check_collision(sf::Vector2f next_position, std::set<int> collision_values) const;
	int get_tile_number(sf::Vector2<std::size_t> tile_position);

private:
	void generate_map(const sf::Texture& tilesheet);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<int> m_tile_map;
	sf::Vector2u m_tile_size;
	sf::Vector2<std::size_t> m_map_size;
	std::vector<sf::Sprite> m_sprites;
};

