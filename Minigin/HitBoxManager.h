#pragma once
#include "HitboxComponent.h"
#include "Singleton.h"

namespace dae
{
	//keep a list of pointers to all the hitboxes, does/should not delete them
	class HitBoxManager final : public Singleton<HitBoxManager>
	{
	public:
		void Update() {};
		void Render() {};
		void addHitBox(HitboxComponent* toAdd) { nm_pHitBoxes.push_back(toAdd); };

		const std::vector<HitboxComponent*>& GetAllHitBoxes() { return nm_pHitBoxes; }

	private:
		friend class Singleton<HitBoxManager>;
		HitBoxManager() = default;
		std::vector<HitboxComponent*> nm_pHitBoxes;
	};
}