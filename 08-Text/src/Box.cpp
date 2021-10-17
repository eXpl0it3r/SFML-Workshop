#include "Box.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

Box::Box(const sf::Texture& tilesheet, const sf::Vector2f position) :
    m_tilesheet{ tilesheet },
    m_sprite{ m_tilesheet }
{
    m_sprite.setPosition(position);
    set_state(State::OnNormalTile);
}

void Box::set_state(const State state)
{
    m_state = state;

    switch (state)
    {
    default:
    case State::OnNormalTile:
        m_sprite.setTextureRect({ 64, 0, 64, 64 });
        break;
    case State::OnTargetTile:
        m_sprite.setTextureRect({ 64, 64, 64, 64 });
        break;
    }
}

Box::State Box::get_state() const
{
    return m_state;
}

sf::Vector2f Box::get_position() const
{
    return m_sprite.getPosition();
}

void Box::set_position(const sf::Vector2f position)
{
    m_sprite.setPosition(position);
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
