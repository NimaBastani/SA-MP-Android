//Add RenderButton in gui.cpp
//Made By NimaBastani
#include "main.h"
#include "gui/gui.h"
#include "game/game.h"
#include "net/netgame.h"
#include "settings.h"
#include "dialog.h"
#include "spawnscreen.h"
#include "GButton.h"
#include "chatwindow.h"
#include "scoreboard.h"
#include "keyboard.h"
extern CGUI * pGUI;
extern CGame* pGame;
extern CNetGame* pNetGame;
extern CSettings* pSettings;
extern CDialogWindow* pDialogWindow;
extern CSpawnScreen* pSpawnScreen;
extern CChatWindow* pChatWindow;
extern CScoreBoard* pScoreBoard;
extern CKeyBoard* pKeyBoard;

CGButton::CGButton()
{
	p_GButtonTexture = (RwTexture*)LoadTextureFromDB("samp","gbutton");//huh ez yeah? add your designed gbutton to "samp"
}

CGButton::~CGButton()
{
}
void CGButton::RenderButton()
{
	//
	if(pDialogWindow->m_bIsActive || pScoreBoard->m_bToggle || pKeyBoard->IsOpen()) return;
	
	if(!pNetGame) return;
	
	ImGuiIO &io = ImGui::GetIO();
	
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0x00, 0x00, 0x00, 0x00).Value);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(0x00, 0x00, 0x00, 0x00).Value);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0x00, 0x00, 0x00, 0x00).Value);
	
	ImGuiStyle style;
	style.FrameBorderSize = ImGui::GetStyle().FrameBorderSize;
	ImGui::GetStyle().FrameBorderSize = 0.0f;
	
	ImGui::Begin("G-Button", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
	
	ImVec2 vecButSize_g = ImVec2(ImGui::GetFontSize() * 5+5.0f, ImGui::GetFontSize() * 5);
	
	CPlayerPed *pPlayerPed = pGame->FindPlayerPed();
	if(!pPlayerPed->IsInVehicle() && !pPlayerPed->IsAPassenger())
	{
		CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
		if(pVehiclePool)
		{
			uint16_t sNearestVehicleID = pVehiclePool->FindNearestToLocalPlayerPed();

			CVehicle *pVehicle = pVehiclePool->GetAt(sNearestVehicleID);
			if(pVehicle)
			{
				if(pVehicle->GetDistanceFromLocalPlayerPed() < 4.0f)
				{
					CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
					if(pPlayerPool)
					{
						CLocalPlayer *pLocalPlayer = pPlayerPool->GetLocalPlayer();
						if(pLocalPlayer)
						{
							if(!pLocalPlayer->IsSpectating())
							{
								if(ImGui::ImageButton((ImTextureID)p_GButtonTexture->raster, vecButSize_g))
								{
									pPlayerPed->EnterVehicle(pVehicle->m_dwGTAId, true);
									pLocalPlayer->SendEnterVehicleNotification(sNearestVehicleID, true);
								}
							}
						}
					}
				}
			}
		}
	}
	
	ImGui::SetWindowSize(ImVec2(-1, -1));
	
	ImGui::SetWindowPos(ImVec2(pGUI->ScaleX(1500), pGUI->ScaleY(345)));
	ImGui::End();
	
	ImGui::PopStyleColor(3);
	ImGui::GetStyle().FrameBorderSize = style.FrameBorderSize;
}
