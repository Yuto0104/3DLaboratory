//=============================================================================
//
// パーツクラス(parts.cpp)
// Author : 唐﨑結斗
// 概要 : パーツ生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "parts.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3Dを生成する
//=============================================================================
CParts * CParts::Create(const int nModelNam)
{
	// オブジェクトインスタンス
	CParts *pParts = nullptr;

	// メモリの解放
	pParts = new CParts;

	// メモリの確保ができなかった
	assert(pParts != nullptr);

	// 数値の初期化
	pParts->Init(nModelNam);

	// インスタンスを返す
	return pParts;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CParts::CParts() : m_pParent(nullptr),			// 親オブジェクトのポインタ
m_posOrigin(D3DXVECTOR3(0.0f,0.0f,0.0f)),		// 元の位置
m_rotOrigin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),		// 元の向き
m_posDest(D3DXVECTOR3(0.0f,0.0f,0.0f)),  		// 目的の位置
m_rotDest(D3DXVECTOR3(0.0f,0.0f,0.0f))			// 目的の向き
{
	
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CParts::~CParts()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CParts::Init(const int nModelNam)
{
	// 初期化
	CModel3D::Init(nModelNam);

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CParts::Uninit()
{
	// 終了
	CModel3D::Uninit();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CParts::Update()
{
	if (!m_pParent->GetFlagDeath())
	{// 更新
		CModel3D::Update();
	}
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CParts::Draw()
{
	if (!m_pParent->GetFlagDeath())
	{
		// 描画
		CModel3D::Draw();

		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
		
		// 自分の情報の取得
		D3DXMATRIX mtxWorld = GetMtxWorld();
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		// 計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans;

		// 行列初期化関数
		D3DXMatrixIdentity(&mtxWorld);

		// 向きの反映( 行列回転関数 )
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		// 行列掛け算関数 
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 位置を反映( 行列移動関数 )
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

		// 行列掛け算関数
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// 親パーツのワールドマトリックスを保持
		D3DXMATRIX mtxParent = m_pParent->GetMtxWorld();

		// 自分の親マトリックスとの掛け算
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// 新規深度値とZバッファの深度値が同じ値ならテスト成功にする
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}
