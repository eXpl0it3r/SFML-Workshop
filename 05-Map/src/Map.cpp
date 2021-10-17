#include "Map.hpp"

void Map::load(const sf::Texture& tilesheet, const sf::Vector2u tile_size,
               const int* tile_map, const sf::Vector2<std::size_t> map_size)
{
    m_tile_size = tile_size;
    m_tile_map = std::vector<int>{ tile_map, tile_map + (map_size.x * map_size.y) };
    m_map_size = map_size;

    generate_map(tilesheet);
}

bool Map::check_collision(const sf::Vector2f next_position, std::set<int> collision_values)
{
    const auto x = static_cast<std::size_t>(next_position.x / m_tile_size.x);
    const auto y = static_cast<std::size_t>(next_position.y / m_tile_size.y);

    return collision_values.find(m_tile_map[x + y * m_map_size.x]) != collision_values.end();
}

void Map::generate_map(const sf::Texture& tilesheet)
{
    m_sprites.resize(m_map_size.x * m_map_size.y);

    for (std::size_t x = 0; x < m_map_size.x; ++x)
    {
        for (std::size_t y = 0; y < m_map_size.y; ++y)
        {
            const auto tile_number = m_tile_map[x + y * m_map_size.x];
            const auto texture_u = tile_number % (tilesheet.getSize().x / m_tile_size.x);
            const auto texture_v = tile_number / (tilesheet.getSize().x / m_tile_size.x);

            auto& sprite = m_sprites[x + y * m_map_size.x];
            sprite.setTexture(tilesheet);
            sprite.setPosition({
                static_cast<float>(x * m_tile_size.x),
                static_cast<float>(y * m_tile_size.y)
            });
            sprite.setTextureRect({
                static_cast<int>(texture_u * m_tile_size.x),
                static_cast<int>(texture_v * m_tile_size.y),
                static_cast<int>(m_tile_size.x),
                static_cast<int>(m_tile_size.y)
            });
        }
    }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& sprite : m_sprites)
    {
        target.draw(sprite, states);
    }
}
