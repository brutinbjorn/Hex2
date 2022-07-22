#pragma once
#include "BaseComponent.h"
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

	//adds to current positions
	void MoveTranslate(float x,float y);
	//resets the position
	void Translate(float x, float y);
	Subject* GetSubject() const { return m_pSubject; };
	bool Recieve(BaseComponent*, const std::string&) override { return false; };
private:
	Subject* m_pSubject = nullptr;

	glm::vec2 m_velocity= glm::vec2{0,0};
	
	bool m_DebugRender = true;
};

