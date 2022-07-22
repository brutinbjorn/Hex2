#include "BurgerTimeFactory.h"

#include "BaseComponent.h"
#include "BurgerComponent.h"
#include <vector>

#include "RenderComponent.h"


std::shared_ptr<dae::GameObject> BurgerTimeFactory::Burger(glm::vec2 position, glm::ivec2 scaleOfTexture, const std::vector<int>& HeightOfPieces,const std::vector<std::string>& TexOfPieces)
{
	auto newBurger = std::make_shared<dae::GameObject>();

	newBurger->AddComponent(new BurgerComponent());
	auto burg = newBurger->GetComponent<BurgerComponent>();
	burg->CreateBurgerParts(position,scaleOfTexture,HeightOfPieces, TexOfPieces);
	return newBurger;
}
