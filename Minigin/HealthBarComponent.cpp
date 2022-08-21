#include "MiniginPCH.h"
#include "HealthBarComponent.h"

#include "ActorComponent.h"

void HealthBarComponent::Update(const float )
{
	if(m_HasChanged == true)
	{
		//m_TextDisplay->SetText(std::string("Levens: " + std::to_string(m_lives)));
		m_HasChanged = false;
	}
}

void HealthBarComponent::OnNotify( const std::string& msg)
{
		
	if(msg == "PLAYER_DIED")
	{
		LoseLive();
	}
	
}
