//==============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �匴�@�叫
//
//==============================================================================

//*=============================================================================
// �C���N���[�h�t�@�C��
//*=============================================================================
#include "enemy.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "sound.h"
#include "player.h"
#include "game.h"
#include "debugproc.h"
#include "score.h"
#include "player.h"
#include "character.h"
#include "collision.h"
#include "enemymanager.h"
#include "gage.h"
#include "camera.h"
#include "particle.h"
#include "effect.h"
#include "item.h"
#include <assert.h>

// �ÓI�����o�ϐ�
CEnemy *CEnemy::m_pTop = nullptr;
CEnemy *CEnemy::m_pCur = nullptr;

int CEnemy::m_nIdx = 0;

//*=============================================================================
// �}�N����`
//*=============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\motion_set_enemy.txt")   //�G�̃e�L�X�g�t�@�C��
#define ENEMYMOVE    (2.0f)                        //�ړ���

// �������O��Ԃ��`
namespace
{
	const int DAMEGECOUNT = 15;  // �_���[�W���

	const D3DXVECTOR3 CAMERAROT[CPlayer::HEAT_MAX] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, D3DX_PI * -0.38f),

	};  // �q�[�g�A�N�V�������̃J�����ʒu
}

//*=============================================================================
// �ÓI�����o�ϐ�
//*=============================================================================
int CEnemy::m_nNumAll = 0;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemy::CEnemy()
{
	// �l���N���A
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.mtxWorld);
	m_Info.state = STATE_NONE;
	m_Mobility = Immobile;
	m_Info.nLife = 0;
	m_Info.nIdxID = -1;
	m_Info.bDraw = true;
	m_nDamegeCounter = 0;
	m_pCurrent = nullptr;
	m_pNext = nullptr;
	m_pLife2D = nullptr;
	m_pLife3D = nullptr;
	m_bDeath = false;

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemy::CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	// �l���N���A
	m_Info.pos = pos;
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = rot;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.mtxWorld);
	m_Info.state = STATE_NONE;
	m_Mobility = Immobile;
	m_Info.nLife = nlife;
	m_Info.nIdxID = -1;
	m_Info.bDraw = true;
	m_nDamegeCounter = 0;
	m_pCurrent = nullptr;
	m_pNext = nullptr;
	m_pLife2D = nullptr;
	m_pLife3D = nullptr;
	m_bDeath = false;

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEnemy::~CEnemy()
{

}

//==============================================================================
// ��������
//==============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy(pos, rot, nlife);

		pEnemy->Init();
	}

	return pEnemy;
}

//==============================================================================
// ����������
//==============================================================================
HRESULT CEnemy::Init(void)
{
	if (m_pMotion == nullptr)
	{// �g�p����Ă��Ȃ�������

		// ����
		m_pMotion = new CMotion;

		// ����������
		m_pMotion->Init();
	}

	m_nDamegeCounter = DAMEGECOUNT;

	m_nNumAll++;

	if (m_Type == TYPE_WEAK)
	{
		
	}

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CEnemy::Uninit(void)
{
	m_bDeath = true;

	// ���X�g���玩�����g���폜����
	if (m_pTop == this)
	{// ���g���擪
		if (m_pNext != nullptr)
		{// �������݂��Ă���
			m_pTop = m_pNext;	// ����擪�ɂ���
			m_pNext->m_pPrev = nullptr;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == this)
	{// ���g���Ō��
		if (m_pPrev != nullptr)
		{// �������݂��Ă���
			m_pCur = m_pPrev;			// �O���Ō���ɂ���
			m_pPrev->m_pNext = nullptr;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	//�T�E���h�̏����擾
	CSound *pSound = CManager::Getinstance()->GetSound();

	//�T�E���h�X�g�b�v
	//pSound->Stop();

	if (m_pMotion != nullptr)
	{
		//�I������
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_apModel != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_apModel[nCount] != nullptr)
			{
				m_apModel[nCount]->Uninit();
				m_apModel[nCount] = nullptr;
			}
		}

		delete m_apModel;
		m_apModel = nullptr;
	}

	CObject::Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CEnemy::Update(void)
{
	if (m_Info.bDraw == true)
	{
		if (m_Info.state != STATE_BIRIBIRI && m_Info.state != STATE_BIRI && m_Info.state != STATE_FAINTING && m_Info.state != STATE_DETH)
		{
			Controll();
		}
		else if (m_Info.state != STATE_DETH)
		{
			MicroWave();
		}
		
		if (m_pMotion != nullptr)
		{
			// �X�V����
			m_pMotion->Update();
		}

		if (m_apModel != nullptr)
		{
			for (int nCount = 0; nCount < m_nNumModel; nCount++)
			{
				if (m_apModel[nCount] != nullptr)
				{
					m_apModel[nCount]->Update();
				}
			}
		}
	}

	if (GetMotion()->IsFinish() == true && (m_Info.state == STATE_HEATDAMEGE || m_Info.state == STATE_PAINFULDAMAGE) && m_Info.state != STATE_GETUP)
	{
		m_Info.state = STATE_GETUP;
		GetMotion()->Set(TYPE_GETUP);
	}
	else if (m_pMotion->IsFinish() == true && m_Info.state == STATE_DETH)
	{
		int nNum = CEnemyManager::GetNum() - 1;
		CEnemyManager::SetNum(nNum);
		Uninit();

		if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
		{
			int nDefeat = CPlayer::GetPlayer()->GetDefeat() + 1;
			CPlayer::GetPlayer()->SetDefeat(nDefeat);
		}

		return;
	}
	else if (GetMotion()->IsFinish() == true)
	{
		m_Info.state = STATE_NEUTRAL;
		GetMotion()->Set(TYPE_NEUTRAL);

		if (m_Chase != CHASE_ON)
		{
			m_Chase = CHASE_ON;
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CEnemy::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_Info.bDraw == true)
	{
		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_Info.mtxWorld);

		if (m_pCurrent != nullptr)
		{
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

			D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

			D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

			// �}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
			D3DXMatrixMultiply(&m_Info.mtxWorld,
				&m_Info.mtxWorld, m_pCurrent);
		}
		else
		{
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

			D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

			D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
		}

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_apModel[nCount] != nullptr)
			{
				//�`�揈��
				m_apModel[nCount]->Draw();
			}
		}
	}
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Controll(void)
{
	int nNum = 0;
	CEnemy **ppEnemy = nullptr;

	if (m_Info.state == STATE_DAMEGE)
	{
		m_nDamegeCounter--;

		if (m_nDamegeCounter <= 0)
		{
			m_Info.state = STATE_NONE;
			m_nDamegeCounter = DAMEGECOUNT;
		}
	}
	else
	{
		if (m_Info.state != STATE_GRAP && m_Mobility == Mobile)
		{
			Move();
		}
	}

	if (m_Info.nLife <= 0)
	{
		m_Info.state = STATE_DETH;
		GetMotion()->Set(TYPE_DETH);
		return;
	}

	if (m_Info.state != STATE_GRAP)
	{
		m_Info.move.y -= 0.9f;

		// �ړ���
		m_Info.pos.x += m_Info.move.x;
		m_Info.pos.y += m_Info.move.y;
		m_Info.pos.z += m_Info.move.z;

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.pos.y = 0.0f;
		}
	}

	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
	pDebugProc->Print("\n�G�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	pDebugProc->Print("�G�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	pDebugProc->Print("�G�̗̑́F%d\n", m_Info.nLife);
	pDebugProc->Print("�G�̔ԍ��F%d\n", m_Info.nIdxID);
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Attack(void)
{
	
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Move(void)
{
	
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act)
{
	/*m_Info.nLife -= damege;
	m_Info.move = D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y) * -blowaway, blowaway, cosf(CGame::GetPlayer()->GetRotition().y) * -blowaway);

	if (m_Info.state != STATE_HEATDAMEGE)
	{
		m_Info.state = STATE_HEATDAMEGE;
		m_pMotion->Set(TYPE_HEATDAMEGE);
	}*/
}

//==============================================================================
// �d�q�����W�т�т�
//==============================================================================
void CEnemy::MicroWave(void)
{
	m_nBiriBiriCount++;

	if (m_nBiriBiriCount > 60 && m_Info.state == STATE_BIRIBIRI)
	{
		if (m_Info.state != STATE_BIRI)
		{
			m_Info.state = STATE_BIRI;
			GetMotion()->Set(TYPE_BIRI);

			CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(CAMERAROT[2].x, CAMERAROT[2].y, CAMERAROT[2].z));
			//CManager::Getinstance()->GetCamera()->SetDistnce(CAMERADISTNCE[m_HeatAct]);
		}

		m_nBiriBiriCount = 0;
	}

	if (m_nBiriBiriCount > 120 && m_Info.state == STATE_BIRI)
	{
		if (m_Info.state != STATE_FAINTING)
		{
			m_Info.state = STATE_FAINTING;
			GetMotion()->Set(TYPE_FAINTING);
			m_Info.nLife -= 300;
			CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_RETURN);
		}

		m_nBiriBiriCount = 0;
	}

	if (m_Info.state == STATE_BIRI)
	{
		if (m_nBiriBiriCount % 20 == 0)
		{
			CParticle::Create(CGame::GetPlayer()->GetItem()->GetPosition(), CParticle::TYPE_SMOOK);
		}
	}
}

//==============================================================================
// �e�L�X�g�t�@�C���ǂݍ���
//==============================================================================
void CEnemy::ReadText(char *fliename)
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

					m_apModel = new CCharacter*[m_nNumModel];

				}  //NUM_MODEL�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //���f���̖��O

					m_apModel[nCntModel] = CCharacter::Create(m_filename);
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
										m_apModel[nCntParts2]->SetParent(m_apModel[m_nParent]);
									}
									else
									{
										m_apModel[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readpos.z);  //���f���̑���

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.y);  //���f���̑���
									fscanf(pFile, "%f", &m_Readrot.z);  //���f���̑���

									m_apModel[nCntParts2]->SetRotOrigin(m_Readrot);

									m_apModel[nCntParts2]->SetRot(m_Readrot);
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

	if (m_pMotion != nullptr)
	{
		//���f���̐ݒ�
		m_pMotion->SetModel(m_apModel, m_nNumModel);

		//����������
		m_pMotion->ReadText(fliename);
	}
}

void CEnemy::SetChase(CHASE cha)
{
}