//===========================================================
//
// ヒートアクション[heataction.h]
// Author 大原怜将
//
//===========================================================
#ifndef _HIEATACTION_H_
#define _HIEATACTION_H_

#include "player.h"

// 前方宣言
class CEnemy;
class CItem;

// ヒートアクションクラス 
class CHeatAction
{
public:

	void Init(void);
	void Uninit(void);
	void Updata(void);

	void BikeCrash(CPlayer* pPlayer, CEnemy* pEnemy);
	void MicroWave(CPlayer* pPlayer, CEnemy* pEnemy, CItem *pItem);
	void SetAction(CPlayer::HEAT heatact, CPlayer* pPlayer, CEnemy* pEnemy);

private:

	CPlayer::HEAT m_HeatAct;
	CPlayer* m_pPlayer;
	CEnemy* m_pEnemy;

	int m_nHeatActTime;

	bool m_bInMicroWave = false;;  // ヒートアクション:電子レンジで敵が電子レンジの中に入ったかどうか

};

#endif