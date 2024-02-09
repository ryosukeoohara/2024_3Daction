//===========================================================
//
//リザルト画面[result.cpp]
//Author 大原怜将
//
//===========================================================

//*==========================================================
//インクルードファイル
//*==========================================================
#include "result.h"
#include "texture.h"
#include "game.h"
#include "debugproc.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "map.h"
#include "field.h"

//===========================================================
//コンストラクタ
//===========================================================
CResult::CResult()
{
	
}

//===========================================================
//デストラクタ
//===========================================================
CResult::~CResult()
{

}

//===========================================================
//生成
//===========================================================
CResult *CResult::Create(void)
{
	CResult *pTitle = NULL;

	if (pTitle == NULL)
	{
		pTitle = new CResult;

		pTitle->Init();
	}

	return pTitle;
}

//===========================================================
//初期化処理
//===========================================================
HRESULT CResult::Init(void)
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
		pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\res.jpg"));
		pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pBg->SetSize(100.0f, 100.0f);
		pBg->SetDraw(true);
	}

	// マップの生成
	if (m_pMap == nullptr)
	{
		m_pMap = CMap::Create();
	}

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CResult::Uninit(void)
{
	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	// マップの破棄
	if (m_pMap != nullptr)
	{
		m_pMap->Uninit();
		m_pMap = nullptr;
	}

	CObject::ReleaseAll();
}

//===========================================================
//更新処理
//===========================================================
void CResult::Update(void)
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
			pFade->Set(CScene::MODE_TITLE);
		}
	}
}

//===========================================================
//描画処理
//===========================================================
void CResult::Draw(void)
{
	
}