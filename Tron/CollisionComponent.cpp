#pragma once
#include "CollisionComponent.h"

#include "CollisionManager.h"
#include "GameObject.h"
#include "Wrappers.h"

void CollisionComponent::Update(const float)
{

	auto currentPos = GetParent()->GetTransform();
	if(m_formerPosition.GetPosition() != currentPos->GetPosition())
	{
		auto Others = dae::CollisionManager::GetInstance().GetAllCollisionBoxes();
		for (int index = 0; index < Others.size(); ++index)
		{
			if (Others[index] != this)
			{
				auto otherRec = Others[index]->GetRect();
				auto dir = IsRectsOverLapping(m_rect, otherRec);

				if (dir)
				{
					m_direction += dir;
					m_IsTouching = true;
				}
			}
		}


	}

}

char CollisionComponent::IsRectsOverLapping(SDL_Rect a, SDL_Rect b)
{
	char overlap = 0;
	glm::ivec2 Cube1TL = { a.x,a.y };
	glm::ivec2 Cube1BR = { a.x + a.w,a.y + a.h };

	glm::ivec2 Cube2TL = { b.x,b.y };
	glm::ivec2 Cube2BR = { b.x + b.w, b.y + b.h };

	if ((Cube1TL.x <= Cube2BR.x && Cube1BR.x >= Cube2TL.x) && (Cube1TL.y <= Cube2BR.y && Cube1BR.y >= Cube2TL.y))
	{
		if (Cube1TL.x <= Cube2BR.x) overlap += DIRECTION_LEFT;
		if (Cube1BR.x >= Cube2TL.x) overlap += DIRECTION_RIGHT;
		if (Cube1TL.y <= Cube2BR.y) overlap += DIRECTION_UP;
		if (Cube1BR.y >= Cube2TL.y) overlap += DIRECTION_DOWN;
		//m_gotHit = true;
		return overlap;
	}
	return false;
}

