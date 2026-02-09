#include "Weapon.h"
#include <iostream>

Weapon::Weapon(sf::Texture& texture) : m_Sprite(24, 4, 10, texture)
{
	m_Parent = nullptr;
	m_Sprite.setFrame(5, 0);
}

void Weapon::attachTo(Transformable& target, float offset)
{
	m_Parent = &target;
	
	setOrigin({ -12.0f,  12.0f});	
	setPosition(m_Parent->getPosition());
}

void Weapon::update(float delta, sf::Vector2f mousePosition)
{
    setPosition(m_Parent->getPosition());
    sf::Vector2f direction = mousePosition - getPosition();

    sf::Angle rotation = direction.angle();

	float deg = rotation.asDegrees();

	bool isPointingRight = deg > -90 && deg < 90;
	bool isPointingLeft  = deg < -90 || deg > 90;
	if ( m_Sprite.isFlipedVertical() && isPointingRight ||
		!m_Sprite.isFlipedVertical() && isPointingLeft)
	{
		m_Sprite.flipVertical();
	}

    setRotation(rotation);
}
