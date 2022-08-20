#include "MoveGridComponent.h"

#include <JsonManager.h>

//RECONS this line ?
#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#pragma warning(disable:26800)
#include <nlohmann/json.hpp>
#pragma warning(pop)

#include "GameObject.h"

MoveGridComponent::MoveGridComponent(const std::string& fileName, glm::ivec2 offset)
	: m_fileName(fileName),m_offset(offset)
{

	//nlohmann::json jArVertical = j["Vertical"];

}

char MoveGridComponent::GetDirections(glm::vec2 pos)
{
	int returnVal = 0;
	for(size_t i = 0; i < m_MoveZones.size(); i++)
	{
		int foundVal = m_MoveZones[i]->GetPossibleDirFromRect(pos);
		if (foundVal != 0)
			returnVal += foundVal;
	}
	return static_cast<char>(returnVal);
}

void MoveGridComponent::Initialize()
{
	nlohmann::json j = JsonManager::GetInstance().LoadJsonDoc(m_fileName);

	nlohmann::json jArHorizontal = j["Horizontal"];
	for (nlohmann::json::iterator it = jArHorizontal.begin(); it != jArHorizontal.end(); ++it)
	{
		if (it->is_object())
		{
			nlohmann::json ob = it.value();

			glm::ivec2 Size;
			Size.x = ob["width"].get<int>() +10;
			Size.y = ob["height"].get<int>() * 2;
			glm::ivec2 Position;
			Position.x = ob["xPos"].get<int>() + m_offset.x - 5;// get_to(BazierPos.y);
			Position.y = ob["yPos"].get<int>() + m_offset.y - 5;// get_to(BazierPos.y);

			SDL_Rect newRect;
			newRect.x = Position.x;
			newRect.y = Position.y;
			newRect.w = Size.x;
			newRect.h = Size.y;

			m_MovementRectangles.push_back(newRect);
			auto papa = GetParent();
			auto newZone = new MoveZoneComponent(newRect, DIRECTION_LEFT + DIRECTION_RIGHT);
			newZone->SetDebugRender(true);
			papa->AddComponent(newZone);
			AddZone(newZone);

		}
	}
	nlohmann::json jArVertical = j["Vertical"];
	for (nlohmann::json::iterator it = jArVertical.begin(); it != jArVertical.end(); ++it)
	{
		if (it->is_object())
		{
			nlohmann::json ob = it.value();

			glm::ivec2 Size;
			Size.x = ob["width"].get<int>() *2 ;
			Size.y = ob["height"].get<int>()+10;
			glm::ivec2 Position;
			Position.x = ob["xPos"].get<int>() + m_offset.x - 5;// get_to(BazierPos.y);
			Position.y = ob["yPos"].get<int>() + m_offset.y - 5;// get_to(BazierPos.y);

			SDL_Rect newRect;
			newRect.x = Position.x;
			newRect.y = Position.y;
			newRect.w = Size.x;
			newRect.h = Size.y;

			m_MovementRectangles.push_back(newRect);
			auto papa = GetParent();
			auto newZone = new MoveZoneComponent(newRect, DIRECTION_UP + DIRECTION_DOWN);
			newZone->SetDebugRender(true);
			papa->AddComponent(newZone);
			AddZone(newZone);

		}
	}

}
