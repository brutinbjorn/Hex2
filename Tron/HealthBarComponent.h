#pragma once
#include <BaseComponent.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "HealthComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"

enum class Direction
{
	horizontal = 0,
	vertical = 1
};


class HealthBarComponent :
    public BaseComponent
{

public:
	HealthBarComponent(HealthComponent* healthref, const std::string& HealthIcon, glm::ivec2 spacing = {10,0}) : nm_pHealthComp(healthref),m_spacing(spacing)
	{
		auto val = nm_pHealthComp->GetMaxHealth();
		m_ActiveSprites = val;
		//m_lives.max_size(val);
		for (int i = 0; i < val; ++i)
		{
			auto Sprite = new RenderComponent();
			Sprite->SetTexture(HealthIcon);
			Sprite->SetOffset(spacing.x * (i+1), spacing.y * (i+1));
			GetParent()->AddComponent(Sprite);
			m_liveIcons.push_back(Sprite);
		}


	};

	HealthBarComponent() = default;

	~HealthBarComponent() override= default;
	HealthBarComponent(const HealthBarComponent& other) = delete;
	HealthBarComponent(HealthBarComponent&& other) noexcept = delete;
	HealthBarComponent& operator=(const HealthBarComponent& other) = delete;
	HealthBarComponent& operator=(HealthBarComponent&& other) noexcept = delete;

	void Initialize() override;
	void FixedUpdate(const float ) override;
	void Update(const float) override {};
	void Render() const override
	{
	};
	void LateUpdate(const float ) override;

	//virtual void Update(const float) {};
	void SetOffset(float x, float y);
	void SetSpacing(float x, float y);
protected:


	int m_ActiveSprites = 0;
	glm::ivec2 m_offset;
	glm::ivec2 m_spacing;

	HealthComponent* nm_pHealthComp;

	std::vector<RenderComponent*> m_liveIcons; 
	Direction m_direction = Direction::horizontal;

};

