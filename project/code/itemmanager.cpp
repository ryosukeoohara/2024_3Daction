//=============================================================================
//
// �G�̊Ǘ� [itemmanager.cpp]
// Author : �匴�@�叫
//
//=============================================================================

//*============================================================================
// �C���N���[�h�t�@�C��
//*============================================================================
#include "itemmanager.h"
#include "item.h"

//*============================================================================
// �ÓI�����o�ϐ�
//*============================================================================

//*============================================================================
// �}�N����`
//*============================================================================
#define ITEM_TEXT ("data\\TEXT\\item.txt")

const char *CItemManager::m_apTexName[CItem::TYPE_MAX] =
{
	"data\\MODEL\\refrigerator.x",  // �①��
	"data\\MODEL\\bike.x",          // ���]��
	"data\\MODEL\\microwave.x",     // �d�q�����W
	"data\\MODEL\\table.x",         // �f�[�u��
	"data\\MODEL\\poster.x",        // �Ŕ�
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemManager::CItemManager()
{
	//������
	m_ppItem = nullptr;
	m_nNum = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CItemManager::~CItemManager()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CItemManager::Init(void)
{
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CItemManager::Uninit(void)
{
	//if (m_ppItem != nullptr)
	//{
	//	for (int nCount = 0; nCount < m_nNumItem; nCount++)
	//	{
	//		if (m_ppItem[nCount] != nullptr)
	//		{// �g�p����Ă�����

	//			// �I������
	//			m_ppItem[nCount]->Uninit();
	//			m_ppItem[nCount] = nullptr;
	//		}
	//	}

	//	delete m_ppItem;
	//	m_ppItem = nullptr;
	//}
}

//=============================================================================
//�X�V����
//=============================================================================
void CItemManager::Update(void)
{
	
}

//=============================================================================
// ��������
//=============================================================================
CItemManager * CItemManager::Create(const char* filename)
{
	CItemManager *pItemManager = nullptr;

	if (pItemManager == nullptr)
	{
		pItemManager = new CItemManager();

		pItemManager->Init();

		pItemManager->ReadText(filename);
	}

	return pItemManager;
}

//=============================================================================
// ����
//=============================================================================
void CItemManager::Release(int idx)
{
	CItem *pItem = CItem::GetTop();

	while (pItem != nullptr)
	{
		CItem *pItemNext = pItem->GetNext();

		if (pItem->GetID() == idx)
		{
			pItem->Uninit();
		}

		pItem = pItemNext;
	}
}

//=============================================================================
//�e�L�X�g�t�@�C���ǂݍ���
//=============================================================================
void CItemManager::ReadText(const char *text)
{
	char aString[128] = {};    // �����ǂݎ��p
	char aFileName[128] = {};  // �t�@�C���̖��O�ǂݎ��p
	int nCntItem = 0;
	int nType = -1;
	D3DXVECTOR3 pos = {}, rot = {};      // �ǂݎ��p

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(text, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_ITEM", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumItem);  //���f���̑���

					//m_ppItem = new CItem*[m_nNumItem];

				}  // NUM_ITEM�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);       //=
					fscanf(pFile, "%s", &aFileName[0]);  //���f���̖��O

				}  // MODEL_LILENAME�̂�����

				if (strcmp("ITEMSET", aString) == 0)
				{
					while (strcmp("END_ITEMSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%d", &nType);  //���f���̑���
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &pos.x);  //���f���̑���
							fscanf(pFile, "%f", &pos.y);  //���f���̑���
							fscanf(pFile, "%f", &pos.z);  //���f���̑���
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &rot.x);  //���f���̑���
							fscanf(pFile, "%f", &rot.y);  //���f���̑���
							fscanf(pFile, "%f", &rot.z);  //���f���̑���
						}
					}

					CItem::Create(pos, rot, (CItem::TYPE)nType, m_nNum, m_apTexName[nType]);
					//m_ppItem[nCntItem]->SetID(nCntItem);
					m_nNum++;
					nCntItem++;
				}
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
// �R���X�g���N�^
//=============================================================================
void CItemManager::ListOut(void)
{

}