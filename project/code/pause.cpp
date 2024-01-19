//===========================================================
//
//ポーズ処理[pause.cpp]
//Author 大原怜将
//
//===========================================================
#include "pause.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "game.h"

// 無名名前空間を定義
namespace 
{
	const D3DXVECTOR3 TEXPOS[3] =   // 位置
	{
		D3DXVECTOR3(640.0f, 350.0f, 0.0f),
		D3DXVECTOR3(640.0f, 500.0f, 0.0f),
		D3DXVECTOR3(640.0f, 650.0f, 0.0f),
	};

	const D3DXVECTOR2 TEXSIZE = { 130.0f, 45.0f };  // サイズ
}

//===========================================================
// テクスチャのお名前
//===========================================================
const char *CPause::m_apTexName[TYPE_MAX] =
{
	"data\\TEXTURE\\pause000.png",     // 続ける
	"data\\TEXTURE\\pause001.png",     // やり直す
	"data\\TEXTURE\\pause002.png",     // タイトル画面に戻る
	"data\\TEXTURE\\iron000.jpg",      // 黒い背景
	"data\\TEXTURE\\pause_bg000.png",  // 枠
};

//===========================================================
// コンストラクタ
//===========================================================
CPause::CPause()
{
	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		m_aMenu[nCount].Object2D = nullptr;
		m_aMenu[nCount].col = D3DXCOLOR(0.0, 0.0f, 0.0f, 0.0f);
	}

	m_pBg = nullptr;
	m_pFrame = nullptr;
}

//===========================================================
// デストラクタ
//===========================================================
CPause::~CPause()
{

}

//===========================================================
// 初期化処理
//===========================================================
HRESULT CPause::Init(void)
{
	if (m_pBg == nullptr)
	{
		m_pBg = CObject2D::Create();
		m_pBg->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[TYPE_BACK]));
		m_pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pBg->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_pBg->SetDraw(false);
	}

	if (m_pFrame == nullptr)
	{
		m_pFrame = CObject2D::Create();
		m_pFrame->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[TYPE_FRAME]));
		m_pFrame->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pFrame->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
		m_pFrame->SetDraw(false);
	}

	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_aMenu[nCount].Object2D == nullptr)
		{
			m_aMenu[nCount].Object2D = CObject2D::Create();
			m_aMenu[nCount].Object2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(m_apTexName[nCount]));
			m_aMenu[nCount].Object2D->SetPosition(D3DXVECTOR3(640.0f, 250.0f + nCount * 150.0f, 0.0f));
			m_aMenu[nCount].Object2D->SetSize(TEXSIZE.x, TEXSIZE.y);
			m_aMenu[nCount].Object2D->SetDraw(false);
		}
	}

	return S_OK;
}

//===========================================================
// 終了処理
//===========================================================
void CPause::Uninit(void)
{
	
}

//===========================================================
// 更新処理
//===========================================================
void CPause::Update(void)
{
	
}

//===========================================================
// 描画処理
//===========================================================
void CPause::Draw(void)
{
	
}

//===========================================================
// 生成処理
//===========================================================
CPause * CPause::Create(void)
{
	// ポーズのポインタ
	CPause *pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{//	使用されていたら

		// 初期化処理
		pPause->Init();
	}
	else
	{// 使用されていなかったらnullを返す

		return nullptr;
	}

	return pPause;
}

//===========================================================
// 描画するかどうか
//===========================================================
void CPause::SetDraw(bool bPause)
{
	if (m_pBg != nullptr)
	{
		m_pBg->SetDraw(bPause);
	}

	if (m_pFrame != nullptr)
	{
		m_pFrame->SetDraw(bPause);
	}

	for (int nCount = 0; nCount < MENU_MAX; nCount++)
	{
		if (m_aMenu[nCount].Object2D != nullptr)
		{
			m_aMenu[nCount].Object2D->SetDraw(bPause);
		}
	}
}