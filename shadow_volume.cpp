//=============================================================================
//
// �V���h�E�{�����[���N���X(shadow_volume.h)
// Author : �������l
// �T�v : �V���h�E�{�����[���������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "shadow_volume.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : �V���h�E�{�����[���𐶐�����
//=============================================================================
CShadowVolume *CShadowVolume::Create(void)
{
	// �I�u�W�F�N�g�C���X�^���X
	CShadowVolume *pShadowVolume = nullptr;

	// �������̉��
	pShadowVolume = new CShadowVolume;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pShadowVolume != nullptr);

	// ���l�̏�����
	pShadowVolume->Init();

	// �C���X�^���X��Ԃ�
	return pShadowVolume;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CShadowVolume::CShadowVolume()
{
	m_pVtxBuff = nullptr;								// ���_�o�b�t�@
	m_mtxWorld = {};									// ���[���h�}�g���b�N�X
	m_vtxPosA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuA
	m_vtxPosB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuB
	m_vtxPosC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuC
	m_vtxPosD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuD
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CShadowVolume::~CShadowVolume()
{

}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CShadowVolume::Init()
{// �����_���[�̃Q�b�g
	CRenderer *pRenderer = CApplication::GetRenderer();

	//���_�o�b�t�@�̐���
	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,		// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														// ���_�t�@�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_vtxPosA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuA
	m_vtxPosB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuB
	m_vtxPosC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuC
	m_vtxPosD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���_�ʒuD

	// ���_���W�Ȃǂ̐ݒ�
	SetVtx();

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CShadowVolume::Uninit()
{
	//���_�o�b�t�@��j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g3D�̉��
	Release();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CShadowVolume::Update()
{
	
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : 2D�`����s��
//=============================================================================
void CShadowVolume::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���W�Ȃǂ̐ݒ�
// Author : �������l
// �T�v : 3D���_���W�Arhw�A���_�J���[��ݒ肷��
//=============================================================================
void CShadowVolume::SetVtx()
{
	//���_���ւ̃|�C���^�𐶐�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = m_vtxPosA;
	pVtx[1].pos = m_vtxPosB;
	pVtx[2].pos = m_vtxPosC;
	pVtx[3].pos = m_vtxPosD;

	// �e���_�̖@���̐ݒ�(*�x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_�ʒu�̐ݒ�
// Author : �������l
// �T�v : ���_�ʒu��ݒ肷��
//=============================================================================
void CShadowVolume::SetVtxPos(D3DXVECTOR3 vtxPosA, D3DXVECTOR3 vtxPosB, D3DXVECTOR3 vtxPosC, D3DXVECTOR3 vtxPosD)
{
	m_vtxPosA = vtxPosA;			// ���_�ʒuA
	m_vtxPosB = vtxPosB;			// ���_�ʒuB
	m_vtxPosC = vtxPosC;			// ���_�ʒuC
	m_vtxPosD = vtxPosD;			// ���_�ʒuD

	SetVtx();
}
