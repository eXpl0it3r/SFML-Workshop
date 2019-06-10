#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Box final : public sf::Drawable
{
public:
	enum class State
	{
		OnNormalTile,
		OnTargetTile
	};

	explicit Box(const sf::Texture& tilesheet, const sf::Vector2f position);
	void set_state(State state);
	State get_state() const;

	sf::Vector2f get_position() const;
	void set_position(sf::Vector2f position);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Texture& m_tilesheet;
	sf::Sprite m_sprite;
	State m_state;
};
