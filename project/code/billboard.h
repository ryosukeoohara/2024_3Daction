//=============================================================================
//
// �E�H�[������ [billboard.h]
// Author : �匴�@�叫
//
//=============================================================================

#ifndef _BILLBOARD_H_             //���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "main.h"
#include "object.h"

//�r���{�[�h�N���X
class CBillBoard : public CObject
{
public:
	CBillBoard();
	~CBillBoard();

	HRESULT Init(void);  // ����������    
	void Uninit(void);   // �I������
	void Update(void);   // �X�V����
	void Draw(void);     // �`�揈��
	 
	static CBillBoard *Create(void);  //����

	void SetCurrent(D3DXMATRIX *Current) { m_pCurrent = Current; }        // �e�̃}�g���b�N�X
	void SetSize(float fHeight, float fWidth);                            // �T�C�Y
	void SetTex(float fTex);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }                    // �ʒu
	void SetRotition(D3DXVECTOR3 rot) { m_rot = rot; }                    // ����
	void SetColor(D3DXCOLOR col);                                         // �F
	void SetDraw(bool bDraw = true) { m_bDraw = bDraw; }                  // �`�悷�邩�ǂ���

private:
	LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxView;
	D3DXMATRIX m_mtxWorld;                     // ���[���h�}�g���b�N�X
	D3DXMATRIX *m_pCurrent;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;        // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;                         // �ʒu
	D3DXVECTOR3 m_rot;                         // ����
	D3DXCOLOR m_col;                           // �F
	int m_nIdxTexture;                         // �e�N�X�`���̃C���f�b�N�X�ԍ�
	float m_fHeight;                           // ����
	float m_fWidth;                            // ��
	bool m_bDraw;                              // �`�悷�邩�ǂ���
};


#endif