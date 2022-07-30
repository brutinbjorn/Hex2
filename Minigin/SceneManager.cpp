#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float dt)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(dt);
	}
}

void dae::SceneManager::LateUpdate(const float lt)
{
	for (auto& scene : m_Scenes)
	{
		scene->LateUpdate(lt);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

//Creates a Base Scene in the SceneManager
dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}



dae::Scene* dae::SceneManager::GetScene(const std::string& name)
{
	for (const auto& scene : m_Scenes)
		if (scene.get()->GetName() == name)
			return scene.get();

	return nullptr;
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> newScene)
{
	m_Scenes.push_back(newScene);
}

void dae::SceneManager::PostInitialize()
{
	for (const auto& scene : m_Scenes)
	{
		scene->PostInitialize();
	}
}

void dae::SceneManager::FixedUpdate(const float ft)
{
	for(auto& scene : m_Scenes)
	{
		scene->FixedUpdate(ft);
	}
}
