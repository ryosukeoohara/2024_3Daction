//=============================================================================
//
// ウォール処理 [billboard.h]
// Author : 大原　怜将
//
//=============================================================================

#ifndef _BILLBOARD_H_             //このマクロ定義がされてなかったら
#define _BILLBOARD_H_             //2重インクルード防止のマクロ定義をする

#include "main.h"
#include "object.h"

//ビルボードクラス
class CBillBoard : public CObject
{
public:
	CBillBoard();
	~CBillBoard();

	HRESULT Init(void);  // 初期化処理    
	void Uninit(void);   // 終了処理
	void Update(void);   // 更新処理
	void Draw(void);     // 描画処理
	 
	static CBillBoard *Create(void);  //生成

	// 設定系
	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }        // 親のマトリックス
	void SetSize(float fHeight, float fWidth);                            // サイズ
	void SetTex(float fTex);
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }                      // テクスチャのインデックス番号
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }                    // 位置
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }                    // 向き
	void SetColor(D3DXCOLOR col);                                         // 色
	void SetDraw(bool bDraw = true) { m_bDraw = bDraw; }                  // 描画するかどうか

	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotition(void) { return m_rot; }

private:
	LPDIRECT3DTEXTURE9 m_pTexture;       //テクスチャへのポインタ
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxWorld;                     // ワールドマトリックス
	D3DXMATRIX *m_pCurrent;
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