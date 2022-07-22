#include "MiniginPCH.h"
#include "ScoreObserver.h"

#include "PeterPepperComponent.h"
#include "ScoreComponent.h"

void ScoreObserver::OnNotify(BaseComponent* event, const std::string& msg) const
{
	if (auto e = dynamic_cast<PeterPepperComponent*>(event))
	{
		if (msg == "GOT_SCORE")
		{
			m_ScoreComponent->AddScore(50);

			if (m_ScoreComponent->GetScore() > 500)
			{

				//g_SteamAchievements = new CSteamAchievements(g_Achievements, 4);

				//if (g_SteamAchievements)
				//	g_SteamAchievements->SetAchievement("ACH_WIN_100_GAMES");

			}
		}
	}
}
