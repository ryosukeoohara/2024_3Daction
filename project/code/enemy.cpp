//==============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 大原　怜将
//
//==============================================================================

//*=============================================================================
//インクルードファイル
//*=============================================================================
#include "enemy.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "sound.h"
#include "player.h"
#include "game.h"
#include "debugproc.h"
#include "score.h"
#include "player.h"
#include "character.h"
#include "collision.h"
#include "enemymanager.h"
#include <assert.h>

// 静的メンバ変数
CEnemy *CEnemy::m_pTop = nullptr;
CEnemy *CEnemy::m_pCur = nullptr;
CEnemy *CEnemy::m_pNext = nullptr;

//*=============================================================================
// マクロ定義
//*=============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\motion_set_enemy.txt")   //敵のテキストファイル
#define ENEMYMOVE    (2.0f)                        //移動量

// 無名名前空間を定義
namespace
{
	const int DAMEGECOUNT = 25;  // ダメージ状態
}

//*=============================================================================
// 静的メンバ変数
//*=============================================================================
int CEnemy::m_nNumAll = 0;

//==============================================================================
// コンストラクタ
//==============================================================================
CEnemy::CEnemy()
{
	// 値をクリア
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.mtxWorld);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	m_Info.nIdxID = -1;
	m_nDamegeCounter = 0;
	m_pCurrent = nullptr;
	m_bDeath = false;
}

//==============================================================================
// コンストラクタ
//==============================================================================
CEnemy::CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	// 値をクリア
	m_Info.pos = pos;
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = rot;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Info.mtxWorld);
	m_Info.state = STATE_NONE;
	m_Info.nLife = nlife;
	m_Info.nIdxID = -1;
	m_nDamegeCounter = 0;
	m_bDeath = false;
}

//==============================================================================
// デストラクタ
//==============================================================================
CEnemy::~CEnemy()
{

}

//==============================================================================
// 生成処理
//==============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nlife)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy(pos, rot, nlife);

		pEnemy->Init();
	}

	return pEnemy;
}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CEnemy::Init(void)
{
	if (m_pMotion == nullptr)
	{// 使用されていなかったら

		// 生成
		m_pMotion = new CMotion;

		// 初期化処理
		m_pMotion->Init();
	}

	m_nDamegeCounter = DAMEGECOUNT;

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CEnemy::Uninit(void)
{
	m_bDeath = true;

	//サウンドの情報を取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンドストップ
	//pSound->Stop();

	if (m_pMotion != nullptr)
	{
		//終了処理
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	CObject::Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CEnemy::Update(void)
{
	Controll();

	if (m_pMotion != NULL)
	{
		// 更新処理
		m_pMotion->Update();
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CEnemy::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);
	
	if (m_pCurrent != nullptr)
	{
		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, 46.0f, m_Info.pos.z);

		D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

		// マトリックスと親のマトリックスをかけ合わせる
		D3DXMatrixMultiply(&m_Info.mtxWorld,
			&m_Info.mtxWorld, m_pCurrent);
	}
	else
	{
		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

		D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_apModel[nCount] != nullptr)
		{
			//描画処理
			m_apModel[nCount]->Draw();
		}
	}
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemy::Controll(void)
{
	Move();

	if (m_Info.state == STATE_DAMEGE)
	{
		m_nDamegeCounter--;

		if (m_nDamegeCounter <= 0)
		{
			m_Info.state = STATE_NONE;
			m_nDamegeCounter = DAMEGECOUNT;
		}
	}

	if (m_Info.nLife <= 0)
	{
		CGame::GetEnemyManager()->Release(m_Info.nIdxID);
		int nNum = CGame::GetEnemyManager()->GetNum() - 1;
		CGame::GetEnemyManager()->SetNum(nNum);
		return;
	}

	if (m_Info.state != STATE_GRAP)
	{
		m_Info.move.y -= 0.9f;
	}

	// 移動量
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.y += m_Info.move.y;
	m_Info.pos.z += m_Info.move.z;

	if (m_Info.pos.y <= 0.0f)
	{
		m_Info.pos.y = 0.0f;
	}

	//デバッグプロックの情報を取得
	CDebugProc *pDebugProc = CManager::Getinstance()->GetDebugProc();
	pDebugProc->Print("\n敵の位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	pDebugProc->Print("敵の向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
	pDebugProc->Print("敵の向き：%d\n", m_Info.nLife);
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemy::Attack(void)
{
	/*if (m_Info.state != STATE_ATTACK)
	{
		m_Info.state = STATE_ATTACK;
		m_pMotion->Set(TYPE_ATTACK);
	}*/
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemy::Move(void)
{
	////プレイヤーの情報取得
	//CPlayer *pPlayer = CGame::GetPlayer();

	//if (CGame::GetCollision()->Circle(&m_Info.pos, &pPlayer->GetPosition(), 400.0f, 50.0f) == true)
	//{//円の中にプレイヤーが入った

	//	D3DXVECTOR3 fDest, PlayerPos = pPlayer->GetPosition();

	//	float fDiffmove, fDestmove;

	//	fDest = m_Info.pos - PlayerPos;

	//	fDestmove = atan2f(fDest.x, fDest.z);
	//	fDiffmove = fDestmove - m_Info.rot.y;

	//	//角度の値を修正する--------------------------------------------------
	//	if (fDiffmove >= D3DX_PI)
	//	{
	//		fDiffmove = -D3DX_PI;
	//	}
	//	else if (fDiffmove <= -D3DX_PI)
	//	{
	//		fDiffmove = D3DX_PI;
	//	}

	//	m_Info.rot.y += fDiffmove * 0.05f;

	//	//角度の値を修正する--------------------------------------------------
	//	if (m_Info.rot.y > D3DX_PI)
	//	{
	//		m_Info.rot.y = -D3DX_PI;
	//	}
	//	else if (m_Info.rot.y < -D3DX_PI)
	//	{
	//		m_Info.rot.y = D3DX_PI;
	//	}

	//	//移動量を更新(減衰させる)
	//	m_Info.move.x = sinf(m_Info.rot.y + D3DX_PI) * ENEMYMOVE;
	//	m_Info.move.z = cosf(m_Info.rot.y + D3DX_PI) * ENEMYMOVE;

	//	if (fDest.x <= 60.0f && fDest.x >= -60.0f && fDest.z <= 60.0f && fDest.z >= -60.0f)
	//	{
	//		Attack();
	//		m_Info.move.x = 0.0f;
	//		m_Info.move.z = 0.0f;

	//		
	//	}
	//	else
	//	{
	//		if (m_Info.state != STATE_DASH)
	//		{
	//			m_Info.state = STATE_DASH;
	//			m_pMotion->Set(TYPE_DASH);
	//		}
	//	}

	//	m_Info.pos.x += m_Info.move.x * 0.5f;
	//	m_Info.pos.z += m_Info.move.z * 0.5f;
	//}
	//else
	//{
	//	m_Info.move.x = 0.0f;
	//	m_Info.move.z = 0.0f;

	//	if (m_Info.state != STATE_NEUTRAL)
	//	{
	//		m_Info.state = STATE_NEUTRAL;
	//		m_pMotion->Set(TYPE_NEUTRAL);
	//	}
	//}
}

//==============================================================================
// 制御処理
//==============================================================================
void CEnemy::Damege(int damege, float blowaway)
{
	m_Info.nLife -= damege;
	m_Info.move = D3DXVECTOR3(sinf(CGame::GetPlayer()->GetRotition().y) * -blowaway, blowaway, cosf(CGame::GetPlayer()->GetRotition().y) * -blowaway);

	if (m_Info.state != STATE_DAMEGE)
	{
		m_Info.state = STATE_DAMEGE;
		m_pMotion->Set(TYPE_DAMEGE);
	}
}

//==============================================================================
// テキストファイル読み込み
//==============================================================================
void CEnemy::ReadText(char *fliename)
{
	char aString[128] = {};
	char aComment[128] = {};
	int nCntParts = 0, nCntParts2 = 0, nCntParts3 = 0;
	int nCntMotion = 0;
	int nCntKeySet = 0;
	int nCntKey = 0;
	int nCntModel = 0;
	int nCntMotionIdx = 0;

	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(fliename, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_MODEL", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%d", &m_nNumModel);  //モデルの総数

					m_apModel = new CCharacter*[m_nNumModel];

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //モデルの名前

					m_apModel[nCntModel] = CCharacter::Create(m_filename);
					nCntModel++;

					nCntParts++;

				}  //MODEL_LILENAMEのかっこ

				if (strcmp("CHARACTERSET", aString) == 0)
				{
					while (strcmp("END_CHARACTERSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("PARTSSET", aString) == 0)
						{
							while (strcmp("END_PARTSSET", aString) != 0)
							{
								fscanf(pFile, "%s", &aString);

								if (strcmp("INDEX", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nIdx);  //モデルの番号
								}

								if (strcmp("PARENT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);          //=
									fscanf(pFile, "%d", &m_nParent);  //親モデルの番号

									if (m_nParent > -1 && m_nNumModel > m_nParent)
									{
										m_apModel[nCntParts2]->SetParent(m_apModel[m_nParent]);
									}
									else
									{
										m_apModel[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.z);  //モデルの総数

									m_apModel[nCntParts2]->SetPositionOri(m_Readpos);

									m_apModel[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.z);  //モデルの総数

									m_apModel[nCntParts2]->SetRotOrigin(m_Readrot);

									m_apModel[nCntParts2]->SetRot(m_Readrot);
								}

							}//END_PARTSSETのかっこ

							nCntParts2++;

						}//PARTSSETのかっこ

					}//END_CHARACTERSETのかっこ 

				}//CHARACTERSETのかっこ 
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}

	if (m_pMotion != nullptr)
	{
		//モデルの設定
		m_pMotion->SetModel(&m_apModel[0], m_nNumModel);

		//初期化処理
		m_pMotion->ReadText(fliename);

		m_pMotion->Set(TYPE_NEUTRAL);
	}
}

void CEnemy::SetChase(CHASE cha)
{
}
