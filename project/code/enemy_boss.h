//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

#include "enemy.h"

//*=============================================================================
//クラス定義
//*=============================================================================
class CMotion;
class CCharacter;

//*=============================================================================
//クラス定義
//*=============================================================================
class CEnemyBoss : public CEnemy
{
public:

	//モーション
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // ニュートラル
		TYPE_DASH,                     // 移動
		TYPE_ATTACK,                   // 攻撃
		TYPE_DAMEGE,                   // ダメージ
		TYPE_HEATDAMEGE,               // ヒートアクションダメージ
		TYPE_GURUGURUPUNCH,            // ぐるぐるパンチ
		TYPE_PUNCH,                    // パンチ
		TYPE_MAX
	};

	enum ATTACKTYPE
	{
		ATTACKTYPE_GURUGURU = 0,
		ATTACKTYPE_PUNCH,
		ATTACKTYPE_FLY,
		ATTACKTYPE_MAX
	};

public:

	CEnemyBoss();                                  //コンストラクタ
	CEnemyBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //コンストラクタ
	~CEnemyBoss();                                 //デストラクタ

	HRESULT Init(void) override;                        //初期化
	void Uninit(void) override;                         //終了
	void Update(void) override;                         //更新
	void Draw(void) override;                           //描画

	static CEnemyBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //生成

	// 設定系
	void SetChase(CHASE cha) { m_Chase = cha; }

private:

	// 敵の動き制御
	//void Controll(void) override;
	void Attack(void) override;
	void Move(void) override;
	void Damege(int damege, float blowaway) override;

	int m_nDamegeCounter;                      // ダメージ状態でいるカウント
	int m_nAtcCounter;                         // 攻撃のインターバル
	int m_nIdx;
	

};

#endif // !_ENEMY_H_