//==============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 大原　怜将
//
//==============================================================================

//*=============================================================================
//インクルードファイル
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
#include <assert.h>

//*=============================================================================
// マクロ定義
//*=============================================================================
#define ENETEXT ("data\\TEXT\\yanki00.txt")

// 無名名前空間を定義
namespace
{
	const int DAMEGECOUNT = 25;  // ダメージ状態
}

//==============================================================================
// コンストラクタ
//==============================================================================
CEnemyWeak::CEnemyWeak()
{
	/*CEnemyWeak *pEnemy = m_pTop;

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
CEnemyWeak::CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
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

	/*CEnemyWeak *pEnemy = m_pTop;

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
CEnemyWeak::~CEnemyWeak()
{

}

//==============================================================================
// 生成処理
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
// 初期化処理
//==============================================================================
HRESULT CEnemyWeak::Init(void)
{
	CEnemy::Init();

	ReadText(ENETEXT);

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CEnemyWeak::Uninit(void)
{
	CEnemy::Uninit();
	CObject::Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CEnemyWeak::Update(void)
{
	CEnemy::Update();
}

//==============================================================================
// 描画処理
//==============================================================================
void CEnemyWeak::Draw(void)
{
	CEnemy::Draw();
}

//==============================================================================
// 制御処理
//==============================================================================
//void CEnemyWeak::Controll(void)
//{
//	Move();
//
//	if (m_Info.state == STATE_DAMEGE)
//	{
//		m_nDamegeCounter--;
//
//		if (m_nDamegeCounter <= 0)
//		{
//			m_Info.state = STATE_NONE;
//		}
//	}
//	
//	if (m_Info.nLife <= 0)
//	{
//		CGame::GetEnemyManager()->Release(m_Info.nIdxID);
//		int nNum = CGame::GetEnemyManager()->GetNum() - 1;
//		CGame::GetEnemyManager()->SetNum(nNum);
//		return;
//	}
//
//	if (m_Info.state != STATE_GRAP)
//	{
//		m_Info.move.y -= 0.9f;
//	}
//
//	// 移動量
//	m_Info.pos.x += m_Info.move.x;
//	m_Info.pos.y += m_Info.move.y;
//	m_Info.pos.z += m_Info.move.z;
//
//	if (m_Info.pos.y <= 0.0f)
//	{
//		m_Info.pos.y = 0.0f;
//	}
//
//	//デバッグプロックの情報を取得
//	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
//	pDebugProc->Print("\n敵の位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
//	pDebugProc->Print("敵の向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
//	pDebugProc->Print("敵の向き：%d\n", m_Info.nLife);
//}

//==============================================================================
// 制御処理
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
		{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

			if (CGame::GetCollision()->Circle(&m_Info.pos, &CGame::GetPlayer()->GetPosition(), 50.0f, 100.0f) == true)
			{
				CGame::GetPlayer()->SetState(CPlayer::STATE_DAMEGE);
				CGame::GetPlayer()->SetMove(D3DXVECTOR3(sinf(m_Info.rot.y) * -5.0f, 10.0f, cosf(m_Info.rot.y) * -5.0f));
				int nLife = CGame::GetPlayer()->GetLife();
				nLife--;
				CGame::GetPlayer()->SetLife(nLife);
			}
		}
	}
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemyWeak::Move(void)
{
	//プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();

	if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), 400.0f, 50.0f) == true)
	{//円の中にプレイヤーが入った

		D3DXVECTOR3 fDest, PlayerPos = pPlayer->GetPosition();

		float fDiffmove, fDestmove;

		if (m_Info.state != STATE_DAMEGE)
		{
			fDest = m_Info.pos - PlayerPos;

			fDestmove = atan2f(fDest.x, fDest.z);
			fDiffmove = fDestmove - m_Info.rot.y;

			//角度の値を修正する--------------------------------------------------
			if (fDiffmove >= D3DX_PI)
			{
				fDiffmove = -D3DX_PI;
			}
			else if (fDiffmove <= -D3DX_PI)
			{
				fDiffmove = D3DX_PI;
			}

			m_Info.rot.y += fDiffmove * 0.05f;

			//角度の値を修正する--------------------------------------------------
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y = -D3DX_PI;
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y = D3DX_PI;
			}

			//移動量を更新(減衰させる)
			m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * 2.0f;
			m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * 2.0f;
		}
		
		if (fDest.x <= 60.0f && fDest.x >= -60.0f && fDest.z <= 60.0f && fDest.z >= -60.0f)
		{
			if (m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_DAMEGE)
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
			if (m_Info.state != STATE_DASH && m_Info.state != STATE_DAMEGE)
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

	if (GetMotion()->IsFinish() == true)
	{
		m_Info.state = STATE_NEUTRAL;
		GetMotion()->Set(TYPE_NEUTRAL);
	}
}

//==============================================================================
// 制御処理
//==============================================================================
//void CEnemyWeak::Damege(int damege)
//{
//	m_Info.nLife -= damege;
//
//	if (m_Info.state != STATE_DAMEGE)
//	{
//		m_Info.state = STATE_DAMEGE;
//		GetMotion()->Set(TYPE_DAMEGE);
//	}
//}