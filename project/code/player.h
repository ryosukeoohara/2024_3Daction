//===========================================================
//
//�|���S�����o�����[player.h]
//Author �匴�叫
//
//===========================================================
#ifndef _PLAYER_H_             //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//*==========================================================
//�C���N���[�h�t�@�C��
//*==========================================================
#include "object.h"

//*==========================================================
//�O���錾
//*==========================================================
class CMotion;
class CCharacter;
class CObjectX;

//*==========================================================
//�v���C���[�N���X
//*==========================================================
class CPlayer : public CObject
{
public:
	// ���
	enum STATE
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_AVOID,
		STATE_LIFT,
		STATE_GRAP,
		STATE_THROW,
		STATE_HEAT,
		STATE_MAX
	};

private:

	//���[�V����
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,                // �j���[�g����
		TYPE_MOVE,                       // �ړ�
		TYPE_ATTACK01,                   // �A��1�i��
		TYPE_ATTACK02,                   // �A��2�i��
		TYPE_ATTACK03,                   // �A��3�i�� 
		TYPE_AVOID,                      // ���
		TYPE_LIFT,                       // �����グ��
		TYPE_THROW,                      // ������
		TYPE_MAX
	} ;

	// �A��
	enum ATTACKTYPE
	{
		TYPE00_NONE = 0,
		TYPE01_ATTACK,
		TYPE02_ATTACK,
		TYPE03_ATTACK,
		TYPEMAX_ATTACK
	};

	enum DAMEGESTATE
	{
		DAMEGE_NONE = 0,
		DAMEGE_SMALL,
		DAMEGE_BIG,
		DAMEGE_MAX
	};

	// ���
	struct INFO
	{
		D3DXVECTOR3 pos;                  // �ʒu
		D3DXVECTOR3 posOld;               // �O��̈ʒu
		D3DXVECTOR3 rot;                  // ����
		D3DXVECTOR3 move;                 // �ړ�
		D3DXCOLOR col;                    // �F
		D3DXMATRIX mtxWorld;              // ���[���h�}�g���b�N�X
		STATE state;                      // ���
		ATTACKTYPE Atc;
	};

	INFO m_Info;                          // ���
	
public:
	CPlayer();  //�R���X�g���N�^
	CPlayer(D3DXVECTOR3 pos);  //�R���X�g���N�^(�I�[�o�[���[�h)
	~CPlayer();  //�f�X�g���N�^

	HRESULT Init(void);        // ����������    
	void Uninit(void);		   // �I������
	void Update(void);         // �X�V����
	void Draw(void);           // �`�揈��

	static CPlayer *Create(D3DXVECTOR3 pos);  // ����
	static CPlayer *Create(void);
	void Hit(void);			                  // �U��������������̏���

	//�@�ݒ�n
	void SetPosition(D3DXVECTOR3 pos) { m_Info.move = pos; }         // �ʒu�ݒ�
	void SetRotition(D3DXVECTOR3 rot) { m_Info.move = rot; }         // �����ݒ�
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }           // �ړ��ʐݒ�
	void SetState(STATE state) { m_Info.state = state; }             // ���
	void SetGrapItem(CObjectX *obj) { m_Obj = obj; }

	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // �ʒu�擾
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // �����擾
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // �ړ��ʎ擾
	STATE GetState(void) { return m_Info.state; }              // ���
	D3DXMATRIX *GetMatrix(void) { return &m_Info.mtxWorld; }     // �}�g���b�N�X
	CCharacter **GetChar(void) { return m_ppCharacter; }
	bool GetbAttack(void) { return m_bAttack; }                // �U�������ǂ���

private:

	void Control(void);                   // ����
	void Move(void);                      // �ړ�
	void Action(void);                    // �U��
	void GrapRotition(void);              // �W���C�A���g�X�C���O
	void ReadText(const char *fliename);  // �e�L�X�g�t�@�C���ǂݍ���

	int m_nNumModel;                    //���f��(�p�[�c)�̑���
	int m_nIdxTexture;
	int m_nIdxShaadow;
	int m_nIdx;
	int m_nParent;
	int m_nCntColi;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_pMotion;                   // ���[�V�����ւ̃|�C���^
	CCharacter **m_ppCharacter;           // �L�����N�^�[�ւ̃|�C���^
	CObjectX *m_Obj;
	float m_fDest;
	float m_fDestOld;
	float m_fDiff;
	float m_fGrapRot;
	bool m_bDesh;                         // �_�b�V��
	bool m_bAttack;                       // �U��
	bool m_bAvoid;                        // ���
	bool m_bLift;                         // �����グ��
	bool m_bGrap;                         // ����

	//�`���[�g���A���Ŏg���֐�,�ϐ�
	void ControlTutorial(void);          // �`���[�g���A���̃v���C���[�̐���
	bool m_bPushW;                       // W�L�[��������
	bool m_bPushA;                       // A�L�[��������
	bool m_bPushS;                       // S�L�[��������
	bool m_bPushD;                       // D�L�[��������
	bool m_bAvoi;                        // �������
	bool m_bWhee;                        // �z�C�[������]����
};

#endif