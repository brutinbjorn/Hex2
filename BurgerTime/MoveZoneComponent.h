#pragma once
#include <BaseComponent.h>
#include <SDL_rect.h>
#include <glm/detail/type_vec.hpp>



enum Directions
{
	right = 0b0001,
	left =	0b0010,
	up =	0b0100,
	down =	0b1000
};

class MoveZoneComponent :
    public BaseComponent
{
public:
	MoveZoneComponent(SDL_Rect rectangle, char PossibleDirections); 
	~MoveZoneComponent() = default;
	MoveZoneComponent(const MoveZoneComponent& other) = delete;
	MoveZoneComponent(MoveZoneComponent&& other) noexcept = delete;
	MoveZoneComponent& operator=(const MoveZoneComponent& other) = delete;
	MoveZoneComponent& operator=(MoveZoneComponent&& other) noexcept = delete;

	char GetPossibleDirFromRect(const glm::vec2& pos) const;

	void Initialize() override {};
	void FixedUpdate(const float) override {}; 
	void Update(const float ) override {};
	void LateUpdate(const float ) override {};
	void Render() const override ;
	void GuiRender() const override{};

	void SetDebugRender(bool val = false) { m_DebugRender = val; };
private:
	SDL_Rect m_Rectangle;
	char m_Directions = 0b0000;

	bool m_DebugRender = false;

};

