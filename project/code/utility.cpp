//===========================================================
//
// 便利関数[utility.cpp]
// Author 大原怜将
//
//===========================================================
#include "utility.h"
#include "object2D.h"

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
// 距離測定
//===========================================================
int CUtility::Nearest(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos)
{
	return 0;
}

//===========================================================
// ポリゴンの拡大
//===========================================================
void CUtility::Enlarge(CObject2D * pObj, float fHei, float fWid)
{
	// 描画させる
	pObj->SetDraw(true);

	// 幅と高さ取得
	float fHeight = pObj->GetHeight();
	float fWidth = pObj->GetWidth();

	fHeight = fHeight + fHei;
	fWidth = fWidth + fWid;

	// サイズ設定
	pObj->SetSize(fWidth, fHeight);
}

//===========================================================
// ポリゴンの縮小
//===========================================================
void CUtility::Shrink(CObject2D * pObj, float fHei, float fWid)
{
	// 幅と高さ取得
	float fHeight = pObj->GetHeight();
	float fWidth = pObj->GetWidth();

	fHeight = fHeight - fHei;
	fWidth = fWidth - fWid;

	// サイズ設定
	pObj->SetSize(fWidth, fHeight);
	pObj->SetSize(fWidth, fHeight);
}

//===========================================================
// ポリゴンの色
//===========================================================
void CUtility::Color_A2D(CObject2D * pObj, float fValue)
{
	// 透明度取得
	float fColor_a = pObj->GetColor().a;

	fColor_a = fColor_a + fValue;

	// 色設定
	pObj->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fColor_a));
}
