#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

#pragma once
class VelocityComponent
{
public:	
	VelocityComponent(sf::Transformable& parentTransformable, sf::Vector2f maxVelocity);
	void update(float delta);
	void addVelocity(const sf::Vector2f& velocity);
	void setVelocity(sf::Vector2f velocity);
	void setMaxVelocity(sf::Vector2f velocity);
	void setFriction(float friction);
	void setApplyXFriction(bool applyXFriction);
	void setApplyYFriction(bool applyYFriction);
	
	const sf::Vector2f& getVelocity() const;	
	const sf::Vector2f& getMaxVelocity() const;

private:
	float m_friction = 300.0f;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Transformable& m_parentTransformable;
	
	bool m_applyXFriction = true;
	bool m_applyYFriction = true;

	void addFrictionX(float delta);
	void addFrictionY(float delta);
	void trimVelocity();
};
