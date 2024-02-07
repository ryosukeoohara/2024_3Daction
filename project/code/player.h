//===========================================================
//
//ポリゴンを出すやつ[player.h]
//Author 大原怜将
//
//===========================================================
#ifndef _PLAYER_H_             //このマクロ定義がされてなかったら
#define _PLAYER_H_             //2重インクルード防止のマクロ定義をする

//*==========================================================
// インクルードファイル
//*==========================================================
#include "object.h"

//*==========================================================
// 前方宣言
//*==========================================================
class CMotion;
class CCharacter;
class CObjectX;
class CGage2D;
class CGage3D;
class CBillBoard;
class CEnemy;
class CObject2D;
class CItem;

//*==========================================================
// プレイヤークラス
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
		STATE_GRAPDASH,
		STATE_DAMEGE,
		STATE_MAX
	};

	enum HEATACT
	{
		HEATACT_BIKE = 0,
	};

	// 連撃
	enum ATTACKTYPE
	{
		TYPE00_NONE = 0,       // なんもない
		TYPE01_ATTACK,         // 一段目
		TYPE02_ATTACK,         // 二段目
		TYPE03_ATTACK,         // 三段目
		TYPE04_HEATACTBIKE,    // ヒートアクション・バイク
		TYPE05_HEATACTREF,     // ヒートアクション・冷蔵庫
		TYPEMAX_ATTACK
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
		TYPE_GRAPDASH,                   // 持って走る
		TYPE_MAX
	} ;

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
		int nLife;
	};

	INFO m_Info;                          // 情報
	HEATACT m_HeatAct;
	
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
	void SetPosition(D3DXVECTOR3 pos) { m_Info.pos = pos; }         // 位置設定
	void SetRotition(D3DXVECTOR3 rot) { m_Info.rot = rot; }         // 向き設定
	void SetMove(D3DXVECTOR3 move) { m_Info.move = move; }           // 移動量設定
	void SetState(STATE state) { m_Info.state = state; }             // 状態
	void SetGrapItem(CItem *obj) { m_pItem = obj; }
	void SetLife(int nlife) { m_Info.nLife = nlife; }                // 体力

	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }       // 位置取得
	D3DXVECTOR3 GetRotition(void) { return m_Info.rot; }       // 向き取得
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }          // 移動量取得
	STATE GetState(void) { return m_Info.state; }              // 状態
	int GetLife(void) { return m_Info.nLife; }                 // 体力
	D3DXMATRIX *GetMatrix(void) { return &m_Info.mtxWorld; }     // マトリックス
	CCharacter **GetChar(void) { return m_ppCharacter; }
	bool GetbAttack(void) { return m_bAttack; }                // 攻撃中かどうか
	CMotion *GetMotion(void) { return m_pMotion; }
	ATTACKTYPE GetActType(void) { return m_Info.Atc; }

private:

	void Control(void);                   // 制御
	void Move(void);                      // 移動
	void Action(void);                    // 攻撃
	void GrapRotition(void);              // ジャイアントスイング
	void Grap(void);
	void Avoid(void);
	void State(void);
	void Damege(void);
	void Heat(void);
	void ReadText(const char *fliename);  // テキストファイル読み込み

	int m_nNumModel;                    //モデル(パーツ)の総数
	int m_nIdxTexture;
	int m_nIdxShaadow;
	int m_nIdx;
	int m_nParent;
	int m_nCntColi;
	int m_nDamegeCounter;
	char m_filename[128] = {};

	D3DXVECTOR3 m_Readpos;
	D3DXVECTOR3 m_Readrot;
	D3DXVECTOR3 m_posOrigin;             
	CMotion *m_pMotion;                   // モーションへのポインタ
	CCharacter **m_ppCharacter;           // キャラクターへのポインタ
	CItem *m_pItem;                      // 掴んでるオブジェクトのポインタ
	CGage2D *m_pLife;                     // ゲージのポインタ
	CGage3D *m_pStamina;                  // ゲージのポインタ
	CEnemy *m_pEnemy;
	CObject2D *m_pBotton;
	int m_nIdxEne;
	float m_fDest;
	float m_fDestOld;
	float m_fDiff;
	float m_fGrapRot;
	float m_fStamina;                     // スタミナ
	int m_nLife;                          // 体力
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