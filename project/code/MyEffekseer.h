//===========================================================
//
// エフェクシア[MyEffekseer.h]
// Author 大原怜将
//
//===========================================================
#ifndef _EFFEKSEER_H_     //このマクロが定義されてなかったら
#define _EFFEKSEER_H_     //2重インクルードを防止のマクロを定義する

#define MAX_EFK   (64)

class CMyEffekseer
{
public:
	CMyEffekseer();
	~CMyEffekseer();

	// 種類
	enum TYPE
	{
		TYPE_NONE = 0,  // なんもない
		TYPE_ORBIT,     // 軌跡
		TYPE_IMPACT,    // 衝撃波
		TYPE_HIT,       // ヒット
		TYPE_LASER,     // レーザー
		TYPE_MAX
	};

	// 情報
	struct Info
	{
		Effekseer::Vector3D pos;       // 位置
		Effekseer::Vector3D rot;       // 向き
		Effekseer::Vector3D scale;     // 大きさ
		Effekseer::EffectRef effect;   // エフェクト
		Effekseer::Handle efkHandle;   // ハンドル
		const char* EfkName;           // 名前
		int32_t time;                  // 時間
	};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(const char* FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale);

	::EffekseerRendererDX9::RendererRef GetEffekseerRenderer(void) { return m_EfkRenderer; }
	::Effekseer::ManagerRef GetEfkManager(void) { return m_EfkManager; }
	void SetupEffekseerModules(::Effekseer::ManagerRef efkManager);

	void Release(int idx);

	static const char* m_apEfkName[CMyEffekseer::TYPE_MAX];

private:

	// メンバ変数 
	Info m_Info[MAX_EFK];
	EffekseerRendererDX9::RendererRef m_EfkRenderer;
	::Effekseer::Matrix44 m_CameraMatrix;
	::Effekseer::Matrix44 m_ProjectionMatrix;
	::Effekseer::ManagerRef m_EfkManager;
	::Effekseer::Vector3D m_ViewerPosition;
	int m_nNum;
};

#endif