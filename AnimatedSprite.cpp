#include "AnimatedSprite.h"
#include "TextureHolder.h"

bool AnimatedSprite::isFrameInsideBounds(sf::Vector2u frame)
{
	bool isInsideX = frame.x < m_ColumnCount;
	bool isInsideY = frame.y < m_RowCount;

	return isInsideX && isInsideY;
}

void AnimatedSprite::updateFrame()
{
	sf::IntRect textureRect;

	textureRect.position.x = m_CurrentFrame * m_SpriteSize;
	textureRect.position.y = m_CurrentRow   * m_SpriteSize;	
	textureRect.size.x = m_SpriteSize;
	textureRect.size.y = m_SpriteSize;

	if (m_FlipHorizontal)
	{
		textureRect.position.x += m_SpriteSize;
		textureRect.size.x *= -1;
	}
	if (m_FlipVertical)
	{
		textureRect.position.y += m_SpriteSize;
		textureRect.size.y *= -1;
	}

	setTextureRect(textureRect);
}

void AnimatedSprite::nextFrame()
{
	if (m_CurrentFrame >= m_FinalFrame && !m_IsLooping)
	{
		return;
	}

	m_CurrentFrame++;

	if (m_CurrentFrame > m_FinalFrame && m_IsLooping)
	{
		m_CurrentFrame = m_StartFrame;
	}
	updateFrame();
}

AnimatedSprite::AnimatedSprite(
	unsigned int spriteSize,
	unsigned int rowCount,
	unsigned int columnCount,
	sf::Texture& texture) : sf::Sprite(texture)
{
	m_FlipHorizontal = false;
	m_FlipVertical   = false;

	m_SpriteSize  = spriteSize;
	m_RowCount    = rowCount;
	m_ColumnCount = columnCount;
}

void AnimatedSprite::setAnimation(unsigned int startFrame, unsigned int finalFrame, unsigned int row, float delayInSeconds, bool loop)
{
	assert(isFrameInsideBounds({ startFrame, row }));
	assert(isFrameInsideBounds({ finalFrame, row }));

	m_StartFrame   = startFrame;
	m_FinalFrame   = finalFrame;
	m_CurrentFrame = m_StartFrame;
	m_CurrentRow   = row;
	m_TimeBetweenFramesInSeconds  = delayInSeconds;
	m_IsLooping = loop;
}

void AnimatedSprite::setFrame(unsigned int frameIndex, unsigned int row)
{
	assert(isFrameInsideBounds({ frameIndex, row }));

	m_CurrentFrame = frameIndex;
	m_CurrentRow   = row;

	updateFrame();
}

void AnimatedSprite::update(float delta)
{
	if (!m_IsPlaying)
	{
		return;
	}
	
	std::cout << m_TimeSinceLastFrameInSeconds << "\n";
	m_TimeSinceLastFrameInSeconds += delta;
	
	if (m_TimeSinceLastFrameInSeconds > m_TimeBetweenFramesInSeconds)
	{
		nextFrame();
		m_TimeSinceLastFrameInSeconds = 0;
	}
}

void AnimatedSprite::stop()
{
	m_IsPlaying = false;

	m_TimeSinceLastFrameInSeconds = 0;
}

void AnimatedSprite::play()
{
	m_IsPlaying = true;

	m_TimeSinceLastFrameInSeconds = m_TimeBetweenFramesInSeconds;

	updateFrame();
}

void AnimatedSprite::flipHorizontal()
{
	m_FlipHorizontal = !m_FlipHorizontal;
	updateFrame();
}

void AnimatedSprite::flipVertical()
{
	m_FlipVertical = !m_FlipVertical;
	updateFrame();
}

bool AnimatedSprite::isFlipedVertical() const
{
	return m_FlipVertical;
}

bool AnimatedSprite::isFlipedHorizontal() const
{
	return m_FlipHorizontal;
}

bool AnimatedSprite::isPlaying() const
{
	return m_IsPlaying;
}


