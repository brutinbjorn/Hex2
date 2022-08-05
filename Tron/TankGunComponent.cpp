#include "TankGunComponent.h"

void TankGunComponent::Update(const float dt)
{
	if(M_FireDelayDelta > 0) M_FireDelayDelta -= dt;
}

void TankGunComponent::ShootGun()
{
	if(M_FireDelayDelta <= 0)
	{
		//spawn projectile
		std::cout << "should spawn bullet" << std::endl;

	}

}
