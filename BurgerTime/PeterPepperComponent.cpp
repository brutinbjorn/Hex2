#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "Subject.h"

PeterPepperComponent::PeterPepperComponent()
{

}

void PeterPepperComponent::Die()
{
	std::cout << "PeterPepper Died" << std::endl;
	m_pSubject.Notify("PLAYER_DIED");
}

void PeterPepperComponent::TestScore()
{
	std::cout << "PeterPepper Got Score" << std::endl;
	m_pSubject.Notify("GOT_SCORE");
}
