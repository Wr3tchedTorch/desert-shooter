#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

using sf::Texture, 
      sf::Drawable, sf::Transformable;

class Player : public Drawable, public Transformable
{
private: 
	AnimatedSprite m_Sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);
    }

public:
	Player(Texture& texture);
    void update(float delta);
};

