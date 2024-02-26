//===========================================================
//
// 敵登場時のUI[appearanceUI.cpp]
// Author 大原怜将
//
//===========================================================
#include "appearanceUI.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"
#include "camera.h"

namespace
{
	const char *TEXTURENAME[CAppearanceUI::TYPE_MAX] =
	{
		"",
		"data\\TEXTURE\\underling.png", // ザコ
		"data\\TEXTURE\\ishii.png",     // ボス
	};  // テクスチャの名前
}

//===========================================================
// コンストラクタ
//===========================================================
CAppearanceUI::CAppearanceUI()
{
	// 初期化
	m_type = TYPE_NONE;
	m_pFrontObj2D = nullptr;
	m_pBackObj2D = nullptr;
}

//===========================================================
// コンストラクタ
//===========================================================
CAppearanceUI::CAppearanceUI(TYPE type)
{
	// 初期化
	m_type = type;
	m_pFrontObj2D = nullptr;
	m_pBackObj2D = nullptr;
}

//===========================================================
// デストラクタ
//===========================================================
CAppearanceUI::~CAppearanceUI()
{

}

//===========================================================
// 初期化処理
//===========================================================
HRESULT CAppearanceUI::Init(void)
{
	// それぞれ生成して、位置、サイズ、テクスチャ、描画状態を設定
	if (m_pBackObj2D == nullptr)
	{
		m_pBackObj2D = CObject2D::Create();
		m_pBackObj2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pBackObj2D->SetSize(0.0f, 0.0f);
		m_pBackObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
		m_pBackObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
		m_pBackObj2D->SetDraw(false);
	}

	if (m_pFrontObj2D == nullptr)
	{
		m_pFrontObj2D = CObject2D::Create();
		m_pFrontObj2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		m_pFrontObj2D->SetSize(1200.0f, 600.0f);
		m_pFrontObj2D->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEXTURENAME[m_type]));
		m_pFrontObj2D->SetDraw();
	}

	return S_OK;
}

//===========================================================
// 終了処理
//===========================================================
void CAppearanceUI::Uninit(void)
{
	// 破棄
	if (m_pFrontObj2D != nullptr)
	{
		m_pFrontObj2D->Uninit();
		m_pFrontObj2D = nullptr;
	}

	if (m_pBackObj2D != nullptr)
	{
		m_pBackObj2D->Uninit();
		m_pBackObj2D = nullptr;
	}

	Release();
}

//===========================================================
// 更新処理
//===========================================================
void CAppearanceUI::Update(void)
{
	if (m_pFrontObj2D != nullptr && m_pBackObj2D != nullptr)
	{// 前と後ろ両方使用していたら

		// 幅と高さ取得
		float fHeight = m_pFrontObj2D->GetHeight();
		float fWidth = m_pFrontObj2D->GetWidth();

		if (m_pFrontObj2D->GetHeight() >= 100.0f && m_pFrontObj2D->GetWidth() >= 30.0f)
		{// この数値以下になるまで小さくする

			fHeight = fHeight - 25.0f;
			fWidth = fWidth - 50.0f;

			// サイズ設定
			m_pFrontObj2D->SetSize(fWidth, fHeight);
			m_pBackObj2D->SetSize(fWidth, fHeight);
		}
		else
		{// 小さくなった

			// 描画させる
			m_pBackObj2D->SetDraw(true);

			// 幅と高さ取得
			float fHeight = m_pBackObj2D->GetHeight();
			float fWidth = m_pBackObj2D->GetWidth();

			fHeight = fHeight + 5.0f;
			fWidth = fWidth + 10.0f;

			// 透明度取得
			float fColor_a = m_pBackObj2D->GetColor().a;

			fColor_a = fColor_a - 0.03f;

			// サイズ設定
			m_pBackObj2D->SetSize(fWidth, fHeight);

			// 色設定
			m_pBackObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fColor_a));
		}

		if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
		{
			D3DXVECTOR3 pos = m_pFrontObj2D->GetPosition();

			pos.x = pos.x + 20.0f;

			m_pFrontObj2D->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));

			// サイズ設定
			m_pFrontObj2D->SetSize(fWidth, fHeight);

			if (pos.x >= 1500.0f)
			{
				Uninit();
			}
		}
	}
}

//===========================================================
// 描画処理
//===========================================================
void CAppearanceUI::Draw(void)
{

}

//===========================================================
// 生成処理
//===========================================================
CAppearanceUI * CAppearanceUI::Create(TYPE type)
{
	CAppearanceUI *pAppearUI = nullptr;
	pAppearUI = new CAppearanceUI(type);

	if (pAppearUI != nullptr)
	{
		pAppearUI->Init();
	}

	return pAppearUI;
}
