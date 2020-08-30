//Please don't remove credits
//Credits : Nima Bastani
//Github : https://github.com/NimaBastani/SA-MP-Android

#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "settings.h"
#include "customname.h"
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


CCustomNameWindow::CCustomNameWindow()
{
	m_bIsActive = false;
	m_bFixer = false;
	m_bFixer2 = false;
	m_bLamb = false;
}

CCustomNameWindow::~CCustomNameWindow()
{

}

void CCustomNameWindow::Show(bool bShow)
{
	m_bIsActive = bShow;
	m_bFixer = false;
}

void CCustomNameWindow::Clear()
{
	m_bIsActive = false;
	m_bFixer = false;

}

void CCustomNameWindow::Render()
{
	if(!m_bIsActive) return;
	ImGuiIO &io = ImGui::GetIO();

	ImGui::GetStyle().ButtonTextAlign = ImVec2(0.5f, 0.5f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin(" ", nullptr,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);
		ImGui::Text("You are connecting as %s", pSettings->Get().szNickName);
		if (ImGui::Button("Connect", ImVec2(125, 50)))
		{
			const auto encryptedAddress = cryptor::create("192.168.1.50", 12); unsigned short port = 7777;
			pNetGame = new CNetGame(encryptedAddress.decrypt(), port, pSettings->Get().szNickName, pSettings->Get().szPassword);
			Show(false);
			if (pGame)
				pGame->FindPlayerPed()->TogglePlayerControllable(true);
		}
		char pNewname[24] = "";
		ImGui::ItemSize(ImVec2(0, pGUI->GetFontSize() / 2 + 5));
		if (ImGui::Button("Change Name", ImVec2(125, 50)))
		{
			ImGui::InputText("Name", pNewname, sizeof(pNewname));
			if (ImGui::Button("Change & Connect", ImVec2(125, 50)))
			{
				const auto encryptedAddress = cryptor::create("192.168.1.50", 12); unsigned short port = 7777;
				pNetGame = new CNetGame(encryptedAddress.decrypt(), port, pNewname, pSettings->Get().szPassword);
				Show(false);
				if (pGame)
					pGame->FindPlayerPed()->TogglePlayerControllable(true);
			}
		}

		ImGui::ItemSize(ImVec2(0, pGUI->GetFontSize() / 2 + 5));
		
    ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}
