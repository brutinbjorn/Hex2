#include "TankFieldLineComponent.h"

#include "ENUMS.h"
#include "Renderer.h"


TankFieldLineComponent::TankFieldLineComponent(const SDL_Rect& MovementZone, char Directions, int OneDirOffset)
	:m_ZoneOfOverlap(MovementZone),m_offset(OneDirOffset),m_Directions(Directions)
{
	SetSquare(MovementZone);
}

char TankFieldLineComponent::GetPossibleDirFromRect(const glm::ivec2& posOfActor, glm::ivec2& CenterOfLine) const
{

	char returnVal = 0;
	if (m_ZoneOfOverlap.y < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y)
	{
		if ((m_ZoneOfOverlap.x < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w - m_offset > posOfActor.x)
			&& (DIRECTION_RIGHT & m_Directions))
			returnVal += DIRECTION_RIGHT;

		if ((m_ZoneOfOverlap.x + m_offset < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w > posOfActor.x)
			&& (DIRECTION_LEFT & m_Directions))
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
}

bool TankFieldLineComponent::IsMovePossible(char direction, const glm::ivec2& posOfActor, glm::ivec2& centerOfLine)
{

	bool canMove = false;
	if ((m_ZoneOfOverlap.y <= posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h >= posOfActor.y)
		&& (m_ZoneOfOverlap.x <= posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w >= posOfActor.x))
	{
		if (m_Directions & direction)
		switch (direction)
		{
		case DIRECTION_RIGHT:
			if ((m_ZoneOfOverlap.x < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w > posOfActor.x + 2))
				canMove = true;
			break;
		case DIRECTION_LEFT:
			if ((m_ZoneOfOverlap.x < posOfActor.x -2 && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w  > posOfActor.x  ))
				canMove = true;
			break;
		case DIRECTION_UP:
			if ((m_ZoneOfOverlap.y < posOfActor.y - 2 && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y ))
				canMove = true;
			break;
		case DIRECTION_DOWN:
			if ((m_ZoneOfOverlap.y < posOfActor.y  && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y + 2))
				canMove = true;
			break;
		default:
			return false;

		}
	}

	//if ((m_ZoneOfOverlap.x <= posOfActor.x  && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w >= posOfActor.x - 2)
	//	&& (DIRECTION_RIGHT & direction)) 
	//	canMove = true;
	//else if ((m_ZoneOfOverlap.x  <= posOfActor.x- 2 && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w - 2 >= posOfActor.x)
	//	&& (DIRECTION_LEFT & direction)) 
	//	canMove = true;
	//else if ((m_ZoneOfOverlap.y <= posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h >= posOfActor.y +2)
	//	&& (DIRECTION_UP & direction))
	//	canMove = true;
	//else if ((m_ZoneOfOverlap.y <= posOfActor.y +2 && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h -2 >= posOfActor.y)
	//	&& (DIRECTION_DOWN & direction))
	//	canMove = true;

	if(canMove)
	{
		centerOfLine = m_CenterPosition;
		return true;
	}

	
	return false;
}


void TankFieldLineComponent::Render() const
{
	//if (m_DebugRender)
	{
		SDL_Color col;
		if (m_Directions == DIRECTION_LEFT + DIRECTION_RIGHT)
			col.r = 255;
		if (m_Directions == DIRECTION_UP + DIRECTION_DOWN)
			col.b = 255;

		dae::Renderer::GetInstance().RenderRect(m_ZoneOfOverlap, col);
	}
}
