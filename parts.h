//=============================================================================
//
// �p�[�c�N���X(parts.h)
// Author : �������l
// �T�v : �p�[�c�������s��
//
//=============================================================================
#ifndef _PARTS_H_			// ���̃}�N����`������ĂȂ�������
#define _PARTS_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "model3D.h"
#include "main.h"

//=============================================================================
// �p�[�c�N���X
// Author : �������l
// �T�v : �p�[�c�������s���N���X
//=============================================================================
class CParts : public CModel3D
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CParts *Create(const int nModelNam);			// �p�[�c�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CParts();
	~CParts();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init(const int nModelNam) override;										// ������
	void Uninit() override;															// �I��
	void Update() override;															// �X�V
	void Draw() override;															// �`��
	void SetParent(CModel3D *pParent) { m_pParent = pParent; }						// �e���f���̐ݒ�
	void SetPosDest(const D3DXVECTOR3 posDest) { m_posDest = posDest; }				// �ړI�̈ʒu�̐ݒ�
	void SetRotDest(const D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }				// �ړI�̌����̐ݒ�
	void SetPosOrigin(const D3DXVECTOR3 posOrigin) { m_posOrigin = posOrigin; }		// ���̈ʒu�̐ݒ�
	void SetRotOrigin(const D3DXVECTOR3 rotOrigin) { m_rotOrigin = rotOrigin; }		// ���̌����̐ݒ�
	D3DXVECTOR3 GetPosDest() { return  m_posDest; }									// �ړI�̈ʒu�̎擾
	D3DXVECTOR3 GetRotDest() { return  m_rotOrigin; }								// �ړI�̌����̎擾
	D3DXVECTOR3 GetPosOrigin() { return  m_posOrigin; }								// ���̈ʒu�̎擾
	D3DXVECTOR3 GetRotOrigin() { return  m_rotOrigin; }								// ���̌����̎擾

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CModel3D *m_pParent;			// �e�I�u�W�F�N�g�̃|�C���^
	D3DXVECTOR3 m_posOrigin;		// ���̈ʒu
	D3DXVECTOR3 m_rotOrigin;		// ���̌���
	D3DXVECTOR3 m_posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
};

#endif