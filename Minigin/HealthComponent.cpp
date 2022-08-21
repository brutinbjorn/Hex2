#include "MiniginPCH.h"
#include "HealthComponent.h"

void HealthComponent::OnNotify(const std::string& msg)
{
	if(msg == "PLAYER_DIED")
	{
		LoseHealth(1);
		m_HealthChanged = true;
	}
}
