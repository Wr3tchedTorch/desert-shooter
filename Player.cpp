#include "Player.h"
#include "TextureHolder.h"

Player::Player(Texture& texture) : 
	m_Sprite(24, 4, 4, texture), 
	m_VelocityComponent(*this, {60.0f, 60.0f})
{
	m_VelocityComponent.setFriction(500.0f);

	m_Sprite.stop();
	m_Sprite.setFrame(1, 0);

	m_Sprite.setOrigin({12, 12});
}

void Player::update(float delta)
{
	m_Sprite.update(delta);
	m_VelocityComponent.update(delta);

	sf::Vector2i dir = getDirectionFromInput();

	bool shouldFaceLeft  = dir.x < 0 && !m_Sprite.isFlipedHorizontal();
	bool shouldFaceRight = dir.x > 0 &&  m_Sprite.isFlipedHorizontal();
	if (shouldFaceLeft || shouldFaceRight)
	{
		m_Sprite.flipHorizontal();
	}

	if (dir.x == 0 && dir.y == 0)
	{
		m_Sprite.stop();
		m_Sprite.setFrame(0, 0);
	}
	else if (!m_Sprite.isPlaying())
	{
		m_Sprite.setAnimation(0, 1, 0, .300f, true);
		m_Sprite.play();
	}	
	
	m_VelocityComponent.setApplyXFriction(dir.x == 0);
	m_VelocityComponent.setApplyYFriction(dir.y == 0);
	m_VelocityComponent.addVelocity({m_Speed * delta * dir.x, m_Speed * delta * dir.y});
}

sf::Vector2i Player::getDirectionFromInput()
{
	int horizontal = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A);
	int vertical   = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W);

	return { horizontal, vertical };
}
