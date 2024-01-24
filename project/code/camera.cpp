//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �匴�@�叫
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "game.h"
#include "player.h"

//�}�N����`
#define CAMERA_DISTNCE    (300.0f)
#define CAMERA_ROTY       (0.03f)
#define CAMERA_MOVE       (2.0f)
#define CAMERA_LOWMOVE    (0.1f)

namespace
{
	const D3DXVECTOR3 HEAT_CAMERAROT = { 0.0f, -D3DX_PI * 0.75f, D3DX_PI * -0.38f };   // �ڕW�̊p�x
}

//================================================================
// �R���X�g���N�^
//================================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mode = MODE_NONE;
	m_nCounter = 0;
}

//================================================================
// �f�X�g���N�^
//================================================================
CCamera::~CCamera()
{

}

//================================================================
// ����������
//================================================================
void CCamera::Init(void)
{
	CScene *pScene = CManager::Getinstance()->GetScene();

	//if (pScene->GetMode() == CScene::MODE_TITLE)
	//{
	//	m_posV = D3DXVECTOR3(0.0f, 150.0f, -30.0f);
	//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	//}
}

//================================================================
// �I������
//================================================================
void CCamera::Uninit(void)
{

}

//================================================================
// �X�V����
//================================================================
void CCamera::Update(void)
{
	Mode();
} 

//================================================================
// �ݒ菈��
//================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		100000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//================================================================
// �����ݒ�
//================================================================
void CCamera::SetRot(D3DXVECTOR3 Rot)
{
	m_rot = Rot;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================================
// ���[�h
//================================================================
void CCamera::Mode(void)
{
	//�V�[���̏�������
	CScene *pScene = CManager::Getinstance()->GetScene();

	switch (m_mode)
	{
	case CCamera::MODE_NONE:
		break;
	case CCamera::MODE_TITLE:

		Title();
		break;
	case CCamera::MODE_GAME:

		CameraV();
		break;
	case CCamera::MODE_RESULT:

		Title();
		break;
	case CCamera::MODE_HEAT:

		Heat();
		break;
	case CCamera::MODE_MAX:
		break;
	default:
		break;
	}

	//������ݒ�
	SetRot(m_rot);

	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n---�J�����̏��---");
	pDebugProc->Print("\n�J�����̈ʒu���_�FX��<%f>,Y��<%f>,Z��<%f>", m_posV.x, m_posV.y, m_posV.z);
	pDebugProc->Print("\n�J�����̈ʒu�����_�FX��<%f>,Y��<%f>,Z��<%f>", m_posR.x, m_posR.y, m_posR.z);
	pDebugProc->Print("\n�J�����̌��� �FX��<%f>,Y��<%f>,Z��<%f>", m_rot.x, m_rot.y, m_rot.z);
}

//================================================================
// ���A�c�A�N�V����
//================================================================
void CCamera::Heat(void)
{
	//// �J������ڕW�̌����܂ŉ�]������
	//D3DXVECTOR3 rotDest = m_Oldrot - m_rot;
	//SetRotation(m_rot + rotDest * 0.1f);

	//m_rot = HEAT_CAMERAROT;

	m_posV.x = m_posR.x - sinf(m_rot.y) * -CAMERA_DISTNCE;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -CAMERA_DISTNCE;

	D3DXVECTOR3 pos = CGame::GetPlayer()->GetPosition();

	m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f, 30.0f + m_posV.z);
	m_posR = D3DXVECTOR3(pos.x, 50.0f, pos.z + 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	//�ڕW�̒����_��ݒ�
	m_posRDest.x = pos.x;
	m_posRDest.z = pos.z;

	//�J�����̈ړ���
	m_move.x = m_posRDest.x - m_posR.x;
	m_move.z = m_posRDest.z - m_posR.z;

	//�ʒu�Ɉړ��ʂ�ۑ�
	m_posR.x += m_move.x;
	m_posR.z += m_move.z;
}

//================================================================
// ���_�̈ړ�
//================================================================
void CCamera::CameraV(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�}�E�X�̏����擾
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//�}�E�X�̈ʒu���擾
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//�Q�[���p�b�h���擾
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	CPlayer *pPlayer = CGame::GetPlayer();

	if (pInputJoyPad->GetRXStick(CInputJoyPad::STICK_RX, 0) > 0)
	{
		m_rot.y += 0.05f;
	}
	else if (pInputJoyPad->GetRXStick(CInputJoyPad::STICK_RX, 0) < 0)
	{
		m_rot.y -= 0.05f;
	}

	m_rot.y += MousePos.x * 0.005f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * -CAMERA_DISTNCE;
	m_posV.z = m_posR.z - cosf(m_rot.y) * -CAMERA_DISTNCE;

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f, 30.0f + m_posV.z);
	m_posR = D3DXVECTOR3(pos.x, 50.0f, pos.z + 10.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	//�ڕW�̒����_��ݒ�
	m_posRDest.x = pos.x;
	m_posRDest.z = pos.z;

	//�J�����̈ړ���
	m_move.x = m_posRDest.x - m_posR.x;
	m_move.z = m_posRDest.z - m_posR.z;

	//�ʒu�Ɉړ��ʂ�ۑ�
	m_posR.x += m_move.x;
	m_posR.z += m_move.z;
}

//================================================================
// ���_�̈ړ�
//================================================================
void CCamera::CameraR(void)
{
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	m_rot.z += MousePos.y * 0.005f;

	m_posR.x = m_posV.x - sinf(m_rot.y) * CAMERA_DISTNCE;
	m_posR.z = m_posV.z - cosf(m_rot.y) * CAMERA_DISTNCE;
}

//================================================================
// ���_�̈ړ�
//================================================================
void CCamera::Title(void)
{
	m_posV = D3DXVECTOR3(-500.0f, 80.0f, -200.0f);
	m_posR = D3DXVECTOR3(-875.0f, 70.0f, 50.0f);
	m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
}

//================================================================
// �{�X���o�ꂷ��Ƃ��̃J����
//================================================================
void CCamera::Edit(void)
{
	////�L�[�{�[�h�̏����擾
	//CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//CPlayer *pPlayer = CGame::GetPlayer();

	//D3DXVECTOR3 pos = pPlayer->Getpos();

	//if (InputKeyboard->GetPress(DIK_F) == true)
	//{
	//	m_move.x += sinf(m_rot.y) * 1.1f;
	//}

	//if (InputKeyboard->GetPress(DIK_H) == true)
	//{
	//	m_move.x -= sinf(m_rot.y) * 1.1f;
	//}

	//if (InputKeyboard->GetPress(DIK_T) == true)
	//{
	//	m_move.y += 1.0f;
	//}

	//if (InputKeyboard->GetPress(DIK_G) == true)
	//{
	//	m_move.y -= 1.0f;
	//}

	//m_rot.y += MousePos.x * 0.005f;

	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI * 2.0f;
	//}
	//else if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI * 2.0f;
	//}

	//m_posV.x = m_posR.x - sinf(m_rot.y) * -2300.0f;
	//m_posV.z = m_posR.z - cosf(m_rot.y) * -2300.0f;

	//m_posR.x = m_posV.x - sinf(m_rot.y) * 2300.0f;
	//m_posR.z = m_posV.z - cosf(m_rot.y) * 2300.0f;

	//m_posR.x += m_move.x;
	//m_posV.x += m_move.x;

	//m_posR.y += m_move.y;
	//m_posV.y += m_move.y;

	////m_posV += m_move;
	////m_posR += m_move;

	//m_posV = D3DXVECTOR3(0.0f + m_posV.x, 150.0f + m_posV.y, 30.0f + m_posV.z);
	//m_posR = D3DXVECTOR3(100.0f + m_posR.x, 50.0f + m_posR.y, m_posR.z + 10.0f);
	//m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
}

//================================================================
// ������������g���Ă���Ƃ��̃J����
//================================================================
void CCamera::Scope(void)
{
	/*CInputMouse *pInputMouse = CManager::GetInputMouse();

	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	CPlayer *pPlayer = CGame::GetPlayer();

	m_rot.y += MousePos.x * 0.005f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posR.x = m_posV.x - sinf(m_rot.y) * 50.0f;
	m_posR.z = m_posV.z - cosf(m_rot.y) * 50.0f;

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 pos = pPlayer->Getpos();

		m_posV = D3DXVECTOR3(pos.x , 70.0f, pos.z);
		m_posR = D3DXVECTOR3(m_posR.x, 70.0f, m_posR.z);
		m_posU = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	}*/
}