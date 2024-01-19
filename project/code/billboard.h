//=============================================================================
//
// ウォール処理 [billboard.h]
// Author : 大原　怜将
//
//=============================================================================

#ifndef _BILLBOARD_H_             //このマクロ定義がされてなかったら
#define _BILLBOARD_H_             //2重インクルード防止のマクロ定義をする

#include "main.h"
#include "object3D.h"

//ビルボードクラス
class CBillBoard : public CObject3D
{
public:
	CBillBoard();
	~CBillBoard();

	HRESULT Init(void);  //ビルボードの初期化処理    
	void Uninit(void);   //ビルボードの終了処理
	void Update(void);   //ビルボードの更新処理
	void Draw(void);     //ビルボードの描画処理

	static CBillBoard *Create(void);  //生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxWorld;                     // ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;        // 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;                         // 位置
	D3DXVECTOR3 m_rot;                         // 向き
	D3DXCOLOR m_col;                           // 色
	int m_nIdxTexture;                         // テクスチャのインデックス番号
	float m_fHeight;                           // 高さ
	float m_fWidth;                            // 幅
	bool m_bDraw;                              // 描画するかどうか
};


#endif