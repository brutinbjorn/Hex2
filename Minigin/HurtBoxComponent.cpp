#include "MiniginPCH.h"
#include "HurtBoxComponent.h"

#include "HitboxManager.h"
#include "Renderer.h"
#include "../Tron/SquareComponent.h"


HurtBoxComponent::HurtBoxComponent(SquareComponent* Sqr, int CollisionID)
	: nm_pRect(Sqr)
	, m_ColisionID(CollisionID)
{

}

bool HurtBoxComponent::IsOverlappingHitbox(HitboxComponent* hitbox)
{
	m_hasHit = false;

	auto& vectorRef = dae::HitBoxManager::GetInstance().GetAllHitBoxes();
	for (int i = 0; i < int(vectorRef.size()); i++)
	{
		if (vectorRef[i]->IsSquareInThisHitBox(nm_pRect->GetSquareWorld(), m_ColisionID))
		{
			//std::cout << "hurtbox is overlapping hitbox" << std::endl;
			m_hasHit = true;

		}
	}
}
