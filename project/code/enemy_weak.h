//=============================================================================
//
// �G�̏��� [enemy_weak.h]
// Author : �匴�@�叫
//
//=============================================================================
#ifndef _ENEMY_WEAK_H_
#define _ENEMY_WEAK_H_

#include "enemy.h"

//*=============================================================================
//�N���X��`
//*=============================================================================
class CMotion;
class CCharacter;

//*=============================================================================
//�N���X��`
//*=============================================================================
class CEnemyWeak : public CEnemy
{
public:

	//���[�V����
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // �j���[�g����
		TYPE_DASH,                     // �ړ�
		TYPE_ATTACK,                   // �U��
		TYPE_DAMEGE,                   // �_���[�W
		TYPE_MAX
	};

public:

	CEnemyWeak();                                  //�R���X�g���N�^
	CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //�R���X�g���N�^
	~CEnemyWeak();                                 //�f�X�g���N�^

	HRESULT Init(void) override;                        //������
	void Uninit(void) override;                         //�I��
	void Update(void) override;                         //�X�V
	void Draw(void) override;                           //�`��

	static CEnemyWeak *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //����
	
private:

	// �G�̓�������
	void Controll(void) override;
	void Attack(void) override;
	void Move(void) override;
	void Damege(void) override;

	int m_nDamegeCounter;                      // �_���[�W��Ԃł���J�E���g
	int m_nAtcCounter;                         // �U���̃C���^�[�o��
	int m_nIdx;
};

#endif // !_ENEMY_H_