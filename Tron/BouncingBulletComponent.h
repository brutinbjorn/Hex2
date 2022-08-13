#pragma once
#include <BaseComponent.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include <HitboxComponent.h>

class BouncingBulletComponent :
    public BaseComponent
{
public:
	BouncingBulletComponent() = default;
	~BouncingBulletComponent() override = default;
	BouncingBulletComponent(const BouncingBulletComponent& other) = delete;
	BouncingBulletComponent(BouncingBulletComponent&& other) noexcept = delete;
	BouncingBulletComponent& operator=(const BouncingBulletComponent& other) = delete;
	BouncingBulletComponent& operator=(BouncingBulletComponent&& other) noexcept = delete;


	void Initialize() override {}
	void FixedUpdate(const float) override {}
	void Update(const float) override
	{
		GetParent()->GetTransform()->Translate(m_Vector.x * m_speed,m_Vector.y, 0);
	}
	void LateUpdate(const float) override {}
	void Render() const override {}

private:

	HitboxComponent* nm_pHitbox = nullptr; // hitbox
	glm::vec2 m_Vector;
	float m_speed = 2;
	int m_BounceLeft = 5;
};

