//===========================================================
//
//ポリゴンを出すやつ[title.h]
//Author 大原怜将
//
//===========================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "manager.h"
#include "object2D.h"

//前方宣言
class CField;
class CObject2D;
class CMap;
class CPlayer;

//タイトルクラス
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitle *Create(void);
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	CField *m_pField;
	CObject2D *m_pBg;
	CMap *m_pMap;
	static CPlayer *m_pPlayer;
	int m_nCnt;
	int m_nCntPos;

};
#endif // !_TITLE_H_