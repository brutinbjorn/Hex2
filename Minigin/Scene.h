#pragma once

#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void AddGameObject(const std::shared_ptr<GameObject>& object);

		void PostInitialize();
		void FixedUpdate(const float ft);
		void Update(const float dt);
		void LateUpdate(const float lt);
		void Render() const;

		std::string GetName() { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
