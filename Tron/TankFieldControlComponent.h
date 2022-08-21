#pragma once
#include <BaseComponent.h>
#include <vector>


#include "TankFieldLineComponent.h"



struct CellOfTheGrid
{
	CellOfTheGrid(int x,int y,int type):x(x),y(y),Type(type) {}
	int x, y;
	int Type;
};



class TankFieldControlComponent :
    public BaseComponent
{
public:
	TankFieldControlComponent() = default;
	~TankFieldControlComponent() override = default;
	TankFieldControlComponent(const TankFieldControlComponent& other) = delete;
	TankFieldControlComponent(TankFieldControlComponent&& other) noexcept = delete;
	TankFieldControlComponent& operator=(const TankFieldControlComponent& other) = delete;
	TankFieldControlComponent& operator=(TankFieldControlComponent&& other) noexcept = delete;

	char GetPossibleDirectionToMove(const glm::ivec3& position, glm::ivec2& CenterPosOfLine) const;
	bool AskIfPlayerCanMoveInRequestedDirection(char direction, const glm::ivec2 playerPos, glm::ivec2& CenterPosOfLine) const;

	void CreateLinesAndWallsFromJsonFile(const std::string& file,glm::ivec2 offset = {});
	void CreateLinesWallsAlt(const std::string& file, glm::ivec2 offset = {});

	glm::ivec2 GetPlayerStartingPosition() const { return m_playerStartPos; };
	glm::ivec2 GetEnemyStartPosition() const { return m_EnemyStartPos; };

	void Initialize() override {};
	void FixedUpdate(const float ) override{};
	void Update(const float ) override{};
	void LateUpdate(const float ) override{};
	void Render() const override {};

	const std::vector<glm::fvec2>& GetWayPoints() { return m_WayPoints; };
	const std::vector<CellOfTheGrid>& GetCells() { return m_Cells; }
	int GetWitdh() { return  m_maxWitdh; };
	int GetHeight() { return m_maxHeight; };
private:
	//void CreateWalls();

	int m_maxWitdh = 0;
	int m_maxHeight = 0;

	std::vector<TankFieldLineComponent*> nm_pLines;
	std::vector<CellOfTheGrid> m_Cells;
	std::vector<glm::fvec2> m_WayPoints;

	int m_PathExtraSpace = 5;
	glm::ivec2 m_Offset = {};
	glm::ivec2 m_playerStartPos = {};
	glm::ivec2 m_EnemyStartPos = {};
};

