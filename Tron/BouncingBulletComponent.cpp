#include "BouncingBulletComponent.h"

#include <iostream>

void BouncingBulletComponent::Update(const float)
{

	if(nm_pHurtBox)
	{
		//HitboxComponent* hit = nullptr;
		//bool HasHit = nm_pHurtBox->IsOverlappingHitbox(hit);
		//if (HasHit)
		//	std::cout << "HurtBox detects hit" << std::endl;


	}

	if (nm_pCollisionBox->IsColliding())
	{
		//auto val = nm_pActor->GetVelocity();
		char dir = nm_pCollisionBox->GetCollisionSides();
		if (dir & DIRECTION_LEFT || dir & DIRECTION_RIGHT)
		{
			m_ContinuesVec.x = -m_ContinuesVec.x;
			
		}
		if (dir & DIRECTION_UP || dir & DIRECTION_DOWN)
		{
			m_ContinuesVec.y = -m_ContinuesVec.y;
		}
		//std::cout << "directionChange" << std::endl;
		GetParent()->GetTransform()->Translate(m_ContinuesVec.x * 3, m_ContinuesVec.y * 3, 0.f);

		m_BounceLeft--;
	};

	nm_pActor->SetVelocity(m_ContinuesVec);

	if (m_BounceLeft <= 0 || nm_pHurtBox->GotAHit())
	{
		GetParent()->SetMarkForDeletion();
	}

}
