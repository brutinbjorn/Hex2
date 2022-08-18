#include "BouncingBulletComponent.h"

#include <iostream>

void BouncingBulletComponent::Update(const float)
{
	GetParent()->GetTransform()->Translate(m_Vector.x * m_speed,m_Vector.y, 0);


	if(nm_pHurtBox)
	{
		HitboxComponent* hit = nullptr;
		bool HasHit = nm_pHurtBox->IsOverlappingHitbox(hit);
		if (HasHit)
			std::cout << "HurtBox detects hit" << std::endl;


	}



	if (nm_pCollisionBox->IsColliding())
	{
		char dir = nm_pCollisionBox->GetCollisionSides();
		if (dir == DIRECTION_LEFT || dir == DIRECTION_RIGHT)
		{
			m_Vector.x = -m_Vector.x;
		}

		if (dir == DIRECTION_UP || dir == DIRECTION_DOWN)
		{
			m_Vector.y = -m_Vector.y;
		}
		m_BounceLeft--;
	};
	if (m_BounceLeft <= 0)
	{
		GetParent()->SetMarkForDeletion();
	}

}
