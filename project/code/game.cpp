//===========================================================
//
//ポリゴンを出すやつ[game.cpp]
//Author 大原怜将
//
//===========================================================

//*==========================================================
//インクルードファイル
//*==========================================================
#include "game.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "object.h"
#include "debugproc.h"
#include "fade.h"
#include "time.h"
#include "score.h"
#include "pause.h"
#include "player.h"
#include "field.h"
#include "texture.h"
#include "enemy.h"
#include "enemymanager.h"
#include "collision.h"
#include "item.h"
#include "map.h"

//================================================================
//　静的メンバ変数
//================================================================
CPause *CGame::m_pPause = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CEnemy *CGame::m_pEnemy = nullptr;
CEnemyManager *CGame::m_pEnemyManager = nullptr;
CCollision *CGame::m_Collision = nullptr;
CItem *CGame::m_pItem = nullptr;
CMap *CGame::m_pMap = nullptr;

//===========================================================
//　コンストラクタ
//===========================================================
CGame::CGame()
{
	m_bUse = false;
	m_bPause = false;
}

//===========================================================
//　コンストラクタ
//===========================================================
CGame::CGame(CScene::MODE mode)
{
	m_bUse = false;
	m_bPause = false;
}

//===========================================================
//　デストラクタ
//===========================================================
CGame::~CGame()
{

}

//===========================================================
//　生成
//===========================================================
CGame *CGame::Create(void)
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		pGame = new CGame;

		pGame->Init();
	}

	return pGame;
}

//===========================================================
//　初期化処理
//===========================================================
HRESULT CGame::Init(void)
{
	CField *pField = new CField;
	pField->Init();
	pField->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\field001.jpg"));
	pField->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pField->SetSize(1000.0f, 1000.0f);
	pField->SetDraw(true);

	// ポーズの生成
	if (m_pPause == nullptr)
	{
		m_pPause = CPause::Create();
	}

	// プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f));
	}

	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = CEnemyManager::Create();
	}

	// 敵の生成
	if (m_pEnemy == nullptr)
	{
		//m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	}

	// 当たり判定
	if (m_Collision == nullptr) 
	{
		m_Collision = CCollision::Create();
	}

	if (m_pItem == nullptr)
	{
		m_pItem = CItem::Create();
	}

	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	return S_OK;
}

//===========================================================
//　終了処理
//===========================================================
void CGame::Uninit(void)
{
	// ポーズの破棄
	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	// プレイヤーの破棄
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	// 敵の破棄
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		delete m_pEnemy;
		m_pEnemy = nullptr;
	}

	// 敵の破棄
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	// マップの破棄
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		delete m_pMap;
		m_pMap = nullptr;
	}
}

//===========================================================
//　更新処理
//===========================================================
void CGame::Update(void)
{
	if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_P) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_START, 0) == true)
	{
		m_bPause = m_bPause ? false : true;

		if (m_pPause != nullptr)
		{
			m_pPause->SetDraw(m_bPause);
		}
	}

	if (m_bPause == true)
	{
		if (m_pPause != nullptr)
		{
			m_pPause->Update();
			m_pPause->SetDraw(m_bPause);
		}

		return;
	}

	//すべての更新処理
	CObject::UpdateAll();
	
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();

	pDebugProc->Print("\nシーン：ゲーム");
}

//===========================================================
//　描画処理
//===========================================================
void CGame::Draw(void)
{
	
}