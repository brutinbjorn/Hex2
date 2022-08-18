#include "EnemyTankComponent.h"

#include <iostream>


EnemyTankComponent::EnemyTankComponent(HitboxComponent* hitbox, EnemySightComponent* sight)
	:nm_pHitbox(hitbox),nm_pSight(sight)
{

}

void EnemyTankComponent::Update(const float)
{
	if (nm_pHitbox)
	{

		if (nm_pHitbox->IsHit())
		{
			m_Health--;
			if (m_Health <= 0)
			{
				GetParent()->SetMarkForDeletion();
			}
			else
			{
				nm_pHitbox->ResetHit();
			}
		}
	}

}

bool EnemyTankComponent::Recieve(BaseComponent* , const std::string& basic_string)
{
	if(basic_string == "GOT_HIT")
	{
		m_Health--;
#ifdef _DEBUG
		std::cout << "Enemy Got Hit" << std::endl;
#endif

		return true;
	}
	return false;
}
