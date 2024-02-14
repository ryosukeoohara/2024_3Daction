//===========================================================
//
// アイテム処理[item.cpp]
// Author 大原怜将
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "item.h"
#include "objectX.h"
#include "debugproc.h"
#include "object.h"
#include "itemmanager.h"
#include "game.h"
#include "collision.h"
#include "player.h"
#include "billboard.h"
#include "texture.h"

// マクロ定義
#define TEXT_NAME  ("data\\TEXT\\item.txt")  // マップに配置するアイテム
#define TEX_GRAP   ("data\\TEXTURE\\arrow.png")  // マップに配置するアイテム

// 無名名前空間を定義
namespace
{
	const D3DXVECTOR2 TEXSIZE = { 15.0f, 15.0f };  // サイズ
}

//================================================================
// コンストラクタ
//================================================================
CItem::CItem()
{
	m_pBill = nullptr;
}

//================================================================
// コンストラクタ(オーバーロード)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename) : CObjectX(aModelFliename)
{
	SetPosition(pos);
	SetRotition(rot);
	m_pBill = nullptr;
}

//================================================================
// デストラクタ
//================================================================
CItem::~CItem()
{

}

//================================================================
// 生成処理
//================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type, const char *aModelFliename)
{
	//オブジェクト2Dのポインタ
	CItem *pItem = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//オブジェクト2Dの生成
			pItem = new CItem(pos, rot, type, aModelFliename);

			//初期化処理
			pItem->Init();
			pItem->SetType(type);
		}
	}

	return pItem;
}

//================================================================
// 初期化処理
//================================================================
HRESULT CItem::Init(void)
{
	CObjectX::Init();

	return S_OK;
}

//================================================================
// 終了処理
//================================================================
void CItem::Uninit(void)
{
	CObjectX::Uninit();

	//CGame::GetItemManager()->Release(m_nID);
}

//================================================================
// 更新処理
//================================================================
void CItem::Update(void)
{
	CObjectX::Update();

	if (CGame::GetCollision()->Circle(&GetPosition(), &CGame::GetPlayer()->GetPosition(), 40.0f, 40.0f) == true)
	{// 範囲内

		if (m_Type != TYPE_MICROWAVE)
		{// 種類が電子レンジ以外

			if (m_pBill == nullptr)
			{
				// 生成して位置、サイズ、描画するかどうか、使用するテクスチャ設定
				m_pBill = CBillBoard::Create();
				m_pBill->SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y + 40.0f, GetPosition().z));
				m_pBill->SetSize(TEXSIZE.x, TEXSIZE.y);
				m_pBill->SetDraw();
				m_pBill->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist(TEX_GRAP));
			}
		}
	}
	else
	{// 範囲外

		if (m_pBill != nullptr)
		{
			// 終了
			m_pBill->Uninit();
			m_pBill = nullptr;
		}
	}
}