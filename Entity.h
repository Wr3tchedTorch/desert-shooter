#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "VelocityComponent.h"

using sf::Texture,
	  sf::Drawable, sf::Transformable;

class Entity : public Transformable, public Drawable
{
protected:
	AnimatedSprite    m_Sprite;
	VelocityComponent m_VelocityComponent;
	
	float m_Speed;

public:
	Entity(
		Texture& texture, 
		unsigned int spriteSize, 
		unsigned int spriteColumnCount,
		unsigned int spriteRowCount,
		sf::Vector2f maxVelocity
	);

	virtual void update(float delta) = 0;
};

