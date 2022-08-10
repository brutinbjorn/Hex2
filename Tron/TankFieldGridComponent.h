#pragma once
#include "ComponentList.h"

enum Directions
{
	DIRECTION_RIGHT = 0b0001,
	DIRECTION_LEFT = 0b0010,
	DIRECTION_UP = 0b0100,
	DIRECTION_DOWN = 0b1000
};

class TankFieldGridComponent final : public BaseComponent
{
public:
	TankFieldGridComponent(const SDL_Rect& Rect) ;
	TankFieldGridComponent() = default;

	~TankFieldGridComponent() override = default;
	TankFieldGridComponent(const TankFieldGridComponent& other) = delete;
	TankFieldGridComponent(TankFieldGridComponent&& other) noexcept = delete;
	TankFieldGridComponent& operator=(const TankFieldGridComponent& other) = delete;
	TankFieldGridComponent& operator=(TankFieldGridComponent&& other) noexcept = delete;

	char GetDirections(const glm::vec3&) { return  DIRECTION_RIGHT + DIRECTION_LEFT + DIRECTION_UP + DIRECTION_DOWN; }
	void CreateLinesEven();
	void CreateLinesFromFile();

	void Initialize() override {};
	void FixedUpdate(const float) override {};
	void Update(const float ) override {};
	void LateUpdate(const float) override {};
	void Render() const override;
	void GuiRender() const override {};
private:

	std::vector<dae::GameObject> m_TankFieldLines;

	SDL_Rect m_Rectangle;

	//int Size;
	int m_Rows = 10;
	int m_Collums = 10;



};

