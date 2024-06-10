//===========================================================
//
// �G�f�B�b�g���[�h[edit.h]
// Author �匴�叫
//
//===========================================================
#include "edit.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "audience.h"

//�}�N����`
#define MODEL_SET_TEXT  ("data\\TEXT\\model_set.txt")
#define SET_AUDIENCE ("data\\TEXT\\set_audience.txt")
#define MOVE   (1.0f)  //�ړ���

//===========================================================
// 
//===========================================================
CEdit::CEdit()
{
	// �l���N���A
	for (int i = 0; i < MAX_MODELSET; i++)
	{
		m_apModel[i] = nullptr;
	}

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_move = {0.0f, 0.0f, 0.0f};
	m_nIdx = 0;
}

//===========================================================
// 
//===========================================================
CEdit::~CEdit()
{

}

//===========================================================
// 
//===========================================================
HRESULT CEdit::Init(void)
{
	TEXTLoad();

	return S_OK;
}

//===========================================================
// 
//===========================================================
void CEdit::Uninit(void)
{

}

//===========================================================
// 
//===========================================================
void CEdit::Update(void)
{
	Control();

	//�L�[�{�[�h�̏����擾
	CInputKeyboard* InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	if (InputKeyboard == nullptr)
		return;

	if (InputKeyboard->GetTrigger(DIK_F6) == true)
	{//2�L�[�������ꂽ

		Save();
	}
}

//===========================================================
// 
//===========================================================
void CEdit::Draw(void)
{
	for (int i = 0; i < MAX_MODELSET; i++)
	{
		if (m_apModel[i] != nullptr)
		{
			if (m_nIdx != i)
			{
				m_apModel[i]->SetbDraw(false);
			}
		}
	}
}

//===========================================================
// 
//===========================================================
void CEdit::Save(void)
{
	CAudience* pAudience = CAudience::GetTop();
	
	FILE* pFile;

	pFile = fopen(SET_AUDIENCE, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fprintf(pFile, "SCRIPT\n");

		while (pAudience != nullptr)
		{
			CAudience* pAudienceNext = pAudience->GetNext();

			fprintf(pFile, "\n");

			D3DXVECTOR3 pos = pAudience->GetPosition();  // �ʒu�擾
			D3DXVECTOR3 rot = pAudience->GetRotition();  // �����擾

			fprintf(pFile, "MODELSET\n");
			fprintf(pFile, "    POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);     // �ʒu
			fprintf(pFile, "    ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);     // ����
			fprintf(pFile, "END_MODELSET\n");
			fprintf(pFile, "\n");
			
			pAudience = pAudienceNext;
		}
	}

	fprintf(pFile, "END_SCRIPT\n");

	//�t�@�C�������
	fclose(pFile);
}

//===========================================================
// �ݒu�ł��郂�f���̓ǂݍ���
//===========================================================
void CEdit::TEXTLoad(void)
{
	char aString[128] = {};
	char aFileName[128] = {};
	int nCntModel = 0;

	FILE* pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(MODEL_SET_TEXT, "r");

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
					fscanf(pFile, "%d", &m_nNumAll);  //���f���̑���

				}  //NUM_MODEL�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &aFileName[0]);  //���f���̖��O

					m_apModel[nCntModel] = CObjectX::Create(&aFileName[0]);
					m_apModel[nCntModel]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					nCntModel++;

				}  //MODEL_LILENAME�̂�����
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//===========================================================
// ���䏈��
//===========================================================
void CEdit::Control(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard* InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//�J�����擾
	CCamera* pCamera = CManager::Getinstance()->GetCamera();

	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc* pDebugProc = CManager::Getinstance()->GetDebugProc();

	if (InputKeyboard == nullptr)
		return;

	if (pCamera == nullptr)
		return;

	//�J�����̌����擾
	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	if (InputKeyboard->GetTrigger(DIK_1) == true)
	{//1�L�[�������ꂽ

		if (m_nIdx > -1)
		{//�C���f�b�N�X�ԍ���-1���傫���Ƃ�

			m_nIdx -= 1;  //�C���f�b�N�X�ԍ�����߂�
		}

		if (m_nIdx < 0)
		{//�C���f�b�N�X�ԍ���0��菬�����Ƃ�

			m_nIdx = m_nNumAll - 1;  //�C���f�b�N�X�ԍ��𑍐�-1�ɂ���
		}
	}

	if (InputKeyboard->GetTrigger(DIK_2) == true)
	{//2�L�[�������ꂽ

		if (m_nIdx < m_nNumAll)
		{//�C���f�b�N�X�ԍ���������菬�����Ƃ�

			m_nIdx += 1;  //�C���f�b�N�X�ԍ�����i�߂�
		}

		if (m_nIdx >= m_nNumAll)
		{//�C���f�b�N�X�ԍ��������ȏ�ɂȂ����Ƃ�

			m_nIdx = 0;  //�C���f�b�N�X�ԍ���0�ɂ���
		}
	}

	if (InputKeyboard->GetTrigger(DIK_N) == true)
	{
		//CAudience::Create(m_apModel[m_nIdx]->GetPosition(), m_apModel[m_nIdx]->GetFileName());

		//�������J�E���g�A�b�v
		m_SetModel++;
	}

	//��Ɉړ�----------------------------------------------
	if (InputKeyboard->GetPress(DIK_W) == true)
	{//W�L�[�������ꂽ

		if (InputKeyboard->GetPress(DIK_D) == true)
		{//D�L�[�������� �E��Ɉړ�

			//�ړ���
			m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.75f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.75f)) * MOVE;
		}
		else if (InputKeyboard->GetPress(DIK_A) == true)
		{//A�L�[�������� ����Ɉړ�

			//�ړ���
			m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * MOVE;
		}
		else
		{//W�L�[����������	�^��Ɉړ�

			//�ړ���
			m_move.x -= sinf(CameraRot.y) * MOVE;
			m_move.z -= cosf(CameraRot.y) * MOVE;
		}
	}
	else if (InputKeyboard->GetPress(DIK_S) == true)
	{//S�L�[�������ꂽ

		//���Ɉړ�----------------------------------------------

		if (InputKeyboard->GetPress(DIK_D) == true)
		{//D�L�[�������� �E���Ɉړ�

			//�ړ���
			m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * MOVE;
		}
		else if (InputKeyboard->GetPress(DIK_A) == true)
		{//A�L�[�������� �����Ɉړ�

			//�ړ���
			m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * MOVE;
		}
		else
		{//S�L�[���������� �^���Ɉړ�

			//�ړ���
			m_move.x += sinf(CameraRot.y) * MOVE;
			m_move.z += cosf(CameraRot.y) * MOVE;
		}
	}
	else if (InputKeyboard->GetPress(DIK_D) == true)
	{//D�L�[����������

		//�E�Ɉړ�----------------------------------------------
		
		//�ړ���
		m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.5f)) * MOVE;
		m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.5f)) * MOVE;
	}
	else if (InputKeyboard->GetPress(DIK_A) == true)
	{//A�L�[����������

		//���Ɉړ�----------------------------------------------
		
		//�ړ���
		m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * MOVE;
		m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * MOVE;
	}

	if (InputKeyboard->GetPress(DIK_U) == true)
	{//U�L�[��������

		m_rot.y += 0.01f;
	}

	if (InputKeyboard->GetPress(DIK_I) == true)
	{//I�L�[��������

		m_rot.y -= 0.01f;
	}

	if (InputKeyboard->GetTrigger(DIK_O) == true)
	{//O�L�[��������

		m_rot.y = 0.0f;
	}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	// �ړ��ʂ��X�V(����������)--------------------------------------------
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	// �ړ��ʉ��Z
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	// �ʒu����
	m_apModel[m_nIdx]->SetPosition(m_pos);
	m_apModel[m_nIdx]->SetRotition(m_rot);

	if (pDebugProc == nullptr)
		return;

	pDebugProc->Print("\n<< �I�u�W�F�N�g�̈ʒu�FX��<%f>,Y��<%f>,Z��<%f> >>", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("\n<< �I�u�W�F�N�g�̌����FX��<%f>,Y��<%f>,Z��<%f> >>", m_rot.x, m_rot.y, m_rot.z);
	pDebugProc->Print("\n<< ���݂̃I�u�W�F�N�g�̔ԍ��F%d/%d >>", m_nIdx, m_nNumAll);
	pDebugProc->Print("\n<< �ݒu�����I�u�W�F�N�g�̐��F%d >>", m_SetModel);
	pDebugProc->Print("\n<< �z�u���Z�b�g�FF7 >>");
	pDebugProc->Print("\n<< �O���t�@�C�������o���FF8 >>");
	pDebugProc->Print("\n<< �O���t�@�C���ǂݍ��݁FF9 >>");
	pDebugProc->Print("\n<< ���f���̐��� : U/I >>");
	pDebugProc->Print("\n<< ���f���̌������Z�b�g : O >>");
}