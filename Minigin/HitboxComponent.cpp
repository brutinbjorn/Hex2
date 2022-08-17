#include "MiniginPCH.h"
#include "HitboxComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "../Tron/SquareComponent.h"

//HitboxComponent::HitboxComponent(const glm::ivec2& pos, const glm::ivec2& size, int CollisionID)
//	:m_rect(SDL_Rect(pos.x, pos.y, size.x, size.y))
//	, m_CollisionID(CollisionID)
//{
//
//}

HitboxComponent::HitboxComponent(SquareComponent* sqr, int CollisionID)
	: nm_pSquareComp(sqr), m_CollisionID(CollisionID)
{
}

void HitboxComponent::Render() const
{
	dae::Renderer::GetInstance().RenderRect(m_rect, SDL_Color{ 0,255,0,255 });
}

void HitboxComponent::Update(const float)
{
	//glm::ivec3 pos = GetParent()->GetTransform()->GetPosition();

	//m_rect.x = pos.x;
	//m_rect.y = pos.y;
	m_rect = nm_pSquareComp->GetSquareWorld();
	
}

dae::GameObject* HitboxComponent::GetParent()
{
	return GetParent();
}

bool HitboxComponent::IsPointInThisHitbox(glm::ivec2 point) const
{
	glm::ivec2 topLeft = glm::ivec2(m_rect.x, m_rect.y);
	glm::ivec2 BottomRight = glm::ivec2(m_rect.x, m_rect.y) + glm::ivec2(m_rect.w, m_rect.h);


	if (topLeft.x <= point.x && topLeft.y <= point.y)
	{
		if (BottomRight.x >= point.x && BottomRight.y >= point.y)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool HitboxComponent::IsSquareInThisHitBox(SDL_Rect rectangle, int CollisionID)
{
	if (m_gotHit)
	{
		return false;
	}

	if (CollisionID != m_CollisionID)
	{
		m_gotHit = false;
		return false;
	}
	m_rect = nm_pSquareComp->GetSquareWorld();


	glm::ivec2 Cube1TL = glm::ivec2(m_rect.x,m_rect.y);
	glm::ivec2 Cube1BR = glm::ivec2(m_rect.x, m_rect.y) + glm::ivec2(m_rect.w, m_rect.h);

	glm::ivec2 Cube2TL = glm::ivec2(rectangle.x, rectangle.y);
	glm::ivec2 Cube2BR = glm::ivec2(rectangle.x, rectangle.y) + glm::ivec2(rectangle.w, rectangle.h);

	if ((Cube1TL.x <= Cube2BR.x && Cube1BR.x >= Cube2TL.x) && (Cube1TL.y <= Cube2BR.y && Cube1BR.y >= Cube2TL.y))
	{
		m_gotHit = true;
		return true;
	}

	m_gotHit = false;
	return false;
}

bool HitboxComponent::IsSquareInThisHitBox(SquareComponent* sqr, int CollisionID)
{
	return IsSquareInThisHitBox(sqr->GetSquareWorld(), CollisionID);
}
