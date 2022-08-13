#pragma once
#include <BaseComponent.h>
#include "SDL.h"
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
	void Update(const float ) override {}
	void LateUpdate(const float lt) override {}
	void Render() const override {}

	SDL_Rect& GetRect() { return m_rect; }


private:
	SDL_Rect m_rect = {};


};

