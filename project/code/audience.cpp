//===========================================================
//
// �}�b�v�̃��f��[map.cpp]
// Author �匴�叫
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "audience.h"
#include "objectX.h"
#include "debugproc.h"
#include "object.h"

//const char *CAudience::m_apTexName[MAX_ITEM] =
//{
//	"data\\MODEL\\refrigerator.x",
//	"data\\MODEL\\bike.x",     // ���]��
//};

// �}�N����`
#define TEXT_NAME  ("data\\TEXT\\audience.txt")  // �}�b�v

namespace
{
	const char *MODELNAME[CAudience::TYPE_MAX] =
	{
		"data\\MODEL\\",
		"data\\MODEL\\crowd_02.x",
		"data\\MODEL\\crowd_03.x",
		"data\\MODEL\\crowd_04.x",
	};
}

//================================================================
// �R���X�g���N�^
//================================================================
CAudience::CAudience()
{
	m_appObjectX = nullptr;
	m_nNumModel = 0;
	m_nNumItem = 0;
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
//CAudience::CAudience(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename)
//{
//
//}

//================================================================
// �f�X�g���N�^
//================================================================
CAudience::~CAudience()
{

}

//================================================================
// ��������
//================================================================
CAudience *CAudience::Create(void)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CAudience *pMap = nullptr;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pMap == nullptr)
		{
			//�I�u�W�F�N�g2D�̐���
			pMap = new CAudience();

			//����������
			pMap->Init();
		}
	}

	return pMap;
}

//================================================================
// ��������
//================================================================
void CAudience::TextLoad(void)
{
	//char aString[128] = {};    // �����ǂݎ��p
	//char aComment[128] = {};   // �e�L�X�g�t�@�C�����̃R�����g�ǂݎ��p
	//char aFileName[128] = {};  // �t�@�C���̖��O�ǂݎ��p
	//int nCntItem = 0;
	//int nCntFileName = 0;
	//int nType = -1;
	//D3DXVECTOR3 pos, rot;      // �ǂݎ��p

	//FILE *pFile;   //�t�@�C���|�C���^��錾

	//pFile = fopen(TEXT_NAME, "r");

	//if (pFile != NULL)
	//{//�t�@�C�����J�����ꍇ

	//	fscanf(pFile, "%s", &aString[0]);

	//	if (strcmp("SCRIPT", aString) == 0)
	//	{
	//		while (strcmp("END_SCRIPT", aString) != 0)
	//		{
	//			fscanf(pFile, "%s", &aString[0]);

	//			if (strcmp("NUM_ITEM", aString) == 0)
	//			{
	//				fscanf(pFile, "%s", &aString);      //=
	//				fscanf(pFile, "%d", &m_nNumItem);  //���f���̑���

	//			}  // NUM_ITEM�̂�����

	//			if (strcmp("MODEL_FILENAME", aString) == 0)
	//			{
	//				fscanf(pFile, "%s", &aString);       //=
	//				fscanf(pFile, "%s", &aFileName[0]);  //���f���̖��O

	//				strcpy(m_aTex[nCntFileName].aName, aFileName);
	//				nCntFileName++;

	//				m_appObjectX = new CObjectX*[MAX_MODEL];

	//			}  // MODEL_LILENAME�̂�����

	//			if (strcmp("MODELSET", aString) == 0)
	//			{
	//				while (strcmp("END_MODELSET", aString) != 0)
	//				{
	//					fscanf(pFile, "%s", &aString[0]);

	//					if (strcmp("TYPE", aString) == 0)
	//					{
	//						fscanf(pFile, "%s", &aString);      //=
	//						fscanf(pFile, "%d", &nType);  //���f���̑���
	//					}

	//					if (strcmp("POS", aString) == 0)
	//					{
	//						fscanf(pFile, "%s", &aString);      //=
	//						fscanf(pFile, "%f", &pos.x);  //���f���̑���
	//						fscanf(pFile, "%f", &pos.y);  //���f���̑���
	//						fscanf(pFile, "%f", &pos.z);  //���f���̑���
	//					}

	//					if (strcmp("ROT", aString) == 0)
	//					{
	//						fscanf(pFile, "%s", &aString);      //=
	//						fscanf(pFile, "%f", &rot.x);  //���f���̑���
	//						fscanf(pFile, "%f", &rot.y);  //���f���̑���
	//						fscanf(pFile, "%f", &rot.z);  //���f���̑���
	//					}
	//				}

	//				m_appObjectX[nCntItem] = CObjectX::Create(m_aTex[nType].aName);
	//				m_appObjectX[nCntItem]->SetPosition(pos);
	//				m_appObjectX[nCntItem]->SetRotition(rot);

	//				nCntItem++;

	//				m_nNumModel++;
	//			}
	//		}
	//	}

	//	//�t�@�C�������
	//	fclose(pFile);
	//}
	//else
	//{
	//	return;
	//}
}

//================================================================
// ����������
//================================================================
HRESULT CAudience::Init(void)
{
	TextLoad();

	m_appObjectX = new CObjectX*[10];

	int a = 0;

	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int n = 0; n < 10; n++)
	{
		a = rand() % TYPE_MAX;  //�U���̎�ޒ��I

		if (a == 0)
		{
			a += 1;
		}

		m_appObjectX[n] = nullptr;
		m_appObjectX[n] = CObjectX::Create(MODELNAME[a]);
		m_appObjectX[n]->SetPosition(D3DXVECTOR3(0.0f + n * 50.0f, 0.0f, -800.0f));
		m_appObjectX[n]->SetRotition(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CAudience::Uninit(void)
{
	/*if (m_appObjectX != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_appObjectX[nCount]->Uninit();
			delete m_appObjectX[nCount];
			m_appObjectX[nCount] = nullptr;
		}

		delete m_appObjectX;
		m_appObjectX = nullptr;
	}*/
}

//================================================================
// �X�V����
//================================================================
void CAudience::Update(void)
{

}