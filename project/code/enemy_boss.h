//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

#include "enemy.h"

//*=============================================================================
//�N���X��`
//*=============================================================================
class CMotion;
class CCharacter;

//*=============================================================================
//�N���X��`
//*=============================================================================
class CEnemyBoss : public CEnemy
{
public:

	//���[�V����
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // �j���[�g����
		TYPE_DASH,                     // �ړ�
		TYPE_ATTACK,                   // �U��
		TYPE_DAMEGE,                   // �_���[�W
		TYPE_HEATDAMEGE,               // �q�[�g�A�N�V�����_���[�W
		TYPE_GURUGURUPUNCH,            // ���邮��p���`
		TYPE_PUNCH,                    // �p���`
		TYPE_MAX
	};

	enum ATTACKTYPE
	{
		ATTACKTYPE_GURUGURU = 0,
		ATTACKTYPE_PUNCH,
		ATTACKTYPE_FLY,
		ATTACKTYPE_MAX
	};

public:

	CEnemyBoss();                                  //�R���X�g���N�^
	CEnemyBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //�R���X�g���N�^
	~CEnemyBoss();                                 //�f�X�g���N�^

	HRESULT Init(void) override;                        //������
	void Uninit(void) override;                         //�I��
	void Update(void) override;                         //�X�V
	void Draw(void) override;                           //�`��

	static CEnemyBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //����

	// �ݒ�n
	void SetChase(CHASE cha) { m_Chase = cha; }

private:

	// �G�̓�������
	//void Controll(void) override;
	void Attack(void) override;
	void Move(void) override;
	void Damege(int damege, float blowaway) override;

	int m_nDamegeCounter;                      // �_���[�W��Ԃł���J�E���g
	int m_nAtcCounter;                         // �U���̃C���^�[�o��
	int m_nIdx;
	

};

#endif // !_ENEMY_H_