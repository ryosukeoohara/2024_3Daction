//==============================================================================
//
// ボスの処理 [enemy_boss.cpp]
// Author : 大原　怜将
//
//==============================================================================

//*=============================================================================
//インクルードファイル
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
#include "fade.h"
#include "utility.h"
#include "gage.h"
#include "camera.h"
#include "particle.h"
#include "item.h"
#include <assert.h>

//*=============================================================================
// マクロ定義
//*=============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\motion_neet.txt")   //敵のテキストファイル

// 無名名前空間を定義
namespace
{
	const int DAMEGECOUNT = 10;  // ダメージ状態

	const D3DXVECTOR3 CAMERAROT[CPlayer::HEAT_MAX] =
	{
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, D3DX_PI * -0.38f),

	};  // ヒートアクション時のカメラ位置
}

//==============================================================================
// コンストラクタ
//==============================================================================
CEnemyBoss::CEnemyBoss()
{
	m_Chase = CHASE_ON;
	m_pLife2D = nullptr;
	m_nBiriBiriCount = 0;
	m_nReceivedAttack = 0;
	m_nAttackType = -1;
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
// コンストラクタ
//==============================================================================
CEnemyBoss::CEnemyBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	// 値をクリア
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
	m_nAtcCounter = 0;
	m_Chase = CHASE_ON;
	m_pLife2D = nullptr;
	m_nBiriBiriCount = 0;
	m_nReceivedAttack = 0;
	m_nAttackType = -1;

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
// デストラクタ
//==============================================================================
CEnemyBoss::~CEnemyBoss()
{

}

//==============================================================================
// 生成処理
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
// 制御処理
//==============================================================================
void CEnemyBoss::Controll(void)
{
	int nNum = 0;
	CEnemy **ppEnemy = nullptr;

	if (CGame::GetEnemyManager() != nullptr)
	{
		ppEnemy = CGame::GetEnemyManager()->GetEnemy();
		nNum = CGame::GetEnemyManager()->GetNum();
	}

	for (int nCount = 0; nCount < nNum; nCount++)
	{
		if (ppEnemy[nCount] != nullptr && ppEnemy[nCount]->GetIdxID() != m_Info.nIdxID)
		{
			//m_Info.pos = *CGame::GetCollision()->CheckEnemy(&m_Info.pos, &m_Info.posOld, &ppEnemy[nCount]->GetPosition(), 40.0f);
		}
	}

	if (m_Info.state == STATE_DAMEGE)
	{
		m_nDamegeCounter--;

		if (m_nDamegeCounter <= 0)
		{
			m_Info.state = STATE_NONE;
			m_nDamegeCounter = DAMEGECOUNT;
		}
	}
	else
	{
		if (m_Info.state != STATE_GRAP)
		{
			Move();
		}
	}

	if (m_Info.nLife <= 0)
	{
		m_Info.state = STATE_DETH;
		GetMotion()->Set(TYPE_DETH);
		return;
	}

	if (m_Info.state != STATE_GRAP)
	{
		m_Info.move.y -= 0.9f;

		// 移動量
		m_Info.pos.x += m_Info.move.x;
		m_Info.pos.y += m_Info.move.y;
		m_Info.pos.z += m_Info.move.z;

		if (m_Info.pos.y <= 0.0f)
		{
			m_Info.pos.y = 0.0f;
		}
	}

	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
	pDebugProc->Print("\n敵の位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	pDebugProc->Print("敵の向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	pDebugProc->Print("敵の向き：%d\n", m_Info.nLife);
	pDebugProc->Print("敵の向き：%d\n", m_Info.nIdxID);
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemyBoss::Attack(void)
{
	if (m_Info.state != STATE_ATTACK)
	{
		m_nAtcCounter++;

		if (m_nAtcCounter >= 40)
		{
			m_nAtcCounter = 0;

			//乱数の種を設定
			srand((unsigned int)time(0));

			m_nAttackType = rand() % ATTACKTYPE_MAX;  //攻撃の種類抽選

			switch (m_nAttackType)
			{
			case ATTACKTYPE_GURUGURU:

				m_Info.state = STATE_ATTACK;
				GetMotion()->Set(TYPE_GURUGURU);

				break;

			case ATTACKTYPE_PUNCH:

				m_Info.state = STATE_ATTACK;
				GetMotion()->Set(TYPE_PUNCH);

				break;

			case ATTACKTYPE_FLY:

				m_Info.state = STATE_ATTACK;
				GetMotion()->Set(TYPE_ATTACK);

				break;

			default:
				break;
			}
		}
	}
	else
	{
		switch (m_nAttackType)
		{
		case ATTACKTYPE_GURUGURU:
			NormalPunch();
			

			break;

		case ATTACKTYPE_PUNCH:

			RollingPunch();

			break;

		case ATTACKTYPE_FLY:

			Fly();

			break;

		default:
			break;
		}
	}
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemyBoss::Move(void)
{
	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	float fDiffmove = 0.0f;

	m_Info.posOld = m_Info.pos;

	if (m_Chase == CHASE_ON)
	{
		if (m_Info.state != STATE_PAINFULDAMAGE)
		{
			if (m_Info.state != STATE_ATTACK)
			{
				fDiffmove = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, PlayerPos, m_Info.rot.y);

				fDiffmove = CManager::Getinstance()->GetUtility()->CorrectAngle(fDiffmove);

				m_Info.rot.y += fDiffmove * 0.05f;

				m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);
			}

			//移動量を更新(減衰させる)
			m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * 2.0f;
			m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * 2.0f;

			D3DXVECTOR3 Dest = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, PlayerPos);

			if (Dest.x <= 120.0f && Dest.x >= -120.0f && Dest.z <= 120.0f && Dest.z >= -120.0f)
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
				if (m_Info.state != STATE_DASH && m_Info.state != STATE_ATTACK && m_Info.state != STATE_DAMEGE && m_Info.state != STATE_PAINFULDAMAGE)
				{
					m_Info.state = STATE_DASH;
					GetMotion()->Set(TYPE_DASH);
				}
			}
		}
	}

	if (GetMotion()->IsFinish() == true && (m_Info.state == STATE_HEATDAMEGE || m_Info.state == STATE_PAINFULDAMAGE) && m_Info.state != STATE_GETUP)
	{
		m_Info.state = STATE_GETUP;
		GetMotion()->Set(TYPE_GETUP);
	}
	else if (GetMotion()->IsFinish() == true)
	{
		m_Info.state = STATE_NEUTRAL;
		GetMotion()->Set(TYPE_NEUTRAL);

		if (m_Chase != CHASE_ON)
		{
			m_Chase = CHASE_ON;

			m_nAtcCounter = 0;
		}
	}
}

//==============================================================================
// ダメージ処理
//==============================================================================
void CEnemyBoss::Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act)
{
	if (m_Info.state != STATE_DAMEGE && m_Info.state != STATE_HEATDAMEGE && m_Info.state != STATE_PAINFULDAMAGE && (m_Info.state != STATE_ATTACK || CGame::GetPlayer()->GetState() == CPlayer::STATE_HEAT))
	{
		m_Info.nLife -= damege;

		m_Info.move = D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y) * -blowaway, blowaway, cosf(CGame::GetPlayer()->GetRotition().y) * -blowaway);

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
				// 乱数の種を設定
				srand((unsigned int)time(0));

				int a = rand() % 60;
				int n = m_Info.nLife / 3;
				if (a >= n && CGame::GetPlayer()->GetActType() == CPlayer::TYPE_ATTACK3)
				{
					m_Info.state = STATE_PAINFULDAMAGE;
					GetMotion()->Set(TYPE_HEATDAMEGE);
					m_Chase = CHASE_OFF;
					m_Info.move.x = 0.0f;
					m_Info.move.z = 0.0f;
				}
				else
				{
					m_Info.state = STATE_DAMEGE;
					GetMotion()->Set(TYPE_DAMEGE);
				}
			}
		}
	}
}

//==============================================================================
// ぐるぐるパンチ攻撃
//==============================================================================
void CEnemyBoss::RollingPunch(void)
{
	// キャラのパーツ取得
	CCharacter **ppParts = nullptr;
	ppParts = GetCharcter();

	D3DXVECTOR3 PartsPosR = {};
	D3DXMATRIX *PartsMtxR = {};
	D3DXVECTOR3 PartsPosL = {};
	D3DXMATRIX *PartsMtxL = {};

	// 左手
	if (ppParts[8] != nullptr)
	{
		// マトリックスの取得
		PartsMtxR = ppParts[8]->GetMtxWorld();

		PartsPosR.x = PartsMtxR->_41;
		PartsPosR.y = PartsMtxR->_42;
		PartsPosR.z = PartsMtxR->_43;
	}

	// 右手
	if (ppParts[11] != nullptr)
	{
		// マトリックスの取得
		PartsMtxL = ppParts[11]->GetMtxWorld();

		PartsPosL.x = PartsMtxL->_41;
		PartsPosL.y = PartsMtxL->_42;
		PartsPosL.z = PartsMtxL->_43;
	}

	if (GetMotion()->GetAttackOccurs() <= GetMotion()->GetNowFrame() && GetMotion()->GetAttackEnd() >= GetMotion()->GetNowFrame())
	{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

		if (CGame::GetCollision()->Circle(&PartsPosR, &CGame::GetPlayer()->GetPosition(), 20.0f, 50.0f) == true)
		{
			CGame::GetPlayer()->Damage(GetMotion()->GetAttackDamege(), GetMotion()->GetKnockBack());
		}

		if (CGame::GetCollision()->Circle(&PartsPosL, &CGame::GetPlayer()->GetPosition(), 20.0f, 50.0f) == true)
		{
			CGame::GetPlayer()->Damage(GetMotion()->GetAttackDamege(), GetMotion()->GetKnockBack());
		}
	}
}

//==============================================================================
// 普通のパンチ
//==============================================================================
void CEnemyBoss::NormalPunch(void)
{
	// キャラのパーツ取得
	CCharacter **ppParts = nullptr;
	ppParts = GetCharcter();

	D3DXVECTOR3 PartsPos = {};
	D3DXMATRIX *PartsMtx = {};

	// 右手
	if (ppParts[11] != nullptr)
	{
		// マトリックスの取得
		PartsMtx = ppParts[11]->GetMtxWorld();

		PartsPos.x = PartsMtx->_41;
		PartsPos.y = PartsMtx->_42;
		PartsPos.z = PartsMtx->_43;
	}

	if (GetMotion()->GetAttackOccurs() <= GetMotion()->GetNowFrame() && GetMotion()->GetAttackEnd() >= GetMotion()->GetNowFrame())
	{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

		if (CGame::GetCollision()->Circle(&PartsPos, &CGame::GetPlayer()->GetPosition(), 50.0f, 50.0f) == true)
		{
			CGame::GetPlayer()->Damage(GetMotion()->GetAttackDamege(), GetMotion()->GetKnockBack());
		}
	}
}

//==============================================================================
// 飛び込み攻撃
//==============================================================================
void CEnemyBoss::Fly(void)
{
	// キャラのパーツ取得
	CCharacter **ppParts = nullptr;
	ppParts = GetCharcter();

	D3DXVECTOR3 PartsPos = {};
	D3DXMATRIX *PartsMtx = {};

	// 腹
	if (ppParts[5] != nullptr)
	{
		// マトリックスの取得
		PartsMtx = ppParts[5]->GetMtxWorld();

		PartsPos.x = PartsMtx->_41;
		PartsPos.y = PartsMtx->_42;
		PartsPos.z = PartsMtx->_43;
	}

	if (GetMotion()->GetAttackOccurs() <= GetMotion()->GetNowFrame() && GetMotion()->GetAttackEnd() >= GetMotion()->GetNowFrame())
	{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

		if (CGame::GetCollision()->Circle(&PartsPos, &CGame::GetPlayer()->GetPosition(), 50.0f, 50.0f) == true)
		{
			CGame::GetPlayer()->Damage(GetMotion()->GetAttackDamege(), GetMotion()->GetKnockBack());
		}
	}
}

//==============================================================================
// ヒートアクション・電子レンジ処理
//==============================================================================
//void CEnemyBoss::MicroWave(void)
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
//			//CManager::Getinstance()->GetCamera()->SetDistnce(CAMERADISTNCE[m_HeatAct]);
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

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CEnemyBoss::Init(void)
{
	CEnemy::Init();
	ReadText(ENEMY_TEXT);

	m_pLife2D = CGage2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, 650.0f, 0.0f), 40.0f, (float)((m_Info.nLife * 0.05f) * 20), CGage2D::TYPE_LIFE);
	m_pLife2D->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.03f) * 20));

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CEnemyBoss::Uninit(void)
{
	CEnemy::Uninit();
	CObject::Release();

	if (m_pLife2D != nullptr)
	{
		m_pLife2D->Uninit();
		m_pLife2D = nullptr;
	}

	//フェードの情報を取得
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (pFade->Get() != pFade->FADE_OUT)
	{
		//シーンをゲームに遷移
		pFade->Set(CScene::MODE_RESULT);
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void CEnemyBoss::Update(void)
{
	CEnemy::Update();

	if (m_pLife2D != nullptr)
	{
		m_pLife2D->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.03f) * 20));
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CEnemyBoss::Draw(void)
{
	CEnemy::Draw();
}