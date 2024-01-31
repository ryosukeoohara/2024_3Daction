//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : 大原　怜将
//
//=============================================================================
#ifndef _CONLLISION_H_
#define _CONLLISION_H_

//=============
//前方宣言
//=============
class CEnemyManager;
class CPlayer;
class CEnemy;
class CBullet;
class CObjectX;


//コリジョンクラス
class CCollision
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);

	static CCollision *Create(void);

	bool Enemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CEnemy **pEnemy);  //敵との当たり判定(プレイヤー基準)
	bool Circle(D3DXVECTOR3 *pMyPos, D3DXVECTOR3 *pTargetPos, float fMyRadius, float fTargetRadius);  //円の当たり判定
	bool AttackCircle(D3DXVECTOR3 *pMyPos, float fMyRadius, float fTargetRadius, float fHeight);  //円の当たり判定
	bool Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer);  //ぷれいやーとの当たり判定
	void Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fRadius);  //マップにある建物との当たり判定
	bool Block(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ);  //ブロックとの判定
	bool Sword(D3DXMATRIX matrix1, D3DXMATRIX matrix2, float flength, CEnemy *pEnemy);
	void MapEnemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX, CEnemy *enemy);  //マップにある建物との当たり判定
	bool Item(D3DXVECTOR3 *pos);
	void ItemAttack(CObjectX *pobj);

	void SetbColli(bool bValue) { m_bColli = bValue; }
	bool GetbColli(void) { return m_bColli; }
	
private:
	bool m_bColli;

};

#endif // !_CONLLISION_H_