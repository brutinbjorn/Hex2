#pragma once
#include <SDL.h>

#include "BaseComponent.h"

class WallComponent : public BaseComponent
{
public:
	WallComponent(SDL_Rect CollisionOffset) : m_Collision(CollisionOffset), m_Color(SDL_Color{255,255,255,255}) {};
	~WallComponent() = default;

	WallComponent(const WallComponent& other) = delete;
	WallComponent(WallComponent&& other) noexcept = delete;
	WallComponent& operator=(const WallComponent& other) = delete;
	WallComponent& operator=(WallComponent&& other) noexcept = delete;

	void SetWallOffset(const SDL_Rect& WallOffset) { m_Collision = WallOffset; };
	void SetColor(const SDL_Color& WallColor) { m_Color = WallColor; };

	void Render() const override;
	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float ) override {};
	void LateUpdate(const float ) override {};
	void GuiRender() const override {};
private:
	SDL_Rect m_Collision;
	SDL_Color m_Color;

};

