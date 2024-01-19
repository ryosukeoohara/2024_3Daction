//=============================================================================
//
// �G�̊Ǘ� [enemymanager.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//*============================================================================
//�C���N���[�h�t�@�C��
//*============================================================================
#include "main.h"
//#include "enemy.h"

// �O���錾
class CEnemy;

//*============================================================================
//�}�N����`
//*============================================================================
#define MAX_ENEMY   (64)    //�G�̍ő吔

//*============================================================================
//�N���X��`
//*============================================================================
class CEnemyManager
{
public:
	CEnemyManager();              //�R���X�g���N�^
	~CEnemyManager();             //�f�X�g���N�^
							       
	HRESULT Init(void);            //����������
	void Uninit(void);             //�I������
	void Update(void);             //�X�V����

	static CEnemyManager *Create(void);   // ��������

	static CEnemy *GetEnemy(void) { return m_pTop; }
							       
private:					       
	void ReadText(void);           //�e�L�X�g�t�@�C���ǂݍ���
	void ListOut(void);

	int m_nEnemyAll;               //�G�̑���
	CEnemy *m_pEnemy[MAX_ENEMY];   //�G�l�~�[�ւ̃|�C���^

	D3DXVECTOR3 m_Readpos;           //�e�L�X�g�t�@�C���̈ʒu�ǂݎ��p
	D3DXVECTOR3 m_Readrot;           //�e�L�X�g�t�@�C���̌����ǂݎ��p

	static CEnemy *m_pTop;  //�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pCur; //�Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pSNext;
	CEnemy *m_pPrev;       //�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CEnemy *m_pNext;       //���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;         //���S�t���O
};


#endif // !_ENEMYMANAGER_H_
