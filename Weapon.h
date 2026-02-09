#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "Bullet.h"

class Weapon : public sf::Drawable, public sf::Transformable
{
private:
    const int   MAX_BULLETS_ALLOWED = 100;
    const float SPRITE_SIZE = 24;

    sf::Transformable* m_Parent;
	AnimatedSprite m_Sprite;
    sf::Vector2f m_StartOrigin;
    
    Bullet* m_Bullets;
    int m_CurrentBulletIndex;

    float m_BulletSpeed;
    float m_BulletDamage;

    float m_DelayBetweenShotsInSeconds;
    float m_TimeSinceLastShotInSeconds;
    bool  m_CanShoot;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_Sprite, states);

        for (int i = 0; i < MAX_BULLETS_ALLOWED; i++)
        {
            Bullet& bullet = m_Bullets[i];
            if (bullet.isActive())
            {
                target.draw(bullet);
            }
        }
    }

public:
    Weapon(sf::Texture& texture, sf::Vector2f origin);    

    void attachTo(Transformable& target, float offset);
    void update(float delta, sf::Vector2f mousePosition);
    void setAttributes(float bulletDamage, float bulletSpeed, float delayMilli);
    void shoot();
    Bullet* getBullets();
};