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

//*============================================================================
// �ÓI�����o�ϐ�
//*============================================================================
CEnemy *CEnemyManager::m_pTop = nullptr;
CEnemy *CEnemyManager::m_pCur = nullptr;
CEnemy *CEnemyManager::m_pSNext = nullptr;

//*============================================================================
// �}�N����`
//*============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\enemyinformation.txt")    //�G�̍ő吔

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyManager::CEnemyManager()
{
	//������
	m_appEnemy = nullptr;
	m_nEnemyAll = 0;
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
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CEnemyManager::Uninit(void)
{
	if (m_appEnemy != nullptr)
	{
		for (int nCount = 0; nCount < m_nEnemyAll; nCount++)
		{
			if (m_appEnemy[nCount] != nullptr)
			{// �g�p����Ă�����

				// �I������
				m_appEnemy[nCount]->Uninit();
				delete m_appEnemy[nCount];
				m_appEnemy[nCount] = nullptr;
			}
		}

		delete m_appEnemy;
		m_appEnemy = nullptr;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void CEnemyManager::Update(void)
{
	
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

		pEnemyManager->ReadText();
	}

	return pEnemyManager;
}

//=============================================================================
//�e�L�X�g�t�@�C���ǂݍ���
//=============================================================================
void CEnemyManager::ReadText(void)
{
	int nLife = 0;
	int nCntEnemy = 0;
	char aString[128] = {};

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(ENEMY_TEXT, "r");

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

					}//ENEMYSET_END�̂����� 

					m_appEnemy[nCntEnemy] = nullptr;

					if (m_appEnemy[nCntEnemy] == nullptr)
					{
						m_appEnemy[nCntEnemy] = CEnemy::Create(m_Readpos, m_Readrot, nLife);

						nCntEnemy++;
					}

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

void CEnemyManager::ListOut(void)
{
	
}
