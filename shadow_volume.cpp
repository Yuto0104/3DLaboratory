//=============================================================================
//
// シャドウボリュームクラス(shadow_volume.h)
// Author : 唐﨑結斗
// 概要 : シャドウボリューム生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "shadow_volume.h"
#include "renderer.h"
#include "application.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : シャドウボリュームを生成する
//=============================================================================
CShadowVolume *CShadowVolume::Create(void)
{
	// オブジェクトインスタンス
	CShadowVolume *pShadowVolume = nullptr;

	// メモリの解放
	pShadowVolume = new CShadowVolume;

	// メモリの確保ができなかった
	assert(pShadowVolume != nullptr);

	// 数値の初期化
	pShadowVolume->Init();

	// インスタンスを返す
	return pShadowVolume;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CShadowVolume::CShadowVolume()
{
	m_pVtxBuff = nullptr;								// 頂点バッファ
	m_mtxWorld = {};									// ワールドマトリックス
	m_vtxPosA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置A
	m_vtxPosB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置B
	m_vtxPosC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置C
	m_vtxPosD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置D
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CShadowVolume::~CShadowVolume()
{

}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CShadowVolume::Init()
{// レンダラーのゲット
	CRenderer *pRenderer = CApplication::GetRenderer();

	//頂点バッファの生成
	pRenderer->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,		// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,														// 頂点ファーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_vtxPosA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置A
	m_vtxPosB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置B
	m_vtxPosC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置C
	m_vtxPosD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 頂点位置D

	// 頂点座標などの設定
	SetVtx();

	return S_OK;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CShadowVolume::Uninit()
{
	//頂点バッファを破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();

		m_pVtxBuff = nullptr;
	}

	// オブジェクト3Dの解放
	Release();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CShadowVolume::Update()
{
	
}

//=============================================================================
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//=============================================================================
void CShadowVolume::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&m_mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 頂点座標などの設定
// Author : 唐﨑結斗
// 概要 : 3D頂点座標、rhw、頂点カラーを設定する
//=============================================================================
void CShadowVolume::SetVtx()
{
	//頂点情報へのポインタを生成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = m_vtxPosA;
	pVtx[1].pos = m_vtxPosB;
	pVtx[2].pos = m_vtxPosC;
	pVtx[3].pos = m_vtxPosD;

	// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 頂点位置の設定
// Author : 唐﨑結斗
// 概要 : 頂点位置を設定する
//=============================================================================
void CShadowVolume::SetVtxPos(D3DXVECTOR3 vtxPosA, D3DXVECTOR3 vtxPosB, D3DXVECTOR3 vtxPosC, D3DXVECTOR3 vtxPosD)
{
	m_vtxPosA = vtxPosA;			// 頂点位置A
	m_vtxPosB = vtxPosB;			// 頂点位置B
	m_vtxPosC = vtxPosC;			// 頂点位置C
	m_vtxPosD = vtxPosD;			// 頂点位置D

	SetVtx();
}
