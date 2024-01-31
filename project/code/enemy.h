//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"

//*=============================================================================
//�N���X��`
//*=============================================================================
class CMotion;
class CCharacter;

//*=============================================================================
//�N���X��`
//*=============================================================================
class CEnemy : public CObject
{
public:

	// ���
	enum STATE
	{
		STATE_NONE = 0,    // �Ȃ���Ȃ�
		STATE_NEUTRAL,     // �ҋ@
		STATE_DASH,        // �ړ�
		STATE_WALK,        // �ړ�
		STATE_ATTACK,      // �U��
		STATE_GRAP,        // �������҂�
		STATE_DAMEGE,      // �U���󂯂�
		STATE_MAX
	};

	//���[�V����
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // �j���[�g����
		TYPE_DASH,                     // �ړ�
		TYPE_ATTACK,                   // �U��
		TYPE_DAMEGE,                   // �_���[�W
		TYPE_MAX
	};

private:

	struct INFO
	{
		D3DXVECTOR3 pos;                         // �ʒu
		D3DXVECTOR3 posOld;                      // �O��̈ʒu
		D3DXVECTOR3 rot;                         // ����
		D3DXVECTOR3 move;                        // �ړ���
		D3DXMATRIX mtxWorld;                     // ���[���h�}�g���b�N�X
		STATE state;                             // ���
		int nIdxID;                              // �C���f�b�N�X�ԍ�
		int nLife;                               // �̗�
	};

	INFO m_Info;                                 // ���

public:

	CEnemy();                                  //�R���X�g���N�^
	CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //�R���X�g���N�^
	~CEnemy();                                 //�f�X�g���N�^
										       
	HRESULT Init(void);                        //������
	void Uninit(void);                         //�I��
	void Update(void);                         //�X�V
	void Draw(void);                           //�`��

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //����
	void ReadText(char *fliename);             //�e�L�X�g�t�@�C���ǂݍ���

	//�@�ݒ�n
	void SetPosition(D3DXVECTOR3 pos) { m_Info.pos = pos; }         // �ʒu
	void SetRotition(D3DXVECTOR3 rot) { m_Info.rot = rot; }         // ����
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }          // �ړ���
	void SetState(STATE state) { m_Info.state = state; }            // ���
	void SetLife(int nLife) { m_Info.nLife = nLife; }               // �̗�
	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }  // �e�̃}�g���b�N�X

	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // �ʒu
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // ����
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // �ړ���
	STATE GetState(void) { return m_Info.state; }              // ���
	int GetLife(void) { return m_Info.nLife; }                 // �̗�
	CCharacter **GetCharcter(void) { return m_apModel; }
	static int GetNumAll(void) { return m_nNumAll; }
	CMotion *GetMotion(void) { return m_pMotion; }

								       
private:

	void Controll(void);                       // ���䏈��
	void Attack(void);
	void Move(void);
	void Damege(void);

	//CEnemy *m_apEnemy[]
	CMotion *m_pMotion;                        // ���[�V�����ւ̃|�C���^
	CCharacter **m_apModel;                    // ���f��(�p�[�c)�ւ̃|�C���^
	static int m_nNumAll;                      // �G�̑���
	int m_nDamegeCounter;                      // �_���[�W��Ԃł���J�E���g
	D3DXMATRIX *m_pCurrent;                     // �e�̃}�g���b�N�X
	static CEnemy *m_pTop;  //�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pCur; //�Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static CEnemy *m_pNext;
	CEnemy *m_pPrev;       //�O�̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;          //���S�t���O
	
	//*=============================================================================
	// �O���t�@�C���ǂݍ��ݗp
	//*=============================================================================
	D3DXVECTOR3 m_Readpos;                     // �ʒu�ǂݍ��ݗp
	D3DXVECTOR3 m_Readrot;                     // �����ǂݍ��ݗp
	int m_nIdx;                                // �C���f�b�N�X�ԍ�
	int m_nParent;                             // �e�̃C���f�b�N�X�ԍ�
	int m_nNumModel;                           // ���f��(�p�[�c)�̑���
	char m_filename[128] = {};                 // �����ǂݍ��ݗp

};

#endif // !_ENEMY_H_