//===========================================================
//
// アイテム処理[item.cpp]
// Author 大原怜将
//
//===========================================================
#include "renderer.h"
#include "manager.h"
#include "item.h"
#include "objectX.h"
#include "debugproc.h"

// マクロ定義
#define TEXT_NAME  ("data\\TEXT\\item.txt")  // マップに配置するアイテム

//================================================================
// コンストラクタ
//================================================================
CItem::CItem()
{
	m_appObjectX = nullptr;
	m_apModelName = nullptr;
	m_nNumModel = 0;
	m_nNumItem = 0;
}

//================================================================
// コンストラクタ(オーバーロード)
//================================================================
CItem::CItem(D3DXVECTOR3 pos, TYPE m_Type, const char *aModelFliename)
{
	
}

//================================================================
// デストラクタ
//================================================================
CItem::~CItem()
{

}

//================================================================
// 生成処理
//================================================================
CItem *CItem::Create(void)
{
	//オブジェクト2Dのポインタ
	CItem *pItem = NULL;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pItem == NULL)
		{
			//オブジェクト2Dの生成
			pItem = new CItem();

			//初期化処理
			pItem->Init();
		}
	}

	return pItem;
}

//================================================================
// 生成処理
//================================================================
void CItem::TextLoad(void)
{
	char aString[128] = {};    // 文字読み取り用
	char aComment[128] = {};   // テキストファイル内のコメント読み取り用
	char aFileName[128] = {};  // ファイルの名前読み取り用
	int nCntItem = 0;
	int nCntFileName = 0;
	int nType = -1;
	D3DXVECTOR3 pos, rot;      // 読み取り用

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(TEXT_NAME, "r");

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
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumModel);  //モデルの総数

					m_apModelName = new char*[m_nNumModel];

				}  // NUM_MODELのかっこ

				if (strcmp("NUM_ITEM", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumItem);  //モデルの総数

					m_appObjectX = new CObjectX*[m_nNumItem];

				}  // NUM_ITEMのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);       //=
					fscanf(pFile, "%s", &aFileName[0]);  //モデルの名前

					m_apModelName[nCntFileName] = aFileName;

					nCntFileName++;

				}  // MODEL_LILENAMEのかっこ

				if (strcmp("ITEMSET", aString) == 0)
				{
					while (strcmp("END_ITEMSET", aString) != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strcmp("TYPE", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%d", &nType);  //モデルの総数
						}

						if (strcmp("POS", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &pos.x);  //モデルの総数
							fscanf(pFile, "%f", &pos.y);  //モデルの総数
							fscanf(pFile, "%f", &pos.z);  //モデルの総数
						}

						if (strcmp("ROT", aString) == 0)
						{
							fscanf(pFile, "%s", &aString);      //=
							fscanf(pFile, "%f", &rot.x);  //モデルの総数
							fscanf(pFile, "%f", &rot.y);  //モデルの総数
							fscanf(pFile, "%f", &rot.z);  //モデルの総数
						}
					}

					m_appObjectX[nCntItem] = CObjectX::Create(m_apModelName[nType]);
					m_appObjectX[nCntItem]->SetPosition(pos);
					m_appObjectX[nCntItem]->SetRotition(rot);
				}
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

//================================================================
// 初期化処理
//================================================================
HRESULT CItem::Init(void)
{
	TextLoad();

	return S_OK;
}

//================================================================
// 終了処理
//================================================================
void CItem::Uninit(void)
{
	if (m_appObjectX != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			m_appObjectX[nCount]->Uninit();
			delete m_appObjectX[nCount];
			m_appObjectX[nCount] = nullptr;
		}

		delete m_appObjectX;
		m_appObjectX = nullptr;
	}
}

//================================================================
// 更新処理
//================================================================
void CItem::Update(void)
{
	
}