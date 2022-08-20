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
	for(size_t i = 0; i < nm_pLines.size();i++)
	{
		auto dir = nm_pLines[i]->GetPossibleDirFromRect(position, CenterPosOfLine);

		if (dir != 0)
			possibleDirections += dir;
	}
	return possibleDirections;
}

 bool TankFieldControlComponent::AskIfPlayerCanMoveInRequestedDirection(char direction, const glm::ivec2 playerPos,
	 glm::ivec2& centerPosOfLine) const
 {
	 for (size_t i = 0; i < nm_pLines.size(); i++)
	 {

	 	if(nm_pLines[i]->IsMovePossible(direction, playerPos, centerPosOfLine))
		return true;
		
	 }
	return false;

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
			nm_pLines.push_back(Line);
			Line->SetSquare(Path);
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

void TankFieldControlComponent::CreateLinesWallsAlt(const std::string& file, glm::ivec2 sizeOfPlayer)
{
	// Generate Grid
	nlohmann::json j = JsonManager::GetInstance().LoadJsonDoc(file);
	nlohmann::json jAr = j["Tiles"];


	/// <summary>
	/// Read the json file
	int maxX = 0, maxY = 0;
	if(jAr.is_array())
	{
		int y = 0;
		for (nlohmann::json::iterator Array = jAr.begin(); Array != jAr.end(); ++Array)
		{
			if(Array->is_array())
			{
				int x = 0;
				for(nlohmann::json::iterator Line = Array->begin(); Line !=  Array->end(); ++Line )
				{
					auto val = Line.value().get<int>();

					CellOfTheGrid cell = CellOfTheGrid(x, y, val);
					m_Cells.push_back(cell);
					x++;
					if (maxX < x) maxX = x;
				}
			}
			y++;
			if (maxY < y) maxY = y;
		}
	}
	/// </summary>



	//
	glm::ivec2 SizeOFWall = sizeOfPlayer / 4;
	glm::ivec2 SizeOfCell = sizeOfPlayer ;
	//int startX = 

	for (size_t Index = 0; Index < m_Cells.size(); ++Index)
	{
		auto cell = m_Cells[Index];

		if(cell.Type == 4)
		{
			cell.Type = 0;
			m_EnemyStartPos = { cell.x * SizeOfCell.x, cell.y * SizeOfCell.y };
			
		}
		if(cell.Type == 2)
		{
			m_playerStartPos = { cell.x * SizeOfCell.x, cell.y * SizeOfCell.y };
			cell.Type = 0;
		}

		switch (cell.Type)
		{
		case 0: //PATH
			if (m_Cells.size() > (Index + 1))
			{
				if ((m_Cells[Index + 1].Type & 0b1) == false)
				{
					SDL_Rect sqr = {cell.x * SizeOfCell.x - m_PathExtraSpace,cell.y * SizeOfCell.y  - m_PathExtraSpace,
						SizeOfCell.x  + m_PathExtraSpace * 2,m_PathExtraSpace * 2};
					auto path = new TankFieldLineComponent(sqr, DIRECTION_RIGHT + DIRECTION_LEFT, 2);
					GetParent()->AddComponent(path);
					path->SetSquare(sqr);
					nm_pLines.push_back(path);

				}

			}
			if(m_Cells.size() > Index + maxX)
			{
				if ((m_Cells[Index + maxX].Type & 0b1) == false)
				{
					SDL_Rect sqr = { cell.x * SizeOfCell.x  - m_PathExtraSpace ,cell.y * SizeOfCell.y - m_PathExtraSpace,
						m_PathExtraSpace * 2,SizeOfCell.y  + m_PathExtraSpace * 2 };
					auto path = new TankFieldLineComponent(sqr, DIRECTION_UP + DIRECTION_DOWN, 2);
					//path.
					GetParent()->AddComponent(path);
					path->SetSquare(sqr);
					nm_pLines.push_back(path);
				}
			}

			break;
		case 1: // WAALLLS
			{
				bool HasAdded = false;
				if (m_Cells.size() > Index + 1)
				{
					if (m_Cells[Index + 1].Type == 1 && m_Cells[Index + 1].y == cell.y)
					{
						SDL_Rect sqr = { cell.x * SizeOfCell.x - SizeOFWall.x *2 , cell.y * SizeOfCell.y - SizeOFWall.x *2,
							SizeOfCell.x ,SizeOfCell.y };

						auto sqrComp = new SquareComponent();
						GetParent()->AddComponent(sqrComp);
						sqrComp->SetSquare(sqr);
						sqrComp->SetRenderFull(true, { 0,255,0,255 });

						auto collComp = new CollisionComponent(sqrComp);
						GetParent()->AddComponent(collComp);
						HasAdded = true;
					}
				}
				if (m_Cells.size() > Index + maxX)
				{
					if (m_Cells[Index + maxX].Type == 1)
					{
						SDL_Rect sqr = { cell.x * SizeOfCell.x - SizeOFWall.x * 2  , cell.y * SizeOfCell.y - SizeOFWall.x *2 ,
							SizeOfCell.x,SizeOfCell.y };

						auto sqrComp = new SquareComponent();
						GetParent()->AddComponent(sqrComp);
						sqrComp->SetSquare(sqr);
						sqrComp->SetRenderFull(true, { 0,255,0,255 });

						auto collComp = new CollisionComponent(sqrComp);
						GetParent()->AddComponent(collComp);
						HasAdded = true;
					}
				}
				if (!HasAdded)
				{
					SDL_Rect sqr = { cell.x * SizeOfCell.x - SizeOFWall.x * 2 , cell.y * SizeOfCell.y - SizeOFWall.y *2 ,
						SizeOfCell.x,SizeOfCell.y };

					auto sqrComp = new SquareComponent();
					GetParent()->AddComponent(sqrComp);
					sqrComp->SetSquare(sqr);
					sqrComp->SetRenderFull(true, { 0,255,0,255 });

					auto collComp = new CollisionComponent(sqrComp);
					GetParent()->AddComponent(collComp);
					HasAdded = true;
				}
			}
			break;
		default: 
			break;
		}

		cell.x;
		cell.y;

	}
}





 

