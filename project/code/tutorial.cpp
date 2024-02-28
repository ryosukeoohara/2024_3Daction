//===============================================================
//
//チュートリアル処理[tutorial.cpp]
// Author 大原怜将
//
//===============================================================
#include "tutorial.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "camera.h"
#include "field.h"
#include "map.h"
#include "player.h"
#include "enemymanager.h"
#include "enemy_weak.h"
#include "itemmanager.h"
#include "collision.h"
#include "tutorialUI.h"

//===========================================================
//　静的メンバ変数
//===========================================================
CPlayer *CTutorial::m_pPlayer = nullptr;
CEnemyManager *CTutorial::m_pEnemyManager = nullptr;
CMap *CTutorial::m_pMap = nullptr;
CTutorialUI *CTutorial::m_pUI = nullptr;

//===============================================================
//コンストラクタ
//===============================================================
CTutorial::CTutorial()
{
	
}

//===============================================================
//デストラクタ
//===============================================================
CTutorial::~CTutorial()
{
	m_pField = nullptr;
	m_pEnemy = nullptr;
	m_pItemManager = nullptr;
}

//===============================================================
//クリエイト
//===============================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		pTutorial = new CTutorial;

		pTutorial->Init();
	}

	return pTutorial;
}

//===============================================================
//初期化処理
//===============================================================
HRESULT CTutorial::Init(void)
{
	// フィールドの生成
	if (m_pField == nullptr)
	{
		m_pField = CField::Create();
		m_pField->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\field001.jpg"));
		m_pField->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pField->SetSize(5000.0f, 5000.0f);
		m_pField->SetDraw(true);
	}

	// 当たり判定
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create();
	}

	// マップの生成
	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	/*if (m_pEnemy == nullptr)
	{
		m_pEnemy = CEnemyWeak::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100);
		m_pEnemy->SetType(CEnemy::TYPE_WEAK);
	}*/

	// 敵マネージャの生成
	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = CEnemyManager::Create();
	}

	if (m_pItemManager == nullptr)
	{
		m_pItemManager = CItemManager::Create();
	}

	if (m_pUI == nullptr)
	{
		m_pUI = CTutorialUI::Create();
	}
	
	// プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
		m_pPlayer->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 500.0f));
		m_pPlayer->SetMobile();
	}

	return S_OK;
}

//===============================================================
//終了処理
//===============================================================
void CTutorial::Uninit(void)
{
	// 破棄
	// フィールド
	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	// 背景
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// マップ
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	// 敵の破棄
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Uninit();
		m_pEnemyManager = nullptr;
	}

	// アイテムの破棄
	if (m_pItemManager != nullptr)
	{
		m_pItemManager->Uninit();
		m_pItemManager = nullptr;
	}

	if (m_pUI != nullptr)
	{
		m_pUI->Uninit();
		m_pUI = nullptr;
	}

	// プレイヤー
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	CObject::ReleaseAll();
}

//===============================================================
//更新処理
//===============================================================
void CTutorial::Update(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//フェードの情報を取得
	CFade *pFade = CManager::Getinstance()->GetFade();

	if (InputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{//ENTERキーを押したかつシーンがタイトルのとき

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//シーンをゲームに遷移
			pFade->Set(CScene::MODE_GAME);
		}
	}

	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->Update();

		if (CEnemyManager::GetNum() <= 0)
		{
			m_pEnemyManager = nullptr;

			m_pEnemyManager = CEnemyManager::Create();
		}
	}
	
	// すべて更新
	CObject::UpdateAll();
}

//===============================================================
//描画処理
//===============================================================
void CTutorial::Draw(void)
{
	
}