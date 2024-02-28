//===========================================================
//
// 便利関数[utility.h]
// Author 大原怜将
//
//===========================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "main.h"

class CObject2D;

//タイトルクラス
class CUtility
{
public:
	CUtility();
	~CUtility();

	static CUtility *Create(void);

	float MoveToPosition(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos, float fMyRotY);
	float CorrectAngle(float fAngle);
	D3DXVECTOR3 Distance(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos);
	int Nearest(D3DXVECTOR3 MyPos, D3DXVECTOR3 TargetPos); 
	void Enlarge(CObject2D *pObj, float fHei, float fWid);  // ポリゴンを拡大
	void Shrink(CObject2D *pObj, float fHei, float fWid);   // ポリゴンを小さく
	void Color_A2D(CObject2D *pObj, float fValue);            // ポリゴンの色

private:
	

};

#endif // !_TITLE_H_