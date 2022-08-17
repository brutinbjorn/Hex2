#include "EnemyTankComponent.h"

#include <iostream>


EnemyTankComponent::EnemyTankComponent(HitboxComponent* hitbox, EnemySightComponent* sight)
	:nm_pHitbox(hitbox),nm_pSight(sight)
{

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

}
