//===========================================================
//
// �|���S�����o�����[audience.h]
// Author �匴�叫
//
//===========================================================
#ifndef _AUDIENCE_H_      //���̃}�N����`������ĂȂ�������
#define _AUDIENCE_H_      //2�d�C���N���[�h�h�~�̃}�N����`������

#include "main.h"

class CObjectX;

// �}�N����`
#define MAX_MODEL (64)   // ���f���̍ő吔
#define MAX_NAME  (128)  // �e�N�X�`���̍ő啶����

//�A�C�e���N���X
class CAudience
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_01,
		TYPE_02,
		TYPE_03,
		TYPE_MAX
	};

	CAudience();  //�R���X�g���N�^
	~CAudience();  //�f�X�g���N�^

	HRESULT Init(void);   //�|���S���̏���������    
	void Uninit(void);    //�|���S���̏I������
	void Update(void);    //�|���S���̍X�V����

	static CAudience *Create(void);

	// �ݒ�n

	// �擾�n
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	int GetNum(void) { return m_nNumModel; }

private:

	struct TEX
	{
		char aName[MAX_NAME];
	};


	void TextLoad(void);
	CObjectX **m_appObjectX;

	int m_nNumModel;
	int m_nNumItem;

	TEX m_aTex[MAX_MODEL];
};

#endif