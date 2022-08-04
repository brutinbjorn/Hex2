#include "WallComponent.h"

#include "Renderer.h"

void WallComponent::Render() const
{
	dae::Renderer::GetInstance().RenderRect(m_Collision,m_Color);
}

