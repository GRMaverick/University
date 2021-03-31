#pragma once

#include <iostream>
#include <Windows.h>

inline void DebugString(const char* _text)
{
#ifdef _DEBUG
	std::cout << "[DIRECTX SCENE] [DEBUG] " << _text << std::endl;
#endif
}
inline void DebugString(std::string _text)
{
#ifdef _DEBUG
	std::cout << "[DIRECTX SCENE] [DEBUG] " << _text.c_str() << std::endl;
#endif
}
inline void DebugString(char* file, char* line, std::string message)
{
#ifdef _DEBUG
	std::cout << file << ": " << line << ": " << message.c_str() << std::endl;
#endif
}