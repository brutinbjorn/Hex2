#include "MiniginPCH.h"
#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Texture2D.h"

RenderComponent::~RenderComponent()
{
	
	delete m_pTexture;
	delete m_pSrcRect;
	
}

void RenderComponent::Render() const
{
	glm::vec3 pos{0,0,0};

	auto parent = GetParent();

	pos = parent->GetTransform()->GetPosition();
	
	SDL_Rect testRect;

	if(m_pTexture)
	{
		pos.x += m_offset.x - m_Size.x / 2;
		pos.y += m_offset.y - m_Size.y / 2;
		//dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);

		//const glm::vec3& pos = m_transform.GetPosition() + glm ::vec3(m_offset,0);
		testRect.x = int(pos.x) ;
		testRect.y = int(pos.y) ;
		testRect.w = int(m_Size.x);
		testRect.h = int(m_Size.y);
		//	dae::Renderer::GetInstance().RenderRect(&testRect, SDL_Color{ 255,0,0,255 });
		if (!m_IsSizeSet)
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);			
		else //if (!m_pSrcRect)
			dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, static_cast<int>(m_Size.x), static_cast<int>(m_Size.y));
		//else
		//	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Size.x, m_Size.y,*m_pSrcRect,m_Rotation);
		
	}

}

void RenderComponent::SetSize(int x, int y)
{

	if(x != 0 || y != 0)
	m_IsSizeSet = true;
	m_Size = glm::ivec2{ x, y };
}

void RenderComponent::SetOffset(int x, int y)
{
	m_offset = glm::ivec2(x, y);
}


void RenderComponent::SetTexture(const std::string& filename)
{
	if (m_pTexture)
		delete m_pTexture;
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetTexture(dae::Texture2D* texture2D)
{
	if (m_pTexture)
		delete m_pTexture;

	m_pTexture = texture2D;
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr,  &m_Size.x,  &m_Size.y);


}

bool RenderComponent::Recieve(BaseComponent* sender, const std::string&)
{
	if(auto textComp = dynamic_cast<dae::TextComponent*>(sender))
	{
		SetTexture(textComp->CreateAndGetTexture());
		return true;
	}
	return false;
}
//
//void RenderComponent::SetSourceRect(SDL_Rect rect)
//{
//
//}
