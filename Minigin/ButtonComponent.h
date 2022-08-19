#pragma once
#include "BaseComponent.h"
#include "Command.h"
#include "Renderer.h"
#include "SquareComponent.h"
class SquareComponent;

class ButtonComponent :
    public BaseComponent
{
public:
	ButtonComponent(SquareComponent* ButtonQuad, Command* command): nm_pSquare(ButtonQuad),m_pCommand(command)
	{
	}
	~ButtonComponent() override= default;
	ButtonComponent(const ButtonComponent& other) = delete;
	ButtonComponent(ButtonComponent&& other) noexcept = delete;
	ButtonComponent& operator=(const ButtonComponent& other) = delete;
	ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;


	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float ) override {};
	void LateUpdate(const float ) override {};
	void Render() const override 
	{
		dae::Renderer::GetInstance().RenderRect(nm_pSquare->GetSquareWorld());
	};

	void PressButton(glm::vec2 )
	{
		//auto sqr = nm_pSquare->GetSquareWorld();

		if (m_pCommand)
			m_pCommand->Execute();
	};

private:
	SquareComponent* nm_pSquare;
	Command* m_pCommand;

	bool m_Highlight;



};

