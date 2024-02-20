//===========================================================
//
// �|���S�����o�����[gage.h]
// Author �匴�叫
//
//===========================================================
#ifndef _GAGE_H_             // ���̃}�N����`������ĂȂ�������
#define _GAGE_H_             // 2�d�C���N���[�h�h�~�̃}�N����`������

#include "object2D.h"
#include "billboard.h"

// �Q�[�W�N���X
class CGage2D : public CObject2D
{
public:

	enum CGAGE2DTYPE
	{
		TYPE_NONE = 0, // �Ȃ���Ȃ�
		TYPE_LIFE,     // �̗�
		TYPE_MAX
	};

	CGage2D();      // �R���X�g���N�^
	~CGage2D();     // �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE2DTYPE type);          // ����������
	HRESULT Init(void);          // ����������
	void Uninit(void);           // �I������
	void Update(void);           // �X�V����
	void Draw(void);             // �`�揈��

	static CGage2D *Create(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE2DTYPE type);      // ����
	void SetSize(float fHeight, float fWidth);                            // �T�C�Y

	CObject2D *GetObj2D(void) { return m_pObject2D; }

private:

	void SetCol(void);

	D3DXVECTOR3 m_pos;        // �ʒu
	D3DXVECTOR3 m_rot;        // ����
	D3DXCOLOR m_col;          // �F
	float m_fHeight;          // ����
	float m_fWidth;           // ��

	CGAGE2DTYPE m_Type;          // ���
	CObject2D *m_pObject2D;    // �I�u�W�F�N�g2D�ւ̃|�C���^
};

// �Q�[�W�N���X
class CGage3D : public CBillBoard
{
public:

	enum CGAGE3DTYPE
	{
		TYPE_NONE = 0, // �Ȃ���Ȃ�
		TYPE_STAMINA,  // �X�^�~�i
		TYPE_LIFE,     // ���C�t
		TYPE_MAX
	};

	CGage3D();      // �R���X�g���N�^
	~CGage3D();     // �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE3DTYPE type);          // ����������
	HRESULT Init(void);          // ����������
	void Uninit(void);           // �I������
	void Update(void);           // �X�V����
	void Draw(void);             // �`�揈��

	static CGage3D *Create(D3DXVECTOR3 pos, float fHei, float fWid, CGAGE3DTYPE type);      // ����
	void SetCurrent(D3DXMATRIX Current) { m_pCurrent = Current; }        // �e�̃}�g���b�N�X
	void SetPos(D3DXVECTOR3 *pPos) { m_pPos = pPos; }
	void SetUpHeight(float fUpHei) { m_UpHeight = fUpHei; }

	CBillBoard *GetBill(void) { return m_pBillBoard; }

private:

	void SetCol(void);
	void SetMixPos(void);

	D3DXVECTOR3 *m_pPos;        // �ʒu
	D3DXVECTOR3 m_rot;        // ����
	D3DXCOLOR m_col;          // �F
	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_pCurrent;
	float m_fHeight;          // ����
	float m_fWidth;           // ��
	float m_UpHeight;

	CGAGE3DTYPE m_Type;          // ���
	CBillBoard *m_pBillBoard;    // �I�u�W�F�N�g2D�ւ̃|�C���^
};

#endif