//===========================================================
//
//ポリゴンを出すやつ[player.h]
//Author 大原怜将
//
//===========================================================
#ifndef _PLAYER_H_             //このマクロ定義がされてなかったら
#define _PLAYER_H_             //2重インクルード防止のマクロ定義をする

//*==========================================================
//インクルードファイル
//*==========================================================
#include "object.h"

//*==========================================================
//前方宣言
//*==========================================================
class CMotion;
class CCharacter;
class CObjectX;

//*==========================================================
//プレイヤークラス
//*==========================================================
class CPlayer : public CObject
{
public:
	// 状態
	enum STATE
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_AVOID,
		STATE_LIFT,
		STATE_GRAP,
		STATE_THROW,
		STATE_HEAT,
		STATE_MAX
	};

private:

	//モーション
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,                // ニュートラル
		TYPE_MOVE,                       // 移動
		TYPE_ATTACK01,                   // 連撃1段目
		TYPE_ATTACK02,                   // 連撃2段目
		TYPE_ATTACK03,                   // 連撃3段目 
		TYPE_AVOID,                      // 回避
		TYPE_LIFT,                       // 持ち上げる
		TYPE_THROW,                      // 投げる
		TYPE_MAX
	} ;

	// 連撃
	enum ATTACKTYPE
	{
		TYPE00_NONE = 0,
		TYPE01_ATTACK,
		TYPE02_ATTACK,
		TYPE03_ATTACK,
		TYPEMAX_ATTACK
	};

	enum DAMEGESTATE
	{
		DAMEGE_NONE = 0,
		DAMEGE_SMALL,
		DAMEGE_BIG,
		DAMEGE_MAX
	};

	// 情報
	struct INFO
	{
		D3DXVECTOR3 pos;                  // 位置
		D3DXVECTOR3 posOld;               // 前回の位置
		D3DXVECTOR3 rot;                  // 向き
		D3DXVECTOR3 move;                 // 移動
		D3DXCOLOR col;                    // 色
		D3DXMATRIX mtxWorld;              // ワールドマトリックス
		STATE state;                      // 状態
		ATTACKTYPE Atc;
	};

	INFO m_Info;                          // 情報
	
public:
	CPlayer();  //コンストラクタ
	CPlayer(D3DXVECTOR3 pos);  //コンストラクタ(オーバーロード)
	~CPlayer();  //デストラクタ

	HRESULT Init(void);        // 初期化処理    
	void Uninit(void);		   // 終了処理
	void Update(void);         // 更新処理
	void Draw(void);           // 描画処理

	static CPlayer *Create(D3DXVECTOR3 pos);  // 生成
	static CPlayer *Create(void);
	void Hit(void);			                  // 攻撃をくらった時の処理

	//　設定系
	void SetPosition(D3DXVECTOR3 pos) { m_Info.move = pos; }         // 位置設定
	void SetRotition(D3DXVECTOR3 rot) { m_Info.move = rot; }         // 向き設定
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }           // 移動量設定
	void SetState(STATE state) { m_Info.state = state; }             // 状態
	void SetGrapItem(CObjectX *obj) { m_Obj = obj; }

	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // 位置取得
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // 向き取得
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // 移動量取得
	STATE GetState(void) { return m_Info.state; }              // 状態
	D3DXMATRIX *GetMatrix(void) { return &m_Info.mtxWorld; }     // マトリックス
	CCharacter **GetChar(void) { return m_ppCharacter; }
	bool GetbAttack(void) { return m_bAttack; }                // 攻撃中かどうか

private:

	void Control(void);                   // 制御
	void Move(void);                      // 移動
	void Action(void);                    // 攻撃
	void GrapRotition(void);              // ジャイアントスイング
	void ReadText(const char *fliename);  // テキストファイル読み込み

	int m_nNumModel;                    //モデル(パーツ)の総数
	int m_nIdxTexture;
	int m_nIdxShaadow;
	int m_nIdx;
	int m_nParent;
	int m_nCntColi;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_pMotion;                   // モーションへのポインタ
	CCharacter **m_ppCharacter;           // キャラクターへのポインタ
	CObjectX *m_Obj;
	float m_fDest;
	float m_fDestOld;
	float m_fDiff;
	float m_fGrapRot;
	bool m_bDesh;                         // ダッシュ
	bool m_bAttack;                       // 攻撃
	bool m_bAvoid;                        // 回避
	bool m_bLift;                         // 持ち上げる
	bool m_bGrap;                         // 投げ

	//チュートリアルで使う関数,変数
	void ControlTutorial(void);          // チュートリアルのプレイヤーの制御
	bool m_bPushW;                       // Wキーを押した
	bool m_bPushA;                       // Aキーを押した
	bool m_bPushS;                       // Sキーを押した
	bool m_bPushD;                       // Dキーを押した
	bool m_bAvoi;                        // 回避した
	bool m_bWhee;                        // ホイールを回転した
};

#endif