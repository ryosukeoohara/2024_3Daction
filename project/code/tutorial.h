//===============================================================
//
//�`���[�g���A������[tutorial.h]
// Author �匴�叫
//
//===============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "manager.h"
#include "game.h"

// �O���錾
class CField;
class CObject2D;
class CMap;
class CPlayer;
class CEnemy;
class CItemManager;
class CCollision;
class CTutorialUI;

// �N���X��`
class CTutorial : public CScene
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
	static CEnemyManager* GetEnemyManager(void) { return m_pEnemyManager; }
	static CItemManager* GetItemManager(void) { return m_pItemManager; }

private:
	CField *m_pField;
	CObject2D *m_pBg;
	CObject2D *m_pStart;
	static CMap *m_pMap;
	CEnemy *m_pEnemy;
	static CItemManager *m_pItemManager;
	CCollision *m_Collision;
	static CTutorialUI *m_pUI;
	static CEnemyManager *m_pEnemyManager;
	static CPlayer *m_pPlayer;

};

#endif 