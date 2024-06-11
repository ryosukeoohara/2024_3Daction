//=============================================================================
//
// アイテムの管理 [itemmanager.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

//*============================================================================
// インクルードファイル
//*============================================================================
#include "main.h"
#include "item.h"

//*============================================================================
// マクロ定義
//*============================================================================

//*============================================================================
// クラス定義
//*============================================================================
class CItemManager
{
public:
	CItemManager();              //コンストラクタ
	~CItemManager();             //デストラクタ

	HRESULT Init(void);            //初期化処理
	void Uninit(void);             //終了処理
	void Update(void);             //更新処理

	static CItemManager *Create(const char* filename);   // 生成処理
	void Release(int idx);
	void ReadText(const char *text);           //テキストファイル読み込み

											   // 設定系
	void SetNum(int num) { m_nNumItem = num; }

	// 取得系
	CItem **GetItem(void) { return m_ppItem; }
	int GetNum(void) { return m_nNumItem; }

private:
	void ListOut(void);

	CItem **m_ppItem;

	int m_nNumModel;
	int m_nNumItem;
	int m_nNum;

	static const char *m_apTexName[CItem::TYPE_MAX];
};

#endif // !_ENEMYMANAGER_H_