#pragma once
#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Sprite
{
private:
	float m_TimeBetweenFramesInSeconds;
	float m_TimeSinceLastFrameInSeconds;
	int m_CurrentFrame;
	int m_StartFrame;
	int m_FinalFrame;
	int m_CurrentRow;
	bool m_IsLooping;
	bool m_IsPlaying;
	bool m_FlipVertical;
	bool m_FlipHorizontal;

	int m_SpriteSize;
	int m_RowCount;
	int m_ColumnCount;
	
	bool isFrameInsideBounds(sf::Vector2u frame);
	void updateFrame();
	void nextFrame();
public:
	AnimatedSprite(
		unsigned int spriteSize,
		unsigned int rowCount,
		unsigned int columnCount,
		const sf::Texture& texture
	);

	void setAnimation(
		unsigned int startFrame,
		unsigned int finalFrame,
		unsigned int row,
		float delayInSeconds, 
		bool loop = false
	);
	void setFrame(unsigned int frameIndex, unsigned int row);
	void update(float delta);
	void stop();
	void play();
	void flipHorizontal();
	void flipVertical();

	bool isFlipedVertical()   const;
	bool isFlipedHorizontal() const;

	bool isPlaying() const;
};
