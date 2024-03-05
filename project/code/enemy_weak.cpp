//==============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �匴�@�叫
//
//==============================================================================

//*=============================================================================
//�C���N���[�h�t�@�C��
//*=============================================================================
#include "enemy.h"
#include "enemy_weak.h"
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
#include "utility.h"
#include "gage.h"
#include "camera.h"
#include "particle.h"
#include "item.h"
#include "animation.h"
#include <time.h>
#include  <assert.h>

//*=============================================================================
// �}�N����`
//*=============================================================================
#define ENETEXT ("data\\TEXT\\yanki00.txt")

// �������O��Ԃ��`
namespace
{
	const int DAMEGECOUNT = 10;  // �_���[�W���

	const D3DXVECTOR3 CAMERAROT[CPlayer::HEAT_MAX] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, D3DX_PI * -0.38f),

	};  // �q�[�g�A�N�V�������̃J�����ʒu
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemyWeak::CEnemyWeak()
{
	m_pLife3D = nullptr;
	m_nBiriBiriCount = 0;
	m_Chase = CHASE_ON;
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CEnemyWeak::CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	// �l���N���A
	SetPosition(pos);
	SetRotition(rot);
	SetLife(nlife);
	SetState(CEnemy::STATE_NONE);
	m_pLife3D = nullptr;
	m_nBiriBiriCount = 0;
	m_Chase = CHASE_ON;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CEnemyWeak::~CEnemyWeak()
{

}

//==============================================================================
// ��������
//==============================================================================
CEnemyWeak * CEnemyWeak::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	CEnemyWeak *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemyWeak(pos, rot, nlife);

		pEnemy->Init();
	}

	return pEnemy;
}

//==============================================================================
// ����������
//==============================================================================
HRESULT CEnemyWeak::Init(void)
{
	CEnemy::Init();
	SetType(WEAK);

	ReadText(ENETEXT);

	m_pLife3D = CGage3D::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z), 5.0f, (float)((m_Info.nLife * 0.01f) * 20), CGage3D::TYPE_LIFE);
	m_pLife3D->SetPos(&m_Info.pos);
	m_pLife3D->SetUpHeight(80.0f);
	m_pLife3D->GetBill()->SetEdgeCenter((float)((m_Info.nLife * 0.01f) * 20), 5.0f);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CEnemyWeak::Uninit(void)
{
	CEnemy::Uninit();

	if (m_pLife3D != nullptr)
	{
		m_pLife3D->Uninit();
		m_pLife3D = nullptr;
	}

	CObject::Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CEnemyWeak::Update(void)
{
	CEnemy::Update();

	if (m_pLife3D != nullptr)
	{
		m_pLife3D->GetBill()->SetEdgeCenter((float)((m_Info.nLife * 0.01f) * 20), 5.0f);
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CEnemyWeak::Draw(void)
{
	CEnemy::Draw();
}

//==============================================================================
// ���䏈��
//==============================================================================
//void CEnemyWeak::Controll(void)
//{
//	int nNum = 0;
//	CEnemy **ppEnemy = nullptr;
//
//	if (CGame::GetEnemyManager() != nullptr)
//	{
//		ppEnemy = CGame::GetEnemyManager()->GetEnemy();
//		nNum = CGame::GetEnemyManager()->GetNum();
//	}
//
//	for (int nCount = 0; nCount < nNum; nCount++)
//	{
//		if (ppEnemy[nCount] != nullptr && ppEnemy[nCount]->GetIdxID() != m_Info.nIdxID)
//		{
//			//m_Info.pos = *CGame::GetCollision()->CheckEnemy(&m_Info.pos, &m_Info.posOld, &ppEnemy[nCount]->GetPosition(), 40.0f);
//		}
//	}
//
//	if (m_Info.state == STATE_DAMEGE)
//	{
//		m_nDamegeCounter--;
//
//		if (m_nDamegeCounter <= 0)
//		{
//			m_Info.state = STATE_NONE;
//			m_nDamegeCounter = DAMEGECOUNT;
//		}
//	}
//	else
//	{
//		if (m_Info.state != STATE_GRAP)
//		{
//			Move();
//		}
//	}
//
//	if (m_Info.nLife <= 0)
//	{
//		m_Info.state = STATE_DETH;
//		GetMotion()->Set(TYPE_DETH);
//
//		return;
//	}
//
//	if (m_Info.state != STATE_GRAP)
//	{
//		m_Info.move.y -= 0.9f;
//
//		// �ړ���
//		m_Info.pos.x += m_Info.move.x;
//		m_Info.pos.y += m_Info.move.y;
//		m_Info.pos.z += m_Info.move.z;
//
//		if (m_Info.pos.y <= 0.0f)
//		{
//			m_Info.pos.y = 0.0f;
//		}
//	}
//	 
//	//�f�o�b�O�v���b�N�̏����擾
//	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
//	pDebugProc->Print("\n�G�̈ʒu�F%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
//	pDebugProc->Print("�G�̌����F%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
//	pDebugProc->Print("�G�̌����F%d\n", m_Info.nLife);
//	pDebugProc->Print("�G�̌����F%d\n", m_Info.nIdxID);
//}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyWeak::Attack(void)
{
	if (m_Info.state != STATE_ATTACK)
	{
		m_nAtcCounter++;

		if (m_nAtcCounter >= 60)
		{
			m_nAtcCounter = 0;

			{
				m_Info.state = STATE_ATTACK;
				GetMotion()->Set(TYPE_ATTACK);
			}
		}
	}
	else
	{
		if (GetMotion()->GetAttackOccurs() <= GetMotion()->GetNowFrame() && GetMotion()->GetAttackEnd() >= GetMotion()->GetNowFrame())
		{// ���݂̃t���[�����U�����蔭���t���[���ȏォ�U������I���t���[���Ȃ�

			if (CGame::GetCollision()->Circle(&m_Info.pos, &CGame::GetPlayer()->GetPosition(), 50.0f, 100.0f) == true)
			{
				CGame::GetPlayer()->Damage(10, 5.0f);
			}
		}
	}
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyWeak::Move(void)
{
	//�v���C���[�̏��擾
	CPlayer *pPlayer = CPlayer::GetPlayer();
	
	if (m_Chase == CHASE_ON)
	{
		if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), 400.0f, 50.0f) == true)
		{//�~�̒��Ƀv���C���[��������

			m_Info.posOld = m_Info.pos;

			D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

			float fDiffmove = 0.0f;

			if (m_Info.state != STATE_DAMEGE)
			{
				// �ǔ�
				fDiffmove = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, PlayerPos, m_Info.rot.y);

				// �p�x�␳
				fDiffmove = CManager::Getinstance()->GetUtility()->CorrectAngle(fDiffmove);

				m_Info.rot.y += fDiffmove * 0.05f;

				// �p�x�␳
				m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);

				//�ړ��ʂ��X�V(����������)
				m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * 2.0f;
				m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * 2.0f;
			}

			// �v���C���[�Ƃ̋���
			D3DXVECTOR3 Dest = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, PlayerPos);

			if (Dest.x <= 60.0f && Dest.x >= -60.0f && Dest.z <= 60.0f && Dest.z >= -60.0f)
			{
				if (m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_DAMEGE && m_Info.state != STATE_PAINFULDAMAGE)
				{
					m_Info.state = STATE_NEUTRAL;
					GetMotion()->Set(TYPE_NEUTRAL);
				}

				Attack();
				m_Info.move.x = 0.0f;
				m_Info.move.z = 0.0f;
			}
			else
			{
				if (m_Info.state != STATE_DASH && m_Info.state != STATE_DAMEGE && m_Info.state != STATE_PAINFULDAMAGE)
				{
					m_Info.state = STATE_DASH;
					GetMotion()->Set(TYPE_DASH);
				}
			}
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

	if (m_Info.state == STATE_PAINFULDAMAGE)
	{
		if (GetMotion()->GetNowFrame() >= 0 && GetMotion()->GetNowFrame() <= 20)
		{
			m_Info.move.x = 0.0f;
			m_Info.move.z = 0.0f;
		}
	}
}

//==============================================================================
// ���䏈��
//==============================================================================
void CEnemyWeak::Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act)
{
	if (m_Info.state != STATE_DAMEGE && m_Info.state != STATE_HEATDAMEGE && m_Info.state != STATE_PAINFULDAMAGE && m_Info.state != STATE_DETH)
	{
		m_Info.nLife -= damege;
		m_Info.move = D3DXVECTOR3(sinf(CPlayer::GetPlayer()->GetRotition().y) * -blowaway, blowaway, cosf(CPlayer::GetPlayer()->GetRotition().y) * -blowaway);

		if (act == CPlayer::ATTACKTYPE::TYPE_HEATACTBIKE || act == CPlayer::ATTACKTYPE::TYPE_HEATACTREF || act == CPlayer::ATTACKTYPE::TYPE_HEATACTMICROWAVE)
		{
			if (m_Info.state != STATE_HEATDAMEGE)
			{
				m_Info.state = STATE_HEATDAMEGE;
				GetMotion()->Set(TYPE_HEATDAMEGE);
			}
		}
		else
		{
			if (m_Info.state != STATE_DAMEGE)
			{
				// �����̎��ݒ�
				srand((unsigned int)time(0));

				int a = rand() % 60;
				if (m_Info.nLife <= a && CPlayer::GetPlayer()->GetActType() == CPlayer::TYPE_ATTACK3)
				{
					m_Info.state = STATE_PAINFULDAMAGE;
					GetMotion()->Set(TYPE_HEATDAMEGE);
					m_Chase = CHASE_OFF;
				}
				else
				{
					m_Info.state = STATE_DAMEGE;
					GetMotion()->Set(TYPE_DAMEGE);
				}
			}
		}

		CAnimation::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 60.0f, m_Info.pos.z), 30.0f, CBillBoard::TYPE_HIT);
		CManager::Getinstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
	}
}

//==============================================================================
// �q�[�g�A�N�V�����E�d�q�����W����
//==============================================================================
//void CEnemyWeak::MicroWave(void)
//{
//	m_nBiriBiriCount++;
//
//	if (m_nBiriBiriCount > 60 && m_Info.state == STATE_BIRIBIRI)
//	{
//		if (m_Info.state != STATE_BIRI)
//		{
//			m_Info.state = STATE_BIRI;
//			GetMotion()->Set(TYPE_BIRI);
//
//			CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(CAMERAROT[2].x, CAMERAROT[2].y, CAMERAROT[2].z));
//			CManager::Getinstance()->GetCamera()->SetDistnce(CAMERADISTNCE[m_HeatAct]);
//		}
//
//		m_nBiriBiriCount = 0;
//	}
//
//	if (m_nBiriBiriCount > 120 && m_Info.state == STATE_BIRI)
//	{
//		if (m_Info.state != STATE_FAINTING)
//		{
//			m_Info.state = STATE_FAINTING;
//			GetMotion()->Set(TYPE_FAINTING);
//		}
//
//		m_nBiriBiriCount = 0;
//	}
//
//	if (m_Info.state == STATE_BIRI)
//	{
//		if (m_nBiriBiriCount % 20 == 0)
//		{
//			CParticle::Create(CGame::GetPlayer()->GetItem()->GetPosition(), CParticle::TYPE_SMOOK);
//		}
//	}
//}