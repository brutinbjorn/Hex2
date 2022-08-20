#pragma once
#include <BaseComponent.h>
#include <vector>


#include "TankFieldLineComponent.h"





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



private:
	//void CreateWalls();

	struct CellOfTheGrid
	{
		CellOfTheGrid(int x,int y,int type):x(x),y(y),Type(type) {}
		int x, y;
		int Type;
	};

	std::vector<TankFieldLineComponent*> nm_pLines;
	std::vector<CellOfTheGrid> m_Cells;

	int m_PathExtraSpace = 4;
	glm::ivec2 m_Offset = {};
	glm::ivec2 m_playerStartPos = {};
	glm::ivec2 m_EnemyStartPos = {};
};

