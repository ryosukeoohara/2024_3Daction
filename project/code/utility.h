//===========================================================
//
// �֗��֐�[utility.h]
// Author �匴�叫
//
//===========================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "main.h"

class CObject2D;

//�^�C�g���N���X
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
	void Enlarge(CObject2D *pObj, float fHei, float fWid);  // �|���S�����g��
	void Shrink(CObject2D *pObj, float fHei, float fWid);   // �|���S����������
	void Color_A2D(CObject2D *pObj, float fValue);            // �|���S���̐F

private:
	

};

#endif // !_TITLE_H_