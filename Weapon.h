#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

class Weapon : public sf::Drawable, public sf::Transformable
{
private:
	AnimatedSprite m_Sprite;
    sf::Transformable* m_Parent;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);
    }

public:
    Weapon(sf::Texture& texture);
    void attachTo(Transformable& target, float offset);
    void update(float delta, sf::Vector2f mousePosition);
};

