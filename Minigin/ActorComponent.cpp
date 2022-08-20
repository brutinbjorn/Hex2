#include "MiniginPCH.h"
#include "ActorComponent.h"

#include "GameObject.h"
#include "Renderer.h"


ActorComponent::ActorComponent()
	:m_pSubject(nullptr), m_velocity(0, 0)
{
}

void ActorComponent::Update(float dt)
{
	//auto pos = GetParent()->GetTransform()->GetPosition();

	GetParent()->GetTransform()->Translate(m_velocity.x * m_speed * dt , m_velocity.y * m_speed * dt , 0);
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


