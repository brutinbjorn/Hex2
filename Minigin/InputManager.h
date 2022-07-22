#pragma once
#include <vector>
#include "list"
#include <Xinput.h>

#include "Command.h"
#include "XBoxController.h"
#include "Singleton.h"



namespace dae
{
	enum class InputType
	{
		WentDown, WentUp, IsPressed
	};

	struct Action
	{
		Action() = default;
		Action(Command* pCommand,XBox360Controller::ControllerButton xButton, SDL_Scancode KeyBoardkey, InputType InputType):
		pCommand(pCommand),XButton(xButton),key(KeyBoardkey),type(InputType) {};

		Command* pCommand = nullptr;
		XBox360Controller::ControllerButton XButton = XBox360Controller::ControllerButton::Start;
		SDL_Scancode key = SDL_SCANCODE_UNKNOWN;
		InputType type = InputType::WentDown;
	};

	//WORD buttonPressedThisFrame;
	//WORD buttonReleasedThisFrame;

	class InputManager final : public Singleton<InputManager>
	{
	public:

		~InputManager() override;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) noexcept = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) noexcept = delete;

		void CheckForController();
		bool ProcessInput();
		void AddAction(const Action& ac);
	private:
		InputManager();
		friend class Singleton<InputManager>;
		//bool IsPressed(XBox360Controller::ControllerButton button) const;
		//XINPUT_STATE m_CurrentState{};

		XBox360Controller* m_pController = nullptr;
		std::vector<XBox360Controller*> m_pControllers;
		std::list<Action> m_Actions;

	};


}
