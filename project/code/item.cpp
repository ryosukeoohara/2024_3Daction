//===========================================================
//
// �A�C�e������[item.cpp]
// Author �匴�叫
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "item.h"
#include "objectX.h"
#include "debugproc.h"

// �}�N����`
#define TEXT_NAME  ("data\\TEXT\\item.txt")  // �}�b�v�ɔz�u����A�C�e��

//================================================================
// �R���X�g���N�^
//================================================================
CItem::CItem()
{
	m_appObjectX = nullptr;
	m_apModelName = nullptr;
	m_nNumModel = 0;
	m_nNumItem = 0;
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename)
{
	
}

//================================================================
// �f�X�g���N�^
//================================================================
CItem::~CItem()
{

}

//================================================================
// ��������
//================================================================
CItem *CItem::Create(void)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CItem *pItem = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pItem = new CItem();

			//����������
			pItem->Init();
		}
	}

	return pItem;
}

//================================================================
// ��������
//================================================================
void CItem::TextLoad(void)
{
	char aString[128] = {};    // �����ǂݎ��p
	char aComment[128] = {};   // �e�L�X�g�t�@�C�����̃R�����g�ǂݎ��p
	char aFileName[128] = {};  // �t�@�C���̖��O�ǂݎ��p
	int nCntItem = 0;
	int nCntFileName = 0;
	int nType = -1;
	D3DXVECTOR3 pos, rot;      // �ǂݎ��p

	FILE *pFile;   //�t�@�C���|�C���^��錾

	pFile = fopen(TEXT_NAME, "r");

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
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumModel);  //���f���̑���

					m_apModelName = new char*[m_nNumModel];

				}  // NUM_MODEL�̂�����

				if (strcmp("NUM_ITEM", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumItem);  //���f���̑���

					m_appObjectX = new CObjectX*[m_nNumItem];

				}  // NUM_ITEM�̂�����

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);       //=
					fscanf(pFile, "%s", &aFileName[0]);  //���f���̖��O

					m_apModelName[nCntFileName] = aFileName;

					nCntFileName++;

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

					m_appObjectX[nCntItem] = CObjectX::Create(m_apModelName[nType]);
					m_appObjectX[nCntItem]->SetPosition(pos);
					m_appObjectX[nCntItem]->SetRotition(rot);
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

//================================================================
// ����������
//================================================================
HRESULT CItem::Init(void)
{
	TextLoad();

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CItem::Uninit(void)
{
	if (m_appObjectX != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_appObjectX[nCount]->Uninit();
			delete m_appObjectX[nCount];
			m_appObjectX[nCount] = nullptr;
		}

		delete m_appObjectX;
		m_appObjectX = nullptr;
	}
}

//================================================================
// �X�V����
//================================================================
void CItem::Update(void)
{
	
}