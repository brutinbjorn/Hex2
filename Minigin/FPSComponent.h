#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
}

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent() = default;
	~FPSComponent() override = default;

	void Initialize() override{};
	void FixedUpdate(const float ) override{};
	void SetTextComponent(dae::TextComponent* textComp) { m_pTextComponent = textComp; };
	void Update(const float dt) override;
	void LateUpdate(const float) override{};
	void Render() const override {};

	uint32_t GetFPS() const { return m_FPS; };
	//messages
	bool Recieve(BaseComponent*, const std::string&) override { return false; };
private:
	dae::TextComponent* m_pTextComponent = nullptr;
	float m_UpdateInterval = 1.f;
	float m_Time = 0.f;
	uint32_t m_FPS = 0;
};

