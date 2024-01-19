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

//=============================================================================
//コンストラクタ
//=============================================================================
CCollision::CCollision()
{

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
bool CCollision::Circle(D3DXVECTOR3 *pPos, float fRadius, CPlayer *pPlayer)
{
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	float PlayerfRadius = 50.0f;

	float circleX = pPos->x - pos.x;
	float circleZ = pPos->z - pos.z;
	float c = 0.0f;

	c = (float)sqrt(circleX * circleX + circleZ * circleZ);

	if (c <= fRadius + PlayerfRadius)
	{
		return true;
	}

	return false;
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
void CCollision::Map(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, CObjectX **pObjectX)
{

}

bool CCollision::Block(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, float fWidthX, float fWidthZ)
{
	return false;
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
