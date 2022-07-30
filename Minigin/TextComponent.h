#pragma once
//#include "GameObject.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "MiniginPCH.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		void Initialize() override {};
		void Update(const float) override;
		void FixedUpdate(const float ) override{};
		void LateUpdate(const float ) override{};
		void Render() const override;
		void GuiRender() const override {};
		void SetText(const std::string& text);

		void SetColor(uint8_t r, uint8_t g, uint8_t b);
		void SetColor(const SDL_Color& newColor);

		TextComponent( const std::string& text, const std::shared_ptr<Font>& font,RenderComponent* renderComp);
		 ~TextComponent() override;

		Texture2D* CreateAndGetTexture() const;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		bool Recieve( BaseComponent* comp, const std::string& string)  override;
	private:
		bool m_NeedsUpdate;

		SDL_Color m_Color = { 255,255,255 }; 
		//direct refrence, want to decouple this.
		RenderComponent* m_pRenderComponent;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		//Texture2D* m_TextTexture = nullptr;
	};
}
