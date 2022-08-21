#pragma once
#include "BaseComponent.h"
#include "ComponentList.h"
#include "Subject.h"

class TankControlComponent final : public BaseComponent
{
public:

	TankControlComponent() = default;
	TankControlComponent(RenderComponent* Body, RenderComponent* Gun);

	~TankControlComponent() override
	{
		delete m_pSubject;
	};
	TankControlComponent(const TankControlComponent& other) = delete;
	TankControlComponent(TankControlComponent&& other) noexcept = delete;
	TankControlComponent& operator=(const TankControlComponent& other) = delete;
	TankControlComponent& operator=(TankControlComponent&& other) noexcept = delete;
 
	void Initialize() override {}
	void FixedUpdate(const float)  override {}
	void Update(const float ) override;
	void LateUpdate(const float ) override {}
	void Render() const override {}
	void GuiRender() const override {}

	//add's the value to the current rotation.
	void RotateGun(float RotToAdd);

	Subject* GetSubject() { return m_pSubject; }

private:
	Subject* m_pSubject = nullptr;
	RenderComponent* m_npBodysprite = nullptr;
	RenderComponent* m_npGunSprite = nullptr;

	float m_GunRotation = 0.f;

	float m_ReloadTime = 0.f;
	float m_MaxReloadTime = 2.f;

};

