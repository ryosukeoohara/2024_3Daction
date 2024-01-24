//===========================================================
//
//�|���S�����o�����[item.h]
//Author �匴�叫
//
//===========================================================
#ifndef _ITEM_H_             //���̃}�N����`������ĂȂ�������
#define _ITEM_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

class CObjectX;

// �}�N����`
#define MAX_ITEM (2)

//�A�C�e���N���X
class CItem
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NEAR,      //�ߋ���
		TYPE_FAR,       //������
		TYPE_NAILBAT,   //�B�o�b�g
		TYPE_BOM,       //���e
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		STATE_NONE = 0,
		STATE_FALL,
		STATE_LAND,
		STATE_MAX
	} STATE;

	CItem();  //�R���X�g���N�^
	CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CItem();  //�f�X�g���N�^

	HRESULT Init(void);      //�|���S���̏���������    
	void Uninit(void);    //�|���S���̏I������
	void Update(void);    //�|���S���̍X�V����

	static CItem *Create(void);

	// �ݒ�n
	
	// �擾�n
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	int GetNum(void) { return m_nNumItem; }

private:
	void TextLoad(void);
	CObjectX **m_appObjectX;
	static const char *m_apTexName[MAX_ITEM];

	int m_nNumModel;
	int m_nNumItem;
};

#endif