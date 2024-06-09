//===========================================================
//
//ポリゴンを出すやつ[main.h]
//Author 大原怜将
//
//===========================================================
#ifndef _MAIN_H_     //このマクロが定義されてなかったら
#define _MAIN_H_     //2重インクルードを防止のマクロを定義する

#define CLASS_NAME        "windowclass"            //ウインドウクラスの名前

typedef struct
{
	D3DXVECTOR3 pos;   //位置
	float rhw;
	D3DCOLOR col;      //色
	D3DXVECTOR2 tex;   //テクスチャの座標
} VERTEX_2D;

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;    //位置
	D3DXVECTOR3 nor;    //法線ベクトル
	D3DCOLOR    col;
	D3DXVECTOR2 tex;
} VERTEX_3D;

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")                    //描画処理に必要
#pragma comment(lib,"d3dx9.lib")                   //[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")                  //Directコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")                   //システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")                 //入力処理に必要

#ifndef _DEBUG
#pragma comment(lib, "Effekseer.lib")
#else
#pragma comment(lib, "Effekseerd.lib")
#endif
#include <Effekseer.h>

#ifndef _DEBUG
#pragma comment(lib, "EffekseerRendererDX9.lib")
#else
#pragma comment(lib, "EffekseerRendererDX9d.lib")
#endif
#include <EffekseerRendererDX9.h>

//===========================================================
//マクロ定義
//===========================================================
#define SCREEN_WIDTH      (1280)                   //ウインドウに幅
#define SCREEN_HEIGHT     (720)                    //ウインドウの高さ
#define FVF_VERTEX_2D     (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D     (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#endif