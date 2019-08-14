//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class ��άģ���ࡣ
//!  \details ��ɶ���άģ����ķ�װ��
//!  \author ��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGGEOMODEL_H__9824004B_0E6A_4340_908D_6FE34882E0AB__INCLUDED_)
#define AFX_UGGEOMODEL_H__9824004B_0E6A_4340_908D_6FE34882E0AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Geometry3D/UGGeometry3D.h"
#include "Base3D/UGVector3d.h"
#include "Base3D/UGMatrix4d.h"
#include "Base3D/UGMaterial.h"
#include "Base3D/UGMesh.h"
#include "Toolkit/UGTextureInfo.h"
#include "Graphics3D/UGModelManager.h"
#include "Geometry3D/UGGeoLine3D.h"

namespace UGC
{

class UGMaterial3D;
//! \brief ��άģ���ࡣ
class GEOMETRY3D_API UGGeoModel : public UGGeometry3D
{
public:
	//! \brief ���캯��
	UGGeoModel();

	//! \brief ��������
	virtual ~UGGeoModel();
	
	//! \brief  ����һ��ģ�͵����ݹ�����ģ��
	UGbool Make( const UGGeoModel& model);

	//! \brief �õ����ζ�������ͣ����ӿڷ���UGGeometry::GeoModel
	virtual UGGeometry::Type GetType() const;

	//! \brief �õ�ģ���ļ���·��,��Ҫ����KML�б���ģ���ļ�·��
	UGString GetSGMName() const;

	//! \brief ����ģ���ļ���·��,��Ҫ����KML�б���ģ���ļ�·��
	void SetSGMName(UGString value);

	//! \����ģ������
	void SetModelDataPtr(const UGModelDataPtr& ModelDataPtr);
	
	//! \����ģ������
	void SetModelDataInfo(ModelDataInfo* pModelDataInfo);
	
	//! \�Ƿ������ģ���ļ���ģ��
	UGbool IsFileAttached();

	//! \������ҵ�ģ���ļ�
	void SetAttachedFilePath(UGString strAttachedFilePath);

	//! \�Ƿ������ģ���ļ���ģ��
	UGString GetAttachedFilePath();

	// �Ȱ����ʵ����
public:
	
	//! \brief �õ�ά��, ��Ϊ0ά, ��/���ߵ�Ϊ1ά, ��/�����Ϊ2ά, GeoCompound/GeoText��Ϊ-1
	virtual UGint GetDimension() const;
	
	//! \brief �õ��ڵ㣨��Geometry�ڲ�����������ĵ㣩
	//! \remarks Ϊ���������Ӷ��� ���м��(�м�����ĵ�, �������м����ĵ�)
	virtual UGPoint2D GetInnerPoint() const;

	//! \brief �õ��ڵ㣬����������ģ�͵�λ��Position
	virtual UGPoint3D GetInnerPoint3D() const;

	//! \brief �õ��ڵ㣬����������ģ�͵�λ��Position�����������巵���ڵ�
	virtual UGPoint3D GetPosition() const;
	
	//! \brief �������, ���ڶ����ѡ
	//! \param pntHitTest ��������ѡ�еĵ�
	//! \param dTolerance ����
	//! \return ѡ�з���true, ���򷵻�false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;
	
	//! \brief ���ζ����Ƿ���Ч
	//! \return ��Ч����true,��Ч����false
	virtual UGbool IsValid() const;

	//! \brief ����geometry���ͣ��ٵ��ø��Ե�make����ȥʵ�֡�
	//! \param pGeometry [in]��
	//! \return ��
	//! \remarks ��
	//! \attention ����ɹ�����true��
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	

	//! \brief ��ȡ���ݴ洢ʱ�Ĵ�С
	//! \return ���ش洢��С
	//! \remarks ��δ���Ǳ����������SaveGeoData()һ��ά��
	//! \attention �ַ����ĳ���Ҫ+4
	virtual UGint GetDataSize() const;

	//! \brief ������GeoModel�ཻ��
	//! \param vecRayStart �������[in]��
	//! \param vecRayEnd ���ߵ��յ�[in]��
	//! \return vecPos �����ཻ�ĵ�����
	void PickingRayWithModel(UGVector3d vecRayStart,UGVector3d vecRayEnd, UGVector3d& vecPos);
	
	//! \brief ��ȡģ������ָ�롣
	UGModelDataPtr& GetModelDataPtr();

	//! \brief ��ȡģ������ָ�롣
	ModelDataInfo* GetModelDataInfo();

	//! \brief ģ�ͻ�ȡ������
	virtual UGbool ConvertToRegion( UGGeoRegion &geoRegion, UGint nSegmentCount  = 0 ) const ;

	//! \brief ģ�ͻ�ȡ������
	virtual UGbool ConvertToRegion(EmSpatialRefType prjCoordType, UGGeoRegion &geoRegion, UGint nSegmentCount  = 0 ) const ;

	//! \brief ��ά��������
	//! \param dRatioX [in] X�������ű���
	//! \param dRatioY [in] Y�������ű���
	//! \param dRatioZ [in] Z�������ű���
	virtual void Inflate3D( UGdouble dRatioX, UGdouble dRatioY, UGdouble dRatioZ);
public:
	//Projection..
	
	//! \brief ����ͶӰת���������ú�ת������Ҫ��, ����ͶӰת��
	//! \param pPJTranslator ͶӰת����
	//! \param bForward ת������, true�����UGRefTranslator��Դ(Src)ת����Ŀ��(Des), false���෴
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);
	
	//! \brief �Ӿ�γ����ϵͳת��ΪͶӰ����ϵͳ
	//! \param pCoordSys ͶӰ����ϵͳ
	virtual void PJForward( UGPrjCoordSys *pCoordSys );
	
	//! \brief ��ͶӰ����ϵͳת��Ϊ��γ����
	//! \param pCoordSys ͶӰ����ϵͳ
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );

	//! \brief �õ�ģ�͵ļ������ݡ�
	UGArray<UGMesh*>& GetMesh() const;

	//! \brief ��ȡģ�͵Ĳ������ݡ�
	UGArray<UGMaterial*>& GetMaterial();

	//! \brief ��ȡģ�͵Ĳ������ݡ�
	UGArray<UGMaterial3D*>& GetMaterial3D();

	//! \brief ģ�͵��ھֲ��������
	UGMatrix4d GetLocalMatrix();

	//! \brief �þ�����Խ�ģ�͵Ķ���ת������������
	//! \brief bDegreeΪTRUE��ģ�������泡����ת����FALSE����ƽ�泡����ת����Ĭ�������泡����ת�� add by gengjing 14/10/10
	UGMatrix4d GetConvertToWorldCartesianMatrix(UGbool bDegree = TRUE);

	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief �洢��Stream��
	virtual UGbool SaveVecData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE, UGfloat fCacheVersion = 1.4) const;

	//! \brief �洢����ĸ�������,����Geometry�洢��һ�������
	//! \brief ģ����ߴ洢�����ģ�ͷֿ�
	//! \return �ɹ�����TRUE,ʧ�ܷ���FLASE
	virtual UGbool SaveExtData(UGArray<UGTextureInfo>& arryTextureInfo);

	//! \brief ͨ�����ζ����б��������·����ʼ��������Ϣ
	//! \return �ɹ�����TRUE,ʧ�ܷ���FLASE
	virtual UGbool InitialTextureInfo(UGArray<UGTextureInfo>& arrayTextureInfos);

	//! \brief ���ض����������ݵ����ζ�����
	//! \return �ɹ�����TRUE,ʧ�ܷ���FLASE
	virtual UGbool LoadExtData(const UGArray<UGTextureInfo>& arrayTextureInfos);

	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData( UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );

	//! \brief ��Stream������Geometry
	virtual UGbool LoadVecData( UGStream& stream ,
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE, UGfloat fCacheVersion = 1.4f);

	virtual UGbool GetSnapPoints(UGArray<UGPoint2D>& aryPnts);

	//! \brief ���ݾ�������Ӧ���Ƶ��ֵ
	//! \param nHandle ���Ƶ���
	//! \param point �����Ӧ�Ŀ��Ƶ������ֵ
	//! \return ���ظ����������
	virtual UGint GetHandle( UGint nHandle, UGPoint2D& point);

	//! \brief ��ȡGeoModel�İ汾��
	UGdouble GetVersion(){ return m_dVersion;};

	//! \brief ������ά���ζ���İ�Χ�С�
	//! \param box [in] �°�Χ�е�ֵ��
	virtual void SetBoundingBox(const UGBoundingBox& box);

	//! \brief �ͷ�����
	void Release(void);

	//! \brief ����ģ�͵�λ�ã���һģ�Ͷ��㣬�����¼����޸�Ϊ�µ�λ��
	//! \param pntPos [in] ģ�͵�λ�á�
	void UnitizeBaseBottom(const UGPoint3D& pntPos);

	//! \brief �õ�ģ�������
	virtual UGdouble GetVolume();

protected:
	//! \brief ��������Bounds
	//! \return ���صõ���Bounds
	virtual UGRect2D ComputeBounds() const;	

	//!\brief �õ�Boundingbox
	virtual UGBoundingBox ComputeBoundingBox() const;

public:
	// ģ�ͱ������
	//! \param pGeoLine ��ά�ߣ�����ϵ��ģ��Ӧ��һ�£�
	//! \param bDegree �ߡ�ģ�������Ƿ��Ǿ�γ������ϵ��Ĭ�Ͼ�γ��
	//! \param pSurfaceLine ��ģ�ͱ������
	//! \return �������
	UGdouble SurfaceDistance(UGGeoLine *pGeoLine, UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);

	// ģ�ͱ����
	//! \param pGeoLine ��ά�棨����ϵ��ģ��Ӧ��һ�£�
	//! \param bDegree �桢ģ�������Ƿ��Ǿ�γ������ϵ��Ĭ�Ͼ�γ��
	//! \param pSurfaceLine ��ģ�ͱ������
	//! \return �����
	UGdouble SurfaceArea(UGGeoRegion *pGeoRegion, UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);

	// ģ�����
	//! \param pGeoRegion ��ά�棨����ϵ��ģ��Ӧ��һ�£�
	//! \param dBaseValue ����߳�
	//! \param bDegree �桢ģ�������Ƿ��Ǿ�γ������ϵ��Ĭ�Ͼ�γ��
	//! \param pSurfaceLine ��ģ�ͱ������
	//! \return ���
	UGdouble SurfaceVolume(UGGeoRegion *pGeoRegion, UGdouble dBaseValue, UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);

	// ģ�����ڷ�
	//! \param pGeoRegion ��ά�棨����ϵ��ģ��Ӧ��һ�£�
	//! \param dBaseValue ����߳�
	//! \param dFillVolume ����
	//! \param dDigVolume �ڷ����
	//! \param dFillArea ����
	//! \param dDigArea �ڷ����
	//! \param bDegree �桢ģ�������Ƿ��Ǿ�γ������ϵ��Ĭ�Ͼ�γ��
	//! \param pSurfaceLine ��ģ�ͱ������
	void SurfaceFillDig(UGGeoRegion *pGeoRegion, UGdouble dBaseValue, 
		UGdouble &dFillVolume, UGdouble &dDigVolume, UGdouble &dFillArea, UGdouble &dDigArea,
		UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);
private:

	//�����������ϱ�����롢���������ṩ
	struct ATriangle
	{
		UGint nMeshIndex;
		UGint nTriangleIndex;
		UGint nVertexIndex1;
		UGint nVertexIndex2;
		UGint nVertexIndex3;
	};

	struct ATriangleEx
	{
		ATriangle aTriangle;
		UGbool bVertex1InRegion;
		UGbool bVertex2InRegion;
		UGbool bVertex3InRegion;
	};

	UGdouble SurfaceDistanceGrid(UGGeoLine *pGeoLine, UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);
	UGdouble SurfaceAreaAccurate(UGGeoRegion *pGeoRegion, UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);
	UGdouble SurfaceVolumeAccurate(UGGeoRegion *pGeoRegion, UGdouble dBaseValue, UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);
	void SurfaceFillDigAccurate(UGGeoRegion *pGeoRegion, UGdouble dBaseValue, 
		UGdouble &dFillVolume, UGdouble &dDigVolume, UGdouble &dFillArea, UGdouble &dDigArea,
		UGbool bDegree = TRUE, UGGeoLine3D *pSurfaceLine = NULL);
	UGbool SurfaceClip(UGArray<UGMesh*> &pArrMeshes, UGGeoRegion geoRegionClip, UGArray< UGArray<UGushort> >& arrIndexClip, UGArray< UGArray<UGushort> >& arrIndexFill, UGMatrix4d matrixToWorldCartesian, UGdouble dBaseValue, UGbool bDegree = TRUE, UGbool bVolumeComputer = TRUE);//�ڶ�ά�����жϰ���
	UGbool JoinSurfaceLines(UGArray<UGVector3d>& intersects,UGGeoLine3D *&pSurfaceLine,UGVector3d minVector, UGVector3d maxVector,UGMatrix4d matrixToWorldCartesian, UGbool bDegree = TRUE);
	UGbool JoinSurfaceLines(UGGeoLine *pGeoLine, UGGeoLine3D *&pSurfaceLine, UGVector3d minVector, UGVector3d maxVector, UGArray<UGMesh*> &pArrMeshes, UGArray< UGArray<UGushort> >& arrIndexClip, UGMatrix4d matrixToWorldCartesian, UGbool bDegree = TRUE);

private:

	//! \breif ģ������,���ڹ���
	UGModelDataPtr m_ModelDataPtr;

	//! \brief ģ�ͱ��������
	ModelDataInfo* m_pModelDataInfo;

	//! \GeoModel�Ƿ������ݵ����е�
	UGbool m_bOwner;

	//! \GeoModel�汾��
	UGdouble m_dVersion;

	//! \�Ƿ������ģ���ļ���ģ��
	UGbool m_bFileAttached;

	//! \ģ����ҵ�ģ���ļ�
	UGString m_strAttachedFile;
};
}
#endif // !defined(AFX_UGGEOMODEL_H__9824004B_0E6A_4340_908D_6FE34882E0AB__INCLUDED_)

