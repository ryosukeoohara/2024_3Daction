//===========================================================
//
//ポリゴンを出すやつ[title.cpp]
//Author 大原怜将
//
//===========================================================

//*==========================================================
//インクルードファイル
//*==========================================================
#include "title.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "field.h"
#include "map.h"
#include "player.h"

// 無名名前空間を定義
namespace
{
	const D3DXVECTOR3 TEXPOS[3] =   // 位置
	{
		D3DXVECTOR3(640.0f, 0.0f, 350.0f),
		D3DXVECTOR3(640.0f, 0.0f, 550.0f),
		D3DXVECTOR3(640.0f, 0.0f, 750.0f),
	};

	const D3DXVECTOR3 CAMERAPOS[3] =   // 位置
	{
		D3DXVECTOR3(640.0f, 0.0f, -350.0f),
		D3DXVECTOR3(640.0f, 0.0f, -550.0f),
		D3DXVECTOR3(640.0f, 0.0f, -750.0f),
	};
}

//===========================================================
//　静的メンバ変数
//===========================================================
CPlayer *CTitle::m_pPlayer = nullptr;

//===========================================================
//コンストラクタ
//===========================================================
CTitle::CTitle()
{
	m_pField = nullptr;
	m_pBg = nullptr;
	m_pMap = nullptr;
	m_nCnt = 0;
	m_nCntPos = 0;
}

//===========================================================
//デストラクタ
//===========================================================
CTitle::~CTitle()
{

}

//===========================================================
//生成
//===========================================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = nullptr;

	if (pTitle == nullptr)
	{
		pTitle = new CTitle;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CTitle::Init(void)
{
	CField *pField = new CField;

	if (pField != nullptr)
	{
		pField->Init();
		pField->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\field001.jpg"));
		pField->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pField->SetSize(5000.0f, 5000.0f);
		pField->SetDraw(true);
	}

	CObject2D *pBg = new CObject2D;

	if (pBg != nullptr)
	{
		pBg->Init();
		pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\taitoru.jpg"));
		pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pBg->SetSize(100.0f, 100.0f);
		pBg->SetDraw(true);
	}

	// マップの生成
	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
		m_pPlayer->SetPosition(TEXPOS[0]);
	}
	
	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTitle::Uninit(void)
{
	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// マップの破棄
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	// プレイヤーの破棄
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	
	CObject::ReleaseAll();
}

//===========================================================
//更新処理
//===========================================================
void CTitle::Update(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

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

	/*if (m_pPlayer != nullptr)
	{
		m_pPlayer->TitleWalk();
	}

	m_nCnt++;

	if (m_nCnt >= 120)
	{
		m_nCnt = 0;

		if (m_pPlayer != nullptr)
		{
			m_nCntPos++;
			
			if (m_nCntPos >= 3)
			{
				m_nCntPos = 0;
			}

			m_pPlayer->SetPosition(TEXPOS[m_nCntPos]);
			CManager::Getinstance()->GetCamera()->SetPositionR(CAMERAPOS[m_nCntPos]);
		}
	}*/

	CManager::Getinstance()->GetDebugProc()->Print("現在のシーン：タイトル");
}

//===========================================================
//描画処理
//===========================================================
void CTitle::Draw(void)
{
	
}