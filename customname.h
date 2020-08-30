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