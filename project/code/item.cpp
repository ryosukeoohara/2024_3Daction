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
#include "collision.h"
#include "player.h"
#include "billboard.h"
#include "texture.h"

// �}�N����`
#define TEXT_NAME  ("data\\TEXT\\item.txt")  // �}�b�v�ɔz�u����A�C�e��
#define TEX_GRAP   ("data\\TEXTURE\\arrow.png")  // �}�b�v�ɔz�u����A�C�e��

// �������O��Ԃ��`
namespace
{
	const D3DXVECTOR2 TEXSIZE = { 15.0f, 15.0f };  // �T�C�Y
}

//================================================================
// �R���X�g���N�^
//================================================================
CItem::CItem()
{
	m_pBill = nullptr;
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename) : CObjectX(aModelFliename)
{
	SetPosition(pos);
	SetRotition(rot);
	m_pBill = nullptr;
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

	if (CGame::GetCollision()->Circle(&GetPosition(), &CGame::GetPlayer()->GetPosition(), 40.0f, 40.0f) == true)
	{// �͈͓�

		if (m_Type != TYPE_MICROWAVE)
		{// ��ނ��d�q�����W�ȊO

			if (m_pBill == nullptr)
			{
				// �������Ĉʒu�A�T�C�Y�A�`�悷�邩�ǂ����A�g�p����e�N�X�`���ݒ�
				m_pBill = CBillBoard::Create();
				m_pBill->SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y + 40.0f, GetPosition().z));
				m_pBill->SetSize(TEXSIZE.x, TEXSIZE.y);
				m_pBill->SetDraw();
				m_pBill->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEX_GRAP));
			}
		}
	}
	else
	{// �͈͊O

		if (m_pBill != nullptr)
		{
			// �I��
			m_pBill->Uninit();
			m_pBill = nullptr;
		}
	}
}