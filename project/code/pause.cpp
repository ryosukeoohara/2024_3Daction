//===========================================================
//
//�|�[�Y����[pause.cpp]
//Author �匴�叫
//
//===========================================================
#include "pause.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "game.h"

// �������O��Ԃ��`
namespace 
{
	const D3DXVECTOR3 TEXPOS[3] =   // �ʒu
	{
		D3DXVECTOR3(640.0f, 350.0f, 0.0f),
		D3DXVECTOR3(640.0f, 500.0f, 0.0f),
		D3DXVECTOR3(640.0f, 650.0f, 0.0f),
	};

	const D3DXVECTOR2 TEXSIZE = { 130.0f, 45.0f };  // �T�C�Y
}

//===========================================================
// �e�N�X�`���̂����O
//===========================================================
const char *CPause::m_apTexName[TYPE_MAX] =
{
	"data\\TEXTURE\\pause000.png",     // ������
	"data\\TEXTURE\\pause001.png",     // ��蒼��
	"data\\TEXTURE\\pause002.png",     // �^�C�g����ʂɖ߂�
	"data\\TEXTURE\\iron000.jpg",      // �����w�i
	"data\\TEXTURE\\pause_bg000.png",  // �g
};

//===========================================================
// �R���X�g���N�^
//===========================================================
CPause::CPause()
{
	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		m_aMenu[nCount].Object2D = nullptr;
		m_aMenu[nCount].col = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	}

	m_pBg = nullptr;
	m_pFrame = nullptr;
}

//===========================================================
// �f�X�g���N�^
//===========================================================
CPause::~CPause()
{

}

//===========================================================
// ����������
//===========================================================
HRESULT CPause::Init(void)
{
	if (m_pBg == nullptr)
	{
		m_pBg = CObject2D::Create();
		m_pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[TYPE_BACK]));
		m_pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pBg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_pBg->SetDraw(false);
	}

	if (m_pFrame == nullptr)
	{
		m_pFrame = CObject2D::Create();
		m_pFrame->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[TYPE_FRAME]));
		m_pFrame->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pFrame->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		m_pFrame->SetDraw(false);
	}

	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_aMenu[nCount].Object2D == nullptr)
		{
			m_aMenu[nCount].Object2D = CObject2D::Create();
			m_aMenu[nCount].Object2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[nCount]));
			m_aMenu[nCount].Object2D->SetPosition(D3DXVECTOR3(640.0f, 250.0f + nCount * 150.0f, 0.0f));
			m_aMenu[nCount].Object2D->SetSize(TEXSIZE.x, TEXSIZE.y);
			m_aMenu[nCount].Object2D->SetDraw(false);
		}
	}

	return S_OK;
}

//===========================================================
// �I������
//===========================================================
void CPause::Uninit(void)
{
	
}

//===========================================================
// �X�V����
//===========================================================
void CPause::Update(void)
{
	
}

//===========================================================
// �`�揈��
//===========================================================
void CPause::Draw(void)
{
	
}

//===========================================================
// ��������
//===========================================================
CPause * CPause::Create(void)
{
	// �|�[�Y�̃|�C���^
	CPause *pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{//	�g�p����Ă�����

		// ����������
		pPause->Init();
	}
	else
	{// �g�p����Ă��Ȃ�������null��Ԃ�

		return nullptr;
	}

	return pPause;
}

//===========================================================
// �`�悷�邩�ǂ���
//===========================================================
void CPause::SetDraw(bool bPause)
{
	if (m_pBg != nullptr)
	{
		m_pBg->SetDraw(bPause);
	}

	if (m_pFrame != nullptr)
	{
		m_pFrame->SetDraw(bPause);
	}

	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_aMenu[nCount].Object2D != nullptr)
		{
			m_aMenu[nCount].Object2D->SetDraw(bPause);
		}
	}
}