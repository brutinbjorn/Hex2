#pragma once
#include <BaseComponent.h>
#include "SDL.h"
#include "ENUMS.h"
#include "GameObject.h"
//#include "SquareComponent.h"
#include "Transform.h"

class SquareComponent;

class CollisionComponent :
    public BaseComponent
{
public:
	CollisionComponent(SquareComponent* CollisionSquare)
		: nm_pSquare(CollisionSquare) {};

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

	SquareComponent* GetSquareUsedForColission() const { return nm_pSquare; };
	void SetSquareForColission(SquareComponent* square) { nm_pSquare = square; };

private:
	static char IsRectsOverLapping(SDL_Rect a, SDL_Rect b);

	bool m_IsTouching = false;
	char m_direction = 0;
	dae::Transform m_formerPosition;
	SquareComponent* nm_pSquare;

};

