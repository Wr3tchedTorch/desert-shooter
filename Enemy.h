#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "VelocityComponent.h"

using sf::Texture,
      sf::Drawable, sf::Transformable;

class Enemy : public Drawable, public Transformable
{
private:
    AnimatedSprite    m_Sprite;
    VelocityComponent m_VelocityComponent;
    
    float m_Speed = 300.0f;
    bool  m_IsAlive = true;

    sf::Transformable* m_Target;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);
    }

    sf::Vector2i getDirection();

public:
    Enemy();

    void Spawn();
    void setSpeed(float toSpeed);
    void setTexture(Texture& texture);
    void setTarget(sf::Transformable* target);
    void update(float delta);
};

