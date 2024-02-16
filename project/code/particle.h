//===========================================================
//
//ポリゴンを出すやつ[particle.h]
//Author 大原怜将
//
//===========================================================
#ifndef _PARTICLE_H__             //このマクロ定義がされてなかったら
#define _PARTICLE_H__             //2重インクルード防止のマクロ定義をする

#include "billboard.h"

//マクロ定義
#define EFFECTMOVE   (5.0f)    //エフェクトの最大数

//パーティクルクラス
class CParticle
{
public:

	enum TYPE
	{
		TYPE_GROUND = 0,  // 土煙
		TYPE_BLOOD,       // 血液
		TYPE_SMOOK,       // 煙
		TYPE_CIRCLE,      // 円形
		TYPE_GLASS,       // ガラスの破片
		TYPE_MAX
	};

	CParticle();  //コンストラクタ
	CParticle(D3DXVECTOR3 pos, TYPE type);  //コンストラクタ
	~CParticle();  //デストラクタ

	HRESULT Init(void); //Bgの初期化処理    
	void Uninit(void);  //Bgの終了処理
	void Update(void);  //Bgの更新処理
	void Draw(void);    //Bgの描画処理

	static HRESULT Load(void);  //テクスチャの生成(読み込み)
	static void UnLoad(void);   //テクスチャの破棄

	void Move(void);
	void Blood(void);
	void Ground(void);
	void Smook(void);
	void Circle(void);
	void Glass(void);

	static CParticle *Create(D3DXVECTOR3 pos, TYPE type);  //生成
	D3DXCOLOR m_col;          //色
	float m_fRadius;          //半径(大きさ)
	int m_nLife;              //寿命(表示時間)
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //テクスチャへのポインタ
	TYPE m_type;

};

#endif