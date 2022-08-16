#pragma once
#include "BaseComponent.h"
#include "HitboxComponent.h"
#include "Transform.h"

class HurtBoxComponent :
    public BaseComponent
{
public:
	HurtBoxComponent(SquareComponent* Sqr, int CollisionID = -1);

	void Render() const override;
	void Update(const float deltatime) override;
	void SetSquareComp(SquareComponent* newRect) { nm_pRect = newRect; };


	void SetOffset(int x, int y);
	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 pos);
	void SetSize(glm::ivec2 size);
	bool IsOverlappingHitbox(HitboxComponent* hitbox);
	bool IsAHit() const { return m_hasHit; }

private:
	SquareComponent* nm_pRect;
	glm::ivec2 m_offset;
	glm::ivec2 m_size;
	dae::Transform m_transform;

	int m_ColisionID = -1;
	bool m_NeedsUpdate = false;
	bool m_hasHit = false;
};

