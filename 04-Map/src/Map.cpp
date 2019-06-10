#include "Map.hpp"

bool Map::load(const std::string& tileset_path, const sf::Vector2u tile_size, const int* tiles, const sf::Vector2<std::size_t> map_size)
{
	if (!m_tileset.loadFromFile(tileset_path))
	{
		return false;
	}

	generate_vertices(tile_size, tiles, map_size);

	return true;
}

void Map::generate_vertices(const sf::Vector2u tile_size, const int* tiles, const sf::Vector2<std::size_t> map_size)
{
	m_vertices.resize(map_size.x * map_size.y * 4);

	for (std::size_t x = 0; x < map_size.x; ++x)
	{
		for (std::size_t y = 0; y < map_size.y; ++y)
		{
			const auto tile_number = tiles[x + y * map_size.x];

			const auto texture_u = tile_number % (m_tileset.getSize().x / tile_size.x);
			const auto texture_v = tile_number / (m_tileset.getSize().x / tile_size.x);

			const auto quad = &m_vertices[(x + y * map_size.x) * 4];

			quad[0].position = { static_cast<float>(x * tile_size.x), static_cast<float>(y * tile_size.y) };
			quad[1].position = { static_cast<float>((x + 1) * tile_size.x), static_cast<float>(y * tile_size.y) };
			quad[2].position = { static_cast<float>((x + 1) * tile_size.x), static_cast<float>((y + 1) * tile_size.y )};
			quad[3].position = { static_cast<float>(x * tile_size.x), static_cast<float>((y + 1) * tile_size.y) };

			quad[0].texCoords = { static_cast<float>(texture_u * tile_size.x), static_cast<float>(texture_v * tile_size.y) };
			quad[1].texCoords = { static_cast<float>((texture_u + 1) * tile_size.x), static_cast<float>(texture_v * tile_size.y) };
			quad[2].texCoords = { static_cast<float>((texture_u + 1) * tile_size.x), static_cast<float>((texture_v + 1) * tile_size.y) };
			quad[3].texCoords = { static_cast<float>(texture_u * tile_size.x), static_cast<float>((texture_v + 1) * tile_size.y) };
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;

	target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
}