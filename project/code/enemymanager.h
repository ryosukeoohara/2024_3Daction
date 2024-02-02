//=============================================================================
//
// 敵の管理 [enemymanager.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//*============================================================================
//インクルードファイル
//*============================================================================
#include "main.h"
//#include "enemy.h"

// 前方宣言
class CEnemy;

//*============================================================================
//マクロ定義
//*============================================================================
#define MAX_ENEMY   (64)    //敵の最大数

//*============================================================================
//クラス定義
//*============================================================================
class CEnemyManager
{
public:
	CEnemyManager();              //コンストラクタ
	~CEnemyManager();             //デストラクタ
							       
	HRESULT Init(void);            //初期化処理
	void Uninit(void);             //終了処理
	void Update(void);             //更新処理

	static CEnemyManager *Create(void);   // 生成処理
	void Release(int idx);

	CEnemy **GetEnemy(void) { return m_appEnemy; }
	int GetNum(void) { return m_nEnemyAll; }
							       
private:					       
	void ReadText(void);           //テキストファイル読み込み
	void ListOut(void);

	int m_nEnemyAll;               //敵の総数
	CEnemy **m_appEnemy;   //エネミーへのポインタ

	D3DXVECTOR3 m_Readpos;           //テキストファイルの位置読み取り用
	D3DXVECTOR3 m_Readrot;           //テキストファイルの向き読み取り用

	static CEnemy *m_pTop;  //先頭のオブジェクトへのポインタ
	static CEnemy *m_pCur; //最後尾のオブジェクトへのポインタ
	static CEnemy *m_pSNext;
	CEnemy *m_pPrev;       //前のオブジェクトへのポインタ
	CEnemy *m_pNext;       //次のオブジェクトへのポインタ
	bool m_bDeath;         //死亡フラグ
};


#endif // !_ENEMYMANAGER_H_
