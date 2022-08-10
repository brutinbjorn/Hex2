#include "TankFieldLineComponent.h"

#include "Renderer.h"
#include "TankFieldGridComponent.h"

TankFieldLineComponent::TankFieldLineComponent(const SDL_Rect& MovementZone, char Directions, int OneDirOffset)
	:m_ZoneOfOverlap(MovementZone),m_offset(OneDirOffset),m_Directions(Directions)
{
	SetSquare(MovementZone);
}

char TankFieldLineComponent::GetPossibleDirFromRect(const glm::vec2& posOfActor, glm::vec2& CenterOfLine) const
{

	char returnVal = 0;
	if (m_ZoneOfOverlap.y < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y)
	{
		if ((m_ZoneOfOverlap.x < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w - m_offset > posOfActor.x)
			&& (DIRECTION_RIGHT & m_Directions))
			returnVal += DIRECTION_RIGHT;
		if ((m_ZoneOfOverlap.x + m_offset < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w > posOfActor.x)
			&& (DIRECTION_RIGHT & m_Directions))
			returnVal += DIRECTION_LEFT;
	}
	if (m_ZoneOfOverlap.x < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w > posOfActor.x)
	{
		if ((m_ZoneOfOverlap.y + m_offset < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y)
			&& (DIRECTION_UP & m_Directions))
			returnVal += DIRECTION_UP;
		if ((m_ZoneOfOverlap.y  < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h - m_offset > posOfActor.y)
			&& (DIRECTION_DOWN & m_Directions))
			returnVal += DIRECTION_DOWN;

	}

	CenterOfLine = m_CenterPosition;
	return returnVal;
	//return m_Directions;
}

void TankFieldLineComponent::Render() const
{
	//if (m_DebugRender)
	{
		SDL_Color col;
		if (m_Directions == DIRECTION_LEFT + DIRECTION_RIGHT)
			col.r = 255;
		if (m_Directions == DIRECTION_UP + DIRECTION_DOWN)
			col.g = 255;

		dae::Renderer::GetInstance().RenderRect(m_ZoneOfOverlap, col);
	}
}
