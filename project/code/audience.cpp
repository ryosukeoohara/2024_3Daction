//===========================================================
//
// マップのモデル[map.cpp]
// Author 大原怜将
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "audience.h"
#include "objectX.h"
#include "debugproc.h"
#include "object.h"

//const char *CAudience::m_apTexName[MAX_ITEM] =
//{
//	"data\\MODEL\\refrigerator.x",
//	"data\\MODEL\\bike.x",     // 自転車
//};

// マクロ定義
#define TEXT_NAME  ("data\\TEXT\\audience.txt")  // マップ

namespace
{
	const char *MODELNAME[CAudience::TYPE_MAX] =
	{
		"data\\MODEL\\",
		"data\\MODEL\\crowd_02.x",
		"data\\MODEL\\crowd_03.x",
		"data\\MODEL\\crowd_04.x",
	};
}

//================================================================
// コンストラクタ
//================================================================
CAudience::CAudience()
{
	m_appObjectX = nullptr;
	m_nNumModel = 0;
	m_nNumItem = 0;
}

//================================================================
// コンストラクタ(オーバーロード)
//================================================================
//CAudience::CAudience(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename)
//{
//
//}

//================================================================
// デストラクタ
//================================================================
CAudience::~CAudience()
{

}

//================================================================
// 生成処理
//================================================================
CAudience *CAudience::Create(void)
{
	//オブジェクト2Dのポインタ
	CAudience *pMap = nullptr;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pMap == nullptr)
		{
			//オブジェクト2Dの生成
			pMap = new CAudience();

			//初期化処理
			pMap->Init();
		}
	}

	return pMap;
}

//================================================================
// 生成処理
//================================================================
void CAudience::TextLoad(void)
{
	//char aString[128] = {};    // 文字読み取り用
	//char aComment[128] = {};   // テキストファイル内のコメント読み取り用
	//char aFileName[128] = {};  // ファイルの名前読み取り用
	//int nCntItem = 0;
	//int nCntFileName = 0;
	//int nType = -1;
	//D3DXVECTOR3 pos, rot;      // 読み取り用

	//FILE *pFile;   //ファイルポインタを宣言

	//pFile = fopen(TEXT_NAME, "r");

	//if (pFile != NULL)
	//{//ファイルを開けた場合

	//	fscanf(pFile, "%s", &aString[0]);

	//	if (strcmp("SCRIPT", aString) == 0)
	//	{
	//		while (strcmp("END_SCRIPT", aString) != 0)
	//		{
	//			fscanf(pFile, "%s", &aString[0]);

	//			if (strcmp("NUM_ITEM", aString) == 0)
	//			{
	//				fscanf(pFile, "%s", &aString);      //=
	//				fscanf(pFile, "%d", &m_nNumItem);  //モデルの総数

	//			}  // NUM_ITEMのかっこ

	//			if (strcmp("MODEL_FILENAME", aString) == 0)
	//			{
	//				fscanf(pFile, "%s", &aString);       //=
	//				fscanf(pFile, "%s", &aFileName[0]);  //モデルの名前

	//				strcpy(m_aTex[nCntFileName].aName, aFileName);
	//				nCntFileName++;

	//				m_appObjectX = new CObjectX*[MAX_MODEL];

	//			}  // MODEL_LILENAMEのかっこ

	//			if (strcmp("MODELSET", aString) == 0)
	//			{
	//				while (strcmp("END_MODELSET", aString) != 0)
	//				{
	//					fscanf(pFile, "%s", &aString[0]);

	//					if (strcmp("TYPE", aString) == 0)
	//					{
	//						fscanf(pFile, "%s", &aString);      //=
	//						fscanf(pFile, "%d", &nType);  //モデルの総数
	//					}

	//					if (strcmp("POS", aString) == 0)
	//					{
	//						fscanf(pFile, "%s", &aString);      //=
	//						fscanf(pFile, "%f", &pos.x);  //モデルの総数
	//						fscanf(pFile, "%f", &pos.y);  //モデルの総数
	//						fscanf(pFile, "%f", &pos.z);  //モデルの総数
	//					}

	//					if (strcmp("ROT", aString) == 0)
	//					{
	//						fscanf(pFile, "%s", &aString);      //=
	//						fscanf(pFile, "%f", &rot.x);  //モデルの総数
	//						fscanf(pFile, "%f", &rot.y);  //モデルの総数
	//						fscanf(pFile, "%f", &rot.z);  //モデルの総数
	//					}
	//				}

	//				m_appObjectX[nCntItem] = CObjectX::Create(m_aTex[nType].aName);
	//				m_appObjectX[nCntItem]->SetPosition(pos);
	//				m_appObjectX[nCntItem]->SetRotition(rot);

	//				nCntItem++;

	//				m_nNumModel++;
	//			}
	//		}
	//	}

	//	//ファイルを閉じる
	//	fclose(pFile);
	//}
	//else
	//{
	//	return;
	//}
}

//================================================================
// 初期化処理
//================================================================
HRESULT CAudience::Init(void)
{
	TextLoad();

	m_appObjectX = new CObjectX*[10];

	int a = 0;

	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int n = 0; n < 10; n++)
	{
		a = rand() % TYPE_MAX;  //攻撃の種類抽選

		if (a == 0)
		{
			a += 1;
		}

		m_appObjectX[n] = nullptr;
		m_appObjectX[n] = CObjectX::Create(MODELNAME[a]);
		m_appObjectX[n]->SetPosition(D3DXVECTOR3(0.0f + n * 50.0f, 0.0f, -800.0f));
		m_appObjectX[n]->SetRotition(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}

	return S_OK;
}

//================================================================
// 終了処理
//================================================================
void CAudience::Uninit(void)
{
	/*if (m_appObjectX != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_appObjectX[nCount]->Uninit();
			delete m_appObjectX[nCount];
			m_appObjectX[nCount] = nullptr;
		}

		delete m_appObjectX;
		m_appObjectX = nullptr;
	}*/
}

//================================================================
// 更新処理
//================================================================
void CAudience::Update(void)
{

}