//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"
#include "player.h"

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
		STATE_HEATDAMEGE,  // 攻撃受けた
		STATE_GETUP,       // 起き上がり
		STATE_BIRIBIRI,    // 電子レンジ待機
		STATE_BIRI,        // 電子レンジびりびり
		STATE_FAINTING,     // 電子レンジ気絶
		STATE_MAX
	};

	//モーション
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // ニュートラル
		TYPE_DASH,                     // 移動
		TYPE_ATTACK,                   // 攻撃
		TYPE_DAMEGE,                   // ダメージ
		TYPE_GRAP,                     // 掴まれ
		TYPE_HEATDAMEGE,               // ヒートアクションダメージ
		TYPE_BIRIBIRI,                 // 電子レンジ待機
		TYPE_BIRI,                     // 電子レンジびりびり
		TYPE_FAINTING,                 // 電子レンジ気絶
		TYPE_PUNCH,                    // パンチ
		TYPE_GURUGURU,                 // ぐるぐるパンチ
		TYPE_GETUP,                    // 起き上がり
		TYPE_MAX
	};

	// 敵の種類
	enum TYPE
	{
		TYPE_WEAK = 0,      // ザコ
		TYPE_BOSS,      // ボス
	};

	enum CHASE
	{
		CHASE_OFF = 0,
		CHASE_ON,
		CHASE_MAX
	};
	CHASE m_Chase;

public:

	CEnemy();                                  //コンストラクタ
	CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //コンストラクタ
	~CEnemy();                                 //デストラクタ
										       
	virtual HRESULT Init(void);                        //初期化
	virtual void Uninit(void);                         //終了
	virtual void Update(void);                         //更新
	virtual void Draw(void);                           //描画

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //生成
	void ReadText(char *fliename);             //テキストファイル読み込み

	//　設定系
	void SetPosition(D3DXVECTOR3 pos)
	{ 
		m_Info.pos = pos; 
	}         // 位置
	void SetRotition(D3DXVECTOR3 rot) { m_Info.rot = rot; }         // 向き
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }          // 移動量
	void SetState(STATE state) { m_Info.state = state; }            // 状態
	void SetLife(int nLife) { m_Info.nLife = nLife; }               // 体力
	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }  // 親のマトリックス
	void SetIdx(int idx) { m_Info.nIdxID = idx; }
	void SetType(TYPE type) { m_Type = type; }
	virtual void SetChase(CHASE cha);
	void SetDraw(bool value) { m_Info.bDraw = value; }

	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // 位置
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // 向き
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // 移動量
	STATE GetState(void) { return m_Info.state; }              // 状態
	int GetLife(void) { return m_Info.nLife; }                 // 体力
	int GetIdxID(void) { return m_Info.nIdxID; }
	CCharacter **GetCharcter(void) { return m_apModel; }
	static int GetNumAll(void) { return m_nNumAll; }
 	CMotion *GetMotion(void) { return m_pMotion; }

	virtual void Damege(int damege, float blowaway, CPlayer::ATTACKTYPE act);
	void MicroWave(void);

protected:

	// 制御処理
	virtual void Controll(void);
	virtual void Attack(void);
	virtual void Move(void);
	
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
		bool bDraw;                              // 描画するかどうか
	};

	INFO m_Info;                                 // 情報
	TYPE m_Type;

private:

	//CEnemy *m_apEnemy[]
	CMotion *m_pMotion;                        // モーションへのポインタ
	CCharacter **m_apModel;                    // モデル(パーツ)へのポインタ
	CGage3D *m_pLife3D;                          // ゲージのポインタ
	CGage2D *m_pLife2D;                          // ゲージのポインタ
	static int m_nNumAll;                      // 敵の総数
	int m_nDamegeCounter;                      // ダメージ状態でいるカウント
	int m_nBiriBiriCount;
	static int m_nIdx;
	D3DXMATRIX *m_pCurrent;                    // 親のマトリックス
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
	int m_nidx;                                // インデックス番号
	int m_nParent;                             // 親のインデックス番号
	int m_nNumModel;                           // モデル(パーツ)の総数
	char m_filename[128] = {};                 // 文字読み込み用

};

#endif // !_ENEMY_H_