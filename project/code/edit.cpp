//===========================================================
//
// エディットモード[edit.h]
// Author 大原怜将
//
//===========================================================
#include "edit.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "audience.h"

//マクロ定義
#define MODEL_SET_TEXT  ("data\\TEXT\\model_set.txt")
#define SET_AUDIENCE ("data\\TEXT\\set_audience.txt")
#define MOVE   (1.0f)  //移動量

//===========================================================
// 
//===========================================================
CEdit::CEdit()
{
	// 値をクリア
	for (int i = 0; i < MAX_MODELSET; i++)
	{
		m_apModel[i] = nullptr;
	}

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_move = {0.0f, 0.0f, 0.0f};
	m_nIdx = 0;
}

//===========================================================
// 
//===========================================================
CEdit::~CEdit()
{

}

//===========================================================
// 
//===========================================================
HRESULT CEdit::Init(void)
{
	TEXTLoad();

	return S_OK;
}

//===========================================================
// 
//===========================================================
void CEdit::Uninit(void)
{

}

//===========================================================
// 
//===========================================================
void CEdit::Update(void)
{
	Control();

	//キーボードの情報を取得
	CInputKeyboard* InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	if (InputKeyboard == nullptr)
		return;

	if (InputKeyboard->GetTrigger(DIK_F6) == true)
	{//2キーが押された

		Save();
	}
}

//===========================================================
// 
//===========================================================
void CEdit::Draw(void)
{
	for (int i = 0; i < MAX_MODELSET; i++)
	{
		if (m_apModel[i] != nullptr)
		{
			if (m_nIdx != i)
			{
				m_apModel[i]->SetbDraw(false);
			}
		}
	}
}

//===========================================================
// 
//===========================================================
void CEdit::Save(void)
{
	CAudience* pAudience = CAudience::GetTop();
	
	FILE* pFile;

	pFile = fopen(SET_AUDIENCE, "w");

	if (pFile != NULL)
	{//ファイルを開けた場合

		fprintf(pFile, "SCRIPT\n");

		while (pAudience != nullptr)
		{
			CAudience* pAudienceNext = pAudience->GetNext();

			fprintf(pFile, "\n");

			D3DXVECTOR3 pos = pAudience->GetPosition();  // 位置取得
			D3DXVECTOR3 rot = pAudience->GetRotition();  // 向き取得

			fprintf(pFile, "MODELSET\n");
			fprintf(pFile, "    POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);     // 位置
			fprintf(pFile, "    ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);     // 向き
			fprintf(pFile, "END_MODELSET\n");
			fprintf(pFile, "\n");
			
			pAudience = pAudienceNext;
		}
	}

	fprintf(pFile, "END_SCRIPT\n");

	//ファイルを閉じる
	fclose(pFile);
}

//===========================================================
// 設置できるモデルの読み込み
//===========================================================
void CEdit::TEXTLoad(void)
{
	char aString[128] = {};
	char aFileName[128] = {};
	int nCntModel = 0;

	FILE* pFile;   //ファイルポインタを宣言

	pFile = fopen(MODEL_SET_TEXT, "r");

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
					fscanf(pFile, "%d", &m_nNumAll);  //モデルの総数

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &aFileName[0]);  //モデルの名前

					m_apModel[nCntModel] = CObjectX::Create(&aFileName[0]);
					m_apModel[nCntModel]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					nCntModel++;

				}  //MODEL_LILENAMEのかっこ
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===========================================================
// 制御処理
//===========================================================
void CEdit::Control(void)
{
	//キーボードの情報を取得
	CInputKeyboard* InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//カメラ取得
	CCamera* pCamera = CManager::Getinstance()->GetCamera();

	//デバッグプロックの情報を取得
	CDebugProc* pDebugProc = CManager::Getinstance()->GetDebugProc();

	if (InputKeyboard == nullptr)
		return;

	if (pCamera == nullptr)
		return;

	//カメラの向き取得
	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	if (InputKeyboard->GetTrigger(DIK_1) == true)
	{//1キーが押された

		if (m_nIdx > -1)
		{//インデックス番号が-1より大きいとき

			m_nIdx -= 1;  //インデックス番号を一つ戻す
		}

		if (m_nIdx < 0)
		{//インデックス番号が0より小さいとき

			m_nIdx = m_nNumAll - 1;  //インデックス番号を総数-1にする
		}
	}

	if (InputKeyboard->GetTrigger(DIK_2) == true)
	{//2キーが押された

		if (m_nIdx < m_nNumAll)
		{//インデックス番号が総数より小さいとき

			m_nIdx += 1;  //インデックス番号を一つ進める
		}

		if (m_nIdx >= m_nNumAll)
		{//インデックス番号が総数以上になったとき

			m_nIdx = 0;  //インデックス番号を0にする
		}
	}

	if (InputKeyboard->GetTrigger(DIK_N) == true)
	{
		//CAudience::Create(m_apModel[m_nIdx]->GetPosition(), m_apModel[m_nIdx]->GetFileName());

		//総数をカウントアップ
		m_SetModel++;
	}

	//上に移動----------------------------------------------
	if (InputKeyboard->GetPress(DIK_W) == true)
	{//Wキーが押された

		if (InputKeyboard->GetPress(DIK_D) == true)
		{//Dキーも押した 右上に移動

			//移動量
			m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.75f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.75f)) * MOVE;
		}
		else if (InputKeyboard->GetPress(DIK_A) == true)
		{//Aキーも押した 左上に移動

			//移動量
			m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * MOVE;
		}
		else
		{//Wキーだけ押した	真上に移動

			//移動量
			m_move.x -= sinf(CameraRot.y) * MOVE;
			m_move.z -= cosf(CameraRot.y) * MOVE;
		}
	}
	else if (InputKeyboard->GetPress(DIK_S) == true)
	{//Sキーが押された

		//下に移動----------------------------------------------

		if (InputKeyboard->GetPress(DIK_D) == true)
		{//Dキーも押した 右下に移動

			//移動量
			m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * MOVE;
		}
		else if (InputKeyboard->GetPress(DIK_A) == true)
		{//Aキーも押した 左下に移動

			//移動量
			m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * MOVE;
			m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * MOVE;
		}
		else
		{//Sキーだけ押した 真下に移動

			//移動量
			m_move.x += sinf(CameraRot.y) * MOVE;
			m_move.z += cosf(CameraRot.y) * MOVE;
		}
	}
	else if (InputKeyboard->GetPress(DIK_D) == true)
	{//Dキーだけ押した

		//右に移動----------------------------------------------
		
		//移動量
		m_move.x += sinf(CameraRot.y + (-D3DX_PI * 0.5f)) * MOVE;
		m_move.z += cosf(CameraRot.y + (-D3DX_PI * 0.5f)) * MOVE;
	}
	else if (InputKeyboard->GetPress(DIK_A) == true)
	{//Aキーだけ押した

		//左に移動----------------------------------------------
		
		//移動量
		m_move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * MOVE;
		m_move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * MOVE;
	}

	if (InputKeyboard->GetPress(DIK_U) == true)
	{//Uキーを押した

		m_rot.y += 0.01f;
	}

	if (InputKeyboard->GetPress(DIK_I) == true)
	{//Iキーを押した

		m_rot.y -= 0.01f;
	}

	if (InputKeyboard->GetTrigger(DIK_O) == true)
	{//Oキーを押した

		m_rot.y = 0.0f;
	}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	// 移動量を更新(減衰させる)--------------------------------------------
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	// 移動量加算
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	// 位置を代入
	m_apModel[m_nIdx]->SetPosition(m_pos);
	m_apModel[m_nIdx]->SetRotition(m_rot);

	if (pDebugProc == nullptr)
		return;

	pDebugProc->Print("\n<< オブジェクトの位置：X軸<%f>,Y軸<%f>,Z軸<%f> >>", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("\n<< オブジェクトの向き：X軸<%f>,Y軸<%f>,Z軸<%f> >>", m_rot.x, m_rot.y, m_rot.z);
	pDebugProc->Print("\n<< 現在のオブジェクトの番号：%d/%d >>", m_nIdx, m_nNumAll);
	pDebugProc->Print("\n<< 設置したオブジェクトの数：%d >>", m_SetModel);
	pDebugProc->Print("\n<< 配置リセット：F7 >>");
	pDebugProc->Print("\n<< 外部ファイル書き出し：F8 >>");
	pDebugProc->Print("\n<< 外部ファイル読み込み：F9 >>");
	pDebugProc->Print("\n<< モデルの旋回 : U/I >>");
	pDebugProc->Print("\n<< モデルの向きリセット : O >>");
}