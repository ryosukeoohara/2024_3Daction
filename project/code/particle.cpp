//===========================================================
//
//�|���S�����o�����[particl.cpp]
//Author �匴�叫
//
//===========================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "effect.h"
#include "effect3D.h"
#include "particle.h"

#include <time.h>

//�}�N����`
#define BLOOD    (1)     //���̃p�[�e�B�N��
#define GROUND   (20)    //�y���̃p�[�e�B�N��
#define CIRCLE   (314)   //�~�`�̃p�[�e�B�N��
#define SPEED    (10.0f)  //�ړ���

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CParticle::CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 0;
	m_nLife = 0;
}

//================================================================
//�R���X�g���N�^
//================================================================
CParticle::CParticle(D3DXVECTOR3 pos, TYPEPAR type)
{
	m_pos = pos;
	m_fRadius = 0;
	m_nLife = 0;
	m_type = type;
}

//================================================================
//�f�X�g���N�^
//================================================================
CParticle::~CParticle()
{

}

//================================================================
//��������
//================================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, TYPEPAR type)
{
	//�I�u�W�F�N�g2D�̃|�C���^
	CParticle *pParticl = NULL;

	if (pParticl == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pParticl = new CParticle(pos, type);

		//����������
		pParticl->Init();
	}
	
	return pParticl;
}

//================================================================
//�|���S���̏���������
//================================================================
HRESULT CParticle::Init(void)
{
	return S_OK;
}

//================================================================
//�|���S���̏I������
//================================================================
void CParticle::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CParticle::Update(void)
{
	switch (m_type)
	{
	case TYPEPAR_GROUND:
		Ground();
		break;

	case TYPEPAR_BLOOD:
		Blood();
		break;

	case TYPEPAR_SMOOK:
		Smook();
		break;

	case TYPEPAR_CIRCLE:
		Circle();
		break;
	}

	m_nLife--;

	if (m_nLife <= 0)
	{
		//�I������
		CParticle::Uninit();
	}
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CParticle::Draw(void)
{
	
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CParticle::Move(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

		//CEffect::Create(pos, { m_move.x, m_move.y, m_move.z }, { 0.8f, 1.0f, 1.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_NONE);
	}
}

//================================================================
//���t�̃p�[�e�B�N��
//================================================================
void CParticle::Blood(void)
{
	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < BLOOD; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

 		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\tier.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\basket.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\handle.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\pedal.x");
		CEffect3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(m_move.x, m_move.y + 10.0f, m_move.z), D3DXVECTOR3(fRot, fRot, fRot), 60, CEffect3D::TYPE_BLOOD, "data\\MODEL\\bike\\tier.x");
	}
}

//================================================================
//�y���݂����ȃp�[�e�B�N��
//================================================================
void CParticle::Ground(void)
{
	float fRot = 0.0f;

	for (int nCnt = 0; nCnt < GROUND; nCnt++)
	{
		// �����ݒ�
		fRot = ((float)nCnt / (D3DX_PI * 1.0f));

		// �ړ��ʐݒ�
		m_move.x = sinf(fRot) * SPEED;
		m_move.z = cosf(fRot) * SPEED;

		CEffect::Create({ m_pos.x, 0.0f, m_pos.z }, { m_move.x, 0.0f, m_move.z }, { 1.0f, 1.0f, 1.0f, 0.8f }, 50.0f, 30, CEffect::TYPE_GROUND);
	}
}

//================================================================
//���݂����ȃp�[�e�B�N��
//================================================================
void CParticle::Smook(void)
{
	
}

//================================================================
//�~�`�̃p�[�e�B�N��
//================================================================
void CParticle::Circle(void)
{
	
}