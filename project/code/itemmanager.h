//=============================================================================
//
// �A�C�e���̊Ǘ� [itemmanager.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

//*============================================================================
// �C���N���[�h�t�@�C��
//*============================================================================
#include "main.h"
#include "item.h"

//*============================================================================
// �}�N����`
//*============================================================================

//*============================================================================
// �N���X��`
//*============================================================================
class CItemManager
{
public:
	CItemManager();              //�R���X�g���N�^
	~CItemManager();             //�f�X�g���N�^

	HRESULT Init(void);            //����������
	void Uninit(void);             //�I������
	void Update(void);             //�X�V����

	static CItemManager *Create(const char* filename);   // ��������
	void Release(int idx);
	void ReadText(const char *text);           //�e�L�X�g�t�@�C���ǂݍ���

											   // �ݒ�n
	void SetNum(int num) { m_nNumItem = num; }

	// �擾�n
	CItem **GetItem(void) { return m_ppItem; }
	int GetNum(void) { return m_nNumItem; }

private:
	void ListOut(void);

	CItem **m_ppItem;

	int m_nNumModel;
	int m_nNumItem;
	int m_nNum;

	static const char *m_apTexName[CItem::TYPE_MAX];
};

#endif // !_ENEMYMANAGER_H_