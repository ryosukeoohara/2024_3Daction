//=============================================================================
//
// �G�̊Ǘ� [enemymanager.cpp]
// Author : �匴�@�叫
//
//=============================================================================

//*============================================================================
// �C���N���[�h�t�@�C��
//*============================================================================
#include "enemymanager.h"
#include "enemy.h"
#include "enemy_weak.h"
#include "enemy_boss.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

//*============================================================================
// �ÓI�����o�ϐ�
//*============================================================================
CEnemy *CEnemyManager::m_pTop = nullptr;
CEnemy *CEnemyManager::m_pCur = nullptr;
CEnemy *CEnemyManager::m_pSNext = nullptr;
int CEnemyManager::m_nNum = 0;

//*============================================================================
// �}�N����`
//*============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyManager::CEnemyManager()
{
	//������
	m_appEnemy = nullptr;
	m_nEnemyAll = 0;
	m_nNum = 0;
	m_Readpos = { 0.0f,0.0f,0.0f };
	m_Readrot = { 0.0f,0.0f,0.0f };
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemyManager::~CEnemyManager()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CEnemyManager::Init(void)
{
	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		ReadText(ENEMYINFO_TEXT);
	}
	else if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_TUTORIAL)
	{
		ReadText(TUTORIALENEMY_TEXT);
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CEnemyManager::Uninit(void)
{
	
}

//=============================================================================
//�X�V����
//=============================================================================
void CEnemyManager::Update(void)
{
	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
	pDebugProc->Print("�G�̐��F%d\n", m_nNum);
}

//=============================================================================
// ��������
//=============================================================================
CEnemyManager * CEnemyManager::Create(void)
{
	CEnemyManager *pEnemyManager = nullptr;

	if (pEnemyManager == nullptr)
	{
		pEnemyManager = new CEnemyManager();

		pEnemyManager->Init();
	}

	return pEnemyManager;
}

//=============================================================================
//�e�L�X�g�t�@�C���ǂݍ���
//=============================================================================
void CEnemyManager::ReadText(const char *text)
{
	int nLife = 0;
	int nType = -1;
	char aString[128] = {};

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(text, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp("ALL_ENEMY", aString) == 0)
			{
				fscanf(pFile, "%s", &aString);          //=
				fscanf(pFile, "%d", &m_nEnemyAll);  //���f���̑���

				m_appEnemy = new CEnemy*[m_nEnemyAll];
				//m_nNum = m_nEnemyAll;

			}  //NUM_MODEL�̂�����

			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("ENEMYSET", aString) == 0)
				{
					while (strcmp("ENEMYSET_END", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &m_Readpos.x);  //�G�̈ʒu
							fscanf(pFile, "%f", &m_Readpos.y);  //�G�̈ʒu
							fscanf(pFile, "%f", &m_Readpos.z);  //�G�̈ʒu
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &m_Readrot.x);  //�G�̌���
							fscanf(pFile, "%f", &m_Readrot.y);  //�G�̌���
							fscanf(pFile, "%f", &m_Readrot.z);  //�G�̌���
						}

						if (strcmp("LIFE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);       //=
							fscanf(pFile, "%d", &nLife);       //�G�̗̑�
						}

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);       //=
							fscanf(pFile, "%d", &nType);       //�G�̗̑�
						}

					}//ENEMYSET_END�̂����� 

					if (nType == CEnemy::WEAK)
					{
						CEnemyWeak::Create(m_Readpos, m_Readrot, nLife);

					}
					else if (nType == CEnemy::BOSS)
					{
						CEnemyBoss::Create(m_Readpos, m_Readrot, nLife);
					}

					m_nNum++;
					
				}//ENEMYSET�̂����� 
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//=============================================================================
// �q�[�g�A�N�V�����̃^�[�Q�b�g
//=============================================================================
void CEnemyManager::SetTarget(int idx)
{
	CEnemy *pEnemy = CEnemy::GetTop();

	while (pEnemy != nullptr)
	{
		CEnemy *pEnemyNext = pEnemy->GetNext();

 		int n = pEnemy->GetIdxID();

		if (n != idx)
		{
			pEnemy->SetDraw(false);
		}

		pEnemy = pEnemyNext;
	}
}

//=============================================================================
// �q�[�g�A�N�V�����̃^�[�Q�b�g
//=============================================================================
void CEnemyManager::SetTrue(int idx)
{
	CEnemy *pEnemy = CEnemy::GetTop();

	while (pEnemy != nullptr)
	{
		CEnemy *pEnemyNext = pEnemy->GetNext();

		if (pEnemy->GetIdxID() != idx)
		{
			pEnemy->SetDraw(true);
		}

		pEnemy = pEnemyNext;
	}
}

//=============================================================================
// �������蓮���Ȃ�������
//=============================================================================
void CEnemyManager::SetMobility(void)
{
	CEnemy *pEnem = CEnemy::GetTop();

	while (pEnem != nullptr)
	{
		CEnemy *pEnemNext = pEnem->GetNext();
		pEnem->SetMobile();
		pEnem = pEnemNext;
	}
}