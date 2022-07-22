#pragma once
#include <BaseComponent.h>
#include <vector>

#include "HitboxComponent.h"
#include "RenderComponent.h"

class BurgerPartComp :
    public BaseComponent
{
public:
	BurgerPartComp(const glm::ivec2& scaleOfTexture, const std::string& TexturePath);
	~BurgerPartComp() = default;
	BurgerPartComp(const BurgerPartComp& other) = delete;
	BurgerPartComp(BurgerPartComp&& other) noexcept = delete;
	BurgerPartComp& operator=(const BurgerPartComp& other) = delete;
	BurgerPartComp& operator=(BurgerPartComp&& other) noexcept = delete;

	void CreateHitBoxes();

	void Initialize() override{};
	void FixedUpdate(const float) override {};
	void Update(const float) override {};
	void LateUpdate(const float) override {};
	void Render() const override {};
	void GuiRender() const override {};



private:
	std::string m_TexturePath;
	glm::ivec2 m_Scale;
	RenderComponent* m_pRenderer = nullptr;
	//std::vector<SDL_Rect> m_HitBoxes;
	std::vector<HitboxComponent*> m_pHitBoxxes;
};

