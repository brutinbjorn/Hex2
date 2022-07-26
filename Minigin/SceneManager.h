#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene* GetScene(const std::string& name);
		void AddScene(std::shared_ptr<Scene> newScene);
		void PostInitialize();
		void FixedUpdate(const float ft);
		void Update(const float dt);
		void LateUpdate(const float lt);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
