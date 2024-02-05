//=============================================================================
//
// 敵の処理 [enemy_weak.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _ENEMY_WEAK_H_
#define _ENEMY_WEAK_H_

#include "enemy.h"

//*=============================================================================
//クラス定義
//*=============================================================================
class CMotion;
class CCharacter;

//*=============================================================================
//クラス定義
//*=============================================================================
class CEnemyWeak : public CEnemy
{
public:

	//モーション
	enum MOTIONTYPE
	{
		TYPE_NEUTRAL = 0,              // ニュートラル
		TYPE_DASH,                     // 移動
		TYPE_ATTACK,                   // 攻撃
		TYPE_DAMEGE,                   // ダメージ
		TYPE_MAX
	};

public:

	CEnemyWeak();                                  //コンストラクタ
	CEnemyWeak(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);                   //コンストラクタ
	~CEnemyWeak();                                 //デストラクタ

	HRESULT Init(void) override;                        //初期化
	void Uninit(void) override;                         //終了
	void Update(void) override;                         //更新
	void Draw(void) override;                           //描画

	static CEnemyWeak *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife);    //生成
	
private:

	// 敵の動き制御
	void Controll(void) override;
	void Attack(void) override;
	void Move(void) override;
	void Damege(void) override;

	int m_nDamegeCounter;                      // ダメージ状態でいるカウント
	int m_nAtcCounter;                         // 攻撃のインターバル
	int m_nIdx;
};

#endif // !_ENEMY_H_