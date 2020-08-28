#pragma once
#include "Tables.h"
#include "../Engine/EnginePrediction.h"

bool __stdcall hkCreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	bool bReturn = HookTables::pCreateMove->GetTrampoline()(flInputSampleTime, pCmd);

	if (CGlobal::IsGameReady && pCmd->command_number != 0 && !CGlobal::FullUpdateCheck)
	{
		CGlobal::GViewAngle = pCmd->viewangles;
		CGlobal::UserCmd = pCmd;
		CGlobal::LocalPlayer = (CBaseEntity*)I::EntityList()->GetClientEntity(I::Engine()->GetLocalPlayer());

		if (bReturn)
			I::Prediction()->SetLocalViewangles(Vector(pCmd->viewangles.x, pCmd->viewangles.y, pCmd->viewangles.z));

		if (GP_EntPlayers)
			GP_EntPlayers->Update();

		if (GP_Esp)
			if (GP_Esp->GranadePrediction)
				grenade_prediction::Get().Tick(pCmd->buttons);

		DWORD* FirstP;
		__asm mov FirstP, ebp;
		CGlobal::bSendPacket = true;

		if (CGlobal::IsGuiVisible)
			pCmd->buttons &= ~IN_ATTACK;
		else if (GP_Skins && !CGlobal::IsGuiVisible)
			GP_Skins->SelectedWeapon = CGlobal::GetWeaponId();

		if (GP_LegitAim)
		{
			GP_LegitAim->SetSelectedWeapon();

			if (GP_LegitAim->Enable)
				GP_LegitAim->CreateMove(CGlobal::bSendPacket, flInputSampleTime, pCmd);

			if (GP_LegitAim->TriggerEnable)
				GP_LegitAim->TriggerCreateMove(pCmd);
		}

		if (GP_Misc)
			GP_Misc->CreateMove(CGlobal::bSendPacket, flInputSampleTime, pCmd);

		EnginePrediction::Run(pCmd);
		{
			if (GP_LegitAim)
				GP_LegitAim->BacktrackCreateMoveEP(pCmd);

			if (GP_Misc)
				GP_Misc->CreateMoveEP(pCmd, CGlobal::bSendPacket);

			if (GP_Misc && std::fabsf(CGlobal::LocalPlayer->GetSpawnTime() - I::GlobalVars()->curtime) > 1.0f)
				GP_Misc->Desync(pCmd, CGlobal::bSendPacket);
		}
		EnginePrediction::End();

		CGlobal::ClampAngles(pCmd->viewangles);
		CGlobal::AngleNormalize(pCmd->viewangles);
		*(bool*)(*FirstP - 0x1C) = CGlobal::bSendPacket;

		if (!CGlobal::bSendPacket)
			return false;
	}

	return bReturn;
}