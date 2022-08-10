#include "MoveZoneComponent.h"

#include "Renderer.h"

MoveZoneComponent::MoveZoneComponent(SDL_Rect rectangle, char PossibleDirections):
	m_Rectangle(rectangle),
	m_Directions(PossibleDirections)
{

}

char MoveZoneComponent::GetPossibleDirFromRect(const glm::vec2& pos) const
{

	int returnVal = 0;
	//if ((m_Rectangle.x < pos.x && m_Rectangle.x + m_Rectangle.w > pos.x) &&
	//	(m_Rectangle.y < pos.y && m_Rectangle.y + m_Rectangle.h > pos.y))
	//{
	//	return m_Directions;
	//}
	if(m_Rectangle.y < pos.y && m_Rectangle.y + m_Rectangle.h > pos.y)
	{
		if ((m_Rectangle.x < pos.x && m_Rectangle.x + m_Rectangle.w - 2 > pos.x)
			&& (DIRECTION_RIGHT & m_Directions))
			returnVal += DIRECTION_RIGHT;
		if ((m_Rectangle.x + 2 < pos.x && m_Rectangle.x + m_Rectangle.w > pos.x)
			&& (DIRECTION_RIGHT & m_Directions))
			returnVal += DIRECTION_LEFT;
	}
	if (m_Rectangle.x < pos.x && m_Rectangle.x + m_Rectangle.w > pos.x)
	{
		if ((m_Rectangle.y + 2 < pos.y && m_Rectangle.y + m_Rectangle.h > pos.y)
			&& (DIRECTION_UP & m_Directions))
			returnVal += DIRECTION_UP;
		if ((m_Rectangle.y  < pos.y && m_Rectangle.y + m_Rectangle.h - 2 > pos.y)
			&& (DIRECTION_DOWN & m_Directions))
			returnVal += DIRECTION_DOWN;

	}
	
	return static_cast<char>(returnVal);

}

void MoveZoneComponent::Render() const
{
	if(m_DebugRender)
	{
		SDL_Color col;
		if (m_Directions == DIRECTION_LEFT + DIRECTION_RIGHT)
			col.r = 255;
		if (m_Directions == DIRECTION_UP + DIRECTION_DOWN)
			col.g = 255;

		dae::Renderer::GetInstance().RenderRect(m_Rectangle,col);
	}

}
