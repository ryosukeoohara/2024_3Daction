//===========================================================
//
//�|���S�����o�����[particle.h]
//Author �匴�叫
//
//===========================================================
#ifndef _PARTICLE_H__             //���̃}�N����`������ĂȂ�������
#define _PARTICLE_H__             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "billboard.h"

//�}�N����`
#define EFFECTMOVE   (5.0f)    //�G�t�F�N�g�̍ő吔

//�p�[�e�B�N���N���X
class CParticle
{
public:

	enum TYPEPAR
	{
		TYPEPAR_GROUND = 0,  // �y��
		TYPEPAR_BLOOD,       // ���t
		TYPEPAR_SMOOK,       // ��
		TYPEPAR_CIRCLE,      // �~�`
		TYPEPAR_MAX
	};

	CParticle();  //�R���X�g���N�^
	CParticle(D3DXVECTOR3 pos, TYPEPAR type);  //�R���X�g���N�^
	~CParticle();  //�f�X�g���N�^

	HRESULT Init(void); //Bg�̏���������    
	void Uninit(void);  //Bg�̏I������
	void Update(void);  //Bg�̍X�V����
	void Draw(void);    //Bg�̕`�揈��

	static HRESULT Load(void);  //�e�N�X�`���̐���(�ǂݍ���)
	static void UnLoad(void);   //�e�N�X�`���̔j��

	void Move(void);
	void Blood(void);
	void Ground(void);
	void Smook(void);
	void Circle(void);

	static CParticle *Create(D3DXVECTOR3 pos, TYPEPAR type);  //����
	D3DXCOLOR m_col;          //�F
	float m_fRadius;          //���a(�傫��)
	int m_nLife;              //����(�\������)
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;  //�e�N�X�`���ւ̃|�C���^
	TYPEPAR m_type;

};

#endif