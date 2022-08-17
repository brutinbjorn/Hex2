#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include <SDL.h>
class SquareComponent;

class HitboxComponent :
    public BaseComponent
{
public:
	// creates the hitboxs and centers it.
	HitboxComponent(SquareComponent* sqr ,int CollisionID = -1);


	~HitboxComponent() override = default;
	HitboxComponent(const HitboxComponent& other) = delete;
	HitboxComponent(HitboxComponent&& other) noexcept = delete;
	HitboxComponent& operator=(const HitboxComponent& other) = delete;
	HitboxComponent& operator=(HitboxComponent&& other) noexcept = delete;

	void Render() const override;
	void Initialize() override {};
	void FixedUpdate(const float) override {};
	void LateUpdate(const float) override {};
	void GuiRender() const override {};
	void Update(const float) override ;

	//void SetRect(const SDL_Rect& newRect) { m_rect = newRect; };

	//void SetOffset(int x, int y) { m_offset.x = x; m_offset.y = y; m_NeedsUpdate = true; };

	//void SetSize(glm::ivec2 size) { m_size = size;  m_NeedsUpdate = true; };

	bool IsHit() { return m_gotHit; };
	void ResetHit(bool HitState = false) { m_gotHit = HitState; };

	//const SDL_Rect& GetRectangle() const { return m_rect; };

	//void Set
	dae::GameObject* GetParent();

	bool IsPointInThisHitbox(glm::ivec2 point) const;
	bool IsSquareInThisHitBox(SDL_Rect rectangle, int CollisionID);
	bool IsSquareInThisHitBox(SquareComponent* sqr, int CollisionID);

private:
	SDL_Rect m_rect;
	SquareComponent* nm_pSquareComp;
	glm::ivec2 m_offset;
	glm::ivec2 m_size;
	

	int m_CollisionID = -1;

	bool m_NeedsUpdate = true;
	bool m_gotHit = false;
};

