//===========================================================
//
//ポリゴンを出すやつ[game.h]
//Author 大原怜将
//
//===========================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"

// 前方宣言
class CPause;
class CEnemyManager;
class CItem;

//ゲームクラス
class CGame : public CScene
{
public:
	CGame();
	CGame(CScene::MODE mode);
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	// 設定系
	void SetbPause(bool bpause) { m_bPause = bpause; }

	// 取得系
	bool GetbPause(void) { return m_bPause; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CCollision *GetCollision(void) { return m_Collision; }
	static CItem *GetItem(void) { return m_pItem; }

private:
	static CPause *m_pPause;
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	static CEnemyManager *m_pEnemyManager;
	static CCollision *m_Collision;
	static CItem *m_pItem;
	bool m_bPause;
	bool m_bUse;  //エディットモード中かどうか
	static int m_nCounter;
};

#endif // !_GAME_H_