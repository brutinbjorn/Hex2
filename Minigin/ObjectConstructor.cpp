#include "MiniginPCH.h"
#include "ObjectConstructor.h"

#include "ActorComponent.h"
#include "HealthBarComponent.h"

#include "ScoreComponent.h"
#include "TextComponent.h"

std::shared_ptr<dae::GameObject> ObjectConstructor::BasicActor(const std::string& RenderFile)
{
	auto newActor = std::make_shared<dae::GameObject>();

	auto PeterComp = new ActorComponent();
	newActor->AddComponent(PeterComp);

	auto RenderComp = new RenderComponent();
	RenderComp->SetTexture(RenderFile);
	newActor->AddComponent(RenderComp);

	return newActor;
}

std::shared_ptr<dae::GameObject> ObjectConstructor::HealthBar(const glm::vec3& pos, const std::shared_ptr<dae::Font>& font)
{
	auto NewHealthBar = std::make_shared<dae::GameObject>();

	auto RenderComp = new RenderComponent();
	auto TextComp = new dae::TextComponent("levens:", font, RenderComp);

	auto LiveManComp = new HealthBarComponent(TextComp);

	NewHealthBar->AddComponent(RenderComp);
	NewHealthBar->AddComponent(TextComp);
	NewHealthBar->AddComponent(LiveManComp);
	NewHealthBar->GetTransform()->SetPosition(pos);
	return NewHealthBar;
}

std::shared_ptr<dae::GameObject> ObjectConstructor::ScoreBar(const glm::vec3& pos,
	const std::shared_ptr<dae::Font>& font)
{
	auto ScoreBar = std::make_shared<dae::GameObject>();

	auto RenderComp = new RenderComponent();
	auto TextComp = new dae::TextComponent("levens:", font, RenderComp);

	auto ScoreBarComp = new ScoreComponent(TextComp);

	ScoreBar->AddComponent(RenderComp);
	ScoreBar->AddComponent(TextComp);
	ScoreBar->AddComponent(ScoreBarComp);
	ScoreBar->GetTransform()->SetPosition(pos);
	return ScoreBar;
}

