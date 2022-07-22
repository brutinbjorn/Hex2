#include "MiniginPCH.h"
#include "Renderer.h"

#include "SceneManager.h"
#include "Texture2D.h"

#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include <backends/imgui_impl_sdl.h>
#include "backends/imgui_impl_opengl2.h"
#pragma warning(pop)

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() 
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGuiRender();



	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::ImGuiRender()
{
	//ImGui::Begin("TTC exercise 1");
	//m_CasheExersice.ExerciseOne();
	//ImGui::End();
	//ImGui::Begin("TTC exercise 2");
	//m_CasheExersice.ExerciseTwo();
	//ImGui::End();
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const int width, const int height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderRect(const SDL_Rect& rec, const SDL_Color& color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_Renderer, &rec);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
}

void dae::Renderer::RenderRect(const glm::vec2& pos, int Height, int Width, const SDL_Color& color)
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(Width);
	dst.h = static_cast<int>(Height);

	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_Renderer, &dst);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

}

void dae::Renderer::RenderPointRect(int xCenter, int yCenter, int size)
{
	SDL_Rect rect;
	rect.x = xCenter- size / 2;
	rect.y = yCenter - size / 2;
	rect.h = size;
	rect.w = size;

	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
}

