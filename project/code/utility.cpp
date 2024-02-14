//===========================================================
//
// �֗��֐�[utility.cpp]
// Author �匴�叫
//
//===========================================================

#include "utility.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CUtility::CUtility()
{
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CUtility::~CUtility()
{
}

//===========================================================
// ����
//===========================================================
CUtility * CUtility::Create(void)
{
	CUtility *pUtility = nullptr;
	pUtility = new CUtility;

	return pUtility;
}

//===========================================================
// �ǔ�
//===========================================================
float CUtility::MoveToPosition(D3DXVECTOR3  MyPos, D3DXVECTOR3  TargetPos, float fMyRotY)
{
	D3DXVECTOR3 fDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fDiffmove = 0.0f, fDestmove = 0.0f;

	fDest = MyPos - TargetPos;

	fDestmove = atan2f(fDest.x, fDest.z);
	fDiffmove = fDestmove - fMyRotY;

	return fDiffmove;
}

//===========================================================
// �p�x�␳
//===========================================================
float CUtility::CorrectAngle(float fAngle)
{
	if (fAngle >= D3DX_PI)
	{
		fAngle = -D3DX_PI;
	}
	else if (fAngle <= -D3DX_PI)
	{
		fAngle = D3DX_PI;
	}

	return fAngle;
}

//===========================================================
// ��������
//===========================================================
D3DXVECTOR3 CUtility::Distance(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos)
{
	D3DXVECTOR3 Dest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	Dest = MyPos - TargetPos;

	if (Dest.x < 0.0f)
	{
		Dest.x *= -1;
	}

	if (Dest.y < 0.0f)
	{
		Dest.y *= -1;
	}

	if (Dest.z < 0.0f)
	{
		Dest.z *= -1;
	}

	return Dest;
}

//===========================================================
// ��������
//===========================================================
int CUtility::Nearest(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos)
{
	return 0;
}
