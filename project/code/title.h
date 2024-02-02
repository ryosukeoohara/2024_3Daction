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

private:
	CField *m_pField;
	CObject2D *m_pBg;

};
#endif // !_TITLE_H_