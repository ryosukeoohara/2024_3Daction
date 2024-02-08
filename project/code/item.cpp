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


// マクロ定義
#define TEXT_NAME  ("data\\TEXT\\item.txt")  // マップに配置するアイテム

//================================================================
// コンストラクタ
//================================================================
CItem::CItem()
{
	
}

//================================================================
// コンストラクタ(オーバーロード)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename) : CObjectX(aModelFliename)
{
	SetPosition(pos);
	SetRotition(rot);
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
}