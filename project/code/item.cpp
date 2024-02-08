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
#include "object.h"
#include "itemmanager.h"
#include "game.h"


// �}�N����`
#define TEXT_NAME  ("data\\TEXT\\item.txt")  // �}�b�v�ɔz�u����A�C�e��

//================================================================
// �R���X�g���N�^
//================================================================
CItem::CItem()
{
	
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename) : CObjectX(aModelFliename)
{
	SetPosition(pos);
	SetRotition(rot);
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
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type, const char *aModelFliename)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CItem *pItem = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pItem = new CItem(pos, rot, type, aModelFliename);

			//����������
			pItem->Init();
			pItem->SetType(type);
		}
	}

	return pItem;
}

//================================================================
// ����������
//================================================================
HRESULT CItem::Init(void)
{
	CObjectX::Init();

	return S_OK;
}

//================================================================
// �I������
//================================================================
void CItem::Uninit(void)
{
	CObjectX::Uninit();

	//CGame::GetItemManager()->Release(m_nID);
}

//================================================================
// �X�V����
//================================================================
void CItem::Update(void)
{
	CObjectX::Update();
}