//===========================================================
//
// �֗��֐�[utility.cpp]
// Author �匴�叫
//
//===========================================================
#include "utility.h"
#include "object2D.h"

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

//===========================================================
// �|���S���̊g��
//===========================================================
void CUtility::Enlarge(CObject2D * pObj, float fHei, float fWid)
{
	// �`�悳����
	pObj->SetDraw(true);

	// ���ƍ����擾
	float fHeight = pObj->GetHeight();
	float fWidth = pObj->GetWidth();

	fHeight = fHeight + fHei;
	fWidth = fWidth + fWid;

	// �T�C�Y�ݒ�
	pObj->SetSize(fWidth, fHeight);
}

//===========================================================
// �|���S���̏k��
//===========================================================
void CUtility::Shrink(CObject2D * pObj, float fHei, float fWid)
{
	// ���ƍ����擾
	float fHeight = pObj->GetHeight();
	float fWidth = pObj->GetWidth();

	fHeight = fHeight - fHei;
	fWidth = fWidth - fWid;

	// �T�C�Y�ݒ�
	pObj->SetSize(fWidth, fHeight);
	pObj->SetSize(fWidth, fHeight);
}

//===========================================================
// �|���S���̐F
//===========================================================
void CUtility::Color_A2D(CObject2D * pObj, float fValue)
{
	// �����x�擾
	float fColor_a = pObj->GetColor().a;

	fColor_a = fColor_a + fValue;

	// �F�ݒ�
	pObj->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fColor_a));
}
