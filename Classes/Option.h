#pragma once

/* 전방선언 */
class OptionMissile;

class Option 
{
public :

	Option();
	~Option();

	void CalcProc(const _In_ FLOAT, const _In_ Vec);
	void DrawProc(_Inout_ HDC);
	void Activate(const _In_ Vec);
	void Deactivate();
	void SetNextOption(_In_ Option&);
	BOOL GetIsOptionActivated();
	void SettingForActivate(const _In_ Vec);

private :

	void init();
	void InitialImgLoad();
	void MissileLoad();
	void Move(const _In_ Vec);

	Vec m_Pos = Vec(0.f, 0.f);
	Vec m_SavePreviousPos = Vec(0.f, 0.f);
	FLOAT m_Width = 0.f;
	FLOAT m_Height = 0.f;
	FLOAT m_AccTime = 0.f;
	FLOAT m_RecordFireTime = 0.f;
	INT m_PowerTier = 1;
	INT m_FrameNum = 1;
	INT m_MaxFrameNum = 8;
	CImage* m_pSprite = nullptr;
	CImage* m_pShadeSprite = nullptr;
	BOOL m_IsOptionActivated = FALSE;
	Option* m_pNextOption = nullptr;

	std::vector<OptionMissile*> m_MissileVec;
};