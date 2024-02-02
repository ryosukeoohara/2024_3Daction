//=============================================================================
//
// 敵の管理 [enemymanager.cpp]
// Author : 大原　怜将
//
//=============================================================================

//*============================================================================
// インクルードファイル
//*============================================================================
#include "enemymanager.h"
#include "enemy.h"
#include "enemy_weak.h"

//*============================================================================
// 静的メンバ変数
//*============================================================================
CEnemy *CEnemyManager::m_pTop = nullptr;
CEnemy *CEnemyManager::m_pCur = nullptr;
CEnemy *CEnemyManager::m_pSNext = nullptr;

//*============================================================================
// マクロ定義
//*============================================================================
#define ENEMY_TEXT   ("data\\TEXT\\enemyinformation.txt")    //敵の最大数

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyManager::CEnemyManager()
{
	//初期化
	m_appEnemy = nullptr;
	m_nEnemyAll = 0;
	m_Readpos = { 0.0f,0.0f,0.0f };
	m_Readrot = { 0.0f,0.0f,0.0f };
}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemyManager::~CEnemyManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CEnemyManager::Uninit(void)
{
	if (m_appEnemy != nullptr)
	{
		for (int nCount = 0; nCount < m_nEnemyAll; nCount++)
		{
			if (m_appEnemy[nCount] != nullptr)
			{// 使用されていたら

				// 終了処理
				m_appEnemy[nCount]->Uninit();
				m_appEnemy[nCount] = nullptr;
			}
		}

		delete m_appEnemy;
		m_appEnemy = nullptr;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CEnemyManager::Update(void)
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemyManager * CEnemyManager::Create(void)
{
	CEnemyManager *pEnemyManager = nullptr;

	if (pEnemyManager == nullptr)
	{
		pEnemyManager = new CEnemyManager();

		pEnemyManager->Init();

		pEnemyManager->ReadText();
	}

	return pEnemyManager;
}

//=============================================================================
// 消す
//=============================================================================
void CEnemyManager::Release(int idx)
{
	if (m_appEnemy[idx] != nullptr)
	{
		if (m_appEnemy[idx]->GetLife() <= 0)
		{
			// 終了処理
			m_appEnemy[idx]->Uninit();
			m_appEnemy[idx] = nullptr;
		}
	}
}

//=============================================================================
//テキストファイル読み込み
//=============================================================================
void CEnemyManager::ReadText(void)
{
	int nLife = 0;
	int nCntEnemy = 0;
	char aString[128] = {};

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(ENEMY_TEXT, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp("ALL_ENEMY", aString) == 0)
			{
				fscanf(pFile, "%s", &aString);          //=
				fscanf(pFile, "%d", &m_nEnemyAll);  //モデルの総数

				m_appEnemy = new CEnemy*[m_nEnemyAll];

			}  //NUM_MODELのかっこ

			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("ENEMYSET", aString) == 0)
				{
					while (strcmp("ENEMYSET_END", aString) != 0)
					{
						fscanf(pFile, "%s", &aString);

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &m_Readpos.x);  //敵の位置
							fscanf(pFile, "%f", &m_Readpos.y);  //敵の位置
							fscanf(pFile, "%f", &m_Readpos.z);  //敵の位置
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &m_Readrot.x);  //敵の向き
							fscanf(pFile, "%f", &m_Readrot.y);  //敵の向き
							fscanf(pFile, "%f", &m_Readrot.z);  //敵の向き
						}

						if (strcmp("LIFE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);       //=
							fscanf(pFile, "%d", &nLife);       //敵の体力
						}

					}//ENEMYSET_ENDのかっこ 

					m_appEnemy[nCntEnemy] = nullptr;

					if (m_appEnemy[nCntEnemy] == nullptr)
					{
						m_appEnemy[nCntEnemy] = CEnemyWeak::Create(m_Readpos, m_Readrot, nLife);
						m_appEnemy[nCntEnemy]->SetIdx(nCntEnemy);
						m_appEnemy[nCntEnemy]->SetType(CEnemy::TYPE_WEAK);

						nCntEnemy++;
					}

				}//ENEMYSETのかっこ 
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		return;
	}
}

//=============================================================================
// コンストラクタ
//=============================================================================
void CEnemyManager::ListOut(void)
{
	
}
