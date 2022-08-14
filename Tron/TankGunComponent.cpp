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
		auto bullet = TronConstructor::PlayerBullet(m_Angle);
		nm_pScene->AddGameObject(bullet);
		//dae::SceneManager::GetInstance().GetScene()->AddGameObject();
		std::cout << "should spawn bullet" << std::endl;

	}

}
