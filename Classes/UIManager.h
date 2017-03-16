#pragma once

const INT maxNumberPos = 6;
class UIManager
{
public:
	static UIManager* GetInstance();
	void DeleteInstance();

	void CalProc(const _In_ FLOAT);
	void DrawProc(_Inout_ HDC);
	void PlusScore(const _In_ INT);

private:
	UIManager();
	~UIManager();

	// ΩÃ±€≈Ê ¿ŒΩ∫≈œΩ∫.
	static UIManager* m_pInstance;

	void Init();
	void DrawScore(_Inout_ HDC);
	void CalcScore();

	FLOAT m_AccTime;
	INT m_Score;
	BOOL m_IsScoreCalcNeeded;
	CImage* m_ScoreSpriteArr[maxNumberPos];
	CImage* m_ScoreShadeArr[maxNumberPos];
};