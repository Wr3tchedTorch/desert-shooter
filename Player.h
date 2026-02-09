#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "VelocityComponent.h"

using sf::Texture, 
      sf::Drawable, sf::Transformable;

class Player : public Drawable, public Transformable
{
private: 
	AnimatedSprite    m_Sprite;
    VelocityComponent m_VelocityComponent;
    float m_Speed = 300.0f;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);
    }

    sf::Vector2i getDirectionFromInput();

public:
	Player(Texture& texture);
    void update(float delta);
};

