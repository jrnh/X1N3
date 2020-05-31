#pragma once
#include "Include/Headers.h"
#include "Include/Def.h"
#include "Engine/SDK/Color.hpp"

class IIStart
{
public:
	virtual class IStart
	{
	public:
		virtual void Start(HINSTANCE hinstDLL) = 0;
	};
};

class CMain
{
public:

	SDK::Color BackgroundColor = SDK::Color(18, 18, 22, 255);
	SDK::Color TitleColor = SDK::Color(112, 112, 116, 255);
	SDK::Color TextColor = SDK::Color(255, 255, 255, 255);
	SDK::Color FrameColor = SDK::Color(34, 35, 37, 255);
	SDK::Color ButtonColor = SDK::Color(128, 135, 140, 255);
	SDK::Color DisableButtonColor = SDK::Color(225, 20, 20, 255);
	SDK::Color LineColor = SDK::Color(120, 121, 123, 255);

	int MenuButton = VK_INSERT;

	string HintMsg = "";

	void SetMenuColors();

	static CMain& Singleton()
	{
		static CMain pObject;
		return pObject;
	}
};

CMain& MainSettings();