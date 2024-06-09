//===========================================================
//
// �G�t�F�N�V�A[MyEffekseer.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFEKSEER_H_     //���̃}�N������`����ĂȂ�������
#define _EFFEKSEER_H_     //2�d�C���N���[�h��h�~�̃}�N�����`����

#define MAX_EFK   (64)

class CMyEffekseer
{
public:
	CMyEffekseer();
	~CMyEffekseer();

	// ���
	enum TYPE
	{
		TYPE_NONE = 0,  // �Ȃ���Ȃ�
		TYPE_ORBIT,     // �O��
		TYPE_IMPACT,    // �Ռ��g
		TYPE_HIT,       // �q�b�g
		TYPE_LASER,     // ���[�U�[
		TYPE_MAX
	};

	// ���
	struct Info
	{
		Effekseer::Vector3D pos;       // �ʒu
		Effekseer::Vector3D rot;       // ����
		Effekseer::Vector3D scale;     // �傫��
		Effekseer::EffectRef effect;   // �G�t�F�N�g
		Effekseer::Handle efkHandle;   // �n���h��
		const char* EfkName;           // ���O
		int32_t time;                  // ����
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

	// �����o�ϐ� 
	Info m_Info[MAX_EFK];
	EffekseerRendererDX9::RendererRef m_EfkRenderer;
	::Effekseer::Matrix44 m_CameraMatrix;
	::Effekseer::Matrix44 m_ProjectionMatrix;
	::Effekseer::ManagerRef m_EfkManager;
	::Effekseer::Vector3D m_ViewerPosition;
	int m_nNum;
};

#endif