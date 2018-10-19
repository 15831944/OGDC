/*---------------------------------------------------------------------------
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoModel(Pro).h
//!  \brief Geo + Model ����
//!  \details 
//!  \author zq
//!  \attention
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
---------------------------------------------------------------------------*/

#ifndef __UGGEOMODELPRO_H__
#define __UGGEOMODELPRO_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000	
#include "Geometry3D/UGGeometry3D.h"
#include "Geometry3D/UGGeoLine3D.h"
#include "Base3D/UGModelNode.h"

namespace UGC
{

class UGOSGGroup;
class UGNodeAnimationInfo;

class GEOMETRY3D_API UGGeoModelPro : public UGGeometry3D
{
public:
	//! \brief ���캯��
	UGGeoModelPro();
	UGGeoModelPro(UGModelNode* pNode, UGbool bDelegate=FALSE);

	//! \brief ��������
	virtual ~UGGeoModelPro();

	//! \brief �õ����ζ�������ͣ����ӿڷ���UGGeometry::GeoModel
	virtual UGGeometry::Type GetType() const;

public:
	//! \brief ��յ�������
	virtual void Clear();

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

	//! \brief ģ�ͻ�ȡ������
	virtual UGbool ConvertToRegion( UGGeoRegion &geoRegion, UGint nSegmentCount  = 0 ) const ;

	//! \brief ģ�ͻ�ȡ������
	virtual UGbool ConvertToRegion(EmSpatialRefType prjCoordType, UGGeoRegion &geoRegion, UGint nSegmentCount  = 0 ) const ;

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

	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData( UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );

	virtual UGbool GetSnapPoints(UGArray<UGPoint2D>& aryPnts);

	//! \brief ���ݾ�������Ӧ���Ƶ��ֵ
	//! \param nHandle ���Ƶ���
	//! \param point �����Ӧ�Ŀ��Ƶ������ֵ
	//! \return ���ظ����������
	virtual UGint GetHandle( UGint nHandle, UGPoint2D& point);

	//! \brief ��ȡGeoModel�İ汾��
	UGint GetVersion(){ return m_nVersion;};

	//! \brief ������ά���ζ���İ�Χ�С�
	//! \param box [in] �°�Χ�е�ֵ��
	virtual void SetBoundingBox(const UGBoundingBox& box);

	//! \brief �õ���ά���ζ���İ�Χ�С�
	//! \return ���ذ�Χ�е�ֵ��
	virtual const UGBoundingBox& GetBoundingBox()	const;

	//! \brief �õ�ģ�������
	virtual UGdouble GetVolume();

	void SetSpherePlaced(UGbool bSpherePlaced);

	UGbool GetSpherePlaced();

	//! \brief �޸�:ģ�͵ķ��õ�λ��(m_pntPos)-->ģ�͵�ʵ�����ĵ�
	//! \brief �� SaveGeoData �е���
	void TransformPntPosition() const;

	//! \brief GeoModel����
	//! \attention ����ɹ�����true��
	UGbool FromGeoModel(const UGGeometry* pGeoSrc);

	//! \brief ����EM
	void SetEM(UGModelEM* pEM);

	//! \brief ���ݴ����Geometry����λ�õ���Ϣ��ModelNode����
	UGbool MakeShell(const UGGeometry* pGeometry);

	//! \brief ģ�ͺϲ�
	static UGGeoModelPro* Compose(UGArray<UGGeoModelPro*> arrGeoModel);

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

	void SetModelNode(UGModelNode* pGroup,UGbool bOwned = FALSE);
	UGModelNode* GetModelNode();

	//! \brief ����m_pntScale m_pntRotate m_pntPos�������
	//! \brief �� ����+ModelNode=UGGeoModelPro
	UGMatrix4d GetLocalMatrix() const;

//! \brief ���ö�������Ŵ�С���������ֻ��ģ�ͺ͹��򼸺�������
	//! \param fScaleX [in] X�������ű��ʡ�
	//! \param fScaleY [in] Y�������ű��ʡ�
	//! \param fScaleZ [in] Z�������ű��ʡ�
	virtual void SetScale(UGdouble fScaleX,UGdouble fScaleY,UGdouble fScaleZ);	

	//! \brief ���ö�������Ŵ�С���������ֻ��ģ�ͺ͹��򼸺������� 
	//! \param fScaleXYZ [in] ���������������Ͻ���ͬ����С������ 
	virtual void SetScale(UGdouble fScaleXYZ);

	//! \brief ���ö������ת�����������ֻ��ģ�ͺ͹��򼸺������� 
	//! \param fRotateX [in] X�������ת�Ƕȡ�
	//! \param fRotateY [in] Y�������ת�Ƕȡ�
	//! \param fRotateZ [in] Z�������ת�Ƕȡ�
	virtual void SetRotation(UGdouble fRotateX,UGdouble fRotateY,UGdouble fRotateZ);	

	//! \brief �Ӽ���UGModelsEntitiesManager���vector
	UGbool LoadEntities(UGModelEM* pEM, UGint nLOD = -1, 
		UGModelEntity::METype mtype = UGModelEntity::etUnknown);

	//! \brief �������Ķ�άBoundsʹ��
	UGBoundingBox GetGeoBoundingBox() const;

	//! \brief ��ȡ���󺣰θ߶ȣ�����˲����з�ʹ��
	void GetAltitude( UGdouble& dbMaxZ, UGdouble& dbMinZ);

	//! \brief ͶӰת�����ⲿ�����Ƿ�ֻת�������
	void SetPJ(UGbool bInsertPntOnly);

	//! \brief ����ģ���ļ���·��,��Ҫ����KML�б���ģ���ļ�·��
	UGString GetFilePathName() const;

	//! \brief ����ģ���ļ���·��,��Ҫ����KML�б���ģ���ļ�·��
	void SetFilePathName(UGString strFilePath);

	//! \brief ����һ���ڵ㶯������
	void CreateNodeAnimation();

	//! \brief ��ȡ�ڵ㶯������
	UGNodeAnimationInfo* GetNodeAnimation();

	//! \brief ƽ�ƵĻ�׼�㣺�����ϻ���ѿ�������ʹ��
	//! \brief ģ�Ͷ���ƽ�ƣ���λ���׻򻡶�
	//! \brief ��֧���������
	UGbool Translate(UGdouble dbX, UGdouble dbY, UGdouble dbZ, UGPoint3D pntBase);

	//! \brief pntBase [in] ��תǰͳһ��׼��
	//! \brief dXAngle [in]	x����ת�Ƕ�
	//! \brief dYAngle [in]	y����ת�Ƕ�
	//! \brief dZAngle [in]	z����ת�Ƕ�
	//! \brief rotatePoint [in] ��ת��
	//! \brief ��֧���������
	UGbool Rotate(UGPoint3D rotatePoint, \
		UGdouble dXAngle, UGdouble dYAngle, UGdouble dZAngle,UGPoint3D pntBase);

	//! \brief ��ȡWλ����ֵ
	void GetMinMaxW(UGdouble& dMin, UGdouble& dMax);
private:
	//! \brief ����Patch
	void TranslatePosition(UGModelPagedPatch* pPatch, UGMatrix4d& matSrc, UGMatrix4d& matLocalBase);

private:
	//! \GeoModel�汾��
	UGint m_nVersion;
	UGModelNode* m_pModelNode;
	UGbool m_bNodeOwned;

	//! \brief �Ƿ�����������ϣ�Ӱ��GeoModelPro����Bounds
	UGbool m_bSpherePlaced;

	UGbool m_bPJInsertPntOnly;

	//! \brief ��¼ģ���ļ�·������Ҫ����KML�ļ�����
	UGString m_strModelFilePath;

	//! \brief �ڵ㶯����Ϣ
	UGNodeAnimationInfo* m_pNodeAnimation;

	//! \brief 
	UGModelEM *m_pEM;
};


}

#endif
