#pragma once
#include "BaseComponent.h"
#include "HitboxComponent.h"
#include "Transform.h"

class HurtBoxComponent :
    public BaseComponent
{
public:
	HurtBoxComponent(SquareComponent* Sqr, int CollisionID = -1);


	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float deltatime) override;
	void LateUpdate(const float ) override {};
	void Render() const override ;
	
	void SetSquareComp(SquareComponent* newRect) { nm_pRect = newRect; };


	bool IsOverlappingHitbox(HitboxComponent* GetHitBox);
	bool IsAHit() const { return m_hasHit; }

private:
	SquareComponent* nm_pRect;
	glm::ivec2 m_offset;
	glm::ivec2 m_size;
	dae::Transform m_transform;

	bool m_debugRender;

	int m_ColisionID = -1;
	bool m_NeedsUpdate = false;
	bool m_hasHit = false;
};

