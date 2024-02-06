//===========================================================
//
// 便利関数[utility.cpp]
// Author 大原怜将
//
//===========================================================

#include "utility.h"

//===========================================================
// コンストラクタ
//===========================================================
CUtility::CUtility()
{
}

//===========================================================
// デストラクタ
//===========================================================
CUtility::~CUtility()
{
}

//===========================================================
// 生成
//===========================================================
CUtility * CUtility::Create(void)
{
	CUtility *pUtility = nullptr;
	pUtility = new CUtility;

	return pUtility;
}

//===========================================================
// 追尾
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
// 角度補正
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
// 距離測定
//===========================================================
D3DXVECTOR3 CUtility::Distance(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos)
{
	D3DXVECTOR3 Dest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	Dest = MyPos - TargetPos;

	return Dest;
}
