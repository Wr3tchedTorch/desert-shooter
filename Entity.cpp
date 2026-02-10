#include "Entity.h"

Entity::Entity(
	Texture& texture, 
	unsigned int spriteSize, 
	unsigned int spriteColumnCount, 
	unsigned int spriteRowCount, 
	sf::Vector2f maxVelocity
) : m_Sprite(spriteSize, spriteColumnCount, spriteRowCount, texture)
{
}
