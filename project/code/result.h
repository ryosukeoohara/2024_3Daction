//===========================================================
//
//���U���g���[result.h]
//Author �匴�叫
//
//===========================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "manager.h"
#include "object2D.h"

// �O���錾
class CField;
class CMap;
class CAppearanceUI;
class CUserRankUI;

//���U���g�N���X
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult *Create(void);

private:
	CMap *m_pMap;
	CField *m_pField;
	CAppearanceUI *m_pNumber;
	CUserRankUI *m_pUserRank;

	int m_nCounter;
};

#endif // !_TITLE_H_