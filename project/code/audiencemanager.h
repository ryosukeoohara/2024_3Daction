//===========================================================
//
// 周りで見ている人の管理[audiencemanager.h]
// Author 大原怜将
//
//===========================================================
#ifndef _AUDIENCEMANAGER_H_      //このマクロ定義がされてなかったら
#define _AUDIENCEMANAGER_H_      //2重インクルード防止のマクロ定義をする

#include "main.h"
#include "objectX.h"

// マクロ定義
#define MAX_MODEL (64)   // モデルの最大数
#define MAX_NAME  (128)  // テクスチャの最大文字数

//アイテムクラス
class CAudienceManager
{
public:

	enum TYPE
	{
		TYPE_01 = 0,
		TYPE_02,
		TYPE_03,
		TYPE_04,
		TYPE_MAX
	};

	CAudienceManager();  //コンストラクタ
	~CAudienceManager();  //デストラクタ

	HRESULT Init(void);   // 初期化処理    
	void Uninit(void);    // 終了処理
	void Update(void);    // 更新処理
	void Draw(void);      // 描画処理

	static CAudienceManager* Create(void);

private:

	//static CAudience* m_pTop;  //先頭のオブジェクトへのポインタ
	//static CAudience* m_pCur;  //最後尾のオブジェクトへのポインタ
	//CAudience* m_pNext;        //次のオブジェクトへのポインタ
	//CAudience* m_pPrev;        //前のオブジェクトへのポインタ
};

#endif