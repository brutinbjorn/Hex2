 #include "TankFieldControlComponent.h"

#include <nlohmann/json.hpp>
#include "JsonManager.h"
#include "TankFieldGridComponent.h"

 void TankFieldControlComponent::CreateLinesAndWallsFromJsonFile(const std::string& file, glm::ivec2 offset)
{
	nlohmann::json j = JsonManager::GetInstance().LoadJsonDoc(file);
	nlohmann::json jAr = j["PathsHorizontal"];
	//CreatePaths(jAr);
	for (nlohmann::json::iterator it = jAr.begin(); it != jAr.end(); ++it)
	{
		//nlohmann::json jPoints = it.value()["Bazier"];
		//std::vector<glm::vec2> NewBazierPoints;
		//for (nlohmann::json::iterator it2 = jPoints.begin(); it2 != jPoints.end(); ++it2)
		if (it->is_object())
		{
			nlohmann::json ob = it.value();

			glm::ivec2 position;
			position.x = ob["x"].get<int>() + offset.x;
			position.y = ob["y"].get<int>() + offset.y;

			glm::ivec2 size;
			size.x = ob["w"].get<int>();
			size.y = ob["h"].get<int>();

			SDL_Rect Path = SDL_Rect{ position.x - m_PathExtraSpace,position.y - m_PathExtraSpace,size.x + m_PathExtraSpace * 2, size.y + m_PathExtraSpace * 2 };

			auto Line = new TankFieldLineComponent(Path, DIRECTION_LEFT + DIRECTION_RIGHT, 2);
			GetParent()->AddComponent(Line);
			Line->SetSquare(Path);
			nm_pLines.push_back(Line);
		}
	}

	jAr = j["PathsVertical"];
	for (nlohmann::json::iterator it = jAr.begin(); it != jAr.end(); ++it)
	{
		if (it->is_object())
		{
			nlohmann::json ob = it.value();

			glm::ivec2 position;
			position.x = ob["x"].get<int>() + offset.x;
			position.y = ob["y"].get<int>() + offset.y;

			glm::ivec2 size;
			size.x = ob["w"].get<int>();
			size.y = ob["h"].get<int>();

			SDL_Rect Path = SDL_Rect{ position.x - m_PathExtraSpace,position.y - m_PathExtraSpace,size.x + m_PathExtraSpace * 2, size.y + m_PathExtraSpace * 2 };

			auto Line = new TankFieldLineComponent(Path, DIRECTION_UP + DIRECTION_DOWN, 2);
			GetParent()->AddComponent(Line);
			Line->SetSquare(Path);
			nm_pLines.push_back(Line);
		}
	}

	nlohmann::json jOb = j["PlayerStartPos"];

	glm::ivec2 PlayerStartPos;
	if(jOb.is_object())
	{
		PlayerStartPos.x = jOb["x"].get<int>() + offset.x;
		PlayerStartPos.y = jOb["y"].get<int>() + offset.y;

	}
	m_playerStartPos = PlayerStartPos;

	jOb = j["EnemyStartPos"];
	glm::ivec2 EnemyStartPos;
	if(jOb.is_object())
	{
		EnemyStartPos.x = jOb["x"].get<int>() + offset.x;
		EnemyStartPos.y = jOb["y"].get<int>() + offset.y;
	}
	m_EnemyStartPos = EnemyStartPos;


}
