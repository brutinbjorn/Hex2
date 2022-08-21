#pragma once



class XBox360Controller final
{
	class XBox360ControllerImp;
	XBox360ControllerImp* m_pImpl = nullptr;
public:
	enum class ControllerButton
	{
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,

		Start = 0x0010,
		Back = 0x0020,

		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,

		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};
	enum class KeyBoardButton
	{
		KeyW = 0x0000,
		KeyS = 0x0001,
		KeyA = 0x0004,
		KeyD = 0x0008,

		KeyZ = 0x1000,
		KeyX = 0x2000,
		KeyC = 0x4000,
		KeyV = 0x8000,
	};

	void Update(int ControllerID) const;
	bool IsDown(ControllerButton Button) const;
	bool IsPressed(ControllerButton Button) const;
	bool IsUp(ControllerButton button) const;

	bool IsValid() { return m_controllerIdx != -1; }
	explicit  XBox360Controller(int controllerIndex);
	~XBox360Controller();
private:
	int m_controllerIdx = -1;
};

