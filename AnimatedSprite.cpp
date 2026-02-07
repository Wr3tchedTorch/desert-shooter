#include "AnimatedSprite.h"
#include "TextureHolder.h"

bool AnimatedSprite::isFrameInsideBounds(sf::Vector2u frame)
{
	bool isInsideX = frame.x * m_SpriteSize <= m_SpritesheetBounds.size.x;
	bool isInsideY = frame.y * m_SpriteSize <= m_SpritesheetBounds.size.y;

	return isInsideX && isInsideY;
}

void AnimatedSprite::updateFrame()
{
	sf::IntRect textureRect = m_SpritesheetBounds;

	textureRect.position.x = m_CurrentFrame * m_SpriteSize;
	textureRect.position.y = m_CurrentRow   * m_SpriteSize;
	
	textureRect.size.x = m_SpriteSize;
	textureRect.size.y = m_SpriteSize;

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
	sf::IntRect spritesheetBounds, 
	unsigned int spriteSize,
	unsigned int rowCount,
	unsigned int columnCount,
	sf::Texture& texture) : sf::Sprite(texture)
{
	assert(rowCount	   * spriteSize <= spritesheetBounds.size.y);
	assert(columnCount * spriteSize <= spritesheetBounds.size.x);

	m_SpritesheetBounds = spritesheetBounds;
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
	m_TimeBetweenFramesInSeconds = delayInSeconds;
	m_IsLooping = loop;
}

void AnimatedSprite::update(float delta)
{
	if (!m_IsPlaying)
	{
		return;
	}

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

	m_TimeSinceLastFrameInSeconds = 0;

	updateFrame();
}

bool AnimatedSprite::isPlaying() const
{
	return m_IsPlaying;
}


