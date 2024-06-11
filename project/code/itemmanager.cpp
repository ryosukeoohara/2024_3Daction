//=============================================================================
//
// 敵の管理 [itemmanager.cpp]
// Author : 大原　怜将
//
//=============================================================================

//*============================================================================
// インクルードファイル
//*============================================================================
#include "itemmanager.h"
#include "item.h"

//*============================================================================
// 静的メンバ変数
//*============================================================================

//*============================================================================
// マクロ定義
//*============================================================================
#define ITEM_TEXT ("data\\TEXT\\item.txt")

const char *CItemManager::m_apTexName[CItem::TYPE_MAX] =
{
	"data\\MODEL\\refrigerator.x",  // 冷蔵庫
	"data\\MODEL\\bike.x",          // 自転車
	"data\\MODEL\\microwave.x",     // 電子レンジ
	"data\\MODEL\\table.x",         // デーブル
	"data\\MODEL\\poster.x",        // 看板
};

//=============================================================================
// コンストラクタ
//=============================================================================
CItemManager::CItemManager()
{
	//初期化
	m_ppItem = nullptr;
	m_nNum = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CItemManager::~CItemManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CItemManager::Init(void)
{
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CItemManager::Uninit(void)
{
	//if (m_ppItem != nullptr)
	//{
	//	for (int nCount = 0; nCount < m_nNumItem; nCount++)
	//	{
	//		if (m_ppItem[nCount] != nullptr)
	//		{// 使用されていたら

	//			// 終了処理
	//			m_ppItem[nCount]->Uninit();
	//			m_ppItem[nCount] = nullptr;
	//		}
	//	}

	//	delete m_ppItem;
	//	m_ppItem = nullptr;
	//}
}

//=============================================================================
//更新処理
//=============================================================================
void CItemManager::Update(void)
{
	
}

//=============================================================================
// 生成処理
//=============================================================================
CItemManager * CItemManager::Create(const char* filename)
{
	CItemManager *pItemManager = nullptr;

	if (pItemManager == nullptr)
	{
		pItemManager = new CItemManager();

		pItemManager->Init();

		pItemManager->ReadText(filename);
	}

	return pItemManager;
}

//=============================================================================
// 消す
//=============================================================================
void CItemManager::Release(int idx)
{
	CItem *pItem = CItem::GetTop();

	while (pItem != nullptr)
	{
		CItem *pItemNext = pItem->GetNext();

		if (pItem->GetID() == idx)
		{
			pItem->Uninit();
		}

		pItem = pItemNext;
	}
}

//=============================================================================
//テキストファイル読み込み
//=============================================================================
void CItemManager::ReadText(const char *text)
{
	char aString[128] = {};    // 文字読み取り用
	char aFileName[128] = {};  // ファイルの名前読み取り用
	int nCntItem = 0;
	int nType = -1;
	D3DXVECTOR3 pos = {}, rot = {};      // 読み取り用

	FILE *pFile;   //ファイルポインタを宣言

	pFile = fopen(text, "r");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fscanf(pFile, "%s", &aString[0]);

		if (strcmp("SCRIPT", aString) == 0)
		{
			while (strcmp("END_SCRIPT", aString) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strcmp("NUM_ITEM", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);      //=
					fscanf(pFile, "%d", &m_nNumItem);  //モデルの総数

					//m_ppItem = new CItem*[m_nNumItem];

				}  // NUM_ITEMのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);       //=
					fscanf(pFile, "%s", &aFileName[0]);  //モデルの名前

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

					CItem::Create(pos, rot, (CItem::TYPE)nType, m_nNum, m_apTexName[nType]);
					//m_ppItem[nCntItem]->SetID(nCntItem);
					m_nNum++;
					nCntItem++;
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

//=============================================================================
// コンストラクタ
//=============================================================================
void CItemManager::ListOut(void)
{

}