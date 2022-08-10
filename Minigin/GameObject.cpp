#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (uint32_t i = 0; i < m_pComponents.size(); ++i)
	{
		delete m_pComponents[i];
	}

}

void dae::GameObject::Initialize()
{
	for (uint32_t i = 0; i < m_pComponents.size(); ++i)
	{
		m_pComponents[i]->Initialize();
	}
}

void dae::GameObject::FixedUpdate(const float ft)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->FixedUpdate(ft);
	}
};

void dae::GameObject::Update(const float dt)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update(dt);
	}
}

void dae::GameObject::LateUpdate(const float lt)
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->LateUpdate(lt);
	}
}

void dae::GameObject::Render() const
{
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Render();
	}

	//const auto& pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
	//m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{ 
	m_Transform.SetPosition(x, y, 0.0f);
}


void dae::GameObject::AddComponent(BaseComponent* ToAdd)
{
	m_pComponents.push_back(ToAdd);
	SetChild(ToAdd);
//	return ToAdd;
}

bool dae::GameObject::Send( BaseComponent* sender, const std::string& msg)
{
	return Recieve(sender, msg);
}

bool dae::GameObject::Recieve(BaseComponent* sender, const std::string& msg)
{
	bool response = false;
	for (uint32_t i = 0; i < m_pComponents.size(); i++)
	{
		if (m_pComponents[i]->Recieve(sender, msg))
			response = true;
	}
	return response;

}

void dae::GameObject::SetChild(BaseComponent* child)
{
	if (child->m_pParent && child->m_pParent != this)
		child->m_pParent->RemoveChild(child);
	child->m_pParent = this;
}

void dae::GameObject::RemoveChild(BaseComponent* child)
{
	for(auto i  = m_pComponents.begin();i != m_pComponents.end(); i++)
	{
		if(*i == child)
		{
			m_pComponents.erase(i);
			break;
		}
	}
}
