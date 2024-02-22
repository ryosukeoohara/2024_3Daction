//===========================================================
//
//ポリゴンを出すやつ[item.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ITEM_H_             //このマクロ定義がされてなかったら
#define _ITEM_H_             //2重インクルード防止のマクロ定義をする

#include "objectX.h"

class CObjectX;
class CBillBoard;

// マクロ定義
#define MAX_ITEM (2)

//アイテムクラス
class CItem : public CObjectX
{
public:

	enum TYPE
	{
		TYPE_REF = 0,       // 冷蔵庫
		TYPE_BIKE,          // 自転車
		TYPE_MICROWAVE,     // 電子レンジ
		TYPE_TABLE,         // テーブル
		TYPE_POSTER,        // 看板
		TYPE_MAX
	};

	CItem();  //コンストラクタ
	CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename);  //コンストラクタ(オーバーロード)
	~CItem();  //デストラクタ

	HRESULT Init(void);      //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE Type, const char *aModelFliename);

	// 設定系
	void SetType(TYPE type) { m_Type = type; }
	void SetID(int id) { m_nID = id; }
	
	// 取得系
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	TYPE GetType(void) { return m_Type; }
	int GetID(void) { return m_nID; }

private:
	CObjectX **m_appObjectX;
	CBillBoard *m_pBill;
	TYPE m_Type;
	int m_nID;
	static const char *m_apTexName[MAX_ITEM];
};

#endif