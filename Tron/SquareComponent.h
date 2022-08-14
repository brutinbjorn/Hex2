#pragma once
#include <BaseComponent.h>
#include <SDL.h>

#include "GameObject.h"

class SquareComponent :
    public BaseComponent
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
			m_RectWorld.x = static_cast<int>(parent->GetPosition().x) + m_rect.x;
			m_RectWorld.y = static_cast<int>(parent->GetPosition().y) + m_rect.y;
		}
	};
	void LateUpdate(const float) override {};
	void Render() const override ;

	void SetSquare(const SDL_Rect& Rect) 
	{

		auto newRect = Rect;
		if (GetParent())
		{
			newRect.x = Rect.x + static_cast<int>(GetParent()->GetTransform()->GetPosition().x);
			newRect.y = Rect.y + static_cast<int>(GetParent()->GetTransform()->GetPosition().y);
		}
		m_rect = newRect;
	};

	const SDL_Rect& GetSquareRelative() const { return m_RectWorld; };
	const SDL_Rect& GetSquareWorld() const { return m_rect; };
private:
	SDL_Rect m_RectWorld = {};  
	SDL_Rect m_rect = {};
	bool m_FollowParent = true;
	glm::vec3 m_formerPos = {}; 
};

