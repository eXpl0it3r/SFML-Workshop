#pragma once

#include <SFML/Graphics.hpp>

class Map final : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset_path, sf::Vector2u tile_size, const int* tiles, sf::Vector2<std::size_t> map_size);

private:
	void generate_vertices(sf::Vector2u tile_size, const int* tiles, sf::Vector2<std::size_t> map_size);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<sf::Vertex> m_vertices;
	sf::Texture m_tileset;
};

