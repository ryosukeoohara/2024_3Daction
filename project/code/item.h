//===========================================================
//
//�|���S�����o�����[item.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ITEM_H_             //���̃}�N����`������ĂȂ�������
#define _ITEM_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "objectX.h"

class CObjectX;
class CBillBoard;

// �}�N����`
#define MAX_ITEM (2)

//�A�C�e���N���X
class CItem : public CObjectX
{
public:

	enum TYPE
	{
		TYPE_REF = 0,       // �①��
		TYPE_BIKE,          // ���]��
		TYPE_MICROWAVE,     // �d�q�����W
		TYPE_TABLE,         // �e�[�u��
		TYPE_POSTER,        // �Ŕ�
		TYPE_MAX
	};

	CItem();  //�R���X�g���N�^
	CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CItem();  //�f�X�g���N�^

	HRESULT Init(void);      //�|���S���̏���������    
	void Uninit(void);    //�|���S���̏I������
	void Update(void);    //�|���S���̍X�V����

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename);

	// �ݒ�n
	void SetType(TYPE type) { m_Type = type; }
	void SetID(int id) { m_nID = id; }
	
	// �擾�n
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	TYPE GetType(void) { return m_Type; }
	int GetID(void) { return m_nID; }

private:
	CObjectX **m_appObjectX;
	CBillBoard *m_pBill;
	TYPE m_Type;
	int m_nID;
	static const char *m_apTexName[MAX_ITEM];
};

#endif