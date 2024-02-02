//==============================================================================
//
// �{�X�̏��� [enemy_boss.cpp]
// Author : �匴�@�叫
//
//==============================================================================

//*=============================================================================
//�C���N���[�h�t�@�C��
//*=============================================================================
#include "enemy.h"
#include "enemy_boss.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "sound.h"
#include "player.h"
#include "game.h"
#include "debugproc.h"
#include "score.h"
#include "player.h"
#include "character.h"
#include "collision.h"
#include "enemymanager.h"
#include <assert.h>

//*=============================================================================
// �}�N����`
//*=============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\motion_neet.txt")   //�G�̃e�L�X�g�t�@�C��

// �������O��Ԃ��`
namespace
{
	const int DAMEGECOUNT = 25;  // �_���[�W���
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemyBoss::CEnemyBoss()
{
	/*CEnemyBoss *pEnemy = m_pTop;

	if (m_pTop == nullptr)
	{
	m_pTop = this;

	m_pCur = this;
	}
	else if (m_pTop != nullptr)
	{
	m_pPrev = m_pCur;
	m_pPrev->m_pNext = this;
	m_pCur = this;
	}*/
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemyBoss::CEnemyBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	// �l���N���A
	/*m_Info.pos = pos;
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = rot;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.mtxWorld);
	m_Info.state = STATE_NONE;
	m_Info.nLife = nlife;
	m_Info.nIdxID = -1;
	m_nDamegeCounter = 0;*/

	SetPosition(pos);
	SetRotition(rot);
	SetLife(nlife);
	SetState(CEnemy::STATE_NONE);

	/*CEnemyBoss *pEnemy = m_pTop;

	if (m_pTop == nullptr)
	{
	m_pTop = this;

	m_pCur = this;
	}
	else if (m_pTop != nullptr)
	{
	m_pPrev = m_pCur;
	m_pPrev->m_pNext = this;
	m_pCur = this;
	}*/
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEnemyBoss::~CEnemyBoss()
{

}

//==============================================================================
// ��������
//==============================================================================
CEnemyBoss * CEnemyBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	CEnemyBoss *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemyBoss(pos, rot, nlife);

		pEnemy->Init();
	}

	return pEnemy;
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyBoss::Controll(void)
{
	if (m_Info.state == STATE_DAMEGE)
	{
		Damege();
	}
	else
	{
		if (m_Type == TYPE_ENEMY)
		{
			Move();
		}
	}

	if (m_Info.nLife <= 0)
	{
		//this->Uninit();
		CGame::GetEnemyManager()->Release(m_Info.nIdxID);
		return;
	}

	if (m_Info.state != STATE_GRAP)
	{
		m_Info.move.y -= 0.9f;
	}

	// �ړ���
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.y += m_Info.move.y;
	m_Info.pos.z += m_Info.move.z;

	if (m_Info.pos.y <= 0.0f)
	{
		m_Info.pos.y = 0.0f;
	}

	//�f�o�b�O�v���b�N�̏����擾
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
	pDebugProc->Print("\n�G�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	pDebugProc->Print("�G�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	pDebugProc->Print("�G�̌����F%d\n", m_Info.nLife);
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyBoss::Attack(void)
{
	if (m_Info.state != STATE_ATTACK)
	{
		m_Info.state = STATE_ATTACK;
		GetMotion()->Set(TYPE_ATTACK);
	}
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyBoss::Move(void)
{
	//�v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), 400.0f, 50.0f) == true)
	{//�~�̒��Ƀv���C���[��������

		D3DXVECTOR3 fDest, PlayerPos = pPlayer->GetPosition();

		float fDiffmove, fDestmove;

		fDest = m_Info.pos - PlayerPos;

		fDestmove = atan2f(fDest.x, fDest.z);
		fDiffmove = fDestmove - m_Info.rot.y;

		//�p�x�̒l���C������--------------------------------------------------
		if (fDiffmove >= D3DX_PI)
		{
			fDiffmove = -D3DX_PI;
		}
		else if (fDiffmove <= -D3DX_PI)
		{
			fDiffmove = D3DX_PI;
		}

		m_Info.rot.y += fDiffmove * 0.05f;

		//�p�x�̒l���C������--------------------------------------------------
		if (m_Info.rot.y > D3DX_PI)
		{
			m_Info.rot.y = -D3DX_PI;
		}
		else if (m_Info.rot.y < -D3DX_PI)
		{
			m_Info.rot.y = D3DX_PI;
		}

		//�ړ��ʂ��X�V(����������)
		m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * 2.0f;
		m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * 2.0f;

		if (fDest.x <= 60.0f && fDest.x >= -60.0f && fDest.z <= 60.0f && fDest.z >= -60.0f)
		{
			Attack();
			m_Info.move.x = 0.0f;
			m_Info.move.z = 0.0f;


		}
		else
		{
			if (m_Info.state != STATE_DASH)
			{
				m_Info.state = STATE_DASH;
				GetMotion()->Set(TYPE_DASH);
			}
		}

		m_Info.pos.x += m_Info.move.x * 0.5f;
		m_Info.pos.z += m_Info.move.z * 0.5f;
	}
	else
	{
		m_Info.move.x = 0.0f;
		m_Info.move.z = 0.0f;

		if (m_Info.state != STATE_NEUTRAL)
		{
			m_Info.state = STATE_NEUTRAL;
			GetMotion()->Set(TYPE_NEUTRAL);
		}
	}
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyBoss::Damege(void)
{
	// �ړ���
	/*m_Info.pos.x += m_Info.move.x * -1.5f;
	m_Info.pos.y = m_Info.move.y;
	m_Info.pos.z += m_Info.move.z * -1.5f;*/

	m_nDamegeCounter--;

	if (m_nDamegeCounter < 0)
	{
		m_nDamegeCounter = DAMEGECOUNT;
		m_Info.state = STATE_NEUTRAL;

		m_Info.move.x = 0.0f;
		m_Info.move.z = 0.0f;
	}
}

//==============================================================================
// ����������
//==============================================================================
HRESULT CEnemyBoss::Init(void)
{
	ReadText(ENEMY_TEXT);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CEnemyBoss::Uninit(void)
{
	CEnemy::Uninit();
	CObject::Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CEnemyBoss::Update(void)
{
	CEnemy::Update();
}

//==============================================================================
// �`�揈��
//==============================================================================
void CEnemyBoss::Draw(void)
{
	CEnemy::Draw();
}