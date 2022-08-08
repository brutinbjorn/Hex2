#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const glm::vec3& pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

void dae::Transform::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void dae::Transform::Translate(const glm::vec3& Translate)
{
	m_Position.x += Translate.x;
	m_Position.y += Translate.y;
	m_Position.z += Translate.z;
}
