#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <map>

using namespace DirectX;

namespace Delegates
{
	public delegate void TriggerPulled();
	public delegate void ButtonPressed();
	public delegate void StickMoved(float x = 0.0f, float y = 0.0f);

	public delegate void KeyPressed();
	public delegate void KeyReleased();
	public delegate void MouseMoved(float x = 0.0f, float y = 0.0f);
	public delegate void MousePressed();
	public delegate void MouseReleased();
}

ref class InputManager
{
public:
	static InputManager^ Instance(void);

	void Update(void);

	void SetLeftTriggerDeadzone(float deadzone);
	void SetRightTriggerDeadzone(float deadzone);
		
	event Delegates::StickMoved^		LeftStickMoved;
	event Delegates::StickMoved^		RightStickMoved;

	event Delegates::TriggerPulled^		LeftTriggerPulled;
	event Delegates::TriggerPulled^		RightTriggerPulled;

	event Delegates::ButtonPressed^		ButtonAPressed;
	event Delegates::ButtonPressed^		ButtonBPressed;
	event Delegates::ButtonPressed^		ButtonXPressed;
	event Delegates::ButtonPressed^		ButtonYPressed;
	event Delegates::ButtonPressed^		ButtonDPadUpPressed;
	event Delegates::ButtonPressed^		ButtonDPadDownPressed;
	event Delegates::ButtonPressed^		ButtonDPadLeftPressed;
	event Delegates::ButtonPressed^		ButtonDPadRightPressed;
	event Delegates::ButtonPressed^		ButtonLeftShoulderPressed;
	event Delegates::ButtonPressed^		ButtonRightShoulderPressed;
	event Delegates::ButtonPressed^		ButtonLeftStickPressed;
	event Delegates::ButtonPressed^		ButtonRightStickPressed;
	event Delegates::ButtonPressed^		ButtonStartPressed;
	event Delegates::ButtonPressed^		ButtonBackPressed;
	event Delegates::ButtonPressed^		ButtonXboxPressed;

	event Delegates::MouseMoved^		MouseMoved;
	event Delegates::MousePressed^		LeftMouseButtonDown;
	event Delegates::MousePressed^		RightMouseButtonDown;
	event Delegates::MouseReleased^		LeftMouseButtonUp;
	event Delegates::MouseReleased^		RightMouseButtonUp;

	void RegisterKeyboardCallback(Windows::System::VirtualKey key, Delegates::KeyPressed^ callback);
	void RegisterKeyboardCallback(Windows::System::VirtualKey key, Delegates::KeyReleased^ callback);

private:
	static InputManager^ m_Instance;

	bool m_IsLeftDown;
	bool m_IsRightDown;

	float m_LeftTriggerDeadzone;
	float m_RightTriggerDeadzone;

	Windows::Gaming::Input::Gamepad^ m_Gamepad;
	Windows::Devices::Input::MouseDevice^ m_Mouse;


	std::map<Windows::System::VirtualKey, bool> m_KeyPressedToggles;
	std::map<Windows::System::VirtualKey, Delegates::KeyPressed^> m_KeyPressedDelegates;
	std::map<Windows::System::VirtualKey, Delegates::KeyReleased^> m_KeyReleasedDelegates;
	
	InputManager(void);

	bool IsLeftTriggerPressed(void);
	bool IsRightTriggerPressed(void);
	bool IsGamepadButtonDown(Windows::Gaming::Input::GamepadButtons button);
	bool IsGamepadButtonReleased(Windows::Gaming::Input::GamepadButtons button);
	bool IsButtonDown(Windows::System::VirtualKey key);
	bool IsButtonReleased(Windows::System::VirtualKey key);

	void UpdateKeyboard(void);
	void UpdateMousePresses(void);
	void UpdateGamepadLeftThumbstick(void);
	void UpdateGamepadRightThumbstick(void);
	void UpdateMouseMovement(Windows::Devices::Input::MouseDevice^ sender, Windows::Devices::Input::MouseEventArgs^ args);

};