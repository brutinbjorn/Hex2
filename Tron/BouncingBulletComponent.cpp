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
		auto val = nm_pActor->GetVelocity();
		char dir = nm_pCollisionBox->GetCollisionSides();
		if (dir & DIRECTION_LEFT || dir & DIRECTION_RIGHT)
		{
			val.x = -val.x;
		}
		if (dir & DIRECTION_UP || dir & DIRECTION_DOWN)
		{
			val.y = -val.y;
		}
		nm_pActor->SetVelocity(val);
		std::cout << "directionChange" << std::endl;

		m_BounceLeft--;
	};
	if (m_BounceLeft <= 0 || nm_pHurtBox->GotAHit())
	{
		GetParent()->SetMarkForDeletion();
	}

}
