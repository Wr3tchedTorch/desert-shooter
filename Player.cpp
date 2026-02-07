#include "Player.h"
#include "TextureHolder.h"

Player::Player(Texture& texture) : m_Sprite({{0, 0}, {96, 96}}, 24, 4, 4, texture)
{
	m_Sprite.setAnimation(0, 1, 0, .300f, true);
	m_Sprite.play();
}

void Player::update(float delta)
{
	m_Sprite.update(delta);
}
