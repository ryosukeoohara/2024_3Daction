//===========================================================
//
//�|���S�����o�����[title.cpp]
//Author �匴�叫
//
//===========================================================

//*==========================================================
//�C���N���[�h�t�@�C��
//*==========================================================
#include "title.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "field.h"

//===========================================================
//�R���X�g���N�^
//===========================================================
CTitle::CTitle()
{
	
}

//===========================================================
//�f�X�g���N�^
//===========================================================
CTitle::~CTitle()
{

}

//===========================================================
//����
//===========================================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CTitle;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
//����������
//===========================================================
HRESULT CTitle::Init(void)
{
	CField *pField = new CField;
	pField->Init();

	CObject2D *pBg = new CObject2D;
	pBg->Init();
	pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\taitoru.jpg"));
	pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pBg->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	pBg->SetDraw(true);

	return S_OK;
}

//===========================================================
//�I������
//===========================================================
void CTitle::Uninit(void)
{
	
}

//===========================================================
//�X�V����
//===========================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{//ENTER�L�[�����������V�[�����^�C�g���̂Ƃ�

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//�V�[�����Q�[���ɑJ��
			pFade->Set(CScene::MODE_GAME);
		}
	}

	CManager::Getinstance()->GetDebugProc()->Print("���݂̃V�[���F�^�C�g��");
}

//===========================================================
//�`�揈��
//===========================================================
void CTitle::Draw(void)
{
	
}