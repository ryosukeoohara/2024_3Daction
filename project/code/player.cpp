//===========================================================
//
// プレイヤー処理[player.cpp]
// Author 大原怜将
//
//===========================================================
#include "main.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include "game.h"
#include "fade.h"
#include "character.h"
#include "collision.h"
#include "enemy.h"
#include "camera.h"
#include "object.h"
#include "gage.h"
#include "billboard.h"
#include "enemymanager.h"
#include "utility.h"
#include "item.h"
#include "itemmanager.h"

#include<stdio.h>
#include<time.h>
#include<string.h>

//================================================================
// マクロ定義
//================================================================
#define MAX_LIFECHIBI (10)                                        // チビの体力
#define MAX_LIFEFOOT  (6)                                         // デブの体力
#define REST_BULLET   (30)                                        // 保持できる弾の数
#define BULLETWAIT    (15)                                        // 射撃の間隔
#define MUTEKITIME    (30)                                        // 無敵時間
#define PLAYER_X      (40.0f)                                     // プレイヤーのX軸の幅
#define PLAYER_Z      (10.0f)                                     // プレイヤーのZ軸の幅
#define GRAPSPEED     (0.7f)                                      // 掴み状態の移動の速さ
#define SPEED         (1.0f)                                      // 移動の速さ
#define MOVE          (4.0f)
#define FRIST         (21)                                        // 攻撃判定発生開始
#define FINISH        (31)                                        // 攻撃判定終了
#define LOSTSTMINA    (10)                                        // ダッシュのスタミナ消費量
#define HAND          (9)                                         // 右手の番号
#define PLAYER01_TEXT ("data\\TEXT\\motion_neet2.txt")       // プレイヤーのテキストファイル
#define PLAYER02_TEXT ("data\\TEXT\\motion_set_player2.txt")      // プレイヤーのテキストファイル

// 無名名前空間を定義
namespace
{
	const D3DXVECTOR3 CAMERAROT[CPlayer::HEAT_MAX] = 
	{ 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 2.35f, D3DX_PI * -0.38f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, D3DX_PI * -0.38f),

	};  // サイズ
}

//================================================================
// 静的メンバ変数宣言
//================================================================
//MODEL *CPlayer::m_Player = NULL;

//================================================================
// コンストラクタ
//================================================================
CPlayer::CPlayer()
{
	// 初期化
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_Grap.pItem = nullptr;
	m_Grap.pEnemy = nullptr;

	m_HeatAct = HEAT_NONE;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pItem = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pBotton = nullptr;
	m_nIdxEne = 0;
	m_nDamageCounter = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;
	
	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
// コンストラクタ(オーバーロード)
//================================================================
CPlayer::CPlayer(D3DXVECTOR3 pos)
{
	// 初期化
	m_Info.pos = pos;
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Info.state = STATE_NONE;
	m_Info.nLife = 0;
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	m_HeatAct = HEAT_NONE;
	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pItem = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pBotton = nullptr;
	m_nIdxEne = 0;
	m_nDamageCounter = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_bDesh = false;
	m_bAttack = false;
	m_bAvoid = false;
	m_bLift = false;
	m_bGrap = false;

	m_bPushW = false;
	m_bPushA = false;
	m_bPushS = false;
	m_bPushD = false;
	m_bAttack = false;
	m_bAvoi = false;
	m_bWhee = false;
}

//================================================================
// デストラクタ
//================================================================
CPlayer::~CPlayer()
{

}

//================================================================
// 生成処理
//================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	//オブジェクト2Dのポインタ
	CPlayer *pPlayer = nullptr;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == nullptr)
		{
			//オブジェクト2Dの生成
			pPlayer = new CPlayer(pos);

			//初期化処理
			pPlayer->Init();
		}
	}

	return pPlayer;
}

//================================================================
// 生成処理
//================================================================
CPlayer * CPlayer::Create(void)
{
	//オブジェクト2Dのポインタ
	CPlayer *pPlayer = nullptr;

	if (CObject::GetNumAll() < MAX_OBJECT)
	{
		if (pPlayer == nullptr)
		{
			//オブジェクト2Dの生成
			pPlayer = new CPlayer();

			//初期化処理
			pPlayer->Init();
		}
	}

	return pPlayer;
}

//================================================================
// ダメージ
//================================================================
void CPlayer::Damage(int nDamage, float fKnockBack)
{
	if (m_Info.state != STATE_DAMEGE)
	{
		m_Info.state = STATE_DAMEGE;
		m_pMotion->Set(TYPE_AVOID);

		m_Info.nLife -= nDamage;
		m_Info.move = D3DXVECTOR3(sinf(CManager::Getinstance()->GetCamera()->GetRotation().y) * -fKnockBack, fKnockBack, cosf(CManager::Getinstance()->GetCamera()->GetRotation().y) * -fKnockBack);
	}
}

//================================================================
// タイトルで歩く
//================================================================
void CPlayer::TitleWalk(void)
{
	// パーツごとの更新
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	// モーションの更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	if (m_Info.state != STATE_MOVE)
	{
		m_Info.state = STATE_MOVE;
		m_pMotion->Set(TYPE_MOVE);
	}

	//位置に移動量加算----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//m_pos.y = fHeight + 18.0f;

	//移動量を更新(減衰させる)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	CManager::Getinstance()->GetDebugProc()->Print("\nプレイヤーの位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("プレイヤーの向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
}

//================================================================
// 初期化処理
//================================================================
HRESULT CPlayer::Init(void)
{
	//テクスチャの情報取得
	CTexture *pTexture = CManager::Getinstance()->GetTexture();

	//シーンの情報を取得
	CScene *pScene = CManager::Getinstance()->GetScene();

	//種類設定
	SetType(TYPE_PLAYER);

	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;

		//初期化処理
		m_pMotion->Init();

		m_pMotion->Set(TYPE_NEUTRAL);
	}

	m_fGrapRot = 1.0f;
	m_fStamina = 40.0f;
	m_Info.nLife = 200;

	ReadText(PLAYER01_TEXT);

	if (CManager::Getinstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		m_pLife = CGage2D::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 40.0f, (float)((m_Info.nLife * 0.01f) * 20), CGage2D::TYPE_LIFE);
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.01f) * 20));
		m_pStamina = CGage3D::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z), 5.0f, m_fStamina, CGage3D::TYPE_STAMINA);
		m_pStamina->SetPos(&m_Info.pos);
		m_pStamina->GetBill()->SetTex(m_fStamina);
	}
	
	return S_OK;
}

//================================================================
// 終了処理
//================================================================
void CPlayer::Uninit(void)
{
	//サウンドの情報を取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//サウンドストップ
	pSound->Stop();

	if (m_pMotion != nullptr)
	{
		//終了処理
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppCharacter != nullptr)
	{
		for (int nCount = 0; nCount < m_nNumModel; nCount++)
		{
			if (m_ppCharacter[nCount] != nullptr)
			{
				m_ppCharacter[nCount]->Uninit();
				m_ppCharacter[nCount] = nullptr;
			}
		}

		delete m_ppCharacter;
		m_ppCharacter = nullptr;
	}

	if (m_pStamina != nullptr)
	{
		m_pStamina->Uninit();
		m_pStamina = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		m_pLife = nullptr;
	}

	CObject::Release();
}

//================================================================
// 更新処理
//================================================================
void CPlayer::Update(void)
{
	//キーボードの情報を取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//フェードの情報を取得
	CFade *pFade = CManager::Getinstance()->GetFade();

	//シーンの情報を取得
	CScene *pScene = CManager::Getinstance()->GetScene();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	// 制御処理
	Control();

	// パーツごとの更新
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	// モーションの更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	// スタミナ
	if (m_fStamina < 40)
	{
		m_fStamina += 0.1f;

		if (m_pStamina != nullptr)
		{
			m_pStamina->GetBill()->SetTex(m_fStamina);
		}
	}

	// 体力
	if (m_pLife != nullptr)
	{
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)((m_Info.nLife * 0.1f) * 20));
	}

	if (m_Info.nLife <= 0)
	{
		//フェードの情報を取得
		CFade *pFade = CManager::Getinstance()->GetFade();

		if (pFade->Get() != pFade->FADE_OUT)
		{
			//シーンをゲームに遷移
			pFade->Set(CScene::MODE_RESULT);
		}
	}
}

//================================================================
// 描画処理
//================================================================
void CPlayer::Draw(void)
{
	CTexture *pTexture = CManager::Getinstance()->GetTexture();
	CRenderer *pRenderer = CManager::Getinstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);

	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Draw();
		}
	}
}

//================================================================
// 制御処理
//================================================================
void CPlayer::Control(void)
{
	if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
	{
		Move();     // 移動
	}

	int nNum = 0;
	CEnemy **ppEnemy = nullptr;

	if (CGame::GetEnemyManager() != nullptr)
	{
		ppEnemy = CGame::GetEnemyManager()->GetEnemy();
		nNum = CGame::GetEnemyManager()->GetNum();
	}

	for (int nCount = 0; nCount < nNum; nCount++)
	{
		if (ppEnemy[nCount] != nullptr)
		{
			m_Info.pos = *CGame::GetCollision()->CheckEnemy(&m_Info.pos, &m_Info.posOld, &ppEnemy[nCount]->GetPosition(), 20.0f);
		}
	}
	
	Action();   // アクション
	State();    // 状態

	{
		//			//キーボードを取得
		//CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

		//if (InputKeyboard->GetTrigger(DIK_T) == true)
		//{//Wキーが押された

		//	float x = m_Grap.pEnemy->GetRotition().x - 0.1f;
		//	m_Grap.pEnemy->SetRotition(D3DXVECTOR3(x, m_Grap.pEnemy->GetRotition().y, m_Grap.pEnemy->GetRotition().z));
		//}
		//if (InputKeyboard->GetTrigger(DIK_Y) == true)
		//{//Wキーが押された

		//	float x = m_Grap.pEnemy->GetRotition().x + 0.1f;
		//	m_Grap.pEnemy->SetRotition(D3DXVECTOR3(x, m_Grap.pEnemy->GetRotition().y, m_Grap.pEnemy->GetRotition().z));
		//}

		//if (InputKeyboard->GetTrigger(DIK_G) == true)
		//{//Wキーが押された

		//	float y = m_Grap.pEnemy->GetRotition().y - 0.1f;
		//	m_Grap.pEnemy->SetRotition(D3DXVECTOR3(m_Grap.pEnemy->GetRotition().x, y, m_Grap.pEnemy->GetRotition().z));
		//}
		//if (InputKeyboard->GetTrigger(DIK_H) == true)
		//{//Wキーが押された

		//	float y = m_Grap.pEnemy->GetRotition().y + 0.1f;
		//	m_Grap.pEnemy->SetRotition(D3DXVECTOR3(m_Grap.pEnemy->GetRotition().x, y, m_Grap.pEnemy->GetRotition().z));
		//}

		//if (InputKeyboard->GetTrigger(DIK_V) == true)
		//{//Wキーが押された

		//	float z = m_Grap.pEnemy->GetRotition().z - 0.1f;
		//	m_Grap.pEnemy->SetRotition(D3DXVECTOR3(m_Grap.pEnemy->GetRotition().x, m_Grap.pEnemy->GetRotition().y, z));
		//}
		//if (InputKeyboard->GetTrigger(DIK_B) == true)
		//{//Wキーが押された

		//	float z = m_Grap.pEnemy->GetRotition().z + 0.1f;
		//	m_Grap.pEnemy->SetRotition(D3DXVECTOR3(m_Grap.pEnemy->GetRotition().x, m_Grap.pEnemy->GetRotition().y, z));
		//}
	}
	
	CManager::Getinstance()->GetDebugProc()->Print("\nプレイヤーの位置：%f,%f,%f\n", m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	CManager::Getinstance()->GetDebugProc()->Print("プレイヤーの向き：%f,%f,%f\n", m_Info.rot.x, m_Info.rot.y, m_Info.rot.z);
}

//================================================================
// 移動処理
//================================================================
void CPlayer::Move(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//マウスの位置を取得
	D3DXVECTOR2 MousePos = pInputMouse->GetMouseMove();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//カメラ取得
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	m_bDesh = false;

	m_Info.posOld = m_Info.pos;
	
	float fSpeed = 0.0f;

	if (m_bGrap == true)
	{
		fSpeed = GRAPSPEED;
	}
	else
	{
		fSpeed = SPEED;
	}

	if (m_Info.state != STATE_GRAP && m_Info.state != STATE_AVOID && m_Info.state != STATE_ATTACK && m_Info.state != STATE_HEAT && m_Info.state != STATE_DAMEGE)
	{
		//上に移動----------------------------------------------
		if (InputKeyboard->GetPress(DIK_W) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
		{//Wキーが押された

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//Dキーも押した 右上に移動

			 // 移動量
				m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;

				//向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//Aキーも押した 左上に移動

			 // 移動量
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * fSpeed;

				//向き
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
			}
			else
			{//Wキーだけ押した	真上に移動

				// 移動量
				m_Info.move.x -= sinf(CameraRot.y) * fSpeed;
				m_Info.move.z -= cosf(CameraRot.y) * fSpeed;

				//向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
			}

			m_bDesh = true;
		}
		//下に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_S) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
		{//Sキーが押された

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//Dキーも押した 右下に移動

			 // 移動量
				m_Info.move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * fSpeed;

				// 向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//Aキーも押した 左下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * fSpeed;

				// 向き
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
			}
			else
			{//Sキーだけ押した 真下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y) * fSpeed;
				m_Info.move.z += cosf(CameraRot.y) * fSpeed;

				// 向き
				m_fDest = (CameraRot.y + (D3DX_PI));
			}

			m_bDesh = true;
		}
		//右に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーだけ押した

			// 移動量
			m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;

			m_bDesh = true;

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
		}
		//左に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーだけ押した

			// 移動量
			m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * fSpeed;

			m_bDesh = true;

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
		}

		m_fDiff = m_fDest - m_Info.rot.y;

		//角度の値を修正する
		if (m_fDiff >= D3DX_PI)
		{
			m_fDiff -= D3DX_PI * 2;
		}
		else if (m_fDiff <= -D3DX_PI)
		{
			m_fDiff += D3DX_PI * 2;
		}

		//移動方向(角度)の補正------------------------------------------------
		m_Info.rot.y += m_fDiff * 0.15f;

		//角度の値を修正する--------------------------------------------------
		if (m_Info.rot.y > D3DX_PI)
		{
			m_Info.rot.y = -D3DX_PI;
		}
		else if (m_Info.rot.y < -D3DX_PI)
		{
			m_Info.rot.y = D3DX_PI;
		}
	}
	else if(m_Info.state == STATE_GRAP)
	{
		GrapRotition();
	}
	
	//位置に移動量加算----------------------------------------------------
	m_Info.pos.x += m_Info.move.x;
	m_Info.pos.z += m_Info.move.z;

	//m_pos.y = fHeight + 18.0f;

	//移動量を更新(減衰させる)--------------------------------------------
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.1f;
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.1f;

	CGame::GetCollision()->Map(&m_Info.pos, &m_Info.posOld, 40.0f);
}

//================================================================
// アクション
//================================================================
void CPlayer::Action(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	// 通常攻撃
	if (pInputMouse->GetLButton() == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_A, 0) == true)
	{
		if (m_Info.state != STATE_GRAP && m_Info.state != STATE_HEAT)
		{
			m_bAttack = true;
		}
	}

	// 投げ
	Grap();

	// 回避
	Avoid();

	// ヒートアクション
	Heat();

	CManager::Getinstance()->GetDebugProc()->Print("回転量:%f", m_fGrapRot);
	CManager::Getinstance()->GetDebugProc()->Print("掴んでいる敵の番号:%d", m_nIdxEne);
}

//================================================================
// 投げる時の角度処理
//================================================================
void CPlayer::GrapRotition(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//マウスを取得
	CInputMouse *pInputMouse = CManager::Getinstance()->GetInputMouse();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	//サウンドを取得
	CSound *pSound = CManager::Getinstance()->GetSound();

	//カメラ取得
	CCamera *pCamera = CManager::Getinstance()->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRotation();

	m_fDestOld = m_fDest;

	//上に移動----------------------------------------------
	if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
	{//Wキーが押された

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーも押した 右上に移動

			//向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーも押した 左上に移動

			//向き
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
		}
		else
		{//Wキーだけ押した	真上に移動

			//向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.0f));
		}

	}
	//下に移動----------------------------------------------
	else if (pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) < 0)
	{//Sキーが押された

		if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーも押した 右下に移動

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
		}
		else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーも押した 左下に移動

			// 向き
			m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
		}
		else
		{//Sキーだけ押した 真下に移動

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * m_fGrapRot));
		}

	}
	//右に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_D) == true)
	{//Dキーだけ押した

		// 向き
		m_fDest += (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//左に移動----------------------------------------------
	else if (InputKeyboard->GetPress(DIK_A) == true)
	{//Aキーだけ押した

		// 向き
		m_fDest -= (CameraRot.y + (D3DX_PI * 0.5f)) * 0.1f;
	}
	//右に移動----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
	{//Dキーだけ押した

		// 向き
		m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
	}
	//左に移動----------------------------------------------
	else if (pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
	{//Aキーだけ押した

		// 向き
		m_fDest = (CameraRot.y + (D3DX_PI * -0.5f));
	}

	if (m_fDest > 0.0f && m_fDestOld < 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}
	else if (m_fDest < 0.0f && m_fDestOld > 0.0f)
	{
		if (m_fGrapRot <= 1.38f)
		{
			m_fGrapRot += 0.02f;
		}
	}

	m_fDiff = m_fDest - m_Info.rot.y;

	//角度の値を修正する
	if (m_fDiff >= D3DX_PI)
	{
		m_fDiff -= D3DX_PI * 2;
	}
	else if (m_fDiff <= -D3DX_PI)
	{
		m_fDiff += D3DX_PI * 2;
	}

	//移動方向(角度)の補正------------------------------------------------
	m_Info.rot.y += m_fDiff * (0.15f * m_fGrapRot);

	//角度の値を修正する--------------------------------------------------
	if (m_Info.rot.y > D3DX_PI)
	{
		m_Info.rot.y = -D3DX_PI;
	}
	else if (m_Info.rot.y < -D3DX_PI)
	{
		m_Info.rot.y = D3DX_PI;
	}
}

//================================================================
// 投げる処理
//================================================================
void CPlayer::Grap(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	// ジャイアントスイング
	if (InputKeyboard->GetTrigger(DIK_E) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_RB, 0) == true)
	{
		if (m_Info.state != STATE_LIFT && m_Info.state != STATE_THROW && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_AVOID && m_bLift == false)
		{
			if (m_Grap.pEnemy == nullptr)
			{
				m_Info.state = STATE_GRAP;
				m_pMotion->Set(TYPE_GRAP);
			}
			else
			{
				m_Grap.pEnemy->SetCurrent(nullptr);
				m_Grap.pEnemy->SetPosition(m_Info.pos);
				m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_Grap.pEnemy->SetState(CEnemy::STATE_NEUTRAL);
				m_Grap.pEnemy = nullptr;
				m_Info.state = STATE_NEUTRAL;
				m_pMotion->Set(TYPE_NEUTRAL);
				m_bGrap = false;
			}
		}
	}

	// アイテム持つ
	if (InputKeyboard->GetTrigger(DIK_F) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_LB, 0) == true)
	{
		if (m_Info.state != STATE_THROW && m_Info.state != STATE_GRAP && m_bGrap == false)
		{// 状態が投げる、掴みかつ何も掴んでいないとき

			// アイテムを投げる
			if (m_bLift == true)
			{
				m_Info.state = STATE_THROW;
				m_pMotion->Set(TYPE_THROW);
			}

			// アイテムを掴むよ
			if (m_Grap.pItem == nullptr && CGame::GetCollision()->Item(&m_Info.pos) == true && m_bLift == false)
			{// 何も掴んでいないときかつアイテムの判定内

				m_bLift = true;
			}
		}
	}
}

//================================================================
// 回避処理
//================================================================
void CPlayer::Avoid(void)
{
	//キーボードを取得
	CInputKeyboard *InputKeyboard = CManager::Getinstance()->GetKeyBoard();

	//ゲームパッドを取得
	CInputJoyPad *pInputJoyPad = CManager::Getinstance()->GetInputJoyPad();

	if ((InputKeyboard->GetTrigger(DIK_LSHIFT) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_X, 0) == true))
	{
		if (m_Info.state != STATE_AVOID && m_Info.state != STATE_LIFT &&
			m_Info.state != STATE_THROW && m_Info.state != STATE_GRAP &&
			m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH &&
			m_Info.state != STATE_GRAPWALK)
		{
			if (m_fStamina >= LOSTSTMINA)
			{// 消費量より多かったら

				// スタミナ減らして回避状態に
				m_bAvoid = true;
				m_fStamina -= LOSTSTMINA;
				m_Info.state = STATE_AVOID;
				m_pMotion->Set(TYPE_AVOID);

				if (m_pStamina != nullptr)
				{
					m_pStamina->GetBill()->SetTex(m_fStamina);
				}
			}
		}
	}
}

//================================================================
// 状態処理
//================================================================
void CPlayer::State(void)
{
	// 敵を掴む
	if (m_bLift == true && m_bDesh == true)
	{
		if (m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_THROW)
		{
			m_Info.state = STATE_GRAPDASH;
			m_pMotion->Set(TYPE_GRAPDASH);
		}
	}

	if (m_bGrap == true && m_bDesh == true)
	{
		if (m_Info.state != STATE_GRAPWALK)
		{
			m_Info.state = STATE_GRAPWALK;
			m_pMotion->Set(TYPE_GRAPWALK);
		}
	}

	// 攻撃一段目
	if (m_Info.state != STATE_ATTACK && m_bAttack == true)
	{
		m_Info.state = STATE_ATTACK;
		m_Info.Atc = TYPE_ATTACK1;
		m_pMotion->Set(TYPE_ATTACK01);
		m_bAttack = false;

		// 移動量
		m_Info.move.x -= sinf(m_Info.rot.y);
		m_Info.move.z -= cosf(m_Info.rot.y);
	}

	// 攻撃二段目
	if (m_Info.Atc == TYPE_ATTACK1 && m_bAttack == true && m_pMotion->IsFinish() == true)
	{
		m_Info.Atc = TYPE_ATTACK2;
		m_pMotion->Set(TYPE_ATTACK02);
		m_bAttack = false;

		// 移動量
		m_Info.move.x -= sinf(m_Info.rot.y);
		m_Info.move.z -= cosf(m_Info.rot.y);
	}

	// 攻撃三段目
	if (m_Info.Atc == TYPE_ATTACK2 && m_bAttack == true && m_pMotion->IsFinish() == true)
	{
		m_Info.Atc = TYPE_ATTACK3;
		m_pMotion->Set(TYPE_ATTACK03);
		m_bAttack = false;

		// 移動量
		m_Info.move.x -= sinf(m_Info.rot.y) * 8.0f;
		m_Info.move.z -= cosf(m_Info.rot.y) * 8.0f;
	}

	// 通常攻撃・こぶしorアイテム
	if (m_Info.state == STATE_ATTACK && m_Info.Atc != TYPE_NONE && m_Info.state != STATE_HEAT)
	{
		// アイテム
		if (m_Grap.pItem != nullptr)
		{
			D3DXMATRIX *mtx = m_Grap.pItem->GetMtxWorld();

			D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Objpos.x = mtx->_41;
			Objpos.y = mtx->_42;
			Objpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

				CGame::GetCollision()->AttackCircle(&Objpos, 50.0f, 50.0f, 100.0f);
			}
		}
		else // こぶし
		{
			D3DXMATRIX *mtx = m_ppCharacter[9]->GetMtxWorld();

			D3DXVECTOR3 Handpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Handpos.x = mtx->_41;
			Handpos.y = mtx->_42;
			Handpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

				CGame::GetCollision()->AttackCircle(&Handpos, 50.0f, 50.0f, 100.0f);
			}
		}
	}

	// アイテムを持った
	if (m_Info.state != STATE_LIFT && m_Info.state != STATE_THROW &&m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_HEAT && m_bLift == true)
	{
		m_Info.state = STATE_LIFT;
		m_pMotion->Set(TYPE_LIFT);
	}

	// 回避
	if (m_Info.state == STATE_AVOID)
	{
		m_bDesh = false;
		m_Info.move.x += sinf(m_Info.rot.y + D3DX_PI) * 0.5f;
		m_Info.move.z += cosf(m_Info.rot.y + D3DX_PI) * 0.5f;
	}

	// 持っているアイテムで攻撃した
	if (m_Info.state == STATE_THROW && m_Grap.pItem != nullptr)
	{
		m_Grap.pItem->SetPosition(D3DXVECTOR3(50.0f, -30.0f, -15.0f));
		m_Grap.pItem->SetRotition(D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI, -D3DX_PI * 0.5f));
		CGame::GetCollision()->ItemAttack(m_Grap.pItem);
	}

	// 持っているアイテムとの親子関係を切る
	if (m_pMotion->GetNumFrame() >= m_pMotion->GetAttackEnd() && m_Grap.pItem != nullptr && (m_Info.state == STATE_THROW || m_Info.state == STATE_HEAT))
	{
		m_Grap.pItem->SetCurrent(nullptr);
		m_Grap.pItem->SetPosition(D3DXVECTOR3(m_Info.pos.x + sinf(m_Info.rot.y) * -60.0f, m_Info.pos.y, m_Info.pos.z + cosf(m_Info.rot.y) * -60.0f));
		m_Grap.pItem->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
		m_Grap.pItem = nullptr;
	}

	// 敵を掴む
	if (m_Info.state == STATE_GRAP && m_bGrap == false)
	{
		CEnemy **ppEnemy = nullptr;

		if (CGame::GetEnemyManager() != nullptr)
		{// 敵の情報

			ppEnemy = CGame::GetEnemyManager()->GetEnemy();
		}

		// 距離測って番号返す
		m_nIdxEne = EnemyDistance();

		if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
		{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

			if (CGame::GetCollision()->Circle(&m_Info.pos, &ppEnemy[m_nIdxEne]->GetPosition(), 40.0f, 40.0f) == true)
			{
				m_Grap.pEnemy = ppEnemy[m_nIdxEne];

				m_Grap.pEnemy->SetCurrent(m_ppCharacter[9]->GetMtxWorld());
				m_Grap.pEnemy->SetPosition(D3DXVECTOR3(-10.0f, -10.0f, 60.0f));
				m_Grap.pEnemy->SetRotition(D3DXVECTOR3(-0.2f, 1.27f, -1.4f));
				m_Grap.pEnemy->SetState(CEnemy::STATE_GRAP);
				m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_GRAP);
				m_bGrap = true;
			}
		}
	}

	// モーションを移動モーションにする
	if (m_Info.state != STATE_MOVE && m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH 
		&& m_Info.state != STATE_GRAPWALK && m_Info.state != STATE_THROW && m_Info.state != STATE_HEAT
		&& m_bDesh == true && m_bAttack == false && m_bAvoi == false)
	{
		m_Info.state = STATE_MOVE;

		//モーションをセット(移動)
		m_pMotion->Set(TYPE_MOVE);
	}

	// モーションが終了かつヒートアクション中
	if (m_pMotion->IsFinish() == true && m_Info.state == STATE_HEAT)
	{
		// カメラをもとの位置に戻す
		CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_RETURN);
	}

	// モーションが終了かつ敵を投げるモーション
	if (m_pMotion->IsFinish() == false && m_pMotion->GetType() == STATE_ENEMYGRAP)
	{
		if (m_Grap.pEnemy != nullptr)
		{
			m_Grap.pEnemy->SetCurrent(m_ppCharacter[6]->GetMtxWorld());
			m_Grap.pEnemy->SetPosition(D3DXVECTOR3(-15.0f, 0.0f, 80.0f));
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(-0.2f, 1.27f, -1.4f));
		}
	}

	// 待機モーションにする
	if (m_pMotion->IsFinish() == true || (m_bDesh == false && m_bLift == true && m_Info.state == STATE_GRAPDASH)
		|| (m_bDesh == false && m_bGrap == true && m_Info.state == STATE_GRAPWALK)
		|| (m_bAttack == false && m_bDesh == false && m_bGrap == false && m_bLift == false 
		 && m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_AVOID
		 && m_Info.state != STATE_LIFT && m_Info.state != STATE_HEAT && m_Info.state != STATE_THROW
		 && m_Info.state != STATE_AVOID && m_Info.state != STATE_GRAP))
	{
		//モーションをセット(待機)
		m_pMotion->Set(TYPE_NEUTRAL);
		m_Info.state = STATE_NEUTRAL;
		m_Info.Atc = TYPE_NONE;
		m_bLift = false;
		m_bAttack = false;
		m_nCntColi = 0;
		CGame::GetCollision()->SetbColli(false);

		if (m_Grap.pItem != nullptr)
		{
			m_Info.state = STATE_LIFT;
			m_pMotion->Set(TYPE_LIFT);
			m_bLift = true;
		}

		if (m_Grap.pEnemy != nullptr)
		{
			m_Info.state = STATE_GRAPNEUTRAL;
			m_pMotion->Set(TYPE_GRAPNEUTRAL);
			m_bGrap = true;
		}
	}
}

//================================================================
// ダメージ
//================================================================
void CPlayer::Damege(void)
{
	if (m_Info.state != STATE_DAMEGE)
	{
		m_Info.state = STATE_DAMEGE;
		//m_pMotion->Set();
		m_nDamegeCounter = 10;
	}

	m_Info.nLife--;

	m_nDamegeCounter--;
}

//================================================================
// ヒートアクション
//================================================================
void CPlayer::Heat(void)
{
	CEnemy **ppEnemy = nullptr;
	int nNum = 0;
	float fLength = 0.0f;
	D3DXVECTOR3 OldDistance = D3DXVECTOR3(10000.0f, 100000.0f, 100000.0f);
	D3DXVECTOR3 Distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (CGame::GetEnemyManager() != nullptr)
	{// 敵の総数と敵の情報

		nNum = CGame::GetEnemyManager()->GetNum();
		ppEnemy = CGame::GetEnemyManager()->GetEnemy();
	}

	// アイテムを持っているときまたはアイテムを持って走っているとき
	if (m_Info.state == STATE_LIFT || m_Info.state == STATE_GRAPDASH)
	{
		for (int nCount = 0; nCount < nNum; nCount++)
		{
			if (ppEnemy[nCount] != nullptr)
			{
				// 距離測って番号返す
				m_nIdxEne = EnemyDistance();
			}
		}

		if (ppEnemy[m_nIdxEne] != nullptr)
		{
			if (CGame::GetCollision()->Circle(&m_Info.pos, &ppEnemy[m_nIdxEne]->GetPosition(), 50.0f, 50.0f) == true)
			{// 範囲内に入ったらYボタンが出てくる

				m_HeatAct = HEAT_SMASH;

				 // Yボタンが出てくる
				{
					if (m_pBotton == nullptr)
					{
						m_pBotton = CObject2D::Create();
					}

					if (m_pBotton != nullptr)
					{
						m_pBotton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
						m_pBotton->SetSize(25.0f, 25.0f);
						m_pBotton->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Ybutton.png"));
						m_pBotton->SetDraw(true);
					}
				}

				if (StartHeatAction() == true)
				{
					ppEnemy[m_nIdxEne]->SetChase(CEnemy::CHASE_OFF);
					ppEnemy[m_nIdxEne]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					m_pMotion->Set(TYPE_THROW);

					// 持っているアイテムの種類に応じた攻撃タイプ
					if (m_Grap.pItem != nullptr)
					{
						if (m_Grap.pItem->GetType() == CItem::TYPE_BIKE)
						{
							m_Info.Atc = TYPE_HEATACTBIKE;
						}

						if (m_Grap.pItem->GetType() == CItem::TYPE_REF)
						{
							m_Info.Atc = TYPE_HEATACTREF;
						}
					}
				}
			}
			else
			{
				if (m_pBotton != nullptr)
				{
					m_pBotton->Uninit();
					m_pBotton = nullptr;
				}
			}
		}
	}

	// 電子レンジ
	if (m_bGrap == true)
	{// 敵を掴んでいる

		if (m_pItem == nullptr)
		{// 使用されていない

			if (CGame::GetItemManager() != nullptr)
			{// アイテムが存在している

				for (int nCount = 0; nCount < CGame::GetItemManager()->GetNum(); nCount++)
				{
					if (CGame::GetItemManager()->GetItem()[nCount] != nullptr && CGame::GetItemManager()->GetItem()[nCount]->GetType() == CItem::TYPE_MICROWAVE)
					{// アイテムの種類が電子レンジ

						m_pItem = CGame::GetItemManager()->GetItem()[nCount];
					}
				}
			}
		}
		
		if (CGame::GetCollision()->Circle(&m_Info.pos, &m_pItem->GetPosition(),30.0f, 30.0f))
		{// 範囲内
			
			m_HeatAct = HEAT_FIRE;

			// Yボタンが出てくる
			{
				if (m_pBotton == nullptr)
				{
					m_pBotton = CObject2D::Create();
				}

				if (m_pBotton != nullptr)
				{
					m_pBotton->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
					m_pBotton->SetSize(25.0f, 25.0f);
					m_pBotton->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Ybutton.png"));
					m_pBotton->SetDraw(true);
				}
			}

			if (StartHeatAction() == true)
			{// 

				m_pMotion->Set(TYPE_ENEMYGRAP);
				m_Info.Atc = TYPE_HEATACTMICROWAVE;
			}
		}
		else
		{
			if (m_pBotton != nullptr)
			{
				m_pBotton->Uninit();
				m_pBotton = nullptr;
			}
		}
	}

	if (m_Info.state == STATE_HEAT)
	{// 状態がヒートアクションのとき　

		switch (m_Info.Atc)
		{
		case TYPE_HEATACTBIKE:

			// たたきつけ
			Smash(ppEnemy[m_nIdxEne]);
			break;

		case TYPE_HEATACTREF:

			// たたきつけ
			Smash(ppEnemy[m_nIdxEne]);
			break;

		case TYPE_HEATACTMICROWAVE:

			// 電子レンジ
			Fire();
			break;

		default:
			break;
		}
		
	}
}

//================================================================
// ヒートアクション・たたきつけ
//================================================================
void CPlayer::Smash(CEnemy *pEnemy)
{
	if (pEnemy != nullptr)
	{
		// 敵の方向に向かせる
		m_fDest = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, pEnemy->GetPosition(), m_Info.rot.y);
		m_Info.rot.y += m_fDest;
		m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);

		// アイテムと敵の当たり判定
		if (m_Grap.pItem != nullptr)
		{
			D3DXMATRIX *mtx = m_Grap.pItem->GetMtxWorld();

			D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Objpos.x = mtx->_41;
			Objpos.y = mtx->_42;
			Objpos.z = mtx->_43;

			// 当たり判定
			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

				if (CGame::GetCollision()->ItemEnemy(m_Grap.pItem, pEnemy, 50.0f, 50.0f, 100.0f) == true)
				{// 範囲内

					// 持っていたアイテムを消す
					CGame::GetItemManager()->Release(m_Grap.pItem->GetID());
					m_Grap.pItem = nullptr;
				}
			}
		}
	}
}

//================================================================
// ヒートアクション・電子レンジ	
//================================================================
void CPlayer::Fire(void)
{
	// 電子レンジの方向に向かせる
	m_fDest = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, m_pItem->GetPosition(), m_Info.rot.y);
	m_Info.rot.y += m_fDest;
	m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);
	m_Info.pos = D3DXVECTOR3(-747.0f, 0.0f, 580.0f);

	if (m_Grap.pEnemy != nullptr && m_pMotion->IsFinish() == true && m_pMotion->GetType() == TYPE_ENEMYGRAP && m_Info.state == STATE_HEAT)
	{
		// プレイヤーとの関係を切る
		{
			m_Grap.pEnemy->SetCurrent(nullptr);
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_Info.state = STATE_NEUTRAL;
			m_pMotion->Set(TYPE_NEUTRAL);
			m_bGrap = false;
		}
		
		// 電子レンジとの関係を作る
		{
			m_Grap.pEnemy->SetCurrent(m_pItem->GetMtxWorld());
			m_Grap.pEnemy->SetPosition(D3DXVECTOR3(0.0f, -70.0f, -30.0f));
			m_Grap.pEnemy->SetRotition(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

			// 状態とモーションを設定
			if (m_Grap.pEnemy->GetState() != CEnemy::STATE_BIRIBIRI)
			{
				m_Grap.pEnemy->SetState(CEnemy::STATE_BIRIBIRI);
				m_Grap.pEnemy->GetMotion()->Set(CEnemy::TYPE_BIRIBIRI);
			}
		}
	}
}

//================================================================
// 外部ファイル読み込み
//================================================================
void CPlayer::ReadText(const char *fliename)
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

					m_ppCharacter = new CCharacter*[m_nNumModel];

				}  //NUM_MODELのかっこ

				if (strcmp("MODEL_FILENAME", aString) == 0)
				{
					fscanf(pFile, "%s", &aString);          //=
					fscanf(pFile, "%s", &m_filename[0]);  //モデルの名前

					m_ppCharacter[nCntModel] = CCharacter::Create(m_filename);
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
										m_ppCharacter[nCntParts2]->SetParent(m_ppCharacter[m_nParent]);
									}
									else
									{
										m_ppCharacter[nCntParts2]->SetParent(NULL);
									}
								}

								if (strcmp("POS", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readpos.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readpos.z);  //モデルの総数

									m_ppCharacter[nCntParts2]->SetPositionOri(m_Readpos);

									m_ppCharacter[nCntParts2]->SetPosition(m_Readpos);
								}

								if (strcmp("ROT", aString) == 0)
								{
									fscanf(pFile, "%s", &aString);      //=
									fscanf(pFile, "%f", &m_Readrot.x);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.y);  //モデルの総数
									fscanf(pFile, "%f", &m_Readrot.z);  //モデルの総数

									m_ppCharacter[nCntParts2]->SetRotOrigin(m_Readrot);

									m_ppCharacter[nCntParts2]->SetRot(m_Readrot);
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
		// モデルの設定
		m_pMotion->SetModel(m_ppCharacter, m_nNumModel);

		// 初期化処理
		m_pMotion->ReadText(fliename);

		// セット(待機)
		m_pMotion->Set(TYPE_NEUTRAL);
	}
}

//================================================================
// ヒートアクション
//================================================================
bool CPlayer::StartHeatAction(void)
{
	if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_E) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_Y, 0) == true)
	{// ヒートアクションする

		if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME)
		{// カメラのモードがゲームのときかつアイテムを手に持っているとき

			// ボタン消す
			if (m_pBotton != nullptr)
			{
				m_pBotton->Uninit();
				m_pBotton = nullptr;
			}

			// 走っていたら止めさせる
			if (m_bDesh == true)
			{
				m_bDesh = false;
			}

			// ヒートアクションのカメラモードにする
			CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_HEAT);
			CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(CAMERAROT[m_HeatAct].x, CAMERAROT[m_HeatAct].y, CAMERAROT[m_HeatAct].z));
			m_Info.state = STATE_HEAT;

			return true;
		}
	}

	return false;
}

//================================================================
// 敵との距離算出：敵の番号を返すよ
//================================================================
int CPlayer::EnemyDistance(void)
{
	CEnemy **ppEnemy = nullptr;
	int nNum = 0; // 敵の総数
	int nIdx = -1; // 敵の番号
	D3DXVECTOR3 OldDistance = D3DXVECTOR3(10000.0f, 100000.0f, 100000.0f);
	D3DXVECTOR3 Distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (CGame::GetEnemyManager() != nullptr)
	{// 敵の総数と敵の情報

		nNum = CGame::GetEnemyManager()->GetNum();
		ppEnemy = CGame::GetEnemyManager()->GetEnemy();
	}

	for (int nCount = 0; nCount < nNum; nCount++)
	{
		if (ppEnemy[nCount] != nullptr)
		{
			// 距離測定
			Distance = CManager::Getinstance()->GetUtility()->Distance(m_Info.pos, ppEnemy[nCount]->GetPosition());

			if (Distance.x <= OldDistance.x && Distance.y <= OldDistance.y && Distance.z <= OldDistance.z)
			{// 今回と前回の距離を比較して近かったら

				OldDistance = Distance;

				// 掴む番号を覚える
				nIdx = nCount;
			}
		}
	}

	return nIdx;
}
