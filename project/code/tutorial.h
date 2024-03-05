//===============================================================
//
//チュートリアル処理[tutorial.h]
// Author 大原怜将
//
//===============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "manager.h"
#include "game.h"

class CField;
class CObject2D;
class CMap;
class CPlayer;
class CEnemy;
class CItemManager;
class CCollision;
class CTutorialUI;

class CTutorial : public CGame
{
public:

	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorial *Create(void);
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CMap *GetMap(void) { return m_pMap; }

private:
	CField *m_pField;
	CObject2D *m_pBg;
	CObject2D *m_pStart;
	static CMap *m_pMap;
	CEnemy *m_pEnemy;
	CItemManager *m_pItemManager;
	CCollision *m_Collision;
	static CTutorialUI *m_pUI;
	static CEnemyManager *m_pEnemyManager;
	static CPlayer *m_pPlayer;

};

#endif 