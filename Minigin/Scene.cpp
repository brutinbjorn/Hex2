#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
: m_Name(name)
{
	
}

Scene::~Scene() = default;

void Scene::AddGameObject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::PostInitialize()
{
	for(auto& object : m_Objects)
	{
		object->Initialize();
	}
}

void Scene::FixedUpdate(const float ft)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(ft);
	}
}

void Scene::Update(const float dt)
{
	for(auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void Scene::LateUpdate(const float lt)
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate(lt);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

