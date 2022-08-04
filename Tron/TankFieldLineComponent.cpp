#include "TankFieldLineComponent.h"

#include "Renderer.h"
#include "TankFieldGridComponent.h"

char TankFieldLineComponent::GetPossibleDirFromRect(const glm::vec2& posOfActor, glm::vec2& CenterOfLine) const
{

	int returnVal = 0;
	//if ((m_Rectangle.x < pos.x && m_Rectangle.x + m_Rectangle.w > pos.x) &&
	//	(m_Rectangle.y < pos.y && m_Rectangle.y + m_Rectangle.h > pos.y))
	//{
	//	return m_Directions;
	//}
	if (m_ZoneOfOverlap.y < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y)
	{
		if ((m_ZoneOfOverlap.x < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w - m_offset > posOfActor.x)
			&& (right & m_Directions))
			returnVal += right;
		if ((m_ZoneOfOverlap.x + m_offset < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w > posOfActor.x)
			&& (right & m_Directions))
			returnVal += left;
	}
	if (m_ZoneOfOverlap.x < posOfActor.x && m_ZoneOfOverlap.x + m_ZoneOfOverlap.w > posOfActor.x)
	{
		if ((m_ZoneOfOverlap.y + m_offset < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h > posOfActor.y)
			&& (up & m_Directions))
			returnVal += up;
		if ((m_ZoneOfOverlap.y  < posOfActor.y && m_ZoneOfOverlap.y + m_ZoneOfOverlap.h - m_offset > posOfActor.y)
			&& (down & m_Directions))
			returnVal += down;

	}

	CenterOfLine = m_CenterPosition;
	return static_cast<char>(returnVal);
	//return m_Directions;
}

void TankFieldLineComponent::Render() const
{
	//if (m_DebugRender)
	{
		SDL_Color col;
		if (m_Directions == left + right)
			col.r = 255;
		if (m_Directions == up + down)
			col.g = 255;

		dae::Renderer::GetInstance().RenderRect(m_ZoneOfOverlap, col);
	}
}
