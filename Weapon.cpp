#include "Weapon.h"
#include <iostream>

Weapon::Weapon(sf::Texture& texture, sf::Vector2f origin) : m_Sprite(SPRITE_SIZE, 4, 10, texture)
{
	m_Parent = nullptr;
	m_Sprite.setFrame(5, 0);

	m_StartOrigin = origin;
	setOrigin(origin);

	m_CurrentBulletIndex = 0;
	m_Bullets = new Bullet[MAX_BULLETS_ALLOWED];
	
	m_CanShoot = true;
	m_TimeSinceLastShotInSeconds = 0;
}

void Weapon::attachTo(Transformable& target, float offset)
{
	m_Parent = &target;

	setOrigin(m_StartOrigin);
	setPosition(m_Parent->getPosition());
}

void Weapon::update(float delta, sf::Vector2f mousePosition)
{
	if (!m_CanShoot)
	{
		m_TimeSinceLastShotInSeconds += delta;

		if (m_TimeSinceLastShotInSeconds >= m_DelayBetweenShotsInSeconds)
		{
			m_CanShoot = true;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		shoot();
	}

	for (int i = 0; i < MAX_BULLETS_ALLOWED; i++)
	{
		Bullet& bullet = m_Bullets[i];
		if (bullet.isActive())
		{
			bullet.update(delta);
		}
	}

    setPosition(m_Parent->getPosition());
	move({0, 4});

    sf::Vector2f direction = mousePosition - getPosition();

    sf::Angle rotation = direction.angle();

	float deg = rotation.asDegrees();

	bool isPointingRight = deg > -90 && deg < 90;
	bool isPointingLeft  = deg < -90 || deg > 90;
	if ( m_Sprite.isFlipedVertical() && isPointingRight ||
		!m_Sprite.isFlipedVertical() && isPointingLeft)
	{
		m_Sprite.flipVertical();

		float newYOrigin = SPRITE_SIZE - getOrigin().y + 1;
		setOrigin({ getOrigin().x, newYOrigin });
	}

    setRotation(rotation);
}

void Weapon::setAttributes(float bulletDamage, float bulletSpeed, float delayMilli)
{
	m_BulletDamage = bulletDamage;
	m_BulletSpeed  = bulletSpeed;
	m_DelayBetweenShotsInSeconds = delayMilli / 1000;
}

void Weapon::shoot()
{	
	if (!m_CanShoot)
	{
		return;
	}
	m_TimeSinceLastShotInSeconds = 0;
	m_CanShoot = false;

	Bullet& bullet = m_Bullets[m_CurrentBulletIndex];
	bullet.setAppearance(sf::Color(0xFAD000FF), 3);

	bullet.getShape().setRotation(getRotation());

	sf::Vector2f dir(1, 0);
	dir = dir.rotatedBy(getRotation());	

	sf::Vector2f bulletStartPosition(getPosition());
	bulletStartPosition += SPRITE_SIZE * dir;

	bullet.spawn(m_BulletDamage, m_BulletSpeed, dir, bulletStartPosition);

	m_CurrentBulletIndex++;
	if (m_CurrentBulletIndex >= 99)
	{
		m_CurrentBulletIndex = 0;
	}
}

Bullet* Weapon::getBullets()
{
	return m_Bullets;
}
