// UGGeoTexture.h: interface for the UGGeoTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOMODELENTITY_H__20EA7583_BE8A_40A7_884A_E1CDB7161DE1__INCLUDED_)
#define AFX_UGGEOMODELENTITY_H__20EA7583_BE8A_40A7_884A_E1CDB7161DE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometry3D/UGGeometry3D.h"
#include "Base3D/UGTextureData.h"
#include "Base3D/UGModelNode.h"

namespace UGC {
//! \brief ģ��ʵ�����
class GEOMETRY3D_API UGGeoModelEntity : public UGGeometry3D  
{
public:
	//! \brief ���캯��
	UGGeoModelEntity();
	//! \brief ��������
	~UGGeoModelEntity();

public:
	//! \brief ʵ������
	enum METype
	{
		Unknown		= 0,
		//! \brief �Ǽ�
		Skeleton	= 1,
		//! \brief ����
		Texture		= 2,
		//! \brief ����
		Material	= 3
	};
	
	//! \brief ��ȡʵ������
	virtual UGGeoModelEntity::METype GetEntityType() const = 0;
	
	//! \brief ��ȡ32λhashֵ
	UGint GeoHashCode();
	
	//! \brief ��ȡ64λhashֵ
	UGlong GeoHashCode64();
	
	//! \brief ��ȡʵ����������
	UGString GetEntityName() const;

	//! \brief �йܸ�ʵ�����������pEM
	virtual void Deposit2EM(UGModelEM* pEM) = 0;

protected:
	//! \brief ʵ����������
	UGString m_strEntityName;

	//! \brief �Ƿ���Ҫ���¼���Hashֵ
	UGbool m_bDirty;

	//! \brief 32λHashֵ
	UGint m_nHashCode;

	//! \brief 64λHashֵ
	UGlong m_lHashCode64;

	//! \brief ʵ������Ƿ����Լ���ռ��
	UGbool m_bEntityOwned;
};

class GEOMETRY3D_API UGGeoModelEntityTexture : public UGGeoModelEntity  
{
public:
	//! \brief ���캯��
	UGGeoModelEntityTexture();
	UGGeoModelEntityTexture(UGModelTexture* pModelTexture);
	//! \brief ��������
	~UGGeoModelEntityTexture();

public:
	//! \brief ��ȡʵ������
	virtual UGGeoModelEntity::METype GetEntityType() const;

	//! \brief ����ʵ�����
	void SetEntity(UGModelTexture* pEntity);

	//! \brief ��ȡʵ�����
	UGModelTexture* GetEntity();

	//! \brief �йܸ�������
	virtual void Deposit2EM(UGModelEM* pEM);

	//! \brief ���
	virtual void Clear();

	//! \brief ���ζ����Ƿ���Ч
	//! \return ��Ч����true,��Ч����false
	virtual UGbool IsValid() const;

	//! \brief �õ�����, �̶�Ϊ GeoRect
	virtual Type GetType() const;

	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData(UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE, UGbool bSDBPlus = FALSE );

	//! \brief ����geometry���ͣ��ٵ��ø��Ե�make����ȥʵ�֡�
	//! \param pGeometry [in]��
	//! \attention ����ɹ�����true��
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);

protected:
	UGModelTexture* m_pModelTexture;
};

class GEOMETRY3D_API UGGeoModelEntitySkeleton : public UGGeoModelEntity  
{
public:
	//! \brief ���캯��
	UGGeoModelEntitySkeleton();
	UGGeoModelEntitySkeleton(UGModelSkeleton* pModelSkeleton);
	//! \brief ��������
	~UGGeoModelEntitySkeleton();

public:
	//! \brief ��ȡʵ������
	virtual UGGeoModelEntity::METype GetEntityType() const;

	//! \brief ����ʵ�����
	void SetEntity(UGModelSkeleton* pEntity);

	//! \brief ��ȡʵ�����
	UGModelSkeleton* GetEntity();

	//! \brief �йܸ�������
	virtual void Deposit2EM(UGModelEM* pEM);

	//! \brief ���
	virtual void Clear();

	//! \brief ���ζ����Ƿ���Ч
	//! \return ��Ч����true,��Ч����false
	virtual UGbool IsValid() const;

	//! \brief �õ�����, �̶�Ϊ GeoRect
	virtual Type GetType() const;

	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData(UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE, UGbool bSDBPlus = FALSE );

	//! \brief ����geometry���ͣ��ٵ��ø��Ե�make����ȥʵ�֡�
	//! \param pGeometry [in]��
	//! \attention ����ɹ�����true��
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);

protected:
	UGModelSkeleton* m_pModelSkeleton;
};

class GEOMETRY3D_API UGGeoModelEntityMaterial3D : public UGGeoModelEntity  
{
public:
	//! \brief ���캯��
	UGGeoModelEntityMaterial3D();
	UGGeoModelEntityMaterial3D(UGModelMaterial* pModelMaterial3D);
	//! \brief ��������
	~UGGeoModelEntityMaterial3D();

public:
	//! \brief ��ȡʵ������
	virtual UGGeoModelEntity::METype GetEntityType() const;

	//! \brief ����ʵ�����
	void SetEntity(UGModelMaterial* pEntity);

	//! \brief ��ȡʵ�����
	UGModelMaterial* GetEntity();

	//! \brief �йܸ�������
	virtual void Deposit2EM(UGModelEM* pEM);
	//! \brief ���
	virtual void Clear();

	//! \brief ���ζ����Ƿ���Ч
	//! \return ��Ч����true,��Ч����false
	virtual UGbool IsValid() const;

	//! \brief �õ�����, �̶�Ϊ GeoRect
	virtual Type GetType() const;

	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData(UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE, UGbool bSDBPlus = FALSE );

	//! \brief ����geometry���ͣ��ٵ��ø��Ե�make����ȥʵ�֡�
	//! \param pGeometry [in]��
	//! \attention ����ɹ�����true��
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);

protected:
	UGModelMaterial* m_pModelMaterial3D;
};
}

#endif // !defined(AFX_UGGEOTEXTURE_H__20EA7583_BE8A_40A7_884A_E1CDB7161DE1__INCLUDED_)

