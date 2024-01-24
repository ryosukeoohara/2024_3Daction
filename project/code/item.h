//===========================================================
//
//ポリゴンを出すやつ[item.h]
//Author 大原怜将
//
//===========================================================
#ifndef _ITEM_H_             //このマクロ定義がされてなかったら
#define _ITEM_H_             //2重インクルード防止のマクロ定義をする

class CObjectX;

// マクロ定義
#define MAX_ITEM (2)

//アイテムクラス
class CItem
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NEAR,      //近距離
		TYPE_FAR,       //遠距離
		TYPE_NAILBAT,   //釘バット
		TYPE_BOM,       //爆弾
		TYPE_MAX
	} TYPE;

	typedef enum
	{
		STATE_NONE = 0,
		STATE_FALL,
		STATE_LAND,
		STATE_MAX
	} STATE;

	CItem();  //コンストラクタ
	CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename);  //コンストラクタ(オーバーロード)
	~CItem();  //デストラクタ

	HRESULT Init(void);      //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理

	static CItem *Create(void);

	// 設定系
	
	// 取得系
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	int GetNum(void) { return m_nNumItem; }

private:
	void TextLoad(void);
	CObjectX **m_appObjectX;
	static const char *m_apTexName[MAX_ITEM];

	int m_nNumModel;
	int m_nNumItem;
};

#endif