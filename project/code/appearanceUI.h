//===========================================================
//
// �G�o�ꎞ��UI[appearanceUI.h]
// Author �匴�叫
//
//===========================================================
#ifndef _APPEARANCEUI_H_
#define _APPEARANCEUI_H_

#include "object.h"

// �O���錾
class CObject2D;
class CNumber;

//*==========================================================
// �N���X��`
//*==========================================================
class CAppearanceUI : CObject
{
public:

	//���
	enum TYPE
	{
		TYPE_NONE = 0,   // �Ȃ���Ȃ�
		TYPE_WEAKNAME,   // �U�R
		TYPE_BOSSNAME,   // �{�X
		TYPE_NUMBER,     // ���U���g
		TYPE_MAX
	};

public:

	CAppearanceUI();                                   // �R���X�g���N�^
	CAppearanceUI(TYPE type);         // �R���X�g���N�^
	~CAppearanceUI();                                  // �f�X�g���N�^

	HRESULT Init(void);                             // ����������
	void Uninit(void);                              // �I������
	void Update(void);                              // �X�V����
	void Draw(void);                                // �`�揈��

	static CAppearanceUI *Create(TYPE type); // ��������

private:
	TYPE m_type;
	CObject2D *m_pFrontObj2D;  // �O�ɏo��F���Z���z
	CObject2D *m_pBackObj2D;   // ���ɏo��F���������
	CObject2D *m_pNumber;
	
};

#endif // !_UIMANAGER_H_