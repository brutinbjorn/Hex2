#include "MiniginPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"
#include "Renderer.h"


ActorComponent::ActorComponent()
	:m_pSubject(nullptr), m_velocity(0, 0)
{
}

void ActorComponent::Update(float)
{

}

void ActorComponent::Render() const
{
	if(m_DebugRender)
	{
		glm::ivec2 val = GetParent()->GetTransform()->GetPosition();
		auto& rend = dae::Renderer::GetInstance();
		rend.RenderPointRect(val.x, val.y, 32);
		rend.RenderRect(val, 2, 32);
	}
}

void ActorComponent::MoveTranslate(float x, float y)
{
	auto trs = GetParent()->GetTransform();
	auto pos = trs->GetPosition();
	pos = { pos.x + x,pos.y + y,0 };
	trs->SetPosition(pos);

}

void ActorComponent::Translate(float x, float y)
{
	auto pos = glm::vec3{ x,y,1 };
	GetParent()->GetTransform()->SetPosition(pos); 
}


