#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "TimeManager.h"



void FPSComponent::Update(const float dt)
{
	m_Time += dt;
	if(m_Time >= m_UpdateInterval)
	{
		m_Time -= m_UpdateInterval;
		m_FPS = dae::TimeManager::GetInstance().GetFPS();
		if(m_pTextComponent)
		{
			m_pTextComponent->SetText("FPS: " + std::to_string(m_FPS));
		}
		else
		{
			//std::cout << "No direct link,send message" << std::endl;

			if (!GetParent()->Recieve(this, "FPSUpdate"))
				throw std::runtime_error(std::string("FPS component is sending without a responce") + SDL_GetError());
		}
		
	}
}
