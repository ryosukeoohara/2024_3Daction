//=============================================================================
//
// ポリゴン処理 [billboard.cpp]
// Author : 大原　怜将
//
//=============================================================================
#include "main.h"
#include "billboard.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "object2D.h"

//================================================================
//コンストラクタ
//================================================================
CBillBoard::CBillBoard()
{
	//値をクリア
	m_pTexture = NULL;  //テクスチャへのポインタ
	m_pVtxBuff = NULL;  //頂点情報を格納
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nIdxTexture = -1;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_bDraw = true;
}

//================================================================
//デストラクタ
//================================================================
CBillBoard::~CBillBoard()
{

}

//================================================================
//生成処理
//================================================================
CBillBoard *CBillBoard::Create(void)
{
	//オブジェクト2Dのポインタ
	CBillBoard *pBillBoard = NULL;

	if (pBillBoard == NULL)
	{
		//オブジェクト2Dの生成
		pBillBoard = new CBillBoard();

		//初期化処理
		pBillBoard->Init();
	}

	return pBillBoard;
}

//================================================================
//壁の初期化処理
//===============================================================
HRESULT CBillBoard::Init(void)
{
	//初期化処理
	CObject3D::Init();

	CObject3D::SetSize(500.0f, 500.0f);

	return S_OK;
}

//================================================================
//壁の終了処理
//================================================================
void CBillBoard::Uninit(void)
{
	//終了処理
	CObject3D::Uninit();
}

//================================================================
//壁の壁の更新処理
//================================================================
void CBillBoard::Update(void)
{
	//更新処理
	CObject3D::Update();
}

//================================================================
//壁の描画処理
//================================================================
void CBillBoard::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);

	D3DXMATRIX m_mtxTrans;           // 計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &m_mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &m_mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類
		0,                      //描画する最初の頂点インデックス
		2                       //描画するプリミティブ数
	);

	//zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 160);
}