#pragma once
#include "ComponentList.h"
class TankGunComponent : public BaseComponent
{
public:
	TankGunComponent() = default;
	~TankGunComponent() override = default;
	TankGunComponent(const TankGunComponent& other) = delete;
	TankGunComponent(TankGunComponent&& other) noexcept = delete;
	TankGunComponent& operator=(const TankGunComponent& other) = delete;
	TankGunComponent& operator=(TankGunComponent&& other) noexcept = delete;

	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float dt) override ;
	void LateUpdate(const float ) override {};
	void Render() const override {};

	void LinkGunTexture(RenderComponent* GunSprite) { nm_pRenderComponent = GunSprite; };
	void ShootGun();

	void RotateGun(float AngleToAdd)
	{
		m_Angle += AngleToAdd;
		nm_pRenderComponent->SetRotation(m_Angle);
	};

private:

	RenderComponent* nm_pRenderComponent = nullptr;

	float m_FireDelay = 1;
	float M_FireDelayDelta = 0;
	float m_Angle = 0;
};

