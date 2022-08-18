#pragma once
#include <BaseComponent.h>

#include "EnemySightComponent.h"
#include "HitboxComponent.h"
#include "Subject.h"

class EnemyTankComponent :
    public BaseComponent
{
public:
	EnemyTankComponent(HitboxComponent* hitbox, EnemySightComponent* sight);
	~EnemyTankComponent() override = default;
	EnemyTankComponent(const EnemyTankComponent& other) = delete;
	EnemyTankComponent(EnemyTankComponent&& other) noexcept = delete;
	EnemyTankComponent& operator=(const EnemyTankComponent& other) = delete;
	EnemyTankComponent& operator=(EnemyTankComponent&& other) noexcept = delete;

	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float ) override;
	void LateUpdate(const float) override {};
	void Render() const override {};

	bool Recieve(BaseComponent*, const std::string&) override;
private:
	HitboxComponent* nm_pHitbox = nullptr;
	EnemySightComponent* nm_pSight = nullptr;
	int m_Health = 3;
	int m_MaxHealth = 3;

	Subject* m_pSubject = nullptr;


};

