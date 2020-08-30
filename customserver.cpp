//Please don't remove credits
//Credits : Nima Bastani
//Github : https://github.com/NimaBastani/SA-MP-Android

#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "settings.h"
#include "customserver.h"
#include "chatwindow.h"
#include "vendor/inih/cpp/INIReader.h"
#include "str_obfuscator_no_template.hpp"

#include <string.h>
#include <stdlib.h>

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CChatWindow *pChatWindow;
extern CSettings *pSettings;


CCustomServerWindow::CCustomServerWindow()
{
	m_bIsActive = false;
	m_bFixer = false;
	m_bFixer2 = false;
	m_bLamb = false;
}

CCustomServerWindow::~CCustomServerWindow()
{

}

void CCustomServerWindow::Show(bool bShow)
{
	m_bIsActive = bShow;
	m_bFixer = false;
}

void CCustomServerWindow::Clear()
{
	m_bIsActive = false;
	m_bFixer = false;
}

void CCustomServerWindow::Render()
{
	if(!m_bIsActive) return;
	ImGuiIO &io = ImGui::GetIO();

	ImGui::GetStyle().ButtonTextAlign = ImVec2(0.5f, 0.5f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin(" ", nullptr,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);
		ImGui::Text("You are connecting as %s", pSettings->Get().szNickName);
		char* svip;
		ImGui::InputText("IP", svip, sizeof(svip));
		char* svport;
		ImGui::InputText("Port", svport, sizeof(svport));
		if(ImGui::Button("Connect", ImVec2(125, 50)))
		{
			const auto encryptedAddress = cryptor::create(svip, sizeof(svip)); unsigned short port = atoi(svport); // why did I add this? 
			
			pNetGame = new CNetGame(encryptedAddress.decrypt(), port, pSettings->Get().szNickName, pSettings->Get().szPassword);
			Show(false);

			if(pGame)
	        	pGame->FindPlayerPed()->TogglePlayerControllable(true);
		}
		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
		
    ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}
