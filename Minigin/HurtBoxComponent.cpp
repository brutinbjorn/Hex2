#include "MiniginPCH.h"
#include "HurtBoxComponent.h"

#include "HitboxManager.h"
#include "Renderer.h"
#include "SquareComponent.h"


HurtBoxComponent::HurtBoxComponent(SquareComponent* Sqr, int CollisionID)
	: nm_pRect(Sqr)
	, m_ColisionID(CollisionID)
{

}

void HurtBoxComponent::Update(const float )
{
	//IsOverlappingHitbox(nullptr);

}

void HurtBoxComponent::Render() const
{
}

bool HurtBoxComponent::IsOverlappingHitbox(HitboxComponent* GetHitBox)
{
	m_hasHit = false;

	auto& vectorRef = dae::HitBoxManager::GetInstance().GetAllHitBoxes();
	for (int i = 0; i < int(vectorRef.size()); i++)
	{
		if (vectorRef[i]->IsSquareInThisHitBox(nm_pRect->GetSquareWorld(), m_ColisionID))
		{
			GetHitBox = vectorRef[i];
			m_hasHit = true;
			return true;
		}
	}
	return true;
}


