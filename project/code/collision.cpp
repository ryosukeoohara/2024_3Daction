//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 大原　怜将
//
//=============================================================================

//*============================================================================
//インクルードファイル
//*============================================================================
#include "main.h"
#include "collision.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "debugproc.h"
#include "collision.h"
#include "object.h"
#include "objectX.h"
#include "game.h"
#include "enemy.h"
#include "enemymanager.h"
#include "itemmanager.h"
#include "character.h"
#include "motion.h"
#include "map.h"
#include "motion.h"
#include "particle.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CCollision::CCollision()
{
	m_bColli = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CCollision::~CCollision()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CCollision::Uninit(void)
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CCollision * CCollision::Create(void)
{
	CCollision *pCollision = nullptr;

	pCollision = new CCollision;

	if (pCollision != nullptr)
	{
		pCollision->Init();
	}

	return pCollision;
}

//=============================================================================
//敵とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::Enemy(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CEnemy **pEnemy)
{
	return false;
}

//=============================================================================
//円の当たり判定処理
//=============================================================================
bool CCollision::Circle(D3DXVECTOR3 *pMyPos, D3DXVECTOR3 *pTargetPos, float fMyRadius, float fTargetRadius)
{
	float circleX = pMyPos->x - pTargetPos->x;
	float circleZ = pMyPos->z - pTargetPos->z;
	float c = 0.0f;

	c = (float)sqrt(circleX * circleX + circleZ * circleZ);

	if (c <= fMyRadius + fTargetRadius)
	{
		return true;
	}
	
	return false;
}

//=============================================================================
//円の当たり判定処理
//=============================================================================
void CCollision::AttackCircle(D3DXVECTOR3 * pMyPos, float fMyRadius, float fTargetRadius, float fHeight)
{
	CEnemyManager *pEnemyManager = CGame::GetEnemyManager();
	CEnemy **ppEnemy = nullptr;
	int nNum = 0;

	if (pEnemyManager != nullptr)
	{
		ppEnemy = pEnemyManager->GetEnemy();
		nNum = CGame::GetEnemyManager()->GetNum();
	}

	for (int nCount = 0; nCount < nNum; nCount++)
	{
		if (ppEnemy[nCount] != nullptr)
		{
			float circleX = pMyPos->x - ppEnemy[nCount]->GetPosition().x;
			float circleZ = pMyPos->z - ppEnemy[nCount]->GetPosition().z;
			float c = 0.0f;

			c = (float)sqrt(circleX * circleX + circleZ * circleZ);

			if (c <= fMyRadius + fTargetRadius && (pMyPos->y >= ppEnemy[nCount]->GetPosition().y && pMyPos->y <= ppEnemy[nCount]->GetPosition().y + fHeight) && ppEnemy[nCount]->GetState() != CEnemy::STATE_DAMEGE && ppEnemy[nCount]->GetState() != CEnemy::STATE_HEATDAMEGE)
			{
				ppEnemy[nCount]->Damege(CGame::GetPlayer()->GetMotion()->GetAttackDamege(), CGame::GetPlayer()->GetMotion()->GetBlowAway(), CGame::GetPlayer()->GetActType());
			}
		}
	}
}

//=============================================================================
//敵とオブジェクトの当たり判定処理
//=============================================================================
bool CCollision::Player(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fWidthX, float fWidthZ, CPlayer *pPlayer)
{
	return false;
}

//=============================================================================
//マップにある建物との当たり判定
//=============================================================================
void CCollision::Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, float fRadius)
{
	int nNum = 0;
	CObjectX **pMap = nullptr;

	if (CGame::GetMap() != nullptr)
	{
		nNum = CGame::GetMap()->GetNum();
		pMap = CGame::GetMap()->GetObjectX();
	}

	for (int nCount = 0; nCount < nNum; nCount++)
	{
		if (pMap[nCount] != nullptr && pMap[nCount]->GetbColli() == true)
		{
			D3DXVECTOR3 Mappos = pMap[nCount]->GetPosition();

			D3DXVECTOR3 vtxMin = pMap[nCount]->GetVtxMin();

			D3DXVECTOR3 vtxMax = pMap[nCount]->GetVtxMax();

			if (pos->x + fRadius > Mappos.x + vtxMin.x
				&& pos->x + fRadius < Mappos.x + vtxMax.x
				&& pos->z + fRadius > Mappos.z + vtxMin.z
				&& pos->z + fRadius < Mappos.z + vtxMax.z)
			{
				//ブロックの上======================================
				if (pos->z + fRadius <= Mappos.z + vtxMax.z
					&& posOld->z + fRadius >= Mappos.z + vtxMax.z)
				{
					pos->z = Mappos.z + vtxMax.z - fRadius;

					//return true;
				}

				//ブロックの下======================================
				else if (pos->z + fRadius >= Mappos.z + vtxMin.z
					&& posOld->z + fRadius <= Mappos.z + vtxMin.z)
				{
					pos->z = Mappos.z + vtxMin.z - fRadius;

					//return true;
				}

				//横からめり込んだ
				else if (pos->x + fRadius > Mappos.x + vtxMin.x
					&& pos->x + fRadius < Mappos.x + vtxMax.x)
				{
					//ブロックの左側面==================================
					if (pos->x + fRadius >= Mappos.x + vtxMin.x
						&& posOld->x + fRadius <= Mappos.x + vtxMin.x)
					{
						pos->x = Mappos.x + vtxMin.x - fRadius;

						//return true;
					}

					//ブロックの右側面==================================
					else if (pos->x - fRadius <= Mappos.x + vtxMax.x
						&& posOld->x - fRadius >= Mappos.x - vtxMax.x)
					{
						pos->x = Mappos.x + vtxMax.x - fRadius;

						//return true;
					}
				}
			}
		}
	}

	//return false;
}

//=============================================================================
//剣の当たり判定
//=============================================================================
bool CCollision::Sword(D3DXMATRIX matrix1, D3DXMATRIX matrix2, float flength, CEnemy *pEnemy)
{
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX Matrix;
	D3DXVECTOR3 offPos = { 0.0f, 0.0f, -flength };
	D3DXVECTOR3 Pos = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 offRot = { 0.0f, 0.0f, 0.0f };

	//計算用マトリックス
	D3DXMATRIX m_mtxRot, m_mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Matrix);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, offRot.y, offRot.x, offRot.z);

	D3DXMatrixMultiply(&Matrix, &Matrix, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, offPos.x, offPos.y, offPos.z);

	D3DXMatrixMultiply(&Matrix, &Matrix, &m_mtxTrans);

	//算出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&Matrix, &Matrix, &matrix2);

	Pos.x = Matrix._41;
	Pos.y = Matrix._42;
	Pos.z = Matrix._43;

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Matrix);

	/*CEnemy *penemy = CEnemyManager::GetEnemy();

	while (penemy != nullptr)
	{
		CEnemy *pNextEnemy = penemy->m_pNext;

		D3DXVECTOR3 Enemypos = penemy->GetPosition();

		if ((matrix1._41 >= Enemypos.x - 30.0f && Pos.x <= Enemypos.x + 30.0f || matrix1._41 <= Enemypos.x + 30.0f && Pos.x >= Enemypos.x - 30.0f)
			&& (matrix1._43 >= Enemypos.z - 30.0f &&  Pos.z <= Enemypos.z + 30.0f || matrix1._43 <= Enemypos.z + 30.0f &&  Pos.z >= Enemypos.z - 30.0f))
		{
			penemy->SetState(CEnemy::STATE_DAMEGE);
			penemy->SetMove(D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y), 1.0f, cosf(CGame::GetPlayer()->GetRotition().y)));
			return true;
		}

		penemy = pNextEnemy;
	}*/

	if (pEnemy != nullptr)
	{
		D3DXVECTOR3 Enemypos = pEnemy->GetPosition();

		if ((matrix1._41 >= Enemypos.x - 30.0f && Pos.x <= Enemypos.x + 30.0f || matrix1._41 <= Enemypos.x + 30.0f && Pos.x >= Enemypos.x - 30.0f)
		&& ( matrix1._43 >= Enemypos.z - 30.0f && Pos.z <= Enemypos.z + 30.0f || matrix1._43 <= Enemypos.z + 30.0f && Pos.z >= Enemypos.z - 30.0f))
		{
			pEnemy->SetState(CEnemy::STATE_DAMEGE);
			pEnemy->SetMove(D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y), 1.0f, cosf(CGame::GetPlayer()->GetRotition().y)));
			return true;
		}
	}
	else
	{
		return false;
	}
	
	return false;
}

//=============================================================================
//マップにある建物との当たり判定
//=============================================================================
void CCollision::MapEnemy(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, CObjectX ** pObjectX, CEnemy *penemy)
{
	
}

//=============================================================================
//マップにある建物との当たり判定
//=============================================================================
bool CCollision::Item(D3DXVECTOR3 *pos)
{
	CItemManager *pItemManager = CGame::GetItemManager();
	CItem **ppItem = pItemManager->GetItem();
	int nNum = 0;

	if (pItemManager != nullptr)
	{
		nNum = pItemManager->GetNum();
	}

	float PlayerfRadius = 50.0f;
	float fRadius = 25.0f;

	for (int nCount = 0; nCount < nNum; nCount++)
	{
		if (ppItem[nCount] != nullptr)
		{
			ppItem[nCount]->GetPosition();

			float circleX = ppItem[nCount]->GetPosition().x - pos->x;
			float circleZ = ppItem[nCount]->GetPosition().z - pos->z;
			float c = 0.0f;

			c = (float)sqrt(circleX * circleX + circleZ * circleZ);

			if (c <= fRadius + PlayerfRadius)
			{
				CCharacter **pChar = CGame::GetPlayer()->GetChar();
				ppItem[nCount]->SetCurrent(pChar[9]->GetMtxWorld());
				ppItem[nCount]->SetPosition(D3DXVECTOR3(50.0f, 5.0f, -15.0f));
				ppItem[nCount]->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
				CGame::GetPlayer()->SetGrapItem(ppItem[nCount]);
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// マップにある建物との当たり判定
//=============================================================================
void CCollision::ItemAttack(CObjectX * pobj)
{
	int nNum = 0;
	float PlayerfRadius = 50.0f;
	float fRadius = 75.0f;
	CEnemy **ppEnemy = nullptr;

	if (CGame::GetEnemyManager() != nullptr)
	{
		ppEnemy = CGame::GetEnemyManager()->GetEnemy();
		nNum = CGame::GetEnemyManager()->GetNum();
	}

	if (pobj != nullptr)
	{
		for (int nCount = 0; nCount < nNum; nCount++)
		{
			if (ppEnemy[nCount] != nullptr)
			{
				float circleX = ppEnemy[nCount]->GetPosition().x - (CGame::GetPlayer()->GetPosition().x + pobj->GetPosition().x);
				float circleZ = ppEnemy[nCount]->GetPosition().z - (CGame::GetPlayer()->GetPosition().z + pobj->GetPosition().z);
				float c = 0.0f;

				c = (float)sqrt(circleX * circleX + circleZ * circleZ);

				if (c <= fRadius + PlayerfRadius)
				{
					ppEnemy[nCount]->SetRotition(-CGame::GetPlayer()->GetRotition());
					ppEnemy[nCount]->SetMove(D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y) * -3.0f, 1.0f, cosf(CGame::GetPlayer()->GetRotition().y) * -3.0f));
					ppEnemy[nCount]->SetState(CEnemy::STATE_DAMEGE);
					int nLife = ppEnemy[nCount]->GetLife();
					nLife -= 1;
					ppEnemy[nCount]->SetLife(nLife);
				}
			}
		}
	}
}

bool CCollision::ItemEnemy(CItem *pItem, CEnemy *pEnemy, float fMyRadius, float fTargetRadius, float fHeight)
{
	if (pEnemy != nullptr)
	{
		float circleX = pItem->GetMtxWorld()->_41 - pEnemy->GetPosition().x;
		float circleZ = pItem->GetMtxWorld()->_43 - pEnemy->GetPosition().z;
		float c = 0.0f;

		c = (float)sqrt(circleX * circleX + circleZ * circleZ);

		if (c <= fMyRadius + fTargetRadius && (pItem->GetPosition().y >= pEnemy->GetPosition().y && pItem->GetPosition().y <= pEnemy->GetPosition().y + fHeight) && pEnemy->GetState() != CEnemy::STATE_DAMEGE && pEnemy->GetState() != CEnemy::STATE_HEATDAMEGE)
		{
			// 敵の番号を保存
			//CGame::GetEnemyManager()->SetTarget(nCount);
			pEnemy->Damege(CGame::GetPlayer()->GetMotion()->GetAttackDamege(), CGame::GetPlayer()->GetMotion()->GetBlowAway(), CGame::GetPlayer()->GetActType());

			CParticle *pPar = CParticle::Create(pEnemy->GetPosition(), CParticle::TYPEPAR_BLOOD);
			pPar->Blood();
			pPar->Uninit();
			delete pPar;
			pPar = nullptr;

			/*CParticle *pParticle = CParticle::Create(ppEnemy[nCount]->GetPosition(), CParticle::TYPEPAR_GROUND);
			pParticle->Ground();
			pParticle->Uninit();
			delete pParticle;
			pParticle = nullptr;*/

			return true;
		}
	}
	
	return false;
}
