//===========================================================
//
// 便利関数[utility.h]
// Author 大原怜将
//
//===========================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "main.h"

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

private:
	

};

#endif // !_TITLE_H_