//===========================================================
//
// �G�o�ꎞ��UI[appearanceUI.cpp]
// Author �匴�叫
//
//===========================================================
#include "appearanceUI.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"

namespace
{
	const char *TEXTURENAME[CAppearanceUI::TYPE_MAX] =
	{
		"",
		"data\\TEXTURE\\underling.png", // �U�R
		"data\\TEXTURE\\ishii.png",     // �{�X
	};  // �e�N�X�`���̖��O
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAppearanceUI::CAppearanceUI()
{
	// ������
	m_type = TYPE_NONE;
	m_pFrontObj2D = nullptr;
	m_pBackObj2D = nullptr;
}

//===========================================================
// �R���X�g���N�^
//===========================================================
CAppearanceUI::CAppearanceUI(TYPE type)
{
	// ������
	m_type = type;
	m_pFrontObj2D = nullptr;
	m_pBackObj2D = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CAppearanceUI::~CAppearanceUI()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CAppearanceUI::Init(void)
{
	// ���ꂼ�ꐶ�����āA�ʒu�A�T�C�Y�A�e�N�X�`���A�`���Ԃ�ݒ�
	if (m_pBackObj2D == nullptr)
	{
		m_pBackObj2D = CObject2D::Create();
		m_pBackObj2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pBackObj2D->SetSize(0.0f, 0.0f);
		m_pBackObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
		m_pBackObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
		m_pBackObj2D->SetDraw(false);
	}

	if (m_pFrontObj2D == nullptr)
	{
		m_pFrontObj2D = CObject2D::Create();
		m_pFrontObj2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pFrontObj2D->SetSize(1200.0f, 600.0f);
		m_pFrontObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
		m_pFrontObj2D->SetDraw();
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CAppearanceUI::Uninit(void)
{
	// �j��
	if (m_pFrontObj2D != nullptr)
	{
		m_pFrontObj2D->Uninit();
		m_pFrontObj2D = nullptr;
	}

	if (m_pBackObj2D != nullptr)
	{
		m_pBackObj2D->Uninit();
		m_pBackObj2D = nullptr;
	}

	Release();
}

//===========================================================
// �X�V����
//===========================================================
void CAppearanceUI::Update(void)
{
	if (m_pFrontObj2D != nullptr && m_pBackObj2D != nullptr)
	{// �O�ƌ�뗼���g�p���Ă�����

		// ���ƍ����擾
		float fHeight = m_pFrontObj2D->GetHeight();
		float fWidth = m_pFrontObj2D->GetWidth();

		if (m_pFrontObj2D->GetHeight() >= 100.0f && m_pFrontObj2D->GetWidth() >= 30.0f)
		{// ���̐��l�ȉ��ɂȂ�܂ŏ���������

			fHeight = fHeight - 25.0f;
			fWidth = fWidth - 50.0f;

			// �T�C�Y�ݒ�
			m_pFrontObj2D->SetSize(fWidth, fHeight);
			m_pBackObj2D->SetSize(fWidth, fHeight);
		}
		else
		{// �������Ȃ���

			// �`�悳����
			m_pBackObj2D->SetDraw(true);

			// ���ƍ����擾
			float fHeight = m_pBackObj2D->GetHeight();
			float fWidth = m_pBackObj2D->GetWidth();

			fHeight = fHeight + 5.0f;
			fWidth = fWidth + 10.0f;

			// �����x�擾
			float fColor_a = m_pBackObj2D->GetColor().a;

			fColor_a = fColor_a - 0.03f;

			// �T�C�Y�ݒ�
			m_pBackObj2D->SetSize(fWidth, fHeight);

			// �F�ݒ�
			m_pBackObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fColor_a));
		}

		if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
		{
			D3DXVECTOR3 pos = m_pFrontObj2D->GetPosition();

			pos.x = pos.x + 20.0f;

			m_pFrontObj2D->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));

			// �T�C�Y�ݒ�
			m_pFrontObj2D->SetSize(fWidth, fHeight);

			if (pos.x >= 1500.0f)
			{
				Uninit();
			}
		}
	}
}

//===========================================================
// �`�揈��
//===========================================================
void CAppearanceUI::Draw(void)
{

}

//===========================================================
// ��������
//===========================================================
CAppearanceUI * CAppearanceUI::Create(TYPE type)
{
	CAppearanceUI *pAppearUI = nullptr;
	pAppearUI = new CAppearanceUI(type);

	if (pAppearUI != nullptr)
	{
		pAppearUI->Init();
	}

	return pAppearUI;
}
