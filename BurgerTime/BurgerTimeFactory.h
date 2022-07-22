#pragma once
#include <memory>

#include "GameObject.h"


namespace BurgerTimeFactory
{
	std::shared_ptr<dae::GameObject> Burger(glm::vec2 position, glm::ivec2 scaleOfTexture,
		const std::vector<int>& HeightOfPieces, const std::vector<std::string>& TexOfPieces);
}

