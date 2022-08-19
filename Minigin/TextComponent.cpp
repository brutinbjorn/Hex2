#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "Texture2D.h"


dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font,RenderComponent* renderComp) 
	:  m_NeedsUpdate(true), m_Text(text), m_Font(font), m_pRenderComponent(renderComp)//, m_TextTexture(nullptr)
{

}

dae::TextComponent::~TextComponent()
{
	// Textcomp should create and pass on a texture but not own it.
	//if (m_TextTexture)
	//delete m_TextTexture;
}

// TextComponent should not own the texture, only create it.
dae::Texture2D* dae::TextComponent::CreateAndGetTexture() const
{
	//const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	return new dae::Texture2D(texture);

}

bool dae::TextComponent::Recieve(BaseComponent* comp, const std::string& ) 
{
	if(auto FPSComp = dynamic_cast<FPSComponent*>(comp))
	{
		SetText("FPS: " + std::to_string(FPSComp->GetFPS()));
		return true;
	}
	return false;
}

void dae::TextComponent::Update(const float)
{
	if (m_NeedsUpdate)
	{

		if(m_pRenderComponent)
		{
			//std::cout << "Text has been set directly" << std::endl;
			m_pRenderComponent->SetTexture(CreateAndGetTexture());
		}
		else
		{
			//std::cout << "error: Textcomponent has no renderTarget, sending msg" << std::endl;
			bool send = false;

			auto parent = GetParent();
			if (parent)
				send = parent->Recieve(this, "NewTexture");
			else
			{

				throw std::runtime_error(std::string("Text component is sending without a parent") + SDL_GetError());
			}

			if (!send)
			{
				throw std::runtime_error(std::string("Text component is sending without a responce") + SDL_GetError());
				//std::cout << "send failed" << std::endl;
			}
		}

		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	//if (m_TextTexture != nullptr)
	//{
	//	const auto& pos = m_Transform.GetPosition();
	//	Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	//}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void  dae::TextComponent::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
	const SDL_Color newCol = SDL_Color{ r, g, b };

	SetColor(newCol);
}

void  dae::TextComponent::SetColor(const SDL_Color& newColor)
{
	m_Color = newColor;
}

