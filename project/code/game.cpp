//===========================================================
//
//�|���S�����o�����[game.cpp]
//Author �匴�叫
//
//===========================================================

//*==========================================================
//�C���N���[�h�t�@�C��
//*==========================================================
#include "game.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "object.h"
#include "debugproc.h"
#include "fade.h"
#include "time.h"
#include "score.h"
#include "pause.h"
#include "player.h"
#include "field.h"
#include "texture.h"
#include "enemy.h"
#include "enemymanager.h"
#include "collision.h"
#include "itemmanager.h"
#include "map.h"

//================================================================
//�@�ÓI�����o�ϐ�
//================================================================
CPause *CGame::m_pPause = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CEnemy *CGame::m_pEnemy = nullptr;
CEnemyManager *CGame::m_pEnemyManager = nullptr;
CCollision *CGame::m_Collision = nullptr;
CItemManager *CGame::m_pItemManager = nullptr;
CMap *CGame::m_pMap = nullptr;
CGame::WAVE CGame::m_Wave = WAVE_00;

//===========================================================
//�@�R���X�g���N�^
//===========================================================
CGame::CGame()
{
	m_bUse = false;
	m_bPause = false;
	m_bOnStage = false;
	m_nOnStageCounter = 0;
}

//===========================================================
//�@�R���X�g���N�^
//===========================================================
CGame::CGame(CScene::MODE mode)
{
	m_bUse = false;
	m_bPause = false;
	m_bOnStage = false;
	m_nOnStageCounter = 0;
}

//===========================================================
//�@�f�X�g���N�^
//===========================================================
CGame::~CGame()
{

}

//===========================================================
//�@����
//===========================================================
CGame *CGame::Create(void)
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;

		pGame->Init();
	}

	return pGame;
}

void CGame::WaveControll(void)
{
	if (m_Wave == WAVE_00)
	{
		m_Wave = WAVE_01;
		m_pEnemyManager->ReadText(ENEMYBOSS_TEXT);
	}
}

//===========================================================
//�@����������
//===========================================================
HRESULT CGame::Init(void)
{
	m_Wave = WAVE_00;

	CField *pField = new CField;
	pField->Init();
	pField->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\field001.jpg"));
	pField->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pField->SetSize(5000.0f, 5000.0f);
	pField->SetDraw(true);
	
	// �|�[�Y�̐���
	if (m_pPause == nullptr)
	{
		m_pPause = CPause::Create();
	}

	// �}�b�v�̐���
	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	// �����蔻��
	if (m_Collision == nullptr) 
	{
		m_Collision = CCollision::Create();
	}

	// �A�C�e���}�l�[�W���̐���
	if (m_pItemManager == nullptr)
	{
		m_pItemManager = CItemManager::Create();
	}

	// �G�}�l�[�W���̐���
	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = CEnemyManager::Create();
	}

	// �v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f));
	}

	CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//===========================================================
//�@�I������
//===========================================================
void CGame::Uninit(void)
{
	CManager::Getinstance()->GetSound()->Stop();

	// �|�[�Y�̔j��
	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		m_pPause = nullptr;
	}

	// �v���C���[�̔j��
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	// �A�C�e���̔j��
	if (m_pItemManager != nullptr)
	{
		m_pItemManager->Uninit();
		m_pItemManager = nullptr;
	}

	// �G�̔j��
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		m_pEnemyManager = nullptr;
	}

	// �}�b�v�̔j��
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	CObject::ReleaseAll();
}

//===========================================================
//�@�X�V����
//===========================================================
void CGame::Update(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_P) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_START, 0) == true)
	{
		m_bPause = m_bPause ? false : true;

		if (m_pPause != nullptr)
		{
			//m_pPause->SetDraw(m_bPause);
		}
	}

	if (m_bPause == true)
	{
		/*if (m_pPause != nullptr)
		{
			m_pPause->Update();
			m_pPause->SetDraw(m_bPause);
		}*/

		return;
	}

	if (pFade->Get() != pFade->FADE_OUT &&  pFade->GetCol() == 0.0f && m_bOnStage == false && CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
	{
		CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_ONSTAGE);
		m_bOnStage = true;
	}

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true /*|| pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_START, 0) == true*/)
	{//ENTER�L�[�����������V�[�����^�C�g���̂Ƃ�

		if (pFade->Get() != pFade->FADE_OUT)
		{
			m_Wave = WAVE_00;
			//�V�[�����Q�[���ɑJ��
			pFade->Set(CScene::MODE_RESULT);
		}
	}

	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Update();

		if (m_pEnemyManager->GetDefeatCounter() <= 0)
		{
			if (pFade->GetCol() >= 0.9f && pFade->FADE_IN)
			{
				CManager::Getinstance()->GetCamera()->Reset();
				m_pPlayer->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 500.0f));
				m_pPlayer->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				WaveControll();
				m_bOnStage = false;
			}
			
			if (pFade->Get() != pFade->FADE_OUT)
			{
				pFade->Set();
			}
		}
	}

	//���ׂĂ̍X�V����
	CObject::UpdateAll();
	
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n�V�[���F�Q�[��");
}

//===========================================================
//�@�`�揈��
//===========================================================
void CGame::Draw(void)
{
	
}