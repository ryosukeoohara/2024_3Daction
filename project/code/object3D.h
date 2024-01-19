//=============================================================================
//
// ポリゴン処理 [object3D.h]
// Author : 大原　怜将
//
//=============================================================================

#ifndef _OBJECT3D_H_             //このマクロ定義がされてなかったら
#define _OBJECT3D_H_             //2重インクルード防止のマクロ定義をする

#include "main.h"
#include "object.h"

//オブジェクト3Dクラス
class CObject3D : public CObject
{
public:
	CObject3D();
	CObject3D(D3DXVECTOR3 pos);  //コンストラクタ(overdose)
	~CObject3D();

	HRESULT Init(void);   // 初期化処理    
	void Uninit(void);    // 終了処理
	void Update(void);    // 更新処理
	void Draw(void);      // 描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 m_Texture);  //テクスチャをバインド

	// 設定系
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }          // 位置
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }          // 向き
	void SetColor(D3DXCOLOR col) { m_col = col; }               // 色
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }            // テクスチャのインデックス番号
	void SetSize(float fHeight, float fWidth);                  // サイズ
	void SetDraw(bool bverdict) { m_bDraw = bverdict; }         // 描画するかどうか

	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_pos; }     // 位置
	D3DXVECTOR3 GetRotition(void) { return m_rot; }     // 向き
	D3DXCOLOR GetColor(void) { return m_col; }          // 色
	int GetIdxTex(void) { return m_nIdxTexture; }       // テクスチャのインデックス番号
	
	static CObject3D *Create(void);  //生成
	
//	float GetHeight(D3DXVECTOR3 pos);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;             // テクスチャへのポインタ
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