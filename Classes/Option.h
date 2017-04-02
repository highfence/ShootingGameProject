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
	void Move(const _In_ Vec);
	void Launch();
	void MissileFly(const _In_ FLOAT);

private :

	void init();
	void InitialImgLoad();
	void MissileLoad();
	void MakeImageNextFrame();
	void AccTime(const _In_ FLOAT);
	void AdjustLaunchPos();
	OptionMissile* GetLaunchableMissile(const _In_ PLAYER::OPTION_COLOR);
	void MissileDraw(_Inout_ HDC);

	Vec m_Pos = Vec(0.f, 0.f);
	Vec m_SavePreviousPos = Vec(0.f, 0.f);
	Vec m_LaunchPos = Vec(0.f, 0.f);
	BOOL m_IsLaunchPosGoesToRight = FALSE;
	FLOAT m_Width = 0.f;
	FLOAT m_Height = 0.f;
	FLOAT m_AccTime = 0.f;
	FLOAT m_RecordRotateTime = 0.f;
	FLOAT m_RecordFireTime = 0.f;
	INT m_PowerTier = 1;
	INT m_FrameNum = 1;
	INT m_MaxFrameNum = 8;
	FLOAT m_TimePerFrame = 0.15f;
	CImage* m_pSprite = nullptr;
	CImage* m_pShadeSprite = nullptr;
	BOOL m_IsOptionActivated = FALSE;
	BOOL m_IsMissileRed = TRUE;
	Option* m_pNextOption = nullptr;

	std::vector<OptionMissile*> m_RedMissileVec;
	std::vector<OptionMissile*> m_BlueMissileVec;
};