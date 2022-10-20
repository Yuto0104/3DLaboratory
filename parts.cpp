//=============================================================================
//
// �p�[�c�N���X(parts.cpp)
// Author : �������l
// �T�v : �p�[�c�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "parts.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CParts * CParts::Create(const int nModelNam)
{
	// �I�u�W�F�N�g�C���X�^���X
	CParts *pParts = nullptr;

	// �������̉��
	pParts = new CParts;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pParts != nullptr);

	// ���l�̏�����
	pParts->Init(nModelNam);

	// �C���X�^���X��Ԃ�
	return pParts;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CParts::CParts() : m_pParent(nullptr),			// �e�I�u�W�F�N�g�̃|�C���^
m_posOrigin(D3DXVECTOR3(0.0f,0.0f,0.0f)),		// ���̈ʒu
m_rotOrigin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		// ���̌���
m_posDest(D3DXVECTOR3(0.0f,0.0f,0.0f)),  		// �ړI�̈ʒu
m_rotDest(D3DXVECTOR3(0.0f,0.0f,0.0f))			// �ړI�̌���
{
	
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CParts::~CParts()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CParts::Init(const int nModelNam)
{
	// ������
	CModel3D::Init(nModelNam);

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CParts::Uninit()
{
	// �I��
	CModel3D::Uninit();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CParts::Update()
{
	if (!m_pParent->GetFlagDeath())
	{// �X�V
		CModel3D::Update();
	}
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CParts::Draw()
{
	if (!m_pParent->GetFlagDeath())
	{
		// �`��
		CModel3D::Draw();

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
		
		// �����̏��̎擾
		D3DXMATRIX mtxWorld = GetMtxWorld();
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

		// �s�񏉊����֐�
		D3DXMatrixIdentity(&mtxWorld);

		// �����̔��f( �s���]�֐� )
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		// �s��|���Z�֐� 
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ʒu�𔽉f( �s��ړ��֐� )
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// �e�p�[�c�̃��[���h�}�g���b�N�X��ێ�
		D3DXMATRIX mtxParent = m_pParent->GetMtxWorld();

		// �����̐e�}�g���b�N�X�Ƃ̊|���Z
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}
