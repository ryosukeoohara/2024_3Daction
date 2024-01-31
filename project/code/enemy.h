//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"

//*=============================================================================
//クラス定義
//*=============================================================================
class CMotion;
class CCharacter;

//*=============================================================================
//クラス定義
//*=============================================================================
class CEnemy : public CObject
{
public:

	// 状態
	enum STATE
	{
		STATE_NONE = 0,    // なんもない
		STATE_NEUTRAL,     // 待機
		STATE_DASH,        // 移動
		STATE_WALK,        // 移動
		STATE_ATTACK,      // 攻撃
		STATE_GRAP,        // 投げられ待ち
		STATE_DAMEGE,      // 攻撃受けた
		STATE_MAX
	};

	//モーション
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // ニュートラル
		TYPE_DASH,                     // 移動
		TYPE_ATTACK,                   // 攻撃
		TYPE_DAMEGE,                   // ダメージ
		TYPE_MAX
	};

private:

	struct INFO
	{
		D3DXVECTOR3 pos;                         // 位置
		D3DXVECTOR3 posOld;                      // 前回の位置
		D3DXVECTOR3 rot;                         // 向き
		D3DXVECTOR3 move;                        // 移動量
		D3DXMATRIX mtxWorld;                     // ワールドマトリックス
		STATE state;                             // 状態
		int nIdxID;                              // インデックス番号
		int nLife;                               // 体力
	};

	INFO m_Info;                                 // 情報

public:

	CEnemy();                                  //コンストラクタ
	CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //コンストラクタ
	~CEnemy();                                 //デストラクタ
										       
	HRESULT Init(void);                        //初期化
	void Uninit(void);                         //終了
	void Update(void);                         //更新
	void Draw(void);                           //描画

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //生成
	void ReadText(char *fliename);             //テキストファイル読み込み

	//　設定系
	void SetPosition(D3DXVECTOR3 pos) { m_Info.pos = pos; }         // 位置
	void SetRotition(D3DXVECTOR3 rot) { m_Info.rot = rot; }         // 向き
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }          // 移動量
	void SetState(STATE state) { m_Info.state = state; }            // 状態
	void SetLife(int nLife) { m_Info.nLife = nLife; }               // 体力
	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }  // 親のマトリックス

	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // 位置
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // 向き
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // 移動量
	STATE GetState(void) { return m_Info.state; }              // 状態
	int GetLife(void) { return m_Info.nLife; }                 // 体力
	CCharacter **GetCharcter(void) { return m_apModel; }
	static int GetNumAll(void) { return m_nNumAll; }
	CMotion *GetMotion(void) { return m_pMotion; }

								       
private:

	void Controll(void);                       // 制御処理
	void Attack(void);
	void Move(void);
	void Damege(void);

	//CEnemy *m_apEnemy[]
	CMotion *m_pMotion;                        // モーションへのポインタ
	CCharacter **m_apModel;                    // モデル(パーツ)へのポインタ
	static int m_nNumAll;                      // 敵の総数
	int m_nDamegeCounter;                      // ダメージ状態でいるカウント
	D3DXMATRIX *m_pCurrent;                     // 親のマトリックス
	static CEnemy *m_pTop;  //先頭のオブジェクトへのポインタ
	static CEnemy *m_pCur; //最後尾のオブジェクトへのポインタ
	static CEnemy *m_pNext;
	CEnemy *m_pPrev;       //前のオブジェクトへのポインタ
	bool m_bDeath;          //死亡フラグ
	
	//*=============================================================================
	// 外部ファイル読み込み用
	//*=============================================================================
	D3DXVECTOR3 m_Readpos;                     // 位置読み込み用
	D3DXVECTOR3 m_Readrot;                     // 向き読み込み用
	int m_nIdx;                                // インデックス番号
	int m_nParent;                             // 親のインデックス番号
	int m_nNumModel;                           // モデル(パーツ)の総数
	char m_filename[128] = {};                 // 文字読み込み用

};

#endif // !_ENEMY_H_