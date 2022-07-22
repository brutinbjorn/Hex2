#pragma once
#include "MiniginPCH.h"
#include <BaseComponent.h>
#include <vector>

//#include "BurgerPartComponent.h"
//#include <glm/glm.hpp>


class BurgerComponent :
    public BaseComponent
{
public:
	BurgerComponent() = default;
	~BurgerComponent() override = default;
	BurgerComponent(const BurgerComponent& other) = delete;
	BurgerComponent(BurgerComponent&& other) noexcept = delete;
	BurgerComponent& operator=(const BurgerComponent& other) = delete;
	BurgerComponent& operator=(BurgerComponent&& other) noexcept = delete;

	void Initialize() override {} ;
	void FixedUpdate(const float) override {};
	void Update(const float) override {};
	void LateUpdate(const float) override {};
	void Render() const override {};
	void GuiRender() const override {};

	void CreateBurgerParts(glm::vec2 position, glm::ivec2 scaleOfTexture, std::vector<int> positions, std::vector<std::string> BurgerTextures);
private:
	//std::vector<BurgerPartComponent*> m_Parts;
	std::vector<glm::ivec2> m_PartPositions;
	glm::ivec2 m_BottomPos;
	glm::ivec2 m_Scale;
};

