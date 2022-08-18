#include "MiniginPCH.h"
#include "ScoreComponent.h"


void ScoreComponent::Update(const float)
{
	if(m_HasChanged)
	{
		m_pTextComponent->SetText("Score: " + std::to_string(m_Score));
		m_HasChanged = false;
	}
}

void ScoreComponent::AddScore(int scoreToAdd)
{
	m_HasChanged = true;
	m_Score += scoreToAdd;
}

void ScoreComponent::OnNotify( const std::string& msg) 
{

	if (msg == "GOT_SCORE")
	{
		AddScore(50);

		if (m_Score > 500){
		}
	}
	if (msg == "BLUE_TANK_DIED")
	{
		AddScore(100);
	}
	if(msg == "RECOGNIZER_DIED")
	{
		AddScore(250);
	}
}