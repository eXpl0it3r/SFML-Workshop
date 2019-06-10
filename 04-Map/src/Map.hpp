#pragma once

#include <SFML/Graphics.hpp>
#include <set>

class Map final : public sf::Drawable
{
public:
	bool load(const std::string& tileset_path, sf::Vector2u tile_size, const int* tile_map, sf::Vector2<std::size_t> map_size);
	bool check_collision(sf::Vector2f next_position, std::set<int> collision_values);

private:
	void generate_map();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<int> m_tile_map;
	sf::Vector2u m_tile_size;
	sf::Vector2<std::size_t> m_map_size;
	std::vector<sf::Sprite> m_sprites;
	sf::Texture m_tileset;
};

