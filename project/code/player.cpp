//===========================================================
//
//�|���S�����o�����[player.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "game.h"
#include "fade.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//================================================================
//�}�N����`
//================================================================
#define MAX_LIFECHIBI (10)                                        // �`�r�̗̑�
#define MAX_LIFEFOOT  (6)                                         // �f�u�̗̑�
#define REST_BULLET   (30)                                        // �ێ��ł���e�̐�
#define BULLETWAIT    (15)                                        // �ˌ��̊Ԋu
#define MUTEKITIME    (30)                                        // ���G����
#define PLAYER_X      (40.0f)                                     // �v���C���[��X���̕�
#define PLAYER_Z      (10.0f)                                     // �v���C���[��Z���̕�
#define SPEED         (1.0f)                                      // �ړ��̑���
#define FRIST         (21)                                        // �U�����蔭���J�n
#define FINISH        (31)                                        // �U������I��
#define PLAYER01_TEXT ("data\\TEXT\\motion_neet2.txt")       // �v���C���[�̃e�L�X�g�t�@�C��
#define PLAYER02_TEXT ("data\\TEXT\\motion_set_player2.txt")      // �v���C���[�̃e�L�X�g�t�@�C��

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
//MODEL *CPlayer::m_Player = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CPlayer::CPlayer()
{
	// ������
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;
	
	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CPlayer::CPlayer(D3DXVECTOR3 pos)
{
	// ������
	SetPosition(pos);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
//�f�X�g���N�^
//================================================================
CPlayer::~CPlayer()
{

}

//================================================================
// ��������
//================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CPlayer *pPlayer = nullptr;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == nullptr)
		{
			//�I�u�W�F�N�g2D�̐���
			pPlayer = new CPlayer(pos);

			//����������
			pPlayer->Init();
		}
	}

	return pPlayer;
}

//================================================================
// ��������
//================================================================
CPlayer * CPlayer::Create(void)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CPlayer *pPlayer = nullptr;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == nullptr)
		{
			//�I�u�W�F�N�g2D�̐���
			pPlayer = new CPlayer();

			//����������
			pPlayer->Init();
		}
	}

	return pPlayer;
}

//================================================================
//�v���C���[�̏���������
//================================================================
HRESULT CPlayer::Init(void)
{
	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//�V�[���̏����擾
	CScene *pScene = CManager::Getinstance()->GetScene();

	//��ސݒ�
	SetType(TYPE_PLAYER);

	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;

		//����������
		m_pMotion->Init();
	}

	m_fGrapRot = 1.0f;

	ReadText(PLAYER01_TEXT);
	
	return S_OK;
}

//================================================================
//�v���C���[�̏I������
//================================================================
void CPlayer::Uninit(void)
{
	//�T�E���h�̏����擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�T�E���h�X�g�b�v
	pSound->Stop();

	CObject::Release();
}

//================================================================
//�v���C���[�̍X�V����
//================================================================
void CPlayer::Update(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�t�F�[�h�̏����擾
	CFade *pFade = CManager::Getinstance()->GetFade();

	//�V�[���̏����擾
	CScene *pScene = CManager::Getinstance()->GetScene();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	Control();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	if (m_pMotion != NULL)
	{
		// �X�V����
		m_pMotion->Update();
	}
}

//================================================================
//�v���C���[�̕`�揈��
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Draw();
		}
	}
}

//================================================================
// ���䏈��
//================================================================
void CPlayer::Control(void)
{
	Move();

	CManager::Getinstance()->GetDebugProc()->Print("\n�v���C���[�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("�v���C���[�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
}

//================================================================
// �ړ�����
//================================================================
void CPlayer::Move(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�}�E�X�̈ʒu���擾
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�J�����擾
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	m_bDesh = false;

	if (m_Info.state != STATE_GRAP)
	{
		//��Ɉړ�----------------------------------------------
		if (InputKeyboard->GetPress(DIK_W) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
		{//W�L�[�������ꂽ

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//D�L�[�������� �E��Ɉړ�

			 // �ړ���
				m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;
				m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;

				//����
				m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//A�L�[�������� ����Ɉړ�

			 // �ړ���
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * SPEED;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * SPEED;

				//����
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
			}
			else
			{//W�L�[����������	�^��Ɉړ�

			 // �ړ���
				m_Info.move.x -= sinf(CameraRot.y) * SPEED;
				m_Info.move.z -= cosf(CameraRot.y) * SPEED;

				//����
				m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
			}

			m_bDesh = true;
		}
		//���Ɉړ�----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_S) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
		{//S�L�[�������ꂽ

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//D�L�[�������� �E���Ɉړ�

			 // �ړ���
				m_Info.move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * SPEED;
				m_Info.move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * SPEED;

				// ����
				m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//A�L�[�������� �����Ɉړ�

			 // �ړ���
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;

				// ����
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
			}
			else
			{//S�L�[���������� �^���Ɉړ�

			 // �ړ���
				m_Info.move.x += sinf(CameraRot.y) * SPEED;
				m_Info.move.z += cosf(CameraRot.y) * SPEED;

				// ����
				m_fDest = (CameraRot.y + (D3DX_PI));
			}

			m_bDesh = true;
		}
		//�E�Ɉړ�----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//D�L�[����������

		 // �ړ���
			m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;
			m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;

			m_bDesh = true;

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
		}
		//���Ɉړ�----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//A�L�[����������

		 // �ړ���
			m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;
			m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;

			m_bDesh = true;

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
		}

		m_fDiff = m_fDest - m_Info.rot.y;

		//�p�x�̒l���C������
		if (m_fDiff >= D3DX_PI)
		{
			m_fDiff -= D3DX_PI * 2;
		}
		else if (m_fDiff <= -D3DX_PI)
		{
			m_fDiff += D3DX_PI * 2;
		}

		//�ړ�����(�p�x)�̕␳------------------------------------------------
		m_Info.rot.y += m_fDiff * 0.15f;

		//�p�x�̒l���C������--------------------------------------------------
		if (m_Info.rot.y > D3DX_PI)
		{
			m_Info.rot.y = -D3DX_PI;
		}
		else if (m_Info.rot.y < -D3DX_PI)
		{
			m_Info.rot.y = D3DX_PI;
		}
	}
	else
	{
		GrapRotition();
	}
	
	//�ʒu�Ɉړ��ʉ��Z----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//m_pos.y = fHeight + 18.0f;

	//�ړ��ʂ��X�V(����������)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	if (InputKeyboard->GetTrigger(DIK_SPACE) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{
		m_bAttack = true;
	}

	if (InputKeyboard->GetTrigger(DIK_E) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_X, 0) == true)
	{
		if (m_Info.state != STATE_GRAP)
		{
			m_bGrap = true;
		}
		else
		{
			m_bGrap = false;
		}
	}

	if (InputKeyboard->GetTrigger(DIK_F) == true)
	{
		if (CGame::GetCollision()->Item(&m_Info.pos) == true)
		{
			m_bLift = true;
			m_Info.state = STATE_LIFT;
			CManager::Getinstance()->GetDebugProc()->Print("�������Ă�`");
		}
	}

	if (m_Info.state != STATE_ATTACK && m_bAttack == true)
	{
		m_Info.state = STATE_ATTACK;

		m_Info.Atc = TYPE01_ATTACK;

		// ���[�V�������Z�b�g(�ߐڍU��)
		m_pMotion->Set(TYPE_ATTACK01);

		m_bAttack = false;
	}

	if (m_Info.Atc == TYPE01_ATTACK && m_bAttack == true && m_pMotion->IsFinish() == true)
	{
		m_Info.Atc = TYPE02_ATTACK;

		// ���[�V�������Z�b�g(�ߐڍU��)
		m_pMotion->Set(TYPE_ATTACK02);

		m_bAttack = false;
	}
	if (m_Info.Atc == TYPE02_ATTACK && m_bAttack == true && m_pMotion->IsFinish() == true)
	{
		m_Info.Atc = TYPE03_ATTACK;

		// ���[�V�������Z�b�g(�ߐڍU��)
		m_pMotion->Set(TYPE_ATTACK03);

		m_bAttack = false;
	}

	if (m_Info.state == STATE_LIFT && m_bLift == true)
	{

	}

	if (m_Info.state != STATE_GRAP && m_bGrap == true)
	{
		m_bDesh = false;

		m_Info.state = STATE_GRAP;

		// ���[�V�������Z�b�g(�ߐڍU��)
		//m_pMotion->Set(TYPE_GRAP);
	}

	if (InputKeyboard->GetTrigger(DIK_LSHIFT) == true)
	{
		m_bAvoid = true;
		m_Info.state = STATE_AVOID;
		m_pMotion->Set(TYPE_AVOID);
	}

	if (m_Info.state == STATE_GRAP && m_bGrap == false)
	{
		CGame::GetEnemy()->SetCurrent(nullptr);
		CGame::GetEnemy()->SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 50.0f, m_Info.pos.z));
		CGame::GetEnemy()->SetRotition(m_Info.rot);
		CGame::GetEnemy()->SetMove(D3DXVECTOR3(sinf(m_Info.rot.y) * (m_fGrapRot * 3.0f), 1.0f, cosf(m_Info.rot.y) * (m_fGrapRot * 3.0f)));
		CGame::GetEnemy()->SetState(CEnemy::STATE_DAMEGE);
		m_fGrapRot = 1.0f;
	}

	if (m_bAttack == true)
	{
		m_nCntColi++;

		if (m_nCntColi >= 15 && 20 >= m_nCntColi)
		{
			if (CGame::GetCollision() != nullptr)
			{
				/*if (CGame::GetCollision()->Sword(m_ppCharacter[28]->GetMtxWorld(), m_ppCharacter[28]->GetMtxWorld(), 100.0f, CGame::GetEnemy()) == true)
				{
					CManager::Getinstance()->GetDebugProc()->Print("��������`");
				}*/
			}

			CManager::Getinstance()->GetDebugProc()->Print("�͂͂͂͂͂́`");
		}
	}

	if (m_bGrap == true)
	{
		CGame::GetEnemy()->SetCurrent(&m_Info.mtxWorld);
		CGame::GetEnemy()->SetPosition(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
		CGame::GetEnemy()->SetRotition(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, D3DX_PI));
		CGame::GetEnemy()->SetState(CEnemy::STATE_GRAP);
	}

	if (m_Info.state != STATE_MOVE && m_bDesh == true && m_bAttack == false)
	{
		m_Info.state = STATE_MOVE;

		//���[�V�������Z�b�g(�ړ�)
		m_pMotion->Set(TYPE_MOVE);
	}

	if (m_pMotion->IsFinish() == true 
	|| (m_bAttack == false && m_bDesh == false && m_bGrap == false && m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_AVOID))
	{
		//���[�V�������Z�b�g(�ҋ@)
		m_pMotion->Set(TYPE_NEUTRAL);

		m_Info.state = STATE_NEUTRAL;

		m_Info.Atc = TYPE00_NONE;

		m_bAttack = false;

		m_nCntColi = 0;
	}

	CManager::Getinstance()->GetDebugProc()->Print("��]��:%f", m_fGrapRot);
}

//================================================================
// �����鎞�̊p�x����
//================================================================
void CPlayer::GrapRotition(void)
{
	//�L�[�{�[�h���擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X���擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//�T�E���h���擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�J�����擾
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	m_fDestOld = m_fDest;

	//��Ɉړ�----------------------------------------------
	if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
	{//W�L�[�������ꂽ

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//D�L�[�������� �E��Ɉړ�

			//����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//A�L�[�������� ����Ɉړ�

			//����
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
		}
		else
		{//W�L�[����������	�^��Ɉړ�

			//����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
		}

	}
	//���Ɉړ�----------------------------------------------
	else if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
	{//S�L�[�������ꂽ

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//D�L�[�������� �E���Ɉړ�

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//A�L�[�������� �����Ɉړ�

			// ����
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
		}
		else
		{//S�L�[���������� �^���Ɉړ�

			// ����
			m_fDest = (CameraRot.y + (D3DX_PI * m_fGrapRot));
		}

	}
	//�E�Ɉړ�----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_D) == true)
	{//D�L�[����������

		// ����
		m_fDest += (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//���Ɉړ�----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_A) == true)
	{//A�L�[����������

		// ����
		m_fDest -= (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//�E�Ɉړ�----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
	{//D�L�[����������

		// ����
		m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
	}
	//���Ɉړ�----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
	{//A�L�[����������

		// ����
		m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
	}

	if (m_fDest > 0.0f && m_fDestOld < 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}
	else if (m_fDest < 0.0f && m_fDestOld > 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}

	m_fDiff = m_fDest - m_Info.rot.y;

	//�p�x�̒l���C������
	if (m_fDiff >= D3DX_PI)
	{
		m_fDiff -= D3DX_PI * 2;
	}
	else if (m_fDiff <= -D3DX_PI)
	{
		m_fDiff += D3DX_PI * 2;
	}

	//�ړ�����(�p�x)�̕␳------------------------------------------------
	m_Info.rot.y += m_fDiff * (0.15f * m_fGrapRot);

	//�p�x�̒l���C������--------------------------------------------------
	if (m_Info.rot.y > D3DX_PI)
	{
		m_Info.rot.y = -D3DX_PI;
	}
	else if (m_Info.rot.y < -D3DX_PI)
	{
		m_Info.rot.y = D3DX_PI;
	}
}

//================================================================
//�O���t�@�C���ǂݍ���
//================================================================
void CPlayer::ReadText(const char *fliename)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

	//�e�N�X�`���̏��擾
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(fliename, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_MODEL", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%d", &m_nNumModel);  //���f���̑���

					m_ppCharacter = new CCharacter*[m_nNumModel];

				}  //NUM_MODEL�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //���f���̖��O

					m_ppCharacter[nCntModel] = CCharacter::Create(m_filename);
					nCntModel++;

					nCntParts++;

				}  //MODEL_LILENAME�̂�����

				if (strcmp("CHARACTERSET", aString) == 0)
				{
					while (strcmp("END_CHARACTERSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("PARTSSET", aString) == 0)
						{
							while (strcmp("END_PARTSSET", aString) != 0)
							{
								fscanf(pFile, "%s", &aString);

								if (strcmp("INDEX", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nIdx);  //���f���̔ԍ�
								}

								if (strcmp("PARENT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nParent);  //�e���f���̔ԍ�

									if (m_nParent > -1 && m_nNumModel > m_nParent)
									{
										m_ppCharacter[nCntParts2]->SetParent(m_ppCharacter[m_nParent]);
									}
									else
									{
										m_ppCharacter[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.z);  //���f���̑���

									m_ppCharacter[nCntParts2]->SetPositionOri(m_Readpos);

									m_ppCharacter[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.z);  //���f���̑���

									m_ppCharacter[nCntParts2]->SetRotOrigin(m_Readrot);

									m_ppCharacter[nCntParts2]->SetRot(m_Readrot);
								}

							}//END_PARTSSET�̂�����

							nCntParts2++;

						}//PARTSSET�̂�����

					}//END_CHARACTERSET�̂����� 

				}//CHARACTERSET�̂����� 
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}

	if (m_pMotion != NULL)
	{
		//���f���̐ݒ�
		m_pMotion->SetModel(m_ppCharacter, m_nNumModel);

		//����������
		m_pMotion->ReadText(fliename);

		m_pMotion->Set(TYPE_NEUTRAL);
	}
}