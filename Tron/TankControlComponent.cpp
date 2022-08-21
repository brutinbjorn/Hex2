#include "TankControlComponent.h"

TankControlComponent::TankControlComponent(RenderComponent* body, RenderComponent* gun)
	:m_npBodysprite(body), m_npGunSprite(gun),m_pSubject(new Subject)
{
}

void TankControlComponent::Update(const float )
{
}

void TankControlComponent::RotateGun(float RotToAdd)
{
	m_GunRotation += RotToAdd;
}