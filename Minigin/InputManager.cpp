#include "MiniginPCH.h"
#include "InputManager.h"
#pragma once
#include <list>
#include <map>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")

#pragma warning(push)

#pragma warning(disable:26812)
#pragma warning(disable:26819)

#include "backends/imgui_impl_sdl.h"
#include "SDL.h"
#pragma warning(pop)

using ControllerCommandMap = std::map<XBox360Controller::ControllerButton, Command*>;
using KeyBoardCommandMap = std::map<XBox360Controller::KeyBoardButton, Command*>;

dae::InputManager::InputManager() : m_EventOld{0}
{
	//int cId = CheckForController();

}

dae::InputManager::~InputManager()
{
	delete m_pController;
	for (int i = 0; i < m_pControllers.size(); i++)
		delete m_pControllers[i];

	for (std::list<Action>::iterator iter = m_Actions.begin(); iter != m_Actions.end(); ++iter)
	{
		if (iter->pCommand)
		{
			delete iter->pCommand;
			iter->pCommand = nullptr;
		}
	}
}

void dae::InputManager::CheckForController()
{
	int controllerId = -1;


	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;

	}
	if (controllerId != -1)
	{
		if (m_pController)
			delete m_pController;

		m_pController = new XBox360Controller(controllerId);
	//	std::cout << "controller found: " << controllerId << std::endl;
	}
	else
	{
		m_pController = nullptr;
	//	std::cout << "no controller found" << std::endl;
	}
}

bool dae::InputManager::ProcessInput()
{
	//CopyMemory(&prevState, &nextState, sizeof(XINPUT_STATE));
	//ZeroMemory(&nextState, sizeof(XINPUT_STATE));
	//XInputGetState(0, &nextState);
	//ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	//XInputGetState(0, &m_CurrentState);

	//const Uint8* keyState = SDL_GetKeyboardState(NULL);
	//const Uint8 

	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	SDL_Event e;

	while (SDL_PollEvent(&e)) {


		if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			return false;
		}
		for (std::list<Action>::iterator iter = m_Actions.begin(); iter != m_Actions.end(); ++iter)
		{
			if (e.type == SDL_KEYDOWN && iter->type == InputType::WentDown  && e.key.keysym.scancode == iter->key)
			{
				iter->pCommand->Execute();
			}
			if (e.type == SDL_KEYUP && iter->type == InputType::WentUp && e.key.keysym.scancode == iter->key)
			{
				iter->pCommand->Execute();
			} //TODO still need to fix this.
			if (keyState[iter->key] && iter->type == InputType::IsPressed)
			{
				iter->pCommand->Execute();
			}
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_EventOld = e;


	if(!m_pController || !m_pController->IsValid())
	{
		CheckForController();
	}

	if (m_pController)
	{
		m_pController->Update();

		for (std::list<Action>::iterator iter = m_Actions.begin(); iter != m_Actions.end(); ++iter)
		{

			if (m_pController->IsDown(iter->XButton) && iter->type == InputType::WentDown)
			{
				iter->pCommand->Execute();
			}
			if (m_pController->IsPressed(iter->XButton) && iter->type == InputType::IsPressed)
			{
				iter->pCommand->Execute();
			}
			if (m_pController->IsUp(iter->XButton) && iter->type == InputType::WentUp)
			{
				iter->pCommand->Execute();
			}
		}

		if (m_pController->IsDown(XBox360Controller::ControllerButton::Back)  )
			return false;	
	}

	return true;

}

void dae::InputManager::AddAction(const Action& ac)
{
	m_Actions.push_back(ac);
}


