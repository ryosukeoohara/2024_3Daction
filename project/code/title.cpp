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

//===========================================================
//コンストラクタ
//===========================================================
CTitle::CTitle()
{
	
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
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
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
	pField->Init();

	CObject2D *pBg = new CObject2D;
	pBg->Init();
	pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\taitoru.jpg"));
	pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pBg->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	pBg->SetDraw(true);

	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CTitle::Uninit(void)
{
	
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

	CManager::Getinstance()->GetDebugProc()->Print("現在のシーン：タイトル");
}

//===========================================================
//描画処理
//===========================================================
void CTitle::Draw(void)
{
	
}