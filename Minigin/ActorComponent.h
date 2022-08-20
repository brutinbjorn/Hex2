#pragma once
#include "BaseComponent.h"
#include "SDL.h"
#include "MiniginPCH.h"
//#include "cstring"

class Subject;

class ActorComponent final : public BaseComponent
{
public:
	ActorComponent();
	~ActorComponent() override = default;
	ActorComponent(const ActorComponent& other) = delete;
	ActorComponent(ActorComponent&& other) noexcept = delete;
	ActorComponent& operator=(const ActorComponent& other) = delete;
	ActorComponent& operator=(ActorComponent&& other) noexcept = delete;

	void Initialize() override{};
	void Update(float delta) override;
	void Render() const override ;

	void FixedUpdate(const float ) override {};
	void LateUpdate(const float) override {};
	void GuiRender() const override {};


	glm::vec2 GetVelocity() const { return m_velocity; };
	void SetVelocity(const glm::vec2& vec) { m_velocity = vec; }

	void SetSpeed(float NewSpeed) { m_speed = NewSpeed; }
	float GetSpeed() { return m_speed; }

	Subject* GetSubject() const { return m_pSubject; };

	bool Recieve(BaseComponent*, const std::string&) override { return false; };
private:
	Subject* m_pSubject = nullptr;
	glm::vec2 m_velocity= glm::vec2{0,0};
	float m_speed = 0.f;
	bool m_DebugRender = true;
};

