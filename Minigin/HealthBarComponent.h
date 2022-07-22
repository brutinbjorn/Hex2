#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

class HealthBarComponent final:
    public BaseComponent, public InterFace::Observer
{
public:
	HealthBarComponent(dae::TextComponent* TargetText): m_TextDisplay(TargetText) {};
	~HealthBarComponent() override = default;
	HealthBarComponent(const HealthBarComponent& other) = delete;
	HealthBarComponent(HealthBarComponent&& other) noexcept = delete;
	HealthBarComponent& operator=(const HealthBarComponent& other) = delete;
	HealthBarComponent& operator=(HealthBarComponent&& other) noexcept = delete;

	void Initialize() override {};
	void Update(const float dt) override;

	void FixedUpdate(const float) override {};
	void LateUpdate(const float) override {};
	void Render() const override  {};
	void GuiRender() const override {};

	void LoseLive(int lives = 1)
	{
		m_HasChanged = true;
		m_lives -= lives;
	}

	void OnNotify( const std::string& msg) override;
private:
	bool m_HasChanged = true;
	dae::TextComponent* m_TextDisplay = nullptr;
	int m_lives = 3;

};

