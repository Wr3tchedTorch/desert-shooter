#include "Enemy.h"
#include "TextureHolder.h"

Enemy::Enemy() :
	m_Sprite(64, 1, 1, TextureHolder::GetTexture("graphics/texture_placeholder.png")),
	m_VelocityComponent(*this, { 60.0f, 60.0f })
{
}

void Enemy::setSpeed(float toSpeed)
{
}
