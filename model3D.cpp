//=============================================================================
//
// 3Dモデルクラス(model3D.h)
// Author : 唐﨑結斗
// 概要 : 3Dモデル生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "model3D.h"
#include "renderer.h"
#include "application.h"
#include "model_manager.h"
#include "texture.h"
#include "light.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 3Dモデルを生成する
//=============================================================================
CModel3D * CModel3D::Create(const int nModelNam)
{
	// オブジェクトインスタンス
	CModel3D *pModel3D = nullptr;

	// メモリの解放
	pModel3D = new CModel3D;

	// メモリの確保ができなかった
	assert(pModel3D != nullptr);

	// 数値の初期化
	pModel3D->Init(nModelNam);

	// インスタンスを返す
	return pModel3D;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CModel3D::CModel3D()
{
	memset(&m_material, 0, sizeof(MODEL_MATERIAL));				// マテリアル情報
	m_mtxWorld = {};											// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;					// 過去位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;						// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;					// 大きさ
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CModel3D::~CModel3D()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CModel3D::Init()
{
	// メンバ変数の初期化
	memset(&m_material, 0, sizeof(MODEL_MATERIAL));				// マテリアル情報
	m_mtxWorld = {};											// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 過去位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 向き
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);						// 大きさ

	return S_OK;
}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CModel3D::Init(const int nModelNam)
{
	// モデルマネージャークラスの設定
	CModelManager *pModelManager = CApplication::GetModelManager();

	// メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 過去位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// 大きさ

	// モデルのマテリアル情報の設定
	m_material = pModelManager->GetModelMateria(nModelNam);
	
	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CModel3D::Uninit()
{
	// オブジェクト3Dの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CModel3D::Update()
{

}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CModel3D::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// テクスチャポインタの取得
	CTexture *pTexture = CApplication::GetTexture();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);											// 行列初期化関数

	// サイズの反映
	D3DXMatrixScaling(&mtxScaling, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScaling);					// 行列掛け算関数

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);			// 行列回転関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);						// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);				// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);					// 行列掛け算関数

	// 影の生成
	Shadow();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	if (m_material.pBuffer != nullptr)
	{// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_material.pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_material.nNumMat; nCntMat++)
		{// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetTexture(m_material.pNumTex[nCntMat]));

			// モデルパーツの描画
			m_material.pMesh->DrawSubset(nCntMat);

			// テクスチャの設定
			pDevice->SetTexture(0, nullptr);
		}
	}

	// 保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置のセッター
// Author : 唐﨑結斗
// 概要 : 位置のメンバ変数に引数を代入
//=============================================================================
void CModel3D::SetPos(const D3DXVECTOR3 &pos)
{
	// 位置の設定
	m_pos = pos;
}

//=============================================================================
// 向きのセッター
// Author : 唐﨑結斗
// 概要 : 向きのメンバ変数に引数を代入
//=============================================================================
void CModel3D::SetRot(const D3DXVECTOR3 &rot)
{
	// 位置の設定
	m_rot = rot;
}

//=============================================================================
// 大きさのセッター
// Author : 唐﨑結斗
// 概要 : 大きさのメンバ変数に引数を代入
//=============================================================================
void CModel3D::SetSize(const D3DXVECTOR3 & size)
{
	// 大きさの設定
	m_size = size;
}

//=============================================================================
// 影の生成
// Author : 唐﨑結斗
// 概要 : モデルの影を生成する
//=============================================================================
void CModel3D::Shadow()
{
	// 変数宣言
	MODEL_MATERIAL	materialShadow = m_material;									// 影のマテリアル情報
	D3DXMATRIX		mtxShadow = {};													// シャドウマトリックス
	D3DXPLANE		planeField = {};												// 平面化用変数
	D3DXVECTOR4		vecLight = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);					// ライト方向の逆ベクトル
	D3DXVECTOR3		posShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);;						// 影の位置
	D3DXVECTOR3		norShadow = D3DXVECTOR3(0.0f, 1.0f, 0.0f);;						// 影の法線
	D3DXVECTOR3		lightVec = CApplication::GetLight()->GetLightVec()  * -1;		// ライト方向

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);	// 行列初期化関数

	// ライト方向の逆ベクトルの設定
	vecLight = D3DXVECTOR4(lightVec.x, lightVec.y, lightVec.z, 0.0f);

	// 平面化用変数の設定
	D3DXPlaneFromPointNormal(&planeField, &posShadow, &norShadow);

	// シャドウマトリックスの設定
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// 行列掛け算関数
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// シャドウマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// 現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	if (materialShadow.pBuffer != nullptr)
	{// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)materialShadow.pBuffer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)materialShadow.nNumMat; nCntMat++)
		{// マテリアル情報の設定
			D3DMATERIAL9  matD3D = pMat[nCntMat].MatD3D;

			// 引数を色に設定
			matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			// マテリアルの設定
			pDevice->SetMaterial(&matD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, nullptr);

			// モデルパーツの描画
			materialShadow.pMesh->DrawSubset(nCntMat);
		}
	}

	// 保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
