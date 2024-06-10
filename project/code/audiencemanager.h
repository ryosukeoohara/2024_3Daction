//===========================================================
//
// ����Ō��Ă���l�̊Ǘ�[audiencemanager.h]
// Author �匴�叫
//
//===========================================================
#ifndef _AUDIENCEMANAGER_H_      //���̃}�N����`������ĂȂ�������
#define _AUDIENCEMANAGER_H_      //2�d�C���N���[�h�h�~�̃}�N����`������

#include "main.h"
#include "objectX.h"

// �}�N����`
#define MAX_MODEL (64)   // ���f���̍ő吔
#define MAX_NAME  (128)  // �e�N�X�`���̍ő啶����

//�A�C�e���N���X
class CAudienceManager
{
public:

	enum TYPE
	{
		TYPE_01 = 0,
		TYPE_02,
		TYPE_03,
		TYPE_04,
		TYPE_MAX
	};

	CAudienceManager();  //�R���X�g���N�^
	~CAudienceManager();  //�f�X�g���N�^

	HRESULT Init(void);   // ����������    
	void Uninit(void);    // �I������
	void Update(void);    // �X�V����
	void Draw(void);      // �`�揈��

	static CAudienceManager* Create(void);

private:

	//static CAudience* m_pTop;  //�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	//static CAudience* m_pCur;  //�Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	//CAudience* m_pNext;        //���̃I�u�W�F�N�g�ւ̃|�C���^
	//CAudience* m_pPrev;        //�O�̃I�u�W�F�N�g�ւ̃|�C���^
};

#endif