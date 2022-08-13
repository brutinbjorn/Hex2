#include "TankGunComponent.h"

#include "Scene.h"
#include "SceneManager.h"
#include "TronConstructor.h"

void TankGunComponent::Update(const float dt)
{
	if(M_FireDelayDelta > 0) M_FireDelayDelta -= dt;
}

void TankGunComponent::ShootGun()
{
	if(M_FireDelayDelta <= 0)
	{
		TronConstructor::PlayerTank();
		nm_pScene->AddGameObject()
		//dae::SceneManager::GetInstance().GetScene()->AddGameObject();
		std::cout << "should spawn bullet" << std::endl;

	}

}
