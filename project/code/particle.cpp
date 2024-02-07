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
#include "particle.h"

#include <time.h>

//�}�N����`
#define TYPE_BLOOD    (20)   //���̃p�[�e�B�N��
#define TYPE_GROUND   (10)   //�y���̃p�[�e�B�N��
#define TYPE_CIRCLE   (314)   //�~�`�̃p�[�e�B�N��
#define SPEED    (2.0f)  //�ړ���

//================================================================
//�ÓI�����o�ϐ��錾
//================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;

//================================================================
//�R���X�g���N�^
//================================================================
CParticle::CParticle()
{
	m_fRadius = 0;
	m_nLife = 0;
	m_type = TYPEPAR_NONE;
}

//================================================================
//�R���X�g���N�^
//================================================================
CParticle::CParticle(D3DXVECTOR3 pos, TYPEPAR type)
{
	SetPosition(pos);
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

	CObject::Release();
}

//================================================================
//�|���S���̍X�V����
//================================================================
void CParticle::Update(void)
{
	switch (m_type)
	{
	case TYPEPAR_NONE:
		break;

	case TYPEPAR_BULLET:
		ParticlMove();
		break;

	case TYPEPAR_BLOOD:
		Blood();
		break;

	case TYPEPAR_GROUND:
		Ground();
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
	CRenderer *pRenderer;
	pRenderer = CManager::Getinstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���u�����f�B���O�����Z���v�ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================
//�|���S���̕`�揈��
//================================================================
void CParticle::ParticlMove(void)
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
	D3DXVECTOR3 pos;

	pos = GetPosition();

	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < TYPE_BLOOD; nCnt++)
	{
		float fMove, fRot;

		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;

		m_move.x = sinf(fRot) * fMove;
		m_move.y = cosf(fRot) * fMove;
		m_move.z = cosf(fRot) * fMove;

		CEffect::Create(pos, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_BLOOD);
	}

	SetPosition(pos);
}

//================================================================
//�y���݂����ȃp�[�e�B�N��
//================================================================
void CParticle::Ground(void)
{
	D3DXVECTOR3 pos;

	pos = GetPosition();

	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < TYPE_BLOOD; nCnt++)
	{
		float fPosX, fPosZ, fMove, fRot, fRange;

		fPosX = (float)(rand() % 100);
		fPosZ = (float)(rand() % 100);
		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;
		fRange = (float)(rand() % 10) - D3DX_PI * 2;

		m_move.x = sinf(fRot * fRange) * fMove;
		m_move.y = cosf(fRot * fRange) * fMove;
		m_move.z = cosf(fRot * fRange) * fMove;

		CEffect::Create({ pos.x, 0.0f, pos.z }, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, m_fRadius, 30, CEffect::TYPEEFF_GROUND);
	}

	SetPosition(pos);
}

//================================================================
//���݂����ȃp�[�e�B�N��
//================================================================
void CParticle::Smook(void)
{
	D3DXVECTOR3 pos;

	pos = GetPosition();

	//�����̎��ݒ�
	srand((unsigned int)time(0));

	for (int nCnt = 0; nCnt < TYPE_BLOOD; nCnt++)
	{
		float fPosX, fPosZ, fMove, fRot, fRange;

		fPosX = (float)(rand() % 100);
		fPosZ = (float)(rand() % 100);
		fMove = (float)(rand() % 50) / 100.0f * 8.0f;
		fRot = (float)(rand() % 629 - 314) / 100.0f;
		fRange = (float)(rand() % 10) - D3DX_PI * 2;

		//m_move.x = sinf(fRot * fRange) * fMove;
		m_move.y = cosf(fRot * fRange) * fMove * 2.0f;
		//m_move.z = cosf(fRot * fRange) * fMove;

		if (m_move.y < 0.0f)
		{
			m_move.y *= -1;
		}

		CEffect::Create({ pos.x, 0.0f, pos.z }, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, 10.0f, 30, CEffect::TYPEEFF_SMOOK);
	}

	SetPosition(pos);
}

//================================================================
//�~�`�̃p�[�e�B�N��
//================================================================
void CParticle::Circle(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 pos;
	float fRot;

	//�ʒu�擾
	pos = GetPosition();

	for (int nCnt = 0; nCnt < TYPE_CIRCLE; nCnt++)
	{
		//�����ݒ�
		fRot = ((float)nCnt / (D3DX_PI * 1.0f));

		//�ړ��ʐݒ�
		m_move.x = sinf(fRot) * SPEED;
		m_move.y = cosf(fRot) * SPEED;

		//�G�t�F�N�g�̐���
		CEffect::Create({ pos.x, pos.y + 50.0f, pos.z }, { m_move.x, m_move.y, m_move.z }, { 1.0f, 0.0f, 0.0f, 1.0f }, 3.0f, 30, CEffect::TYPEEFF_CIRCLE);
	}

	//�ʒu�ݒ�
	SetPosition(pos);
}