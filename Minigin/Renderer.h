#pragma once
#include "Singleton.h"

#pragma warning(push, 0)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#pragma warning(disable:26495)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() ;
		void ImGuiRender();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, int width, int height, const double angle = 0) const;
		void RenderTexture(const Texture2D& texture, float x, float y, int width, int height, const struct SDL_Rect& srcRect, const double angle) const;
		void RenderRect(const SDL_Rect& rec, const SDL_Color& color = { 255,255,255,255 });
		void RenderRect(const glm::vec2& pos, int Height,int yWidth, const SDL_Color& color = {255,255,255,255});
		void RenderPointRect(int xCenter, int yCenter, int size);

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:
		//TrashTheCache m_CasheExersice;
	};
}

