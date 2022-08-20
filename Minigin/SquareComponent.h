#pragma once

#include <SDL.h>
#include <glm/detail/type_vec.hpp>

#include "BaseComponent.h"
#include "GameObject.h"
#include "Renderer.h"

class SquareComponent :public BaseComponent
{
public:
	SquareComponent() = default;
	~SquareComponent() override = default;
	SquareComponent(const SquareComponent& other) = delete;
	SquareComponent(SquareComponent&& other) noexcept = delete;
	SquareComponent& operator=(const SquareComponent& other) = delete;
	SquareComponent& operator=(SquareComponent&& other) noexcept = delete;

	void Initialize() override {};
	void FixedUpdate(const float) override {};
	void Update(const float) override
	{
		auto parent = GetParent()->GetTransform();
		if(m_FollowParent && parent)
		{
			m_rectWorld.x = static_cast<int>(parent->GetPosition().x) + m_rect.x;
			m_rectWorld.y = static_cast<int>(parent->GetPosition().y) + m_rect.y;
		}
	};
	void LateUpdate(const float) override {};

	void Render() const override
	{
		//dae::Renderer::GetInstance().RenderRect(m_RectWorld);
		if (m_RenderFull)
			dae::Renderer::GetInstance().RenderRect(m_rectWorld, m_ColorFull);

		if(m_RenderLines)
			dae::Renderer::GetInstance().RenderFullRect(m_rectWorld, m_ColorBorder);
	}

	void SetSquare(const SDL_Rect& Rect) 
	{
		m_rect = Rect;
		if (GetParent())
		{
			m_rectWorld = m_rect;
			m_rectWorld.x = Rect.x + static_cast<int>(GetParent()->GetTransform()->GetPosition().x);
			m_rectWorld.y = Rect.y + static_cast<int>(GetParent()->GetTransform()->GetPosition().y);
		}
	};
	void SetRenderLines(bool rnd = true,SDL_Color clr = {255,255,255,255})
	{
		m_RenderLines = rnd;
		m_ColorBorder = clr;
	}
	void SetRenderFull(bool rnd = true, SDL_Color clr = {255,255,255,255})
	{
		m_RenderFull = rnd;
		m_ColorFull = clr;
	}

	const SDL_Rect& GetSquareRelative() const { return m_rect; };
	const SDL_Rect& GetSquareWorld() const { return m_rectWorld; };
private:
	SDL_Rect m_rectWorld = {};  
	SDL_Rect m_rect = {};
	bool m_FollowParent = true;
	SDL_Color m_ColorBorder = SDL_Color{};
	bool m_RenderLines = false;
	SDL_Color m_ColorFull = SDL_Color{};
	bool m_RenderFull = false;


	glm::vec3 m_formerPos = {}; 
};

