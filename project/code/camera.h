//=============================================================================
//
// �J�������� [camera.h]
// Author : �匴�@�叫
//
//=============================================================================

#ifndef _CAMERA_H_             //���̃}�N����`������ĂȂ�������
#define _CAMERA_H_             //2�d�C���N���[�h�h�~�̃}�N����`������

#include "main.h"

//�J�����N���X
class CCamera
{
public:
	CCamera();
	~CCamera();

	enum MODE
	{
		MODE_NONE = 0,
		MODE_TITLE,      // �^�C�g���̃J����
		MODE_GAME,       // �Q�[���̃J����
		MODE_RESULT,     // ���U���g�̃J����
		MODE_HEAT,       // �q�[�g�A�N�V����
		MODE_RETURN,     // ���̈ʒu�ɖ߂�
		MODE_MAX 
	};

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_HEAT,
		TYPE_MAX
	};

	void Init(void);          //�J�����̏���������    
	void Uninit(void);        //�J�����̏I������
	void Update(void);        //�J�����̍X�V����
	void CameraV(void);
	void Edit(void);          //�G�f�B�b�g�̃J����
	void CameraR(void);
	void Title(void);
	void Scope(void);
	void SetCamera(void);
	void Reset(void);

	void Boss(void);

	// �ݒ�n
	void SetMode(MODE type) { m_mode = type; }
	void SetPositionR(D3DXVECTOR3 pos);
	void SetPositionV(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 Rot);

	// �擾�n
	MODE GetMode(void) { return m_mode; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:
	void Mode(void);
	void Heat(void);
	void Return(void);

	D3DXMATRIX m_mtxView;        // �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;  // �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;          // ���_
	D3DXVECTOR3 m_OldposV;       // �O��̎��_�̈ʒu
	D3DXVECTOR3 m_posR;          // �����_
	D3DXVECTOR3 m_OldposR;       // �O��̒����_�̈ʒu
	D3DXVECTOR3 m_posU;          // ������x�N�g��
	D3DXVECTOR3 m_posVDest;      // �ړI�̎��_
	D3DXVECTOR3 m_posRDest;      // �ړI�̒����_
	D3DXVECTOR3 m_rot;           // ����
	D3DXVECTOR3 m_Oldrot;        // �O��̌��� 
	D3DXVECTOR3 m_move;          // �ړ�

	MODE m_mode;

	int m_nCounter;     //�J�������؂�ւ���Ă��鎞��
};



#endif
