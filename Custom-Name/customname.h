//Please don't remove credits
//Credits : Nima Bastani
//Github : https://github.com/NimaBastani/SA-MP-Android

#pragma once

class CCustomNameWindow
{
public:
	CCustomNameWindow();
	~CCustomNameWindow();

	void Render();
	void Clear();
	void Show(bool bShow);
	
public:
	bool				m_bIsActive;
	bool				m_bFixer;
	bool				m_bFixer2;
	bool 				m_bLamb;
};