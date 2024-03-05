//===========================================================
//
//�|���S�����o�����[object.cpp]
//Author �匴�叫
//
//===========================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"

CObject *CObject::m_apObjct[MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

////================================================================
////�R���X�g���N�^
////================================================================
//CObject::CObject()
//{
//	if (m_nNumAll < MAX_OBJECT)
//	{
//		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//		{
//			if (m_apObjct[nCntObject] == NULL)
//			{//�g�p����Ă��Ȃ�������
//
//				m_apObjct[nCntObject] = this;  //�������g����
//				m_nID = nCntObject;  //�������g��ID
//				m_nNumAll++;         //�������J�E���g�A�b�v
//				break;
//			}
//		}
//	}
//}
//
////================================================================
////�f�X�g���N�^
////================================================================
//CObject::~CObject()
//{
//	
//}
//
////================================================================
////���ׂẴI�u�W�F�N�g�̔j��
////================================================================
//void CObject::ReleaseAll(void)
//{
//	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//	{
//		if (m_apObjct[nCntObject] != NULL)
//		{
//			//�I������
//			m_apObjct[nCntObject]->Uninit();
//		}
//	}
//}
//
////================================================================
////���ׂẴI�u�W�F�N�g�̍X�V
////================================================================
//void CObject::UpdateAll(void)
//{
//	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//	{
//		if (m_apObjct[nCntObject] != NULL)
//		{
//			//�X�V����
//			m_apObjct[nCntObject]->Update();
//		}
//	}
//
//	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
//
//	pDebugProc->Print("\n\n�I�u�W�F�N�g�̑����F%d", m_nNumAll);
//}
//
////================================================================
////���ׂẴI�u�W�F�N�g�̕`��
////================================================================
//void CObject::DrawAll(void)
//{
//	CCamera *pCamera = CManager::Getinstance()->GetCamera();
//
//	if (pCamera != NULL)
//	{
//		//�J�����̐ݒ�
//		pCamera->SetCamera();
//	}
//	
//	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//	{
//		if (m_apObjct[nCntObject] != NULL)
//		{
//			//�`�揈��
//			m_apObjct[nCntObject]->Draw();
//		}
//	}
//}
//
////================================================================
////�I�u�W�F�N�g�̔j��
////================================================================
//void CObject::Release(void)
//{
//	int nIdx = m_nID;
//
//	//�I�u�W�F�N�g�̔j��
//	if (m_apObjct[nIdx] != NULL)
//	{
//		//���������J��
//		delete m_apObjct[nIdx];
//
//		//�g�p���Ă��Ȃ���Ԃɂ���
//		m_apObjct[nIdx] = NULL;
//
//		m_nNumAll--;    //�������J�E���g�_�E��
//	}
//}
//
////================================================================
////�I�u�W�F�N�g�̎擾
////================================================================
//CObject *CObject::Getobject(int nIdx)
//{
//	return m_apObjct[nIdx];
//}

//================================================================
//�e�N�X�`���擾
//================================================================
//void CObject::BindTexture(LPDIRECT3DTEXTURE9 m_Texture)
//{
//	m_pTexture = m_Texture;
//}

CObject *CObject::m_pTop[NUM_PRIORITY] = {};
CObject *CObject::m_pCur[NUM_PRIORITY] = {};

//================================================================
//�R���X�g���N�^
//================================================================
CObject::CObject(int nPriority)
{
	m_bDeath = false;

	this->SetPriority(nPriority);

	CObject *pObject = m_pTop[nPriority];

	if (m_pTop[nPriority] != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur[nPriority]->m_pNext = this;
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority] = this;
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop[nPriority] = this;
		m_pCur[nPriority] = this;
	}
}

//================================================================
//�f�X�g���N�^
//================================================================
CObject::~CObject()
{

}

//================================================================
//���ׂẴI�u�W�F�N�g�̔j��
//================================================================
void CObject::ReleaseAll(void)
{
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject *pObject = m_pTop[i];

		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Uninit();

			pObject = pObjectNext;
		}
	}
}

//================================================================
//���ׂẴI�u�W�F�N�g�̍X�V
//================================================================
void CObject::UpdateAll(void)
{
	DeadChuck();

	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject *pObject = m_pTop[i];

		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Update();
			pObject = pObjectNext;
		}
	}

	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\n\n�I�u�W�F�N�g�̑����F%d", m_nNumAll);
}

//================================================================
//���ׂẴI�u�W�F�N�g�̕`��
//================================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	DeadChuck();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject *pObject = m_pTop[i];

		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Draw();
			pObject = pObjectNext;
		}
	}
}

//================================================================
//�I�u�W�F�N�g�̔j��
//================================================================
void CObject::Release(void)
{
	// ����
	m_bDeath = true;
}

//================================================================
//�I�u�W�F�N�g�̎擾
//================================================================
CObject *CObject::Getobject(int nIdx)
{
	return m_apObjct[nIdx];
}

//================================================================
//�I�u�W�F�N�g�̎擾
//================================================================
void CObject::DeadChuck(void)
{
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject *pObject = m_pTop[i];

		while (pObject != nullptr)
		{
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bDeath == true)
			{
				// ���X�g���玩�����g���폜����
				if (m_pTop[i] == pObject)
				{// ���g���擪

					if (pObject->m_pNext != nullptr)
					{// �������݂��Ă���

						m_pTop[i] = pObject->m_pNext;	// ����擪�ɂ���
						pObject->m_pNext->m_pPrev = nullptr;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
					}
					else
					{// ���݂��Ă��Ȃ�

						m_pTop[i] = nullptr;	// �擪���Ȃ���Ԃɂ���
						m_pCur[i] = nullptr;	// �Ō�����Ȃ���Ԃɂ���
					}
				}
				else if (m_pCur[i] == pObject)
				{// ���g���Ō��

					if (pObject->m_pPrev != nullptr)
					{// �������݂��Ă���

						m_pCur[i] = pObject->m_pPrev;			// �O���Ō���ɂ���
						pObject->m_pPrev->m_pNext = nullptr;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
					}
					else
					{// ���݂��Ă��Ȃ�

						m_pTop[i] = nullptr;	// �擪���Ȃ���Ԃɂ���
						m_pCur[i] = nullptr;	// �Ō�����Ȃ���Ԃɂ���
					}
				}
				else
				{
					if (pObject->m_pNext != nullptr)
					{
						pObject->m_pNext->m_pPrev = pObject->m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
					}
					if (pObject->m_pPrev != nullptr)
					{
						pObject->m_pPrev->m_pNext = pObject->m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
					}
				}
			}

			pObject = pObjectNext;
		}
	}
}
