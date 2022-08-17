#include "BurgerPartComp.h"

#include "GameObject.h"
#include "RenderComponent.h"


BurgerPartComp::BurgerPartComp(const glm::ivec2& scaleOfTexture, const std::string& TexturePath)
	:m_Scale(scaleOfTexture),m_TexturePath(TexturePath)
{

}

void BurgerPartComp::CreateHitBoxes()
{
	auto papa = GetParent();
	auto pos = papa->GetTransform()->GetPosition();
	auto render = new RenderComponent();
	render->SetTexture(m_TexturePath);
	render->SetSize(m_Scale.x, m_Scale.y);
	papa->AddComponent(render);

	for (int i = -2; i < 2; i++)
	{
		glm::ivec2 size{ m_Scale.x / 5 , m_Scale.y };
		glm::ivec2 position{pos.x + size.x * i,pos.y};


		//papa->AddComponent(new HitboxComponent(position,size,1));
		//		SDL_Rect HitboxRec;
		//		HitboxRec.h = scaleOfTexture.y;
		//		HitboxRec.w = scaleOfTexture.x / 5;
		//		HitboxRec.x = scaleOfTexture.x + i * HitboxRec.w;
		//
		////		HitboxRec.y = static_cast<int>(GetParent()->GetTransform()->GetPosition().y);
		//		m_HitBoxes.emplace_back(HitboxRec);
		//
		//		auto hitbo = new HitboxComponent(glm::ivec2{,},glm::ivec2{},1);
	}
}
