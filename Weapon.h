#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

class Weapon : public sf::Drawable, public sf::Transformable
{
private:
    const float SPRITE_SIZE = 24;

	AnimatedSprite m_Sprite;
    sf::Transformable* m_Parent;    
    sf::Vector2f m_StartOrigin;    

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);
    }

public:
    Weapon(sf::Texture& texture, sf::Vector2f origin);

    void attachTo(Transformable& target, float offset);
    void update(float delta, sf::Vector2f mousePosition);
};

