//===========================================================
//
//  �e�N�X�`���A�j���[�V����[animation.cpp]
// Author �匴�叫
//
//===========================================================

#include "animation.h"

//===========================================================
// �R���X�g���N�^
//===========================================================
CAnimation::CAnimation()
{
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.type = TYPE_NONE;
	m_Info.nLife = 0;
	m_Info.fRadius = 0.0f;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAnimation::CAnimation(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, TYPE type)
{
	m_Info.pos = pos;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = col;
	m_Info.type = type;
	m_Info.nLife = 0;
	m_Info.fRadius = fRadius;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CAnimation::~CAnimation()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CAnimation::Init(void)
{
	CBillBoard::Init();

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CAnimation::Uninit(void)
{
	CBillBoard::Uninit();
}

//===========================================================
// �X�V����
//===========================================================
void CAnimation::Update(void)
{
	CBillBoard::Update();
}

//===========================================================
// �`�揈��
//===========================================================
void CAnimation::Draw(void)
{
	CBillBoard::Draw();
}

//===========================================================
// ����
//===========================================================
CAnimation * CAnimation::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, TYPE type)
{
	CAnimation *pAnim = nullptr;
	pAnim = new CAnimation;

	if (pAnim != nullptr)
	{
		pAnim->Init();
		pAnim->SetPosition(pos);
		pAnim->SetSize(fRadius, fRadius);
		pAnim->SetColor(col);
	}

	return pAnim;
}
