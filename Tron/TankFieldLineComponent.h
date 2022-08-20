#pragma once
//#include <SDL_rect.h>
#include "MiniginPCH.h"
#include "ComponentList.h"
#include "GameObject.h"


class TankFieldLineComponent : public BaseComponent
{
public:
	TankFieldLineComponent() = default;
	TankFieldLineComponent(const SDL_Rect& MovementZone, char Directions, int OneDirOffset);

	~TankFieldLineComponent() override = default;
	TankFieldLineComponent(const TankFieldLineComponent& other) = delete;
	TankFieldLineComponent(TankFieldLineComponent&& other) noexcept = delete;
	TankFieldLineComponent& operator=(const TankFieldLineComponent& other) = delete;
	TankFieldLineComponent& operator=(TankFieldLineComponent&& other) noexcept = delete;

	// returns the directions the actor can go to.
	// INPUT position of actor;
	// INOUT centerOfline, x or y pos depening if the line is horizontal/vertical, to Center the Actor on the line;
	char GetPossibleDirFromRect(const glm::ivec2& posOfActor, glm::ivec2& CenterOfLine) const;

	//Request if its possbile to move in direction, returns true if move is allowed & sets the centerofline
	bool IsMovePossible(char direction, const glm::ivec2& posOfActor, glm::ivec2& centerOfLine);
	

	//adds left/right/up/down "only" extra border.
	void SetZoneExtraBorder(int offset) { m_offset = offset; };

	//void SetCenterOfLine

	void SetSquare(const SDL_Rect& newZone)
	{

		auto newRect = newZone;
		if(GetParent())
		{
			newRect.x = newZone.x + static_cast<int>(GetParent()->GetTransform()->GetPosition().x);
			newRect.y = newZone.y + static_cast<int>(GetParent()->GetTransform()->GetPosition().y);

			m_CenterPosition.x = newRect.x + newRect.w / 2;
			m_CenterPosition.y = newRect.y + newRect.h / 2;
		}
		m_ZoneOfOverlap = newRect;
	};

	//void CenterPosition

	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float ) override {};
	void LateUpdate(const float ) override {};
	void GuiRender() const override {};
	void Render() const override ;
private:
	SDL_Rect m_ZoneOfOverlap = {5,5,5,5};
	glm::ivec2 m_CenterPosition;
	int m_offset = 2;

	char m_Directions = 0b0000;

	bool m_IsVerticleMovement = false;
	bool m_IsHorizontalMovement = false;

};
 
