//==============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �匴�@�叫
//
//==============================================================================

//*=============================================================================
//�C���N���[�h�t�@�C��
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
#include <assert.h>

// �ÓI�����o�ϐ�
CEnemy *CEnemy::m_pTop = nullptr;
CEnemy *CEnemy::m_pCur = nullptr;
CEnemy *CEnemy::m_pNext = nullptr;

//*=============================================================================
// �}�N����`
//*=============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\motion_set_enemy.txt")   //�G�̃e�L�X�g�t�@�C��
#define ENEMYMOVE    (2.0f)                        //�ړ���

// �������O��Ԃ��`
namespace
{
	const int DAMEGECOUNT = 25;  // �_���[�W���
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
	m_Info.nLife = 0;
	m_Info.nIdxID = -1;
	m_nDamegeCounter = 0;
	m_pCurrent = nullptr;
	m_bDeath = false;
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
	m_Info.nLife = nlife;
	m_Info.nIdxID = -1;
	m_nDamegeCounter = 0;
	m_bDeath = false;
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

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CEnemy::Uninit(void)
{
	m_bDeath = true;

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

	CObject::Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CEnemy::Update(void)
{
	Controll();

	if (m_pMotion != NULL)
	{
		// �X�V����
		m_pMotion->Update();
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

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);
	
	if (m_pCurrent != nullptr)
	{
		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, 46.0f, m_Info.pos.z);

		D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

		// �}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_Info.mtxWorld,
			&m_Info.mtxWorld, m_pCurrent);
	}
	else
	{
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

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Controll(void)
{
	Move();

	if (m_Info.state == STATE_DAMEGE)
	{
		m_nDamegeCounter--;

		if (m_nDamegeCounter <= 0)
		{
			m_Info.state = STATE_NONE;
			m_nDamegeCounter = DAMEGECOUNT;
		}
	}

	if (m_Info.nLife <= 0)
	{
		CGame::GetEnemyManager()->Release(m_Info.nIdxID);
		int nNum = CGame::GetEnemyManager()->GetNum() - 1;
		CGame::GetEnemyManager()->SetNum(nNum);
		return;
	}

	if (m_Info.state != STATE_GRAP)
	{
		m_Info.move.y -= 0.9f;
	}

	// �ړ���
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.y += m_Info.move.y;
	m_Info.pos.z += m_Info.move.z;

	if (m_Info.pos.y <= 0.0f)
	{
		m_Info.pos.y = 0.0f;
	}

	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
	pDebugProc->Print("\n�G�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	pDebugProc->Print("�G�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	pDebugProc->Print("�G�̌����F%d\n", m_Info.nLife);
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Attack(void)
{
	/*if (m_Info.state != STATE_ATTACK)
	{
		m_Info.state = STATE_ATTACK;
		m_pMotion->Set(TYPE_ATTACK);
	}*/
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Move(void)
{
	////�v���C���[�̏��擾
	//CPlayer *pPlayer = CGame::GetPlayer();

	//if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), 400.0f, 50.0f) == true)
	//{//�~�̒��Ƀv���C���[��������

	//	D3DXVECTOR3 fDest, PlayerPos = pPlayer->GetPosition();

	//	float fDiffmove, fDestmove;

	//	fDest = m_Info.pos - PlayerPos;

	//	fDestmove = atan2f(fDest.x, fDest.z);
	//	fDiffmove = fDestmove - m_Info.rot.y;

	//	//�p�x�̒l���C������--------------------------------------------------
	//	if (fDiffmove >= D3DX_PI)
	//	{
	//		fDiffmove = -D3DX_PI;
	//	}
	//	else if (fDiffmove <= -D3DX_PI)
	//	{
	//		fDiffmove = D3DX_PI;
	//	}

	//	m_Info.rot.y += fDiffmove * 0.05f;

	//	//�p�x�̒l���C������--------------------------------------------------
	//	if (m_Info.rot.y > D3DX_PI)
	//	{
	//		m_Info.rot.y = -D3DX_PI;
	//	}
	//	else if (m_Info.rot.y < -D3DX_PI)
	//	{
	//		m_Info.rot.y = D3DX_PI;
	//	}

	//	//�ړ��ʂ��X�V(����������)
	//	m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * ENEMYMOVE;
	//	m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * ENEMYMOVE;

	//	if (fDest.x <= 60.0f && fDest.x >= -60.0f && fDest.z <= 60.0f && fDest.z >= -60.0f)
	//	{
	//		Attack();
	//		m_Info.move.x = 0.0f;
	//		m_Info.move.z = 0.0f;

	//		
	//	}
	//	else
	//	{
	//		if (m_Info.state != STATE_DASH)
	//		{
	//			m_Info.state = STATE_DASH;
	//			m_pMotion->Set(TYPE_DASH);
	//		}
	//	}

	//	m_Info.pos.x += m_Info.move.x * 0.5f;
	//	m_Info.pos.z += m_Info.move.z * 0.5f;
	//}
	//else
	//{
	//	m_Info.move.x = 0.0f;
	//	m_Info.move.z = 0.0f;

	//	if (m_Info.state != STATE_NEUTRAL)
	//	{
	//		m_Info.state = STATE_NEUTRAL;
	//		m_pMotion->Set(TYPE_NEUTRAL);
	//	}
	//}
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemy::Damege(int damege, float blowaway)
{
	m_Info.nLife -= damege;
	m_Info.move = D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y) * -blowaway, blowaway, cosf(CGame::GetPlayer()->GetRotition().y) * -blowaway);

	if (m_Info.state != STATE_DAMEGE)
	{
		m_Info.state = STATE_DAMEGE;
		m_pMotion->Set(TYPE_DAMEGE);
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
		m_pMotion->SetModel(&m_apModel[0], m_nNumModel);

		//����������
		m_pMotion->ReadText(fliename);

		m_pMotion->Set(TYPE_NEUTRAL);
	}
}

void CEnemy::SetChase(CHASE cha)
{
}
