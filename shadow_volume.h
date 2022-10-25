//=============================================================================
//
// �V���h�E�{�����[���N���X(shadow_volume.h)
// Author : �������l
// �T�v : �V���h�E�{�����[���������s��
//
//=============================================================================
#ifndef _SHADOW_VOLUME_H_		// ���̃}�N����`������ĂȂ�������
#define _SHADOW_VOLUME_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "texture.h"

//=============================================================================
// �V���h�E�{�����[���N���X
// Author : �������l
// �T�v : �V���h�E�{�����[���������s���N���X
//=============================================================================
class CShadowVolume : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);

	//*****************************************************************************
	// �\���̒�`
	//*****************************************************************************
	// ���_�f�[�^
	typedef struct
	{
		D3DXVECTOR3			pos;			// ���_���W
		D3DXVECTOR3			nor;			// �@���x�N�g��
		D3DCOLOR			col;			// ���_�J���[
	}VERTEX_3D;

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CShadowVolume *Create(void);				// 2D�I�u�W�F�N�g�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CShadowVolume();
	~CShadowVolume();

	//--------------------------------------------------------------------
	// �I�[�o�[���C�h�֐�
	//--------------------------------------------------------------------
	HRESULT Init() override;																				// ������
	void Uninit() override;																					// �I��
	void Update() override;																					// �X�V
	void Draw() override;																					// �`��
	void SetPos(const D3DXVECTOR3 &pos) override {}															// �ʒu�̃Z�b�^�[
	void SetPosOld(const D3DXVECTOR3 &posOld) override {}													// �ߋ��ʒu�̃Z�b�^�[
	void SetRot(const D3DXVECTOR3 &rot) override {}															// �����̃Z�b�^�[
	void SetSize(const D3DXVECTOR3 &size) override {}														// �傫���̃Z�b�^�[
	D3DXVECTOR3 GetPos() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }									// �ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetPosOld()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }								// �ߋ��ʒu�̃Q�b�^�[
	D3DXVECTOR3 GetRot()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }								// �����̃Q�b�^�[
	D3DXVECTOR3 GetSize()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }								// �傫���̃Q�b�^�[
	void SetVtx();																							// ���_���W�Ȃǂ̐ݒ�
	void SetVtxPos(D3DXVECTOR3 vtxPosA, D3DXVECTOR3 vtxPosB, D3DXVECTOR3 vtxPosC, D3DXVECTOR3 vtxPosD);		// ���_�ʒu�̐ݒ�

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			// ���_�o�b�t�@
	D3DXMATRIX					m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_vtxPosA;			// ���_�ʒuA
	D3DXVECTOR3					m_vtxPosB;			// ���_�ʒuB
	D3DXVECTOR3					m_vtxPosC;			// ���_�ʒuC
	D3DXVECTOR3					m_vtxPosD;			// ���_�ʒuD
};

#endif




