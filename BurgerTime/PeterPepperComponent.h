#pragma once
#include "BaseComponent.h"
#include "Subject.h"
//#include "BaseComponent.h"
//#include "Subject.h"


//RECONS pepper could be the one to own the lives, but not neccesary.


class PeterPepperComponent final:
    public BaseComponent
{
public:
	PeterPepperComponent();
	~PeterPepperComponent() override = default;
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) noexcept = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) noexcept = delete;

	void Die();
	void TestScore();

	void FixedUpdate(const float ) override{};
	void Update(const float ) override {};
	void LateUpdate(const float ) override{};
	void Render() const override {};

	Subject* GetSubject()  { return &m_pSubject; }
	void GuiRender() const override {};
private:
	Subject m_pSubject;

};
