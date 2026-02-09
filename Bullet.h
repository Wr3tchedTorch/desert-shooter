#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

class Bullet : public sf::Transformable, public sf::Drawable
{
private:
    sf::RectangleShape m_Shape;
    sf::Vector2f m_Direction;
    float m_Speed;
    float m_Damage;
    bool  m_IsActive;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Shape, states);
    }

public:
    Bullet();
    void setAppearance(sf::Color color, float size);
    void spawn(float damage, float speed, sf::Vector2f direction, sf::Vector2f startPosition);
    void despawn();
    bool isActive();

    void update(float delta);
    sf::RectangleShape& getShape();
};

