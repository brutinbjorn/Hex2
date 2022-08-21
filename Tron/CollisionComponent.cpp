#pragma once
#include "CollisionComponent.h"

#include "CollisionManager.h"
#include "GameObject.h"
#include "SquareComponent.h"
#include "Wrappers.h"

void CollisionComponent::Update(const float)
{
	m_direction = 0;
	m_IsTouching = false;

	auto currentPos = GetParent()->GetTransform();
	if(m_formerPosition.GetPosition() != currentPos->GetPosition() && !m_IsTouching)
	{
		auto Others = dae::CollisionManager::GetInstance().GetAllCollisionBoxes();
		for (size_t index = 0; index < Others.size(); ++index)
		{
			const auto otherRec = Others[index]->GetSquareUsedForColission();

			if (otherRec && otherRec != nm_pSquare)
			{
				auto sqrWorld = nm_pSquare->GetSquareWorld();

				if(!m_static)
				{
					auto val = nm_pActor->GetVelocity();
					sqrWorld.x += static_cast<int>(val.x + 1.2f);
					sqrWorld.y += static_cast<int>(val.y + 1.2f);
				}
				auto dir = IsRectsOverLapping(sqrWorld, otherRec->GetSquareWorld());

				if (dir)
				{
					m_direction += dir;
					m_IsTouching = true;
#ifdef _DEBUG
					std::cout << "Collision Overlap" << std::endl;
					break;
#endif
				}
			}
		}
		m_formerPosition.SetPosition(currentPos->GetPosition());
	}
}

char CollisionComponent::IsRectsOverLapping(SDL_Rect a, SDL_Rect b)
{
	char overlap = 0;
	glm::ivec2 Cube1TL = { a.x,a.y };
	glm::ivec2 Cube1BR = { a.x + a.w,a.y + a.h };

	glm::ivec2 Cube2TL = { b.x,b.y };
	glm::ivec2 Cube2BR = { b.x + b.w, b.y + b.h };

	glm::vec2 val;
	if(nm_pActor)val = nm_pActor->GetVelocity();

	if ((Cube1TL.x <= Cube2BR.x &&  Cube2TL.x <= Cube1BR.x) && (Cube1TL.y <= Cube2BR.y && Cube1BR.y >= Cube2TL.y))
	{
		if (Cube1TL.x <= Cube2BR.x && Cube1TL.x -val.x >= Cube2BR.x) 
			overlap = Directions::DIRECTION_RIGHT;
		if (Cube1BR.x >= Cube2TL.x && Cube1BR.x - val.x <= Cube2TL.x)
			overlap = Directions::DIRECTION_LEFT;
		 if (Cube1TL.y <= Cube2BR.y && Cube1TL.y - val.y >= Cube2BR.y)
			overlap = Directions::DIRECTION_UP;
		 if (Cube1BR.y >= Cube2TL.y && Cube1BR.y - val.y <= Cube2TL.y)
			overlap = Directions::DIRECTION_DOWN;
		//m_gotHit = true;
		return overlap;
	}
	return false;
}

