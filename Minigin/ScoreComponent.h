#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"


/**
 * Feedback
 * make Observers pure virtual
 * Make the observer and Component 1 class.
 * Hou Rekening met de steam achievements dat ZE NIET IN COMPONENTS ZITTEN, Steam moet Decoupled zijn
 * GEEN BASECOMPONENT MEEGEVEN EN DAN WEER Casten
 *
 */
class ScoreComponent final:
    public BaseComponent , public InterFace::Observer
{
public:
	ScoreComponent(dae::TextComponent* TextComp) : m_pTextComponent(TextComp) {};
	~ScoreComponent() override = default;

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;


	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float) override;
	void LateUpdate(const float ) override{};
	void Render() const override {}
	void GuiRender() const override {};

	void AddScore(int scoreToAdd);

	int GetScore() { return m_Score; }
	void OnNotify(const std::string& msg)  override;
private:

	bool m_HasChanged = true;
	dae::TextComponent* m_pTextComponent ;
	int m_Score = 0;

};

