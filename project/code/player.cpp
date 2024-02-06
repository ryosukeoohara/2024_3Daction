//===========================================================
//
//ポリゴンを出すやつ[player.cpp]
//Author 大原怜将
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

#include<stdio.h>
#include<time.h>
#include<string.h>

//================================================================
//マクロ定義
//================================================================
#define MAX_LIFECHIBI (10)                                        // チビの体力
#define MAX_LIFEFOOT  (6)                                         // デブの体力
#define REST_BULLET   (30)                                        // 保持できる弾の数
#define BULLETWAIT    (15)                                        // 射撃の間隔
#define MUTEKITIME    (30)                                        // 無敵時間
#define PLAYER_X      (40.0f)                                     // プレイヤーのX軸の幅
#define PLAYER_Z      (10.0f)                                     // プレイヤーのZ軸の幅
#define SPEED         (1.0f)                                      // 移動の速さ
#define MOVE          (4.0f)
#define FRIST         (21)                                        // 攻撃判定発生開始
#define FINISH        (31)                                        // 攻撃判定終了
#define LOSTSTMINA    (10)                                        // ダッシュのスタミナ消費量
#define PLAYER01_TEXT ("data\\TEXT\\motion_neet2.txt")       // プレイヤーのテキストファイル
#define PLAYER02_TEXT ("data\\TEXT\\motion_set_player2.txt")      // プレイヤーのテキストファイル

//================================================================
//静的メンバ変数宣言
//================================================================
//MODEL *CPlayer::m_Player = NULL;

//================================================================
//コンストラクタ
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

	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pObj = nullptr;
	m_nIdxEne = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_nLife = 0;
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
//コンストラクタ(オーバーロード)
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

	m_nIdxTexture = -1;
	m_nIdxShaadow = -1;
	m_nCntColi = 0;
	m_nDamegeCounter = 0;
	m_Readpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Readrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_ppCharacter = nullptr;
	m_pLife = nullptr;
	m_pStamina = nullptr;
	m_pEnemy = nullptr;
	m_pObj = nullptr;
	m_nIdxEne = 0;
	m_fDest = 0.0f;
	m_fDestOld = 0.0f;
	m_fDiff = 0.0f;
	m_fGrapRot = 0.0f;
	m_fStamina = 0.0f;
	m_nLife = 0;
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
//デストラクタ
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
//プレイヤーの初期化処理
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
	m_Info.nLife = 10;

	ReadText(PLAYER01_TEXT);

	m_pLife = CGage2D::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 40.0f, (float)(m_nLife * 20), CGage2D::TYPE_LIFE);
	m_pLife->GetObj2D()->SetEdgeCenterTex((float)m_Info.nLife * 20);
	m_pStamina = CGage3D::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z), 5.0f, m_fStamina, CGage3D::TYPE_STAMINA);
	m_pStamina->SetPos(&m_Info.pos);
	m_pStamina->GetBill()->SetTex(m_fStamina);
	
	return S_OK;
}

//================================================================
//プレイヤーの終了処理
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
//プレイヤーの更新処理
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

	Control();

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_ppCharacter[nCount] != nullptr)
		{
			m_ppCharacter[nCount]->Update();
		}
	}

	if (m_pMotion != NULL)
	{
		// 更新処理
		m_pMotion->Update();
	}

	if (m_fStamina < 40)
	{
		m_fStamina += 0.1f;

		if (m_pStamina != nullptr)
		{
			m_pStamina->GetBill()->SetTex(m_fStamina);
		}
	}

	if (m_pLife != nullptr)
	{
		m_pLife->GetObj2D()->SetEdgeCenterTex((float)m_Info.nLife * 20);
	}
}

//================================================================
//プレイヤーの描画処理
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
	Move();     // 移動
	Action();   // アクション
	State();    // 状態

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

	if (m_Info.state != STATE_GRAP && m_Info.state != STATE_AVOID && m_Info.state != STATE_ATTACK && m_Info.state != STATE_HEAT && m_Info.state != STATE_DAMEGE)
	{
		//上に移動----------------------------------------------
		if (InputKeyboard->GetPress(DIK_W) == true || pInputJoyPad->GetLYStick(CInputJoyPad::STICK_LY, 0) > 0)
		{//Wキーが押された

			if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
			{//Dキーも押した 右上に移動

			 // 移動量
				m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;
				m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;

				//向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.25f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//Aキーも押した 左上に移動

			 // 移動量
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * SPEED;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * SPEED;

				//向き
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.25f));
			}
			else
			{//Wキーだけ押した	真上に移動

			 // 移動量
				m_Info.move.x -= sinf(CameraRot.y) * SPEED;
				m_Info.move.z -= cosf(CameraRot.y) * SPEED;

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
				m_Info.move.x += sinf(CameraRot.y + (-D3DX_PI * 0.25f)) * SPEED;
				m_Info.move.z += cosf(CameraRot.y + (-D3DX_PI * 0.25f)) * SPEED;

				// 向き
				m_fDest = (CameraRot.y + (D3DX_PI * 0.75f));
			}
			else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
			{//Aキーも押した 左下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;
				m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * SPEED;

				// 向き
				m_fDest = (CameraRot.y + (-D3DX_PI * 0.75f));
			}
			else
			{//Sキーだけ押した 真下に移動

				// 移動量
				m_Info.move.x += sinf(CameraRot.y) * SPEED;
				m_Info.move.z += cosf(CameraRot.y) * SPEED;

				// 向き
				m_fDest = (CameraRot.y + (D3DX_PI));
			}

			m_bDesh = true;
		}
		//右に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) > 0)
		{//Dキーだけ押した

		 // 移動量
			m_Info.move.x -= sinf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;
			m_Info.move.z -= cosf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;

			m_bDesh = true;

			// 向き
			m_fDest = (CameraRot.y + (D3DX_PI * 0.5f));
		}
		//左に移動----------------------------------------------
		else if (InputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetLXStick(CInputJoyPad::STICK_LX, 0) < 0)
		{//Aキーだけ押した

			// 移動量
			m_Info.move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;
			m_Info.move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * SPEED;

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

	// ヒートアクション
	if (InputKeyboard->GetTrigger(DIK_Q) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_RB, 0) == true)
	{
		if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME && m_bLift == true)
		{
			CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_HEAT);
			CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, m_Info.rot.y - 2.35f, D3DX_PI * -0.38f));
			m_Info.state = STATE_HEAT;
			m_pMotion->Set(TYPE_THROW);
		}
	}

	// 投げ
	Grap();

	// 回避
	Avoid();

	Heat();

	CManager::Getinstance()->GetDebugProc()->Print("回転量:%f", m_fGrapRot);
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
	/*if (InputKeyboard->GetTrigger(DIK_E) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_Y, 0) == true)
	{
		if (m_Info.state != STATE_LIFT && m_Info.state != STATE_THROW && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_AVOID)
		{
			if (m_Info.state != STATE_GRAP)
			{
				m_bGrap = true;
			}
			else
			{
				m_bGrap = false;
			}
		}
	}*/

	// アイテム持つ
	if (InputKeyboard->GetTrigger(DIK_F) == true || pInputJoyPad->GetTrigger(CInputJoyPad::BUTTON_LB, 0) == true)
	{
		if (m_Info.state != STATE_THROW && m_Info.state != STATE_GRAP)
		{
			if (m_bLift == true)
			{
				m_Info.state = STATE_THROW;
				m_pMotion->Set(TYPE_THROW);
			}

			if (m_Obj == nullptr && CGame::GetCollision()->Item(&m_Info.pos) == true && m_bLift == false)
			{
				m_bLift = true;
				CManager::Getinstance()->GetDebugProc()->Print("当たってる～");
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
			m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH)
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
	if (m_bLift == true && m_bDesh == true)
	{
		if (m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_THROW)
		{
			m_Info.state = STATE_GRAPDASH;
			m_pMotion->Set(TYPE_GRAPDASH);
		}
	}

	if (m_Info.state != STATE_ATTACK && m_bAttack == true)
	{
		m_Info.state = STATE_ATTACK;
		m_Info.Atc = TYPE01_ATTACK;
		m_pMotion->Set(TYPE_ATTACK01);
		m_bAttack = false;

		// 移動量
		m_Info.move.x -= sinf(m_Info.rot.y) * MOVE;
		m_Info.move.z -= cosf(m_Info.rot.y) * MOVE;
	}

	if (m_Info.Atc == TYPE01_ATTACK && m_bAttack == true && m_pMotion->IsFinish() == true)
	{
		m_Info.Atc = TYPE02_ATTACK;
		m_pMotion->Set(TYPE_ATTACK02);
		m_bAttack = false;

		// 移動量
		m_Info.move.x -= sinf(m_Info.rot.y) * MOVE;
		m_Info.move.z -= cosf(m_Info.rot.y) * MOVE;
	}
	if (m_Info.Atc == TYPE02_ATTACK && m_bAttack == true && m_pMotion->IsFinish() == true)
	{
		m_Info.Atc = TYPE03_ATTACK;
		m_pMotion->Set(TYPE_ATTACK03);
		m_bAttack = false;

		// 移動量
		m_Info.move.x -= sinf(m_Info.rot.y) * 8.0f;
		m_Info.move.z -= cosf(m_Info.rot.y) * 8.0f;
	}

	if (m_Info.state == STATE_ATTACK && m_Info.Atc != TYPE00_NONE && m_Info.state != STATE_HEAT)
	{
		if (m_Obj != nullptr)
		{
			D3DXMATRIX *mtx = m_Obj->GetMtxWorld();

			D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Objpos.x = mtx->_41;
			Objpos.y = mtx->_42;
			Objpos.z = mtx->_43;

			if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
			{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

				CGame::GetCollision()->AttackCircle(&Objpos, 50.0f, 50.0f, 100.0f);
			}
		}
		else
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

	if (m_Info.state != STATE_LIFT && m_Info.state != STATE_THROW &&m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_HEAT && m_bLift == true)
	{
		m_Info.state = STATE_LIFT;
		m_pMotion->Set(TYPE_LIFT);
	}

	if (m_Info.state != STATE_GRAP && m_Info.state != STATE_ATTACK &&m_bGrap == true)
	{
		m_bDesh = false;

		m_Info.state = STATE_GRAP;

		// モーションをセット(近接攻撃)
		//m_pMotion->Set(TYPE_GRAP);
	}

	if (m_Info.state == STATE_AVOID)
	{
		m_bDesh = false;
		m_Info.move.x += sinf(m_Info.rot.y + D3DX_PI) * 0.5f;
		m_Info.move.z += cosf(m_Info.rot.y + D3DX_PI) * 0.5f;

		//m_Info.pos.x += m_Info.move.x * 0.0005f;
		//m_Info.pos.z += m_Info.move.z * 0.0005f;
	}

	if (m_Info.state == STATE_THROW && m_Obj != nullptr)
	{
		m_Obj->SetPosition(D3DXVECTOR3(50.0f, -30.0f, -15.0f));
		m_Obj->SetRotition(D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI, -D3DX_PI * 0.5f));
		CGame::GetCollision()->ItemAttack(m_Obj);
	}

	if (m_pMotion->GetNumFrame() >= 15 && m_Obj != nullptr && (m_Info.state == STATE_THROW || m_Info.state == STATE_HEAT))
	{
		m_Obj->SetCurrent(nullptr);
		m_Obj->SetPosition(D3DXVECTOR3(m_Info.pos.x + sinf(m_Info.rot.y) * -60.0f, m_Info.pos.y, m_Info.pos.z + cosf(m_Info.rot.y) * -60.0f));
		m_Obj->SetRotition(D3DXVECTOR3(0.0f, -D3DX_PI, -D3DX_PI * 0.5f));
		m_Obj = nullptr;
	}

	/*if (m_Info.state == STATE_GRAP && m_bGrap == false)
	{
		CGame::GetEnemy()->SetCurrent(nullptr);
		CGame::GetEnemy()->SetPosition(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 50.0f, m_Info.pos.z));
		CGame::GetEnemy()->SetRotition(m_Info.rot);
		CGame::GetEnemy()->SetMove(D3DXVECTOR3(sinf(m_Info.rot.y) * (m_fGrapRot * 3.0f), 1.0f, cosf(m_Info.rot.y) * (m_fGrapRot * 3.0f)));
		CGame::GetEnemy()->SetState(CEnemy::STATE_DAMEGE);
		m_fGrapRot = 1.0f;
	}

	if (m_bGrap == true)
	{
		CGame::GetEnemy()->SetCurrent(&m_Info.mtxWorld);
		CGame::GetEnemy()->SetPosition(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
		CGame::GetEnemy()->SetRotition(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, D3DX_PI));
		CGame::GetEnemy()->SetState(CEnemy::STATE_GRAP);
	}*/

	if (m_Info.state != STATE_MOVE && m_Info.state != STATE_ATTACK && m_Info.state != STATE_GRAPDASH && m_Info.state != STATE_THROW && m_Info.state != STATE_HEAT
		&& m_bDesh == true && m_bAttack == false && m_bAvoi == false)
	{
		m_Info.state = STATE_MOVE;

		//モーションをセット(移動)
		m_pMotion->Set(TYPE_MOVE);
	}

	if (m_pMotion->IsFinish() == true && m_Info.state == STATE_HEAT)
	{
		CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_RETURN);
	}

	if (m_pMotion->IsFinish() == true || (m_bDesh == false && m_bLift == true && m_Info.state == STATE_GRAPDASH)
		|| (m_bAttack == false && m_bDesh == false && m_bGrap == false && m_bLift == false &&
			m_Info.state != STATE_NEUTRAL && m_Info.state != STATE_ATTACK && m_Info.state != STATE_AVOID
			&& m_Info.state != STATE_LIFT && m_Info.state != STATE_HEAT && m_Info.state != STATE_THROW))
	{
		//モーションをセット(待機)
		m_pMotion->Set(TYPE_NEUTRAL);
		m_Info.state = STATE_NEUTRAL;
		m_Info.Atc = TYPE00_NONE;
		m_bLift = false;
		m_bAttack = false;
		m_nCntColi = 0;
		CGame::GetCollision()->SetbColli(false);

		if (m_Obj != nullptr)
		{
			m_Info.state = STATE_LIFT;
			m_pMotion->Set(TYPE_LIFT);
			m_bLift = true;
		}

		if (m_pEnemy != nullptr)
		{
			m_pEnemy->SetChase(CEnemy::CHASE_ON);
			m_pEnemy = nullptr;
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

	m_nDamegeCounter--;
}

//================================================================
// ヒートアクション
//================================================================
void CPlayer::Heat(void)
{
	CEnemy **ppEnemy = CGame::GetEnemyManager()->GetEnemy();

	if (m_Info.state == STATE_LIFT || m_Info.state == STATE_GRAPDASH)
	{
		int nNum = 0;

		if (CGame::GetEnemyManager() != nullptr)
		{
			nNum = CGame::GetEnemyManager()->GetNum();
		}
		
		for (int nCount = 0; nCount < nNum; nCount++)
		{
			if (ppEnemy[nCount] != nullptr)
			{
				if (CGame::GetCollision()->Circle(&m_Info.pos, &ppEnemy[nCount]->GetPosition(), 50.0f, 50.0f) == true)
				{
					if (m_pObj == nullptr)
					{
						m_pObj = CObject2D::Create();
						m_pObj->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT  * 0.8f, 0.0f));
						m_pObj->SetSize(25.0f, 25.0f);
						m_pObj->SetIdxTex(CManager::Getinstance()->GetTexture()->Regist("data\\TEXTURE\\Ybutton.png"));
						m_pObj->SetDraw(true);
					}

					if (CManager::Getinstance()->GetKeyBoard()->GetTrigger(DIK_E) == true || CManager::Getinstance()->GetInputJoyPad()->GetTrigger(CInputJoyPad::BUTTON_Y, 0) == true)
					{
						m_nIdxEne = nCount;
						//ppEnemy[m_nIdxEne]->SetState(CEnemy::STATE_DAMEGE);
						ppEnemy[m_nIdxEne]->SetChase(CEnemy::CHASE_OFF);
						ppEnemy[m_nIdxEne]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						if (CManager::Getinstance()->GetCamera()->GetMode() == CCamera::MODE_GAME && m_bLift == true)
						{
							if (m_pObj != nullptr)
							{
								m_pObj->Uninit();
								m_pObj = nullptr;
							}

							CManager::Getinstance()->GetCamera()->SetMode(CCamera::MODE_HEAT);
							CManager::Getinstance()->GetCamera()->SetRotation(D3DXVECTOR3(0.0f, m_Info.rot.y - 2.35f, D3DX_PI * -0.38f));
							m_Info.state = STATE_HEAT;
							m_pMotion->Set(TYPE_THROW);
						}
					}
				}
				else
				{
					if (m_pObj != nullptr)
					{
						m_pObj->Uninit();
						m_pObj = nullptr;
					}
				}
			}
		}
	}

	if (m_Info.state == STATE_HEAT)
	{
		if (ppEnemy[m_nIdxEne] != nullptr)
		{
			m_fDest = CManager::Getinstance()->GetUtility()->MoveToPosition(m_Info.pos, ppEnemy[m_nIdxEne]->GetPosition(), m_Info.rot.y);
			m_Info.rot.y += m_fDest;
			m_Info.rot.y = CManager::Getinstance()->GetUtility()->CorrectAngle(m_Info.rot.y);

			if (m_Obj != nullptr)
			{
				D3DXMATRIX *mtx = m_Obj->GetMtxWorld();

				D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				Objpos.x = mtx->_41;
				Objpos.y = mtx->_42;
				Objpos.z = mtx->_43;

				if (m_pMotion->GetAttackOccurs() <= m_pMotion->GetNowFrame() && m_pMotion->GetAttackEnd() >= m_pMotion->GetNowFrame())
				{// 現在のフレームが攻撃判定発生フレーム以上かつ攻撃判定終了フレームない

					CGame::GetCollision()->AttackCircle(&Objpos, 50.0f, 50.0f, 100.0f);
				}
			}
		}
	}
}

//================================================================
//外部ファイル読み込み
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

	if (m_pMotion != NULL)
	{
		//モデルの設定
		m_pMotion->SetModel(m_ppCharacter, m_nNumModel);

		//初期化処理
		m_pMotion->ReadText(fliename);

		m_pMotion->Set(TYPE_NEUTRAL);
	}
}