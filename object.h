//=============================================================================
//
// �I�u�W�F�N�g�N���X(object.h)
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s��
//
//=============================================================================
#ifndef _OBJECT_H_		// ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : �������l
// �T�v : �I�u�W�F�N�g�������s���N���X
//=============================================================================
class CObject
{
public:
	//--------------------------------------------------------------------
	// �v���C�I���e�B�̃��x��
	// Author : �������l
	// �T�v : �v���C�I���e�B�̃��x����ݒ�
	//--------------------------------------------------------------------
	enum PRIORITY_LEVEL
	{
		PRIORITY_LEVEL0 = 0,	// ���x��0
		PRIORITY_LEVEL1,		// ���x��1
		PRIORITY_LEVEL2,		// ���x��2
		PRIORITY_LEVEL3,		// ���x��3
		PRIORITY_LEVEL4,		// ���x��4
		MAX_LEVEL				// �ő僌�x��
	};

	//--------------------------------------------------------------------
	// �I�u�W�F�N�g�̎�ʂ̗񋓌^
	// Author : �������l
	// �T�v : �I�u�W�F�N�g�̎�ʏ����i�[
	//--------------------------------------------------------------------
	enum EObjectType
	{
		OBJTYPE_NONE = 0,			// �^�C�v����
		OBJTYPE_3DPLAYER,			// 3D�v���C���[
		OBJTYPE_3DENEMY,			// 3D�G�l�~�[
		OBJTYPE_3DBULLET,			// 3D�o���b�g
		OBJTYPE_FADE,				// �t�F�[�h
		MAX_OBJTYPE,				// ��ʂ̍ő吔
	};

	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static void ReleaseAll(bool bPermanent);	// ���ׂẴI�u�W�F�N�g�̉��
	static void UpdateAll();					// ���ׂẴI�u�W�F�N�g�̍X�V
	static void DrawAll();						// ���ׂẴI�u�W�F�N�g�̕`��
	static void ReleaseListAll();				// ���ׂẴI�u�W�F�N�g�̃��X�g����

#ifdef _DEBUG
	static void ReleaseTop(int nPriority);
	static void ReleaseCurrent(int nPriority);
	static void RandomRelease(int nPriority);
#endif // DEBUG

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	explicit CObject(int nPriority = PRIORITY_LEVEL0);
	virtual ~CObject();

	//--------------------------------------------------------------------
	// �������z�֐�
	//--------------------------------------------------------------------
	virtual HRESULT Init() = 0;														// ������
	virtual void Uninit() = 0;														// �I��
	virtual void Update() = 0;														// �X�V
	virtual void Draw() = 0;														// �`��
	virtual void SetPos(const D3DXVECTOR3 &pos) = 0;								// �ʒu�̃Z�b�^�[
	virtual void SetPosOld(const D3DXVECTOR3 &posOld) = 0;							// �ߋ��ʒu�̃Z�b�^
	virtual void SetRot(const D3DXVECTOR3 &rot) = 0;								// �����̃Z�b�^�[
	virtual void SetSize(const D3DXVECTOR3 &size) = 0;								// �傫���̃Z�b�^�[
	virtual D3DXVECTOR3 GetPos() = 0;												// �ʒu�̃Q�b�^�[
	virtual D3DXVECTOR3 GetPosOld() = 0;											// �ߋ��ʒu�̃Q�b�^
	virtual D3DXVECTOR3 GetRot() = 0;												// �����̃Q�b�^�[
	virtual D3DXVECTOR3 GetSize() = 0;												// �傫���̃Q�b�^�[
	void SetObjType(EObjectType objectType) { m_objectType = objectType; }			// �I�u�W�F�N�g�̎�ʐݒ�
	EObjectType GetObjType() { return m_objectType; }								// �I�u�W�F�N�g�̎�ʐݒ�
	bool GetFlagDeath() { return m_bDeath; }										// ���S�t���O�̎擾

protected:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Release(void);			// �I�u�W�F�N�g�̉��
	void ReleaseList(void);		// �I�u�W�F�N�g�̃��X�g����

private:
	//--------------------------------------------------------------------
	// �ÓI�����o�ϐ�
	//--------------------------------------------------------------------
	static CObject *m_pTop[MAX_LEVEL];				// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCurrent[MAX_LEVEL];			// ���݂�(��Ԍ��)�I�u�W�F�N�g�ւ̃|�C���^
	static int m_nMaxObject;						// �g�p��
	static int m_nPriorityMaxObj[MAX_LEVEL];		// �v���C�I���e�B���Ƃ̃I�u�W�F�N�g��

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CObject *m_pPrev;				// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;				// ���̃I�u�W�F�N�g�ւ̃|�C���^
	EObjectType m_objectType;		// �I�u�W�F�N�g�̎��
	int	 m_nLevPriority;			// �v���C�I���e�B�̃��x��
	bool m_bDeath;					// ���S�t���O
};

#endif
