//===========================================================
//
// �����ȃQ�[�W����[gage.cpp]
// Author �匴�叫
//
//===========================================================
#include "gage.h"
#include "game.h"
#include "player.h"

namespace
{
	const D3DXCOLOR GAGECOL[2] =
	{
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),
		D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
	};
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CGage2D::CGage2D()
{
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_Type = TYPE_NONE;
	m_pObject2D = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CGage2D::~CGage2D()
{

}

//===========================================================
// ��������
//===========================================================
CGage2D * CGage2D::Create(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE2DTYPE type)
{
	CGage2D *pGage = nullptr;
	pGage = new CGage2D;

	if (pGage != nullptr)
	{
		pGage->Init(pos, fHei, fWid, type);
		pGage->SetCol();
	}

	return pGage;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage2D::Init(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE2DTYPE type)
{
	m_Type = type;

	if (m_pObject2D == nullptr)
	{
		m_pObject2D = CObject2D::Create();
		m_pObject2D->SetPosition(pos);
		m_pObject2D->SetEdgeCenter(fWid, fHei);
		m_pObject2D->SetDraw(true);
	}
	
	return S_OK;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage2D::Init(void)
{
	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CGage2D::Uninit(void)
{
	CObject::Release();
}

//===========================================================
// �X�V����
//===========================================================
void CGage2D::Update(void)
{

}

//===========================================================
// �`�揈��
//===========================================================
void CGage2D::Draw(void)
{

}

//===========================================================
// ��ނ��Ƃ̐F�ݒ�
//===========================================================
void CGage2D::SetCol(void)
{
	switch (m_Type)
	{
	case CGage2D::TYPE_NONE:
		m_pObject2D->SetColor(GAGECOL[TYPE_NONE]);
		break;

	case CGage2D::TYPE_LIFE:
		m_pObject2D->SetColor(GAGECOL[TYPE_LIFE]);
		break;

	case CGage2D::TYPE_MAX:

		break;

	default:
		break;
	}
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CGage3D::CGage3D()
{
	// �l���N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_Type = TYPE_NONE;
	m_pBillBoard = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CGage3D::~CGage3D()
{

}

//===========================================================
// ��������
//===========================================================
CGage3D * CGage3D::Create(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE3DTYPE type)
{
	CGage3D *pGage = nullptr;
	pGage = new CGage3D;

	if (pGage != nullptr)
	{
		pGage->Init(pos, fHei, fWid, type);
		pGage->SetCol();
	}

	return pGage;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage3D::Init(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE3DTYPE type)
{
	m_Type = type;

	if (m_pBillBoard == nullptr)
	{
		m_pBillBoard = CBillBoard::Create();
		m_pBillBoard->SetPosition(pos);
		m_pBillBoard->SetSize(fHei, fWid);
		m_pBillBoard->SetDraw(true);
	}

	return S_OK;
}

//===========================================================
// ����������
//===========================================================
HRESULT CGage3D::Init(void)
{
	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CGage3D::Uninit(void)
{
	if (m_pBillBoard != nullptr)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = nullptr;
	}

	CObject::Release();
}

//===========================================================
// �X�V����
//===========================================================
void CGage3D::Update(void)
{
	SetMixPos();
}

//===========================================================
// �`�揈��
//===========================================================
void CGage3D::Draw(void)
{

}

//===========================================================
// ��ނ��Ƃ̐F�ݒ�
//===========================================================
void CGage3D::SetCol(void)
{
	switch (m_Type)
	{
	case CGage3D::TYPE_NONE:
		m_pBillBoard->SetColor(GAGECOL[TYPE_NONE]);
		break;

	case CGage3D::TYPE_STAMINA:
		m_pBillBoard->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.2f, 1.0f));
		break;

	case CGage3D::TYPE_MAX:

		break;

	default:
		break;
	}
}

void CGage3D::SetMixPos(void)
{
	if (m_pPos == nullptr)
	{
		return;
	}

	D3DXVECTOR3 pos = *m_pPos;

	pos.y += m_UpHeight;

	m_pBillBoard->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
}