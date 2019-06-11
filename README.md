# SFML Workshop

This repository holds the example code use for an SFML Workshop at the C++ Usergroup Zentralschweiz.
If you find something to improve, don't hesitate to reach out or send a pull request.

## 01 - Setup

The most basic game loop using SFML.

- Basic game loop
- `sf::RenderWindow`
- `sf::Event`

## 02 - Movement

Move are a colored rectangle one keyboard button press at a time.

- Clear, draw, display
- `sf::RectangleShape`
- `sf::Keyboard`
- `sf::Event::KeyPressed` & `sf::Event::KeyReleased`
- `sf::Vector2<T>`

## 03 - Structure

Scope the application inside a class, thus allowing to share variables across multiple functions.

- Basic game structure

## 04 - Sprite & Texture

Replace the colored shape with some picture.

- Resource management
- `sf::Sprite`
- `sf::Texture`

## 05 - Map

Render the map based on fixed integer values.

- Basic map handling
- `sf::Drawable`

## 06 - Entity

Box entities need to be rendered separately.

- Collision detection
- Enum for types

## 07 - Audio

Play some background music and make some noise when moving.

- `sf::Music`
- `sf::SoundBuffer`
- `sf::Sound`

## 08 - Text

Display a 'You Won!' text when the win condition is reached.

- `sf::Font`
- `sf::Text`

----

## License

This software is dual licensed under the Public Domain and the MIT license, choose whichever you prefer. See the LICENSE.md file for more details.  
**Note:** The used assets do not fall under this license, but they are all licensed either CC0 or in the public domain