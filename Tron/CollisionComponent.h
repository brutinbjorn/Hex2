#pragma once
#include <BaseComponent.h>
#include "SDL.h"
#include "ENUMS.h"
#include "GameObject.h"
#include "Transform.h"

class CollisionComponent :
    public BaseComponent
{
public:
	CollisionComponent() = default;
	~CollisionComponent() override = default;
	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) noexcept = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

	void Initialize() override {}
	void FixedUpdate(const float ) override {}
	void Update(const float) override;
	void LateUpdate(const float ) override {}
	void Render() const override {}

	SDL_Rect& GetRect() { return m_rect; };
	void SetRect(SDL_Rect rec)
	{
		m_rect = rec;

		auto pos =	GetParent()->GetTransform()->GetPosition();
		m_rect.x += static_cast<int>(pos.x);
		m_rect.y += static_cast<int>(pos.y);

	};


private:
	static char IsRectsOverLapping(SDL_Rect a, SDL_Rect b);

	SDL_Rect m_rect = {};
	bool m_IsTouching = false;
	char m_direction = 0;
	dae::Transform m_formerPosition;

};

