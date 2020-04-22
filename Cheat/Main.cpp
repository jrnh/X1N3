#include "Main.h"
#include "X1API/ThreadInMemory.h"
#include "Initialize/Initialize.h"
#include "GUI/Gui.h"
#include <thread>

DWORD WINAPI SetupThread(LPVOID lpThreadParameter)
{
	VMP_ULTRA("SetupThread");
	auto LSetupThread = [&]() -> DWORD
	{
		ADD_LOG("2-1-0\n");
		ADD_LOG("======================Setup: Started\n");
		ADD_LOG("2-1-1\n");
		CInit::IInit* pInit = new CInit::IInit();
		pInit->Init();
		DELETE_PTR(pInit);
		ADD_LOG("2-1-2\n");
		ADD_LOG("======================Setup: Successful\n");
		return 0;
	};

	return LSetupThread();
	VMP_END;
}

void Start()
{
	ADD_LOG("2-0\n");
	auto LStatr = [&]() -> void
	{
		ADD_LOG("2-1\n");
		FastCall::G().t_CreateThread(NULL, 0, &SetupThread, NULL, 0, NULL);
	};
	ADD_LOG("2-2\n");
	LStatr();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		VMP_ULTRA("DllMain");

		auto LDllMain = [&]() -> void
		{
#ifdef ENABLE_CONSOLE_LOG
			AllocConsole();
			AttachConsole(FastCall::G().t_GetCurrentProcessId());
			freopen("CONOUT$", "w", stdout);

			ADD_LOG("DLL ATTACH\n");
			ADD_LOG("DLL BUILD: %s | %s\n", __TIME__, __DATE__);
#endif
			ADD_LOG("1\n");
			Start();
			ADD_LOG("2\n");
		};
		LDllMain();

		VMP_END;
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		GP_Setup->Shutdown();
		DELETE_PTR(GP_Setup);

		ADD_LOG("DLL DETACH\n");
	}
	return TRUE;
}

CMain& MainSettings()
{
	return CMain::Singleton();
}

void CMain::SetMenuColors()
{
	GuiStyle& style = X1Gui().GetStyle();

	auto AutoChagngeColor = [&](Color col, float ch) -> Color
	{
		Color entry;

		entry.SetR(((col.r() + ch < 0) ? 0 : ((col.r() + ch > 255) ? 255 : (col.r() + ch))));
		entry.SetG(((col.g() + ch < 0) ? 0 : ((col.g() + ch > 255) ? 255 : (col.g() + ch))));
		entry.SetB(((col.b() + ch < 0) ? 0 : ((col.b() + ch > 255) ? 255 : (col.b() + ch))));
		entry.SetA(col.a());

		return entry;
	};

	style.clrLine = LineColor;
	style.clrBackground = BackgroundColor;
	style.clrText = TextColor;

	style.clrFrame = FrameColor;
	style.clrFrameHover = AutoChagngeColor(FrameColor, -5);
	style.clrFrameHold = AutoChagngeColor(FrameColor, -9);

	style.clrTabLabel = color_t(ButtonColor.r(), ButtonColor.g(), ButtonColor.b(), 120);
	style.clrTabLabelText = color_t(TextColor.r(), TextColor.g(), TextColor.b(), 160);

	style.clrButton = ButtonColor;
	style.clrButtonHover = AutoChagngeColor(ButtonColor, -10);
	style.clrButtonHold = AutoChagngeColor(ButtonColor, -20);

	style.clrDisButton = DisableButtonColor;
	style.clrDisButtonHover = AutoChagngeColor(DisableButtonColor, -10);
	style.clrDisButtonHold = AutoChagngeColor(DisableButtonColor, -20);

	style.clrScroll = AutoChagngeColor(ButtonColor, -20);
	style.clrScrollHover = AutoChagngeColor(ButtonColor, -20);
	style.clrScrollHold = AutoChagngeColor(ButtonColor, -20);
	style.clrTitle = TitleColor;
}