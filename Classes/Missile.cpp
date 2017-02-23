#include "stdafx.h"
#include "Missile.h"


Missile::Missile()
{
	m_pSprite = new CImage;
	init();
}

void Missile::init()
{

}

Missile::~Missile()
{
	delete m_pSprite;
}