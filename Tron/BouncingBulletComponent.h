#pragma once
#include <BaseComponent.h>
#include <glm/glm.hpp>

#include "GameObject.h"
//#include <iostream>
#include "CollisionComponent.h"
#include "math.h"

#include "CollisionManager.h"
#include "HurtBoxComponent.h"

class BouncingBulletComponent :
    public BaseComponent
{
public:
	BouncingBulletComponent() = default;
	BouncingBulletComponent(float rotation,CollisionComponent* collision, HurtBoxComponent* hurtBox):nm_pCollisionBox(collision),nm_pHurtBox(hurtBox)
	{
		m_Vector.x = std::cos(rotation);
		m_Vector.y = std::sin(rotation);
	};
	~BouncingBulletComponent() override = default;
	BouncingBulletComponent(const BouncingBulletComponent& other) = delete;
	BouncingBulletComponent(BouncingBulletComponent&& other) noexcept = delete;
	BouncingBulletComponent& operator=(const BouncingBulletComponent& other) = delete;
	BouncingBulletComponent& operator=(BouncingBulletComponent&& other) noexcept = delete;


	void Initialize() override {}
	void FixedUpdate(const float) override {}
	void Update(const float) override;
	void LateUpdate(const float) override {}
	void Render() const override {}

private:

	//HitboxComponent* nm_pHitbox = nullptr; // hitbox
	HurtBoxComponent* nm_pHurtBox = nullptr;
	CollisionComponent* nm_pCollisionBox = nullptr;

	glm::vec2 m_Vector;
	float m_speed = 2;
	int m_BounceLeft = 5;
};

