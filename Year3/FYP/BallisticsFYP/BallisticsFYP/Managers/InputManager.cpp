#include "pch.h"
#include "InputManager.h"
#include <WinUser.h>

#include <iostream>

using namespace Windows::Gaming::Input;
using namespace Windows::Devices::Input;
using namespace Windows::Devices::HumanInterfaceDevice;

InputManager^ InputManager::m_Instance = nullptr;

InputManager::InputManager(void)
{
	m_LeftTriggerDeadzone = 0.0f;
	m_RightTriggerDeadzone = 0.0f;

	MouseCapabilities^ mouseCap = ref new MouseCapabilities();
	if (mouseCap->MousePresent == 1)
	{
		m_KeyPressedToggles[Windows::System::VirtualKey::LeftButton] = false;
		m_KeyPressedToggles[Windows::System::VirtualKey::RightButton] = false;

		m_Mouse = m_Mouse->GetForCurrentView();
		m_Mouse->MouseMoved += ref new Windows::Foundation::TypedEventHandler<MouseDevice^, MouseEventArgs^>(this, &InputManager::UpdateMouseMovement);
	}

	KeyboardCapabilities^ keyboardCap = ref new KeyboardCapabilities();
	if (keyboardCap->KeyboardPresent == 1)
	{
		
	}
}
InputManager^ InputManager::Instance(void)
{
	if (!m_Instance)
		m_Instance = ref new InputManager();

	return m_Instance;
}

void InputManager::SetLeftTriggerDeadzone(float deadzone)
{
	m_LeftTriggerDeadzone = deadzone;
}
void InputManager::SetRightTriggerDeadzone(float deadzone)
{
	m_RightTriggerDeadzone = deadzone;
}

void InputManager::RegisterKeyboardCallback(Windows::System::VirtualKey key, Delegates::KeyPressed^ callback)
{
	m_KeyPressedDelegates[key] = callback;

	auto keyUpDelegate = m_KeyReleasedDelegates.find(key);
	if (keyUpDelegate == m_KeyReleasedDelegates.end())
	{
		m_KeyReleasedDelegates[key] = nullptr;
	}

	m_KeyPressedToggles[key] = false;
}
void InputManager::RegisterKeyboardCallback(Windows::System::VirtualKey key, Delegates::KeyReleased^ callback)
{
	m_KeyReleasedDelegates[key] = callback;

	auto keyDownDelegate = m_KeyPressedDelegates.find(key);
	if (keyDownDelegate == m_KeyPressedDelegates.end())
	{
		m_KeyPressedDelegates[key] = nullptr;
	}

	m_KeyPressedToggles[key] = false;
}

void InputManager::Update(void)
{
	if (Gamepad::Gamepads->Size)
	{
		m_Gamepad = Gamepad::Gamepads->GetAt(0);
	}

	if (IsLeftTriggerPressed())
		LeftTriggerPulled();
	if (IsRightTriggerPressed())
		RightTriggerPulled();

	UpdateMousePresses();
	UpdateKeyboard();
	UpdateGamepadLeftThumbstick();
	UpdateGamepadRightThumbstick();

	if (IsGamepadButtonDown(GamepadButtons::A))
		ButtonAPressed();
	if (IsGamepadButtonDown(GamepadButtons::B))
		ButtonBPressed();
	if (IsGamepadButtonDown(GamepadButtons::X))
		ButtonXPressed();
	if (IsGamepadButtonDown(GamepadButtons::Y))
		ButtonYPressed();

	if (IsGamepadButtonDown(GamepadButtons::DPadUp))
		ButtonDPadUpPressed();
	if (IsGamepadButtonDown(GamepadButtons::DPadDown))
		ButtonDPadDownPressed();
	if (IsGamepadButtonDown(GamepadButtons::DPadLeft))
		ButtonDPadLeftPressed();
	if (IsGamepadButtonDown(GamepadButtons::DPadRight))
		ButtonDPadRightPressed();

	if (IsGamepadButtonDown(GamepadButtons::LeftShoulder))
		ButtonLeftShoulderPressed();
	if (IsGamepadButtonDown(GamepadButtons::RightShoulder))
		ButtonRightShoulderPressed();

	if (IsGamepadButtonDown(GamepadButtons::LeftThumbstick))
		ButtonLeftStickPressed();
	if (IsGamepadButtonDown(GamepadButtons::RightThumbstick))
		ButtonRightStickPressed();
}

void InputManager::UpdateKeyboard(void)
{
	std::map<Windows::System::VirtualKey, Delegates::KeyPressed^>::iterator iterator = m_KeyPressedDelegates.begin();
	for (; iterator != m_KeyPressedDelegates.end(); iterator++)
	{
		if (this->IsButtonDown(iterator->first))
		{
			m_KeyPressedToggles[iterator->first] = true;
			if (iterator->second != nullptr)
			{
				iterator->second->Invoke();
			}
		}
		else
		{
			if (m_KeyPressedToggles[iterator->first])
			{
				auto releasedCallback = m_KeyReleasedDelegates.find(iterator->first);
				if ((releasedCallback != m_KeyReleasedDelegates.end()) && (releasedCallback->second != nullptr))
				{
					releasedCallback->second->Invoke();
				}
				m_KeyPressedToggles[iterator->first] = false;
			}
		}
	}
}
void InputManager::UpdateMousePresses(void)
{
	if (this->IsButtonDown(Windows::System::VirtualKey::LeftButton))
	{
		m_KeyPressedToggles[Windows::System::VirtualKey::LeftButton] = true;
		LeftMouseButtonDown();
	}
	if (this->IsButtonDown(Windows::System::VirtualKey::RightButton))
	{
		m_KeyPressedToggles[Windows::System::VirtualKey::RightButton] = true;
		RightMouseButtonDown();
	}
	if (this->IsButtonReleased(Windows::System::VirtualKey::LeftButton))
	{
		LeftMouseButtonUp();
		m_KeyPressedToggles[Windows::System::VirtualKey::LeftButton] = false;
	}
	if (this->IsButtonReleased(Windows::System::VirtualKey::RightButton))
	{
		RightMouseButtonUp();
		m_KeyPressedToggles[Windows::System::VirtualKey::RightButton] = false;
	}
}
void InputManager::UpdateGamepadLeftThumbstick(void)
{
	if (m_Gamepad)
	{
		float X = m_Gamepad->GetCurrentReading().LeftThumbstickX;
		float Y = m_Gamepad->GetCurrentReading().LeftThumbstickY;

		const float deadzoneRadius = 0.3;
		const float deadzoneSquared = deadzoneRadius * deadzoneRadius;

		float adjacentSquared = X * X;
		float oppositeSquared = Y * Y;

		if ((oppositeSquared + adjacentSquared) > deadzoneSquared)
			LeftStickMoved(X, Y);
		else
			LeftStickMoved(0.0f, 0.0f);
	}
	else
	{
		LeftStickMoved(0.0f, 0.0f);
	}
}
void InputManager::UpdateGamepadRightThumbstick(void)
{
	if (m_Gamepad)
	{
		float X = m_Gamepad->GetCurrentReading().RightThumbstickX;
		float Y = m_Gamepad->GetCurrentReading().RightThumbstickY;

		const float deadzoneRadius = 0.3;
		const float deadzoneSquared = deadzoneRadius * deadzoneRadius;

		float adjacentSquared = X * X;
		float oppositeSquared = Y * Y;

		if ((oppositeSquared + adjacentSquared) > deadzoneSquared)
			RightStickMoved(X, Y);
		else
			RightStickMoved(0.0f, 0.0f);
	}
	else
	{
		RightStickMoved(0.0f, 0.0f);
	}
}
void InputManager::UpdateMouseMovement(MouseDevice^ sender, MouseEventArgs^ args)
{
	MouseMoved(args->MouseDelta.X, args->MouseDelta.Y);
}

bool InputManager::IsLeftTriggerPressed(void)
{
	return m_Gamepad ? (((float)m_Gamepad->GetCurrentReading().LeftTrigger) >= m_LeftTriggerDeadzone) : false;
}
bool InputManager::IsRightTriggerPressed(void)
{
	return m_Gamepad ? (((float)m_Gamepad->GetCurrentReading().RightTrigger) >= m_RightTriggerDeadzone) : false;
}
bool InputManager::IsGamepadButtonDown(GamepadButtons button)
{
	return m_Gamepad ? (button == (m_Gamepad->GetCurrentReading().Buttons & button)) : false;
}
bool InputManager::IsGamepadButtonReleased(GamepadButtons button)
{
	return m_Gamepad ? (GamepadButtons::None == (m_Gamepad->GetCurrentReading().Buttons & button)) : false;

}
bool InputManager::IsButtonDown(Windows::System::VirtualKey key)
{
	return ((Windows::UI::Core::CoreWindow::GetForCurrentThread()->GetAsyncKeyState(key) & Windows::UI::Core::CoreVirtualKeyStates::Down) == Windows::UI::Core::CoreVirtualKeyStates::Down);
}
bool InputManager::IsButtonReleased(Windows::System::VirtualKey key)
{
	if (m_KeyPressedToggles[key])
	{
		return !((Windows::UI::Core::CoreWindow::GetForCurrentThread()->GetAsyncKeyState(key) & Windows::UI::Core::CoreVirtualKeyStates::Down) == Windows::UI::Core::CoreVirtualKeyStates::Down);
	}
}
