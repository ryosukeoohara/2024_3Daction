//===========================================================
//
//�|���S�����o�����[player.h]
//Author �匴�叫
//
//===========================================================
#ifndef _PLAYER_H_             //���̃}�N����`������ĂȂ�������
#define _PLAYER_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

//*==========================================================
// �C���N���[�h�t�@�C��
//*==========================================================
#include "object.h"

//*==========================================================
// �O���錾
//*==========================================================
class CMotion;
class CCharacter;
class CObjectX;
class CGage2D;
class CGage3D;
class CBillBoard;
class CEnemy;
class CObject2D;
class CItem;

//*==========================================================
// �v���C���[�N���X
//*==========================================================
class CPlayer : public CObject
{
public:
	// ���
	enum STATE
	{
		STATE_NONE = 0,     // �Ȃ���Ȃ�
		STATE_NEUTRAL,      // �j���[�g����
		STATE_GRAPNEUTRAL,  // �͂ݏ�Ԃ̃j���[�g����
		STATE_MOVE,         // �ړ�
		STATE_ATTACK,       // �U��
		STATE_AVOID,        // ���
		STATE_LIFT,         // �A�C�e���͂�ł�
		STATE_GRAP,         // �͂�
		STATE_THROW,        // ������
		STATE_HEAT,         // �q�[�g�A�N�V����
		STATE_GRAPDASH,     // �͂�ő���
		STATE_ENEMYGRAP,    // �G�𓊂���
		STATE_GRAPWALK,     // �G��͂�ŕ���
		STATE_DAMEGE,       // �_���[�W
		STATE_INVINCIBE,    // ���G
		STATE_DEHT,         // ��Smash
		STATE_MAX
	};

	enum HEAT
	{
		HEAT_NONE = 0,  // �Ȃ���Ȃ�
		HEAT_SMASH,     // ��������
		HEAT_FIRE,      // �d�q�����W
		HEAT_MAX
	};

	// �A��
	enum ATTACKTYPE
	{
		TYPE_NONE = 0,          // �Ȃ���Ȃ�
		TYPE_ATTACK1,          // ��i��
		TYPE_ATTACK2,          // ��i��
		TYPE_ATTACK3,          // �O�i��
		TYPE_HEATACTBIKE,       // �q�[�g�A�N�V�����E�o�C�N
		TYPE_HEATACTREF,        // �q�[�g�A�N�V�����E�①��
		TYPE_HEATACTMICROWAVE,  // �q�[�g�A�N�V�����E�d�q�����W
		TYPEMAX_ATTACK
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
		TYPE_GRAPDASH,                   // �����đ���
		TYPE_GRAP,                       // �͂�
		TYPE_GRAPNEUTRAL,                // �͂݃j���[�g����
		TYPE_ENEMYGRAP,                  // �G��͂�œ�����
		TYPE_GRAPWALK,                   // �͂�ŕ���
		TYPE_MAX
	} ;

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
		int nLife;
	};

	struct GRAP
	{
		CItem *pItem;                     // �A�C�e��
		CEnemy *pEnemy;                   // �G
	};

	INFO m_Info;                          // ���
	GRAP m_Grap;                          // �͂ނł������
	HEAT m_HeatAct;
	
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
	void Damage(int nDamage, float fKnockBack);			              // �U��������������̏���
	void TitleWalk(void);                     // �^�C�g��

	//�@�ݒ�n
	void SetPosition(D3DXVECTOR3 pos) { m_Info.pos = pos; }         // �ʒu�ݒ�
	void SetRotition(D3DXVECTOR3 rot) { m_Info.rot = rot; }         // �����ݒ�
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }           // �ړ��ʐݒ�
	void SetState(STATE state) { m_Info.state = state; }             // ���
	void SetGrapItem(CItem *obj) { m_Grap.pItem = obj; }
	void SetLife(int nlife) { m_Info.nLife = nlife; }                // �̗�

	// �擾�n
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // �ʒu�擾
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // �����擾
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // �ړ��ʎ擾
	STATE GetState(void) { return m_Info.state; }              // ���
	int GetLife(void) { return m_Info.nLife; }                 // �̗�
	D3DXMATRIX *GetMatrix(void) { return &m_Info.mtxWorld; }     // �}�g���b�N�X
	CCharacter **GetChar(void) { return m_ppCharacter; }
	bool GetbAttack(void) { return m_bAttack; }                // �U�������ǂ���
	CMotion *GetMotion(void) { return m_pMotion; }
	ATTACKTYPE GetActType(void) { return m_Info.Atc; }
	CItem *GetItem(void) { return m_pItem; }
	CEnemy *GetGrapEnemy(void) { return m_Grap.pEnemy; }

private:

	// �����o�֐�
	void Control(void);                   // ����
	void Move(void);                      // �ړ�
	void Action(void);                    // �U��
	void GrapRotition(void);              // �W���C�A���g�X�C���O
	void Grap(void);                      // �͂�
	void Avoid(void);                     // ���
	void State(void);                     // ���
	void Damege(void);                    // �_���[�W
	void Heat(void);                      // �q�[�g�A�N�V����
	void Smash(CEnemy *pEnemy);           // �q�[�g�A�N�V�����E��������
	void Fire(void);                      // �q�[�g�A�N�V�����E�d�q�����W
	void ReadText(const char *fliename);  // �e�L�X�g�t�@�C���ǂݍ���
	bool StartHeatAction(void);
	D3DXVECTOR3 EnemyDistance(void);              // �G�Ƃ̋���
	D3DXVECTOR3 ItemDistance(void);

	// �����o�ϐ�
	int m_nNumModel;                    //���f��(�p�[�c)�̑���
	int m_nIdxTexture;
	int m_nIdxShaadow;
	int m_nIdx;
	int m_nParent;
	int m_nCntColi;
	int m_nDamegeCounter;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_pMotion;                   // ���[�V�����ւ̃|�C���^
	CCharacter **m_ppCharacter;           // �L�����N�^�[�ւ̃|�C���^
	CItem *m_pItem;                       // �͂�ł�I�u�W�F�N�g�̃|�C���^
	CGage2D *m_pLife;                     // �Q�[�W�̃|�C���^
	CGage3D *m_pStamina;                  // �Q�[�W�̃|�C���^
	CEnemy *m_pEnemy;
	CObject2D *m_pBotton;
	int m_nIdxEne;
	int m_nIdxItem;
	int m_nDamageCounter;
	float m_fDest;
	float m_fDestOld;
	float m_fDiff;
	float m_fGrapRot;
	float m_fStamina;                     // �X�^�~�i
	bool m_bDesh;                         // �_�b�V��
	bool m_bAttack;                       // �U��
	bool m_bAvoid;                        // ���
	bool m_bLift;                         // �����グ��
	bool m_bGrap;                         // ����
	bool m_bInvi;                         // ���G���ǂ���

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