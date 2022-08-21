#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Observer.h"
#include "TextComponent.h"
enum class Direction
{
	horizontal = 0,
	vertical = 1
};
class HealthBarComponent final:
    public BaseComponent, public InterFace::Observer
{
public:
	HealthBarComponent(HealthComponent* healthref, const std::string& HealthIcon, glm::ivec2 spacing = { 10,0 })
	: nm_pHealthComp(healthref), m_spacing(spacing),m_FilePath(HealthIcon)
	{
	};

	~HealthBarComponent() override = default;
	HealthBarComponent(const HealthBarComponent& other) = delete;
	HealthBarComponent(HealthBarComponent&& other) noexcept = delete;
	HealthBarComponent& operator=(const HealthBarComponent& other) = delete;
	HealthBarComponent& operator=(HealthBarComponent&& other) noexcept = delete;

	void Initialize() override
	{
		auto val = nm_pHealthComp->GetMaxHealth();
		m_ActiveSprites = val;
		//m_lives.max_size(val);
		for (int i = 0; i < val; ++i)
		{
			auto Sprite = new RenderComponent();
			Sprite->SetTexture(m_FilePath);
			Sprite->SetOffset(m_spacing.x * (i + 1), m_spacing.y * (i + 1));
			Sprite->SetSize(10, 10);
			GetParent()->AddComponent(Sprite);
			m_liveIcons.push_back(Sprite);
		}

	};
	void Update(const float dt) override;

	void FixedUpdate(const float) override {};
	void LateUpdate(const float) override {};
	void Render() const override  {};
	void GuiRender() const override {};

	void LoseLive(int lives = 1)
	{
		m_HasChanged = true;
		m_lives -= lives;
	}

	void OnNotify(const std::string& msg) override;
private:

	bool m_HasChanged = true;
	int m_lives = 3;

	const std::string m_FilePath = 0;
	int m_ActiveSprites = 0;
	glm::ivec2 m_offset;
	glm::ivec2 m_spacing;

	HealthComponent* nm_pHealthComp;

	std::vector<RenderComponent*> m_liveIcons;
	Direction m_direction = Direction::horizontal;


};

