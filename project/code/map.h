//===========================================================
//
//�|���S�����o�����[item.h]
//Author �匴�叫
//
//===========================================================
#ifndef _MAP_H_             //���̃}�N����`������ĂȂ�������
#define _MAP_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "main.h"

class CObjectX;

// �}�N����`
#define MAX_MODEL (512)  // ���f���̍ő吔
#define MAX_NAME  (128)  // �e�N�X�`���̍ő啶����

//�A�C�e���N���X
class CMap
{
public:

	CMap();  //�R���X�g���N�^
	~CMap();  //�f�X�g���N�^

	HRESULT Init(void);   //�|���S���̏���������    
	void Uninit(void);    //�|���S���̏I������
	void Update(void);    //�|���S���̍X�V����

	static CMap *Create(void);

	// �ݒ�n

	// �擾�n
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	int GetNum(void) { return m_nNumModel; }

private:

	struct TEX
	{
		char aName[MAX_NAME];
	} ;
	

	void TextLoad(void);
	CObjectX **m_appObjectX;

	int m_nNumModel;
	int m_nNumItem;

	TEX m_aTex[MAX_MODEL];
};

#endif