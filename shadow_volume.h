//=============================================================================
//
// シャドウボリュームクラス(shadow_volume.h)
// Author : 唐﨑結斗
// 概要 : シャドウボリューム生成を行う
//
//=============================================================================
#ifndef _SHADOW_VOLUME_H_		// このマクロ定義がされてなかったら
#define _SHADOW_VOLUME_H_		// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include "texture.h"

//=============================================================================
// シャドウボリュームクラス
// Author : 唐﨑結斗
// 概要 : シャドウボリューム生成を行うクラス
//=============================================================================
class CShadowVolume : public CObject
{
public:
	// 頂点フォーマット
	const unsigned int	FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);

	//*****************************************************************************
	// 構造体定義
	//*****************************************************************************
	// 頂点データ
	typedef struct
	{
		D3DXVECTOR3			pos;			// 頂点座標
		D3DXVECTOR3			nor;			// 法線ベクトル
		D3DCOLOR			col;			// 頂点カラー
	}VERTEX_3D;

	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CShadowVolume *Create(void);				// 2Dオブジェクトの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CShadowVolume();
	~CShadowVolume();

	//--------------------------------------------------------------------
	// オーバーライド関数
	//--------------------------------------------------------------------
	HRESULT Init() override;																				// 初期化
	void Uninit() override;																					// 終了
	void Update() override;																					// 更新
	void Draw() override;																					// 描画
	void SetPos(const D3DXVECTOR3 &pos) override {}															// 位置のセッター
	void SetPosOld(const D3DXVECTOR3 &posOld) override {}													// 過去位置のセッター
	void SetRot(const D3DXVECTOR3 &rot) override {}															// 向きのセッター
	void SetSize(const D3DXVECTOR3 &size) override {}														// 大きさのセッター
	D3DXVECTOR3 GetPos() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }									// 位置のゲッター
	D3DXVECTOR3 GetPosOld()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }								// 過去位置のゲッター
	D3DXVECTOR3 GetRot()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }								// 向きのゲッター
	D3DXVECTOR3 GetSize()  override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }								// 大きさのゲッター
	void SetVtx();																							// 頂点座標などの設定
	void SetVtxPos(D3DXVECTOR3 vtxPosA, D3DXVECTOR3 vtxPosB, D3DXVECTOR3 vtxPosC, D3DXVECTOR3 vtxPosD);		// 頂点位置の設定

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;			// 頂点バッファ
	D3DXMATRIX					m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3					m_vtxPosA;			// 頂点位置A
	D3DXVECTOR3					m_vtxPosB;			// 頂点位置B
	D3DXVECTOR3					m_vtxPosC;			// 頂点位置C
	D3DXVECTOR3					m_vtxPosD;			// 頂点位置D
};

#endif




