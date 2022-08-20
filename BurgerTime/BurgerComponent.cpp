#include "BurgerComponent.h"

#include <iostream>
#include "BurgerPartComp.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"


void BurgerComponent::CreateBurgerParts(glm::vec2 position, glm::ivec2 scaleOfTexture, std::vector<int> positions, std::vector<std::string> BurgerTextures)
{

	m_BottomPos = position;
	m_Scale = scaleOfTexture;
	if (positions.size() != BurgerTextures.size())
	{
		std::cout << "Error Not the same amount fo vals int BurgerComp" << std::endl;
		return;
	}


	auto scene = dae::SceneManager::GetInstance().GetScene("Demo");

	for(size_t i = 0; i < positions.size();i++)
	{
		auto burgerSlice = std::make_shared<dae::GameObject>();
		burgerSlice->AddComponent(new BurgerPartComp(scaleOfTexture,BurgerTextures[i]));
		scene->AddGameObject(burgerSlice);


		//auto RenderComp = new RenderComponent();
		//RenderComp->SetTexture(BurgerTextures[i]);
		//RenderComp->SetOffset(m_BottomPos.x,positions[i]);
		//RenderComp->SetSize(m_Scale.x,m_Scale.y);
		////RenderComp->SetOffset(static_cast<int>(GetParent()->GetTransform()->GetPosition().x), positions[i]);
		//GetParent()->AddComponent(RenderComp);
	}
}
