//=============================================================================
//
// パーツクラス(parts.h)
// Author : 唐﨑結斗
// 概要 : パーツ生成を行う
//
//=============================================================================
#ifndef _PARTS_H_			// このマクロ定義がされてなかったら
#define _PARTS_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "model3D.h"
#include "main.h"

//=============================================================================
// パーツクラス
// Author : 唐﨑結斗
// 概要 : パーツ生成を行うクラス
//=============================================================================
class CParts : public CModel3D
{
public:
	//--------------------------------------------------------------------
	// 静的メンバ関数
	//--------------------------------------------------------------------
	static CParts *Create(const int nModelNam);			// パーツの生成

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CParts();
	~CParts();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	HRESULT Init(const int nModelNam) override;										// 初期化
	void Uninit() override;															// 終了
	void Update() override;															// 更新
	void Draw() override;															// 描画
	void SetParent(CModel3D *pParent) { m_pParent = pParent; }						// 親モデルの設定
	void SetPosDest(const D3DXVECTOR3 posDest) { m_posDest = posDest; }				// 目的の位置の設定
	void SetRotDest(const D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }				// 目的の向きの設定
	void SetPosOrigin(const D3DXVECTOR3 posOrigin) { m_posOrigin = posOrigin; }		// 元の位置の設定
	void SetRotOrigin(const D3DXVECTOR3 rotOrigin) { m_rotOrigin = rotOrigin; }		// 元の向きの設定
	D3DXVECTOR3 GetPosDest() { return  m_posDest; }									// 目的の位置の取得
	D3DXVECTOR3 GetRotDest() { return  m_rotOrigin; }								// 目的の向きの取得
	D3DXVECTOR3 GetPosOrigin() { return  m_posOrigin; }								// 元の位置の取得
	D3DXVECTOR3 GetRotOrigin() { return  m_rotOrigin; }								// 元の向きの取得

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	CModel3D *m_pParent;			// 親オブジェクトのポインタ
	D3DXVECTOR3 m_posOrigin;		// 元の位置
	D3DXVECTOR3 m_rotOrigin;		// 元の向き
	D3DXVECTOR3 m_posDest;			// 目的の位置
	D3DXVECTOR3 m_rotDest;			// 目的の向き
};

#endif