#include "MiniginPCH.h"
#include "XBoxController.h"
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")



class XBox360Controller::XBox360ControllerImp
{
public:
	XBox360ControllerImp() = default;
	~XBox360ControllerImp() = default;
	void Update() ;
	bool IsDown(XBox360Controller::ControllerButton button) const;
	bool IsUp(XBox360Controller::ControllerButton button) const ;
	bool IsPressed(XBox360Controller::ControllerButton button) const;
private:
	XINPUT_STATE previeusState{};
	XINPUT_STATE CurrentState{};

};

void XBox360Controller::XBox360ControllerImp::Update()
{
	CopyMemory(&previeusState, &CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&CurrentState, sizeof(XINPUT_STATE));

	//ZeroMemory(&CurrentState, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT ); // voorbeeld van het gebruik meerdere controllers
	XInputGetState(0, &CurrentState);
	
}

bool XBox360Controller::XBox360ControllerImp::IsDown(XBox360Controller::ControllerButton button) const
{
	return ((CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0) &&
		((previeusState.Gamepad.wButtons & static_cast<unsigned int>(button)) == 0);
}

bool XBox360Controller::XBox360ControllerImp::IsUp(XBox360Controller::ControllerButton button) const
{
	return ((CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) == 0) &&
		((previeusState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0);
}

bool XBox360Controller::XBox360ControllerImp::IsPressed(XBox360Controller::ControllerButton button) const
{
	return (CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0;
}


void XBox360Controller::Update() const
{
	if (m_pImpl != nullptr)
		m_pImpl->Update();
}

bool XBox360Controller::IsDown(ControllerButton Button) const
{
	return m_pImpl->IsDown(Button);
}

bool XBox360Controller::IsPressed(ControllerButton Button) const
{
	return m_pImpl->IsPressed(Button);
}

bool XBox360Controller::IsUp(ControllerButton button) const
{
	return m_pImpl->IsUp(button);
}

XBox360Controller::XBox360Controller(int ControllerIndex)
		 : m_controllerIdx(ControllerIndex)
{
	m_pImpl = new XBox360ControllerImp();
}

XBox360Controller::~XBox360Controller()
{
	delete m_pImpl;
}
