#include "VelocityComponent.h"
#include <iostream>
#include <string>
#include <algorithm>

VelocityComponent::VelocityComponent(sf::Transformable& parentTransformable, sf::Vector2f maxVelocity) : m_parentTransformable(parentTransformable)
{
	setMaxVelocity(maxVelocity);
}

void VelocityComponent::update(float delta)
{
	if (m_velocity.x != 0 && m_applyXFriction)
	{
		addFrictionX(delta);
	}
	if (m_velocity.y != 0 && m_applyYFriction)
	{
		addFrictionY(delta);
	}
	//std::cout << "velocity, x: " << std::to_string(m_velocity.x) << " y: " << std::to_string(m_velocity.y) << "\n";
	m_parentTransformable.move(m_velocity * delta);
}

void VelocityComponent::addVelocity(const sf::Vector2f& velocity)
{
	m_velocity += velocity;

	trimVelocity();
}

void VelocityComponent::addFrictionX(float delta)
{
	float frictionAmount = m_friction * delta;

	if (frictionAmount >= std::abs(m_velocity.x))
	{
		m_velocity.x = 0;
		return;
	}

	int sign = m_velocity.x > 0 ? -1 : 1;
	addVelocity({frictionAmount * sign, 0});
}

void VelocityComponent::addFrictionY(float delta)
{
	float frictionAmount = m_friction * delta;

	if (frictionAmount >= std::abs(m_velocity.y))
	{
		m_velocity.y = 0;
		return;
	}

	int sign = m_velocity.y > 0 ? -1 : 1;
	addVelocity({ 0, frictionAmount * sign });
}

void VelocityComponent::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;

	trimVelocity();
}

void VelocityComponent::setMaxVelocity(sf::Vector2f velocity)
{
	m_maxVelocity = velocity;

	trimVelocity();
}

void VelocityComponent::setFriction(float friction)
{
	m_friction = friction;
}

void VelocityComponent::setApplyYFriction(bool applyYFriction)
{
	m_applyYFriction = applyYFriction;
}

void VelocityComponent::setApplyXFriction(bool applyXFriction)
{
	m_applyXFriction = applyXFriction;
}

const sf::Vector2f& VelocityComponent::getVelocity() const
{
	return m_velocity;
}

const sf::Vector2f& VelocityComponent::getMaxVelocity() const
{
	return m_maxVelocity;
}

void VelocityComponent::trimVelocity()
{
	if (m_maxVelocity.x != 0) {
		m_velocity.x = std::clamp(m_velocity.x, -m_maxVelocity.x, m_maxVelocity.x);
	}

	if (m_maxVelocity.y != 0) {
		m_velocity.y = std::clamp(m_velocity.y, -m_maxVelocity.y, m_maxVelocity.y);
	}
}
