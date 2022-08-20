#pragma once
#include <BaseComponent.h>
#include "SDL.h"
#include "ENUMS.h"
#include "GameObject.h"
//#include "SquareComponent.h"
#include "ActorComponent.h"
#include "CollisionManager.h"
#include "Transform.h"

class SquareComponent;

class CollisionComponent :
    public BaseComponent
{
public:
	CollisionComponent(SquareComponent* CollisionSquare, bool IsStatic = true, ActorComponent* ac = nullptr)
		: nm_pSquare(CollisionSquare), m_static(IsStatic), nm_pActor(ac)
	{
		dae::CollisionManager::GetInstance().AddCollisionComp(this);
	};

	~CollisionComponent() override
	{
		dae::CollisionManager::GetInstance().RemoveCollisionComp(this);
	}

	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) noexcept = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

	void Initialize() override {}
	void FixedUpdate(const float ) override {}
	void Update(const float) override;
	void LateUpdate(const float ) override {}
	void Render() const override {}

	SquareComponent* GetSquareUsedForColission() const { return nm_pSquare; };
	void SetSquareForColission(SquareComponent* square) { nm_pSquare = square; };

	bool IsColliding() const { return m_IsTouching; };
	char GetCollisionSides() const { return m_direction; };

private:
	static char IsRectsOverLapping(SDL_Rect a, SDL_Rect b);

	bool m_IsTouching = false;
	char m_direction = 0;
	bool m_static = true;
	dae::Transform m_formerPosition;
	SquareComponent* nm_pSquare;
	ActorComponent* nm_pActor;
};

