#pragma once
#include "Font.h"
#include "GameObject.h"

namespace ObjectConstructor
{
	std::shared_ptr<dae::GameObject> BasicActor(const std::string& RenderFile);

	std::shared_ptr<dae::GameObject> HealthBar(const glm::vec3& pos, const std::shared_ptr<dae::Font>& font );

	std::shared_ptr<dae::GameObject> ScoreBar(const glm::vec3& pos, const std::shared_ptr<dae::Font>& font);

	std::shared_ptr<dae::GameObject> BaseButton(const glm::vec3& pos, const SDL_Rect& relativeRect ,const std::shared_ptr<dae::Font>& font);
}
