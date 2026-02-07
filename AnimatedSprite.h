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

	int m_SpriteSize;
	int m_RowCount;
	int m_ColumnCount;
	sf::IntRect m_SpritesheetBounds;

	bool isFrameInsideBounds(sf::Vector2u frame);
	void updateFrame();
	void nextFrame();
public:
	AnimatedSprite(
		sf::IntRect spritesheetBounds,
		unsigned int spriteSize,
		unsigned int rowCount,
		unsigned int columnCount,
		sf::Texture& texture
	);

	void setAnimation(
		unsigned int startFrame,
		unsigned int finalFrame,
		unsigned int row,
		float delayInSeconds, 
		bool loop = false
	);
	void update(float delta);
	void stop();
	void play();

	bool isPlaying() const;
};
