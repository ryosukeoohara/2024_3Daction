//===========================================================
//
// ポリゴンを出すやつ[audience.h]
// Author 大原怜将
//
//===========================================================
#ifndef _AUDIENCE_H_      //このマクロ定義がされてなかったら
#define _AUDIENCE_H_      //2重インクルード防止のマクロ定義をする

#include "main.h"

class CObjectX;

// マクロ定義
#define MAX_MODEL (64)   // モデルの最大数
#define MAX_NAME  (128)  // テクスチャの最大文字数

//アイテムクラス
class CAudience
{
public:

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_01,
		TYPE_02,
		TYPE_03,
		TYPE_MAX
	};

	CAudience();  //コンストラクタ
	~CAudience();  //デストラクタ

	HRESULT Init(void);   //ポリゴンの初期化処理    
	void Uninit(void);    //ポリゴンの終了処理
	void Update(void);    //ポリゴンの更新処理

	static CAudience *Create(void);

	// 設定系

	// 取得系
	CObjectX **GetObjectX(void) { return m_appObjectX; }
	int GetNum(void) { return m_nNumModel; }

private:

	struct TEX
	{
		char aName[MAX_NAME];
	};


	void TextLoad(void);
	CObjectX **m_appObjectX;

	int m_nNumModel;
	int m_nNumItem;

	TEX m_aTex[MAX_MODEL];
};

#endif