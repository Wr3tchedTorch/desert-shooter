#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{	
	m_Damage = 0;
	m_Speed  = 0;
	m_IsActive = true;
}

void Bullet::setAppearance(sf::Color color, float size)
{	
	m_Shape.setFillColor(color);
	m_Shape.setSize({ size, size });
}

void Bullet::spawn(float damage, float speed, sf::Vector2f direction)
{
	m_Damage	= damage;
	m_Speed		= speed;
	m_Direction = direction;
	m_IsActive  = true;
}

void Bullet::despawn()
{
	m_IsActive = false;
	m_Speed	   = 0;
	setPosition({ 0, 0 });
}

bool Bullet::isActive()
{
	return m_IsActive;
}

void Bullet::update(float delta)
{
	m_Shape.move(m_Direction * m_Speed * delta);

	sf::Vector2f position = getPosition();	
	bool outOfBoundsY = position.y < 0 || position.y > 1080;
	bool outOfBoundsX = position.x < 0 || position.x > 1920;

	if (outOfBoundsX || outOfBoundsY)
	{
		despawn();
	}
}

sf::RectangleShape Bullet::getShape()
{
	return m_Shape;
}
