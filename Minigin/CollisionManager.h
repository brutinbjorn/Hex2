#pragma once
#include <vector>

#include "Singleton.h"

class CollisionComponent;

namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddCollisionComp(CollisionComponent* toAdd) { nm_pCollisionList.push_back(toAdd); }
		void RemoveCollisionComp(CollisionComponent* toRemove)
		{
			auto element = std::find(nm_pCollisionList.begin(), nm_pCollisionList.end(), toRemove);
			if (element != nm_pCollisionList.end())
				nm_pCollisionList.erase(element);
		};

		const std::vector<CollisionComponent*>& GetAllCollisionBoxes() { return nm_pCollisionList; }


	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		~CollisionManager() override = default;
		std::vector<CollisionComponent*> nm_pCollisionList;
	};
}

//namespace dae
//{
//	//keep a list of pointers to all the hitboxes, does/should not delete them
//	class HitBoxManager final : public Singleton<HitBoxManager>
//	{
//	public:
//		void Update() {};
//		void Render() {};
//		void addHitBox(HitboxComponent* toAdd) { nm_pHitBoxes.push_back(toAdd); };
//
//		const std::vector<HitboxComponent*>& GetAllHitBoxes() { return nm_pHitBoxes; }
//
//	private:
//		friend class Singleton<HitBoxManager>;
//		HitBoxManager() = default;
//		std::vector<HitboxComponent*> nm_pHitBoxes;
//	};
//}