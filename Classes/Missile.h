#pragma once

/*
	Missile
	�̻����� ǥ���ϴ� Ŭ����. 
	�ɼ��� �־� ������ �Ʊ��� �̻����� �����ؼ� ������ �� �ֵ��� �ؾ��� �� ����.
*/

class Missile
{
public : 
	Missile();
	~Missile();

private :

	void init();

	CImage* m_pSprite;
	CImage* m_pShapeSprite;
};