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
	BouncingBulletComponent(float rotation,CollisionComponent* collision, HurtBoxComponent* hurtBox,ActorComponent* ac,float speed)
	:nm_pCollisionBox(collision),nm_pHurtBox(hurtBox),nm_pActor(ac),m_Rotation(rotation)
	{
		//m_Rotation = rotation;
		if (nm_pActor)
		{
			glm::vec2 vec;
			vec.x = std::cos(m_Rotation);
			vec.y = std::sin(m_Rotation);
			m_ContinuesVec = vec;
			nm_pActor->SetVelocity(vec);
			nm_pActor->SetSpeed(speed);

		}
		//m_Vector.x = std::cos(rotation);
		//m_Vector.y = std::sin(rotation);
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
	ActorComponent* nm_pActor = nullptr;
	HurtBoxComponent* nm_pHurtBox = nullptr;
	CollisionComponent* nm_pCollisionBox = nullptr;

	//glm::vec2 m_Vector;
	glm::fvec2 m_ContinuesVec = {};

	float m_Rotation = 0.f;
	float m_speed = 2;
	int m_BounceLeft = 4;
};

