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
	return S_OK;
}

//===========================================================
//終了処理
//===========================================================
void CResult::Uninit(void)
{
	
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