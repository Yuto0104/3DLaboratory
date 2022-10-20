//=============================================================================
//
// �A�v���P�[�V�����N���X(application.h)
// Author : �������l
// �T�v : �e�N���X�̌Ăяo�����s���N���X
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "application.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "renderer.h"
#include "debug_proc.h"
#include "keyboard.h"
#include "mouse.h"
#include "texture.h"
#include "model_manager.h"
#include "camera_manager.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "model3D.h"
#include "model_manager.h"
#include "motion_model3D.h"
#include "mesh.h"
#include "sphere.h"
#include "player.h"
#include "scene_mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
HWND CApplication::m_hWnd = nullptr;								// �E�B���h�E
CDebugProc *CApplication::m_pDebugProc = nullptr;					// �f�o�b�N�\��
CRenderer *CApplication::m_pRenderer = nullptr;						// �����_���[�C���X�^���X
CKeyboard *CApplication::m_pKeyboard = {};							// �L�[�{�[�h�C���X�^���X
CMouse *CApplication::m_pMouse = {};								// �}�E�X�C���X�^���X
CTexture *CApplication::m_pTexture = nullptr;						// �e�N�X�`���C���X�^���X
CModelManager *CApplication::m_pModelManager = nullptr;				// ���f���}�l�[�W���[�N���X
CCameraManager *CApplication::m_pCameraManager = nullptr;			// �J�����}�l�[�W���[�N���X
CCamera *CApplication::m_pCamera = nullptr;							// �J�����C���X�^���X
CApplication::SCENE_MODE CApplication::m_mode = MODE_GAME;			// ���݂̃��[�h�̊i�[
CApplication::SCENE_MODE CApplication::m_nextMode = MODE_GAME;		// ���̃��[�h�̊i�[
CSceneMode *CApplication::pSceneMode = nullptr;						// �V�[�����[�h���i�[
CFade *CApplication::m_pFade = nullptr;								// �t�F�[�h�N���X
CLight *CApplication::m_pLight = nullptr;							// ���C�g�N���X
int CApplication::m_nPriority = 0;									// �v���C�I���e�B�ԍ�
bool CApplication::m_bWireFrame = false;							// ���C���[�t���[�����g����

//=============================================================================
// �X�N���[�����W�����[���h���W�ɃL���X�g����
// Author : �������l
// �T�v : 
//=============================================================================
D3DXVECTOR3 CApplication::ScreenCastWorld(const D3DXVECTOR3 &pos)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �J�����̃r���[�}�g���b�N�X�̎擾
	mtxView = m_pCamera->GetMtxView();

	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̎擾
	mtxPrj = m_pCamera->GetMtxProj();

	// �}�g���b�N�X�̏�Z
	mtx = mtxTrans * mtxView * mtxPrj;

	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	float w = (float)CRenderer::SCREEN_WIDTH / 2.0f;
	float h = (float)CRenderer::SCREEN_HEIGHT / 2.0f;

	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// �}�g���b�N�X��XYZ
	D3DXVECTOR3 vec = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);

	D3DXVec3TransformCoord(&vec, &vec, &mtxViewPort);

	return vec;
}

//=============================================================================
// ���[���h���W���X�N���[�����W�ɃL���X�g����
// Author : �������l
// �T�v : 
//=============================================================================
D3DXVECTOR3 CApplication::WorldCastScreen(const D3DXVECTOR3 &pos)
{
	// �v�Z�p�x�N�g��
	D3DXVECTOR3 vec = pos;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtx, mtxTrans, mtxView, mtxPrj, mtxViewPort;

	// �s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	// �J�����̃r���[�}�g���b�N�X�̎擾
	mtxView = m_pCamera->GetMtxView();

	// �J�����̃v���W�F�N�V�����}�g���b�N�X�̎擾
	mtxPrj = m_pCamera->GetMtxProj();
	
	// �r���[�|�[�g�s��i�X�N���[���s��j�̍쐬
	D3DXMatrixIdentity(&mtxViewPort);
	float w = (float)CRenderer::SCREEN_WIDTH / 2.0f;
	float h = (float)CRenderer::SCREEN_HEIGHT / 2.0f;
	mtxViewPort = {
		w , 0 , 0 , 0 ,
		0 ,-h , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		w , h , 0 , 1
	};

	// �t�s��̎Z�o
	D3DXMatrixInverse(&mtxView, NULL, &mtxView);
	D3DXMatrixInverse(&mtxPrj, NULL, &mtxPrj);
	D3DXMatrixInverse(&mtxViewPort, NULL, &mtxViewPort);

	// �t�ϊ�
	mtx = mtxViewPort * mtxPrj * mtxView;
	D3DXVec3TransformCoord(&vec, &D3DXVECTOR3(vec.x, vec.y, vec.z), &mtx);

	return vec;
}

//=============================================================================
// �p�x�̐��K������
// Author : �������l
// �T�v : �p�x���~������2�{�𒴂����Ƃ��ɔ͈͓��ɖ߂�
//=============================================================================
float CApplication::RotNormalization(float fRot)
{
	if (fRot >= D3DX_PI)
	{// �ړ������̐��K��
		fRot -= D3DX_PI * 2;
	}
	else if (fRot <= -D3DX_PI)
	{// �ړ������̐��K��
		fRot += D3DX_PI * 2;
	}

	return fRot;
}

//=============================================================================
// �p�x�̐��K������
// Author : �������l
// �T�v : �p�x���~������2�{�𒴂����Ƃ��ɔ͈͓��ɖ߂�
//=============================================================================
float CApplication::RotNormalization(float fRot, float fMin, float fMax)
{
	if (fRot >= fMax)
	{// �ړ������̐��K��
		fRot -= D3DX_PI * 2;
	}
	else if (fRot <= fMin)
	{// �ړ������̐��K��
		fRot += D3DX_PI * 2;
	}

	return fRot;
}

//=============================================================================
// �V�[���̐ݒ�
// Author : �������l
// �T�v : ���݂̃V�[�����I�����A�V�����V�[����ݒ肷��
//=============================================================================
void CApplication::SetMode(SCENE_MODE mode)
{
	if (pSceneMode != nullptr)
	{
		pSceneMode->Uninit();
		pSceneMode = nullptr;
	}

	// �I�u�W�F�N�g�̉��
	CObject::ReleaseAll(false);

	m_mode = mode;

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		pSceneMode = new CTitle;
		break;

	case CApplication::MODE_GAME:
		pSceneMode = new CGame;
		break;

	case CApplication::MODE_RESULT:
		pSceneMode = new CResult;
		break;

	default:
		break;
	}

	if (pSceneMode != nullptr)
	{
		pSceneMode->Init();
	}
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CApplication::CApplication()
{
	// �^�������̏�����
	srand((unsigned int)time(NULL));
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CApplication::~CApplication()
{
	assert(m_pRenderer == nullptr);
	assert(m_pKeyboard == nullptr);
	assert(m_pMouse == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pModelManager == nullptr);
	assert(m_pCameraManager == nullptr);
	assert(m_pCamera == nullptr);
}

//=============================================================================
// ������
// Author : �������l
// �T�v : �����o�ϐ���������A���N���X�̃N���G�C�g�֐����Ăяo��
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �E�B���h�E
	m_hWnd = hWnd;

	// �������̊m��	
	m_pRenderer = new CRenderer;
	m_pDebugProc = new CDebugProc;
	m_pTexture = new CTexture;
	m_pModelManager = new CModelManager;
	m_pCameraManager = new CCameraManager;
	m_pCamera = new CCamera;

	// ���̓f�o�C�X�̃������m��
	m_pKeyboard = new CKeyboard;
	m_pMouse = new CMouse;

	// ����������
	assert(m_pRenderer != nullptr);

	if (FAILED(m_pRenderer->Init(m_hWnd, TRUE)) != 0)
	{//���������������s�����ꍇ
		return-1;
	}

//#ifdef _DEBUG
//	if (FAILED(m_pRenderer->Init(m_hWnd, TRUE)) != 0)
//	{//���������������s�����ꍇ
//		return-1;
//	}
//#else
//	if (FAILED(m_pRenderer->Init(m_hWnd, FALSE)) != 0)
//	{//���������������s�����ꍇ
//		return-1;
//	}
//#endif

	// ����������
	assert(m_pTexture != nullptr);
	m_pTexture->Init();

	// ����������
	assert(m_pModelManager != nullptr);
	m_pModelManager->Init();

	// ����������
	assert(m_pCameraManager != nullptr);
	m_pCameraManager->Init();

	// ����������
	assert(m_pCamera != nullptr);
	m_pCamera->Init();
	m_pCamera->SetViewType(CCamera::TYPE_CLAIRVOYANCE);

	// ������
	assert(m_pDebugProc != nullptr);
	m_pDebugProc->Init();

	// ����������
	assert(m_pKeyboard != nullptr);
	if (FAILED(m_pKeyboard->Init(hInstance, m_hWnd)))
	{
		return E_FAIL;
	}

	// ����������
	assert(m_pMouse != nullptr);
	if (FAILED(m_pMouse->Init(hInstance, m_hWnd)))
	{
		return E_FAIL;
	}

	// ���C�g�̍쐬
	m_pLight = CLight::Create(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �V�[�����[�h�̐ݒ�
	SetMode(CApplication::MODE_TITLE);

	// �t�F�[�h�̐ݒ�
	m_pFade = CFade::Create();

	return S_OK;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �������̉���ƃ����[�X�֐����Ăяo��
//=============================================================================
void CApplication::Uninit()
{
	// �I�u�W�F�N�g�̉��
	CObject::ReleaseAll(true);

	if (m_pRenderer != nullptr)
	{// �I������
		m_pRenderer->Uninit();

		// �������̉��
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{// �I������
		m_pDebugProc->Uninit();

		// �������̉��
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{// �I������
		m_pKeyboard->Uninit();

		// �������̉��
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pMouse != nullptr)
	{// �I������
		m_pMouse->Uninit();

		// �������̉��
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->Uninit();

		// �������̉��
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pModelManager != nullptr)
	{// �I������
		m_pModelManager->Uninit();

		// �������̉��
		delete m_pModelManager;
		m_pModelManager = nullptr;
	}

	if (m_pCameraManager != nullptr)
	{// �I������
		m_pCameraManager->Uninit();

		// �������̉��
		delete m_pCameraManager;
		m_pCameraManager = nullptr;
	}

	if (m_pCamera != nullptr)
	{// �I������
		m_pCamera->Uninit();

		// �������̉��
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ���C�g�̉��
	CLight::ReleaseAll();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : �X�V
//=============================================================================
void CApplication::Update()
{
	if (m_nextMode != MODE_NONE)
	{
		m_pFade->SetFade(m_nextMode);
		m_nextMode = MODE_NONE;
	}

	CDebugProc::Print("FPS : %d\n", GetFps());
	CDebugProc::Print("���݂̃V�[�� : %d\n", (int)m_mode);

	m_pKeyboard->Update();
	m_pMouse->Update();
	m_pCamera->Update();

	m_pRenderer->Update();

#ifdef _DEBUG
	if (m_pKeyboard->GetTrigger(DIK_F2))
	{
		m_bWireFrame ^= 1;
	}

	if (m_bWireFrame)
	{
		m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	//if (m_pMouse->GetTrigger(CMouse::MOUSE_KEY_LEFT))
	//{
	//	CObject2D *pObject2D = CObject2D::Create(m_nPriority);
	//	pObject2D->SetPos(D3DXVECTOR3(m_pMouse->GetMouseCursor()));
	//	pObject2D->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//	pObject2D->LoadTex(0);
	//}

	//if (m_pKeyboard->GetTrigger(DIK_UP))
	//{
	//	m_nPriority++;

	//	if (m_nPriority >= CObject::MAX_LEVEL)
	//	{
	//		m_nPriority = 0;
	//	}
	//}
	//if (m_pKeyboard->GetTrigger(DIK_DOWN))
	//{
	//	m_nPriority--;

	//	if (m_nPriority < 0)
	//	{
	//		m_nPriority = CObject::MAX_LEVEL - 1;
	//	}
	//}

	//if (m_pKeyboard->GetTrigger(DIK_F3))
	//{// �J�����̒Ǐ]�ݒ�(�ڕW : �v���C���[)
	//	
	//}
	//if (m_pKeyboard->GetTrigger(DIK_F4))
	//{
	//	CObject::ReleaseCurrent(m_nPriority);
	//}
	//if (m_pKeyboard->GetTrigger(DIK_F5))
	//{
	//	CObject::RandomRelease(m_nPriority);
	//}

	//CDebugProc::Print("���݂�PriorityLevel : %d\n", m_nPriority);
#endif // DEBUG
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`��
//=============================================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();
}