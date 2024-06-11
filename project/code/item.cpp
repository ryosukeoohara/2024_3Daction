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

// �ÓI�����o�ϐ�
CItem *CItem::m_pTop = nullptr;
CItem *CItem::m_pCur = nullptr;


// �}�N����`
#define TEXT_NAME  ("data\\TEXT\\item.txt")        // �}�b�v�ɔz�u����A�C�e��
#define TEX_GRAP   ("data\\TEXTURE\\Ybutton.png")  // �}�b�v�ɔz�u����A�C�e��

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

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;
		m_pPrev = m_pCur;
		m_pCur = this;
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;
		m_pCur = this;
	}
}

//================================================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, int nIdx, const char *aModelFliename) : CObjectX(aModelFliename)
{
	SetPosition(pos);
	SetRotition(rot);
	m_pBill = nullptr;

	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ

		m_pCur->m_pNext = this;
		m_pPrev = m_pCur;
		m_pCur = this;
	}
	else
	{// ���݂��Ȃ��ꍇ

		m_pTop = this;
		m_pCur = this;
	}
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
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type, int nIdx, const char *aModelFliename)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CItem *pItem = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//�I�u�W�F�N�g2D�̐���
			pItem = new CItem(pos, rot, type, nIdx, aModelFliename);

			//����������
			pItem->Init();
			pItem->SetType(type);
			pItem->SetID(nIdx);
		}
	}

	return pItem;
}

//================================================================
// �f�[�u���Ƃ̓����蔻��
//================================================================
void CItem::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, float fRadius)
{
	if (m_Type == TYPE_TABLE)
	{
		D3DXVECTOR3 vtxMax = GetVtxMax();
		D3DXVECTOR3 vtxMin = GetVtxMin();

		D3DXVECTOR3 Itempos = GetPosition();

		if (pos->z + fRadius > Itempos.z + vtxMin.z
			&& pos->z + -fRadius < Itempos.z + vtxMax.z)
		{
			//�u���b�N�̉E����==================================
			if (pos->x + -fRadius <= Itempos.x + vtxMax.x
				&& posOld->x + -fRadius >= Itempos.x + vtxMax.x)
			{
				pos->x = (Itempos.x + vtxMax.x) - -fRadius;

				//return true;
			}
			//�u���b�N�̍�����==================================
			if (pos->x + fRadius >= Itempos.x + vtxMin.x
				&& posOld->x + fRadius <= Itempos.x + vtxMin.x)
			{
				pos->x = (Itempos.x + vtxMin.x) - fRadius;

				//return true;
			}
		}

		if (pos->x + fRadius > Itempos.x + vtxMin.x
			&& pos->x + -fRadius < Itempos.x + vtxMax.x)
		{
			//�u���b�N�̏�======================================
			if (pos->z - fRadius <= Itempos.z + vtxMax.z
				&& posOld->z - fRadius >= Itempos.z + vtxMax.z)
			{
				pos->z = (Itempos.z + vtxMax.z) + fRadius + fRadius;

				//return true;
			}

			//�u���b�N�̉�======================================
			if (pos->z + fRadius >= Itempos.z + vtxMin.z
				&& posOld->z + fRadius <= Itempos.z + vtxMin.z)
			{
				pos->z = (Itempos.z + vtxMin.z) - fRadius;

				//return true;
			}
		}
	}
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

	CObjectX::Uninit();

	//CGame::GetItemManager()->Release(m_nID);
}

//================================================================
// �X�V����
//================================================================
void CItem::Update(void)
{
	CObjectX::Update();

	if (CPlayer::GetPlayer() == nullptr)
		return;

	if (CGame::GetCollision()->Circle(&GetPosition(), &CPlayer::GetPlayer()->GetPosition(), 40.0f, 40.0f) == true)
	{// �͈͓�

		if (m_Type != TYPE_MICROWAVE && m_Type != TYPE_TABLE && m_Type != TYPE_POSTER && CPlayer::GetPlayer()->GetGrapItem() == nullptr)
		{// ��ނ��d�q�����W���e�[�u���ȊO

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
	
	if(CGame::GetCollision()->Circle(&GetPosition(), &CPlayer::GetPlayer()->GetPosition(), 40.0f, 40.0f) != true || CPlayer::GetPlayer()->GetGrapItem() != nullptr)
	{// �͈͊O

		if (m_pBill != nullptr)
		{
			// �I��
			m_pBill->Uninit();
			m_pBill = nullptr;
		}
	}
}