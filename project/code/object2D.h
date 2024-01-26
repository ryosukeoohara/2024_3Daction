//===========================================================
//
//ポリゴンを出すやつ[object2D.h]
//Author 大原怜将
//
//===========================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//オブジェクト2Dクラス
class CObject2D : public CObject
{
public:		//誰でもアクセスできる
	CObject2D();  //コンストラクタ
	CObject2D(D3DXVECTOR3 pos);  //コンストラクタ(overdose)
	~CObject2D(); //デストラクタ

	HRESULT Init(void);   //初期化処理
	void Uninit(void);    //終了処理
	void Update(void);    //更新処理
	void Draw(void);      //描画処理

	static CObject2D *Create(void);             //生成
	static CObject2D *Create(D3DXVECTOR3 pos);  //生成

	// 設定系
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }          // 位置
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }          // 向き
	void SetColor(D3DXCOLOR col);                               // 色
	void SetIdxTex(int Idx) { m_nIdxTexture = Idx; }            // テクスチャのインデックス番号
	void SetSize(float fWidth, float fHeight);                  // サイズ
	void SetEdgeCenter(float fWidth, float fHeight);            // サイズ
	void SetEdgeCenterTex(float ftex);
	void SetDraw(bool bverdict) { m_bDraw = bverdict; }         // 描画するかどうか
	
	// 取得系
	D3DXVECTOR3 GetPosition(void) { return m_pos; }     // 位置
	D3DXVECTOR3 GetRotition(void) { return m_rot; }     // 向き
	D3DXCOLOR GetColor(void) { return m_col; }          // 色
	int GetIdxTex(void) { return m_nIdxTexture;	}       // テクスチャのインデックス番号

private:	//自分だけがアクセスできる
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   // 頂点情報を格納
	D3DXVECTOR3 m_pos;                    // 位置
	D3DXVECTOR3 m_rot;                    // 向き
	D3DXCOLOR m_col;                      // 色
	int m_nIdxTexture;                    // テクスチャのインデックス番号
	int m_nCounterAnimPlayer = 0;         // カウンターを初期化する
	int m_nPatternAnimPlayer = 0;         // パターンNo.を初期化する
	float m_fHeight;                      // 高さ
	float m_fWidth;                       // 幅
	bool m_bDraw;                          // 描画するかどうか
};

#endif // !1