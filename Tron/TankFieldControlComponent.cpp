 #include "TankFieldControlComponent.h"

#include <nlohmann/json.hpp>

#include "CollisionComponent.h"
#include "ENUMS.h"
#include "JsonManager.h"
#include "SquareComponent.h"


 char TankFieldControlComponent::GetPossibleDirectionToMove(const glm::ivec3& position, glm::ivec2& CenterPosOfLine) const
{
	char possibleDirections = 0;
	//glm::ivec2 playerPos = {position.x,position.y};
	for(int i = 0; i < nm_pLines.size();i++)
	{
		auto dir = nm_pLines[i]->GetPossibleDirFromRect(position, CenterPosOfLine);

		if (dir != 0)
			possibleDirections += dir;
	}
	return possibleDirections;
}


void TankFieldControlComponent::CreateLinesAndWallsFromJsonFile(const std::string& file, glm::ivec2 offset)
{
	nlohmann::json j = JsonManager::GetInstance().LoadJsonDoc(file);
	nlohmann::json jAr = j["PathsHorizontal"];
	//CreatePaths(jAr);
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

	jAr = j["Wall"];
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

			SDL_Rect Path = SDL_Rect{ position.x ,position.y,size.x, size.y };

			//auto Line = new TankFieldLineComponent(Path, 2);
			auto Square = new SquareComponent();
			Square->SetSquare(Path);
			GetParent()->AddComponent(Square);
			auto wall = new CollisionComponent(Square);
			GetParent()->AddComponent(wall);

		}
	}



	nlohmann::json jOb = j["PlayerStartPos"];

	glm::ivec2 PlayerStartPos;
	if(jOb.is_object())
	{
		PlayerStartPos.x = jOb["x"].get<int>() + offset.x + static_cast<int>(GetParent()->GetTransform()->GetPosition().x);
		PlayerStartPos.y = jOb["y"].get<int>() + offset.y + static_cast<int>(GetParent()->GetTransform()->GetPosition().y);

	}

	m_playerStartPos = PlayerStartPos;

	jOb = j["EnemyStartPos"];
	glm::ivec2 EnemyStartPos;

	if(jOb.is_object())
	{
		EnemyStartPos.x = jOb["x"].get<int>() + offset.x + static_cast<int>(GetParent()->GetTransform()->GetPosition().x);
		EnemyStartPos.y = jOb["y"].get<int>() + offset.y + static_cast<int>(GetParent()->GetTransform()->GetPosition().y);
	}
	m_EnemyStartPos = EnemyStartPos;


}

 void TankFieldControlComponent::CreateLinesWallsALt(const std::string& file, glm::ivec2 )
 {
	 // Generate Grid
	 nlohmann::json j = JsonManager::GetInstance().LoadJsonDoc(file);
	 nlohmann::json jAr = j["Walls"];
	if(jAr.is_array())
	{
		for (nlohmann::json::iterator Array = jAr.begin(); Array != jAr.end(); ++Array)
		{
			if(Array->is_array())
			{
				for(nlohmann::json::iterator Line = Array->begin(); Line !=  Array->end(); ++Line )
				{
					
				}
			}

			
		}
	}



 }

