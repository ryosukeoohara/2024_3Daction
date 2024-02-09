//===========================================================
//
//ポリゴンを出すやつ[particl.cpp]
//Author 大原怜将
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "effect.h"
#include "effect3D.h"
#include "particle.h"

#include <time.h>

//マクロ定義
#define BLOOD    (1)     //血のパーティクル
#define GROUND   (20)    //土埃のパーティクル
#define CIRCLE   (314)   //円形のパーティクル
#define SPEED    (10.0f)  //移動量

//================================================================
//静的メンバ変数宣言
//================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;

//================================================================
//コンストラクタ
//================================================================
CParticle::CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 0;
	m_nLife = 0;
}

//================================================================
//コンストラクタ
//================================================================
CParticle::CParticle(D3DXVECTOR3 pos, TYPEPAR type)
{
	m_pos = pos;
	m_fRadius = 0;
	m_nLife = 0;
	m_type = type;
}

//================================================================
//デストラクタ
//================================================================
CParticle::~CParticle()
{

}

//================================================================
//生成処理
//================================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, TYPEPAR type)
{
	//オブジェクト2Dのポインタ
	CParticle *pParticl = NULL;

	if (pParticl == NULL)
	{
		//オブジェクト2Dの生成
		pParticl = new CParticle(pos, type);

		//初期化処理
		pParticl->Init();
	}
	
	return pParticl;
}

//================================================================
//ポリゴンの初期化処理
//================================================================
HRESULT CParticle::Init(void)
{
	return S_OK;
}

//================================================================
//ポリゴンの終了処理
//================================================================
void CParticle::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//================================================================
//ポリゴンの更新処理
//================================================================
void CParticle::Update(void)
{
	switch (m_type)
	{
	case TYPEPAR_GROUND:
		Ground();
		break;

	case TYPEPAR_BLOOD:
		Blood();
		break;

	case TYPEPAR_SMOOK:
		Smook();
		break;

	case TYPEPAR_CIRCLE:
		Circle();
		break;
	}

	m_nLife--;

	if (m_nLife <= 0)
	{
		//終了処理
		CParticle::Uninit();
	}
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CParticle::Draw(void)
{
	
}

//================================================================
//ポリゴンの描画処理
//================================================================
void CParticle::Move(void)
{
	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

		//CEffect::Create(pos, { m_move.x, m_move.y, m_move.z }, { 0.8f, 1.0f, 1.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_NONE);
	}
}

//================================================================
//血液のパーティクル
//================================================================
void CParticle::Blood(void)
{
	//乱数の種を設定
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < BLOOD; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

 		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\tier.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\basket.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\handle.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\pedal.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\tier.x");
	}
}

//================================================================
//土埃みたいなパーティクル
//================================================================
void CParticle::Ground(void)
{
	float fRot = 0.0f;

	for (int nCnt = 0; nCnt < GROUND; nCnt++)
	{
		// 向き設定
		fRot = ((float)nCnt / (D3DX_PI * 1.0f));

		// 移動量設定
		m_move.x = sinf(fRot) * SPEED;
		m_move.z = cosf(fRot) * SPEED;

		CEffect::Create({ m_pos.x, 0.0f, m_pos.z }, { m_move.x, 0.0f, m_move.z }, { 1.0f, 1.0f, 1.0f, 0.8f }, 50.0f, 30, CEffect::TYPE_GROUND);
	}
}

//================================================================
//煙みたいなパーティクル
//================================================================
void CParticle::Smook(void)
{
	
}

//================================================================
//円形のパーティクル
//================================================================
void CParticle::Circle(void)
{
	
}