#pragma once
#include <BaseComponent.h>
#include <string>
#include <vector>
#include "MoveZoneComponent.h"

#pragma warning(push, 0)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#pragma warning(disable:26495)
#include <glm/glm.hpp>
#pragma warning (pop)

class MoveGridComponent final:
    public BaseComponent
{
public:
	MoveGridComponent() = default;
	MoveGridComponent(const std::string& fileName, glm::ivec2 offset);
	~MoveGridComponent() override = default;
	MoveGridComponent(const MoveGridComponent& other) = delete;
	MoveGridComponent(MoveGridComponent&& other) noexcept = delete;
	MoveGridComponent& operator=(const MoveGridComponent& other) = delete;
	MoveGridComponent& operator=(MoveGridComponent&& other) noexcept = delete;

	void AddZone(MoveZoneComponent* pZone) { m_MoveZones.push_back(pZone); }
	char GetDirections(glm::vec2 pos);

	void Initialize() override;

	void FixedUpdate(const float) override {};
	void Update(const float) override {};
	void LateUpdate(const float) override {};
	void Render() const override {};
	void GuiRender() const override {};

	bool Recieve(BaseComponent*, const std::string&) override { return false; };
private:
	std::string m_fileName;
	glm::ivec2 m_offset;

	std::vector<MoveZoneComponent*> m_MoveZones;
	std::vector<SDL_Rect> m_MovementRectangles;
};

