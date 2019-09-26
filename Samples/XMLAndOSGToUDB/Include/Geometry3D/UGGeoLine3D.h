//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoLine3D.h
//!  \brief ��ά�߼��ζ���
//!  \author UGCTeam��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOLINE3D_H__C9F9464F_CCB3_4297_B3CB_B7D5114B9CBE__INCLUDED_)
#define AFX_UGGEOLINE3D_H__C9F9464F_CCB3_4297_B3CB_B7D5114B9CBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Geometry3D/UGGeometry3D.h"
#include "Base3D/UGRenderOperationGroup.h"

namespace UGC
{
class UGRenderOperationGeometry;

//! \brief �ڲ�ʹ�õı����ߵ���Ӱ�嵥���������ݵĽṹ
struct LineShadowVolumeVertex
{
	// ��Ӱ�嶥������
	UGVector3d Vertex;
	// ��Ӱ�嶥�㴦������ֱ��ˮƽ����
	UGVector3d CrossDir;
	// ��Ӱ�嶥�㴦��ֱ���췽��
	UGVector3d VerticalDir;
};

class UGGeoLine;
class UGGeoLineEPS;
//! \brief ��ά�߼��ζ���
class GEOMETRY3D_API UGGeoLine3D : public UGGeometry3D
{
public:
	
	//! \brief ȱʡ���캯����
	UGGeoLine3D();	

	//! \brief Ĭ������������
	virtual ~UGGeoLine3D();	

public:
	
	//! \brief �õ�ά�ȡ�
	//! \return ����ά�ȣ���Ϊ0ά, ��/���ߵ�Ϊ1ά, ��/�����Ϊ2ά, GeoCompound/GeoText��Ϊ-1��
	virtual UGint GetDimension() const;	
	
	//! \brief �õ��ڵ㣨��Geometry�ڲ�����������ĵ㣩
	//! \remarks Ϊ���������Ӷ��� ���м��(�м�����ĵ�, �������м����ĵ�)
	virtual UGPoint2D GetInnerPoint() const;

	//! \brief �õ��������
	//! \return �������
	virtual UGdouble GetArea() const;
	
	//! \brief �õ��������
	//! \return �������
	virtual UGdouble GetArea3D() const;
	
	//! \brief ѡ��������ά�߶���ĵ�ѡ��
	//! \param &pntHitTest [in] ��������ѡ�еĵ㡣
	//! \param dTolerance [in] ���ޡ�
	//! \return ѡ�з���true, ���򷵻�false��
	//! \remarks ���ö�ά��HitTest()�����жϡ�
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;	
	
	//! \brief ���ζ����Ƿ���Ч
	//! \return ��Ч����true,��Ч����false
	//! \remarks ����ת��2ά��Geometry�󣬵������ķ���ʵ�֣����ο�2ά��ʵ�֡�
	virtual UGbool IsValid()const;

	//! \brief ���������߶����ָ�룬��������һ��Geoline3D��
	//! \param pGeometry [in] �����߶���ָ�롣
	//! \return ����ɹ�����true��
	//! \remarks �ڲ�����make����ȥʵ�֡�
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	

	//! \brief ������ά�㴮����һ��GeoLine
	//! \param pPoints [in] �㴮ָ�롣
	//! \param nPntCount [in] ��ĸ�����
	//! \param UGEditType3D::ET3D_NULL [in] �༭������״����ѡ����
	//! \return ����ɹ�����true��
	//! \remarks �ڲ�����make����ȥʵ�֣������ڱ༭�ж�̬�������GeoLine��
	virtual UGbool MakeWithPoints3D(UGPoint3D* pPoints,UGint nPntCount,
		UGEditType3D::EditToolShape3D nEditType = UGEditType3D::ET3D_NULL);	

	//! \brief ���ݴ���ĵ㴮���ɶ�����Ҫ���ڱ༭�еĲ�������û���ڲ����鱣��㴮�Ķ���
	//! Ҳ�����Զ������,�������ڲ����鱣��㴮�Ķ��󣬸ú���ֱ��return�ȿɣ�
	//! ����GeoLine�ȶ����ֱ����AddHandle�����ɣ�Ч�ʱȽϸ� 
	//! \param pPoints 3ά�㴮
	//! \param nPntCount  ��ĸ���
	virtual void MakeWithPoints(UGPoint3D* pPoints,UGint nPntCount,
				UGEditType::EditToolShape nEditType=UGEditType::ET_Default);

	//! \brief �õ������λ�ã��������ֻ��ģ�ͺ͹��򼸺������壬λ��Ϊģ�͵�����ĵ������ĵ�
	//! \return �����λ�á�
	virtual UGPoint3D GetPosition() const;
	 
	//! \brief ��ȡ���ݴ洢ʱ�Ĵ�С
	//! \return ���ش洢��С
	//! \remarks ��δ���Ǳ����������SaveGeoData()һ��ά��
	//! \attention �ַ����ĳ���Ҫ+4
	virtual UGint GetDataSize() const;

	//! \brief ��ȡģ�͹����Ķ����弯�ϡ�
	//! \param nResolution [in] �ֱ��ʡ�
	//! \param nFragmentSize [in] Ƭ�δ�С����λ���ס�
	//! \param nFragmentAngle [in] Ƭ�νǶȣ���λ�ȡ�
	//! \attention ʹ�ú���Ҫ�û��ͷ��ڴ档
	virtual UGPolySet* GetPolySet(
		UGuint nResolution = 0, 
		UGuint nFragmentSize = 2, 
		UGuint nFragmentAngle = 12) const;

	//! \brief ʹ��UGPolySet���¹���GeoRegion3D��
	virtual UGbool MakeWithPolySet(const UGPolySet* pPolySet);

	//! \brief ����ϸ�֡�
	//! \param dGranularity [in] ϸ�����ȡ�����Ϊ��γ������ʱ������Ĭ��ΪPI/180.0�ȣ�����Ϊƽ������ʱ������Ĭ��Ϊ1.0�ס�
	//! \param bLonLat [in] ���������Ƿ��Ǿ�γ�ȡ�
	virtual UGbool ComputeSubDivision(UGdouble dGranularity, UGbool bLonLat);

protected:
	//! \brief ��������Bounds
	//! \return ���صõ���Bounds
	virtual UGRect2D ComputeBounds() const;	

	//! \brief ֻ���漸�����ݲ���
	//! \param stream [in] �洢��, ����֮ǰӦ����Open
	//! \param eCodecType [in] �洢�ı��뷽ʽ
	//! \param bSDBPlus [in] �Ƿ�洢ΪSDBPlus�ĸ�ʽ
	//! \remarks ����SDBPlus��������ݿ�����Ĵ洢�ϲ��ϴ�,���Ա���ֱ�ӵ��øú���,
	//! �����ӱ������зֱ���
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;
	
	//! \brief ֻת�ؼ������ݲ���
	//! \param stream [in] �� 
	//! \param eCodecType [in] ���뷽ʽ
	//! \attention [in] ����Ҫ���� UGbool bSDBPlus = FALSE �Ĳ���
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool LoadGeoData( UGStream& stream , 
	UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );

	
	//!\brief �õ�Boundingbox
	virtual UGBoundingBox ComputeBoundingBox() const;

public:


	//! \brief ����
	//! \param dRatioX X�������ű���
	//! \param dRatioY Y�������ű���
	//! \param dRatioY Z�������ű���
	//! \remarks M������
	virtual void Inflate3D( UGdouble dRatioX, UGdouble dRatioY, UGdouble dRatioZ);
 	
	//! \brief ����
	//! \param dRatio ���ű���(X,Y,Z��ͬ)
	virtual void Inflate3D( UGdouble dRatio);

	//! \brief ����
	//! \param dRatioX [in] X�������ű��ʡ�
	//! \param dRatioY [in] Y�������ű��ʡ�
	virtual void Inflate( UGdouble dRatioX, UGdouble dRatioY);	

	//! \brief ƽ��
	//! \param dX ƽ�Ƶ�Xƫ����
	//! \param dY ƽ�Ƶ�Yƫ����
	virtual void Offset( UGdouble dX, UGdouble dY);
	
	//! \brief ƽ��
	//! \param ƫ����(X,Y������ͬ)
	virtual void Offset( UGdouble dOffset);
	
	//! \brief ƽ��
	//! \param ƽ�Ƶ�ƫ����(�ֱ���UGSize2D�е�x,y����X,Y�����ƫ����)
	virtual void Offset( const UGSize2D &szOffset);

	//! \brief ��ת
	//! \param pntOrigin ��ת�����ĵ�(ê��,������)
	//! \param dAngle ��ת�Ƕ�
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dAngle);

	//! \brief ��ת,����һЩ����,�Ա��ڲ����Բ��ý���cos,sin, �����������ʱ�����������Ч��
	//! \remarks dAngle���ƶ���,��GeoText��Ҫ,����Ҫ����
	//! \param pntOrigin ��ת�����ĵ�(ê��,������)
	//! \param dCosAngle ��ת��cosֵ
	//! \param dSinAngle ��ת��sinֵ
	//! \param dAngle ��ת�Ƕ�
	virtual void Rotate( const UGPoint2D& pntOrigin, UGdouble dCosAngle, UGdouble dSinAngle, double dAngle = 0);

	//! \brief ��ά����ƽ��
	//! \param dX [in] ƽ�Ƶ�Xƫ����
	//! \param dY [in] ƽ�Ƶ�Yƫ����	
	//! \param dZ [in] ƽ�Ƶ�Zƫ����	
	virtual void Offset3D( UGdouble dX, UGdouble dY, UGdouble dZ);
	
	//! \brief ��ά����ƽ��
	//! \param dOffset [in] ƫ����(X,Y,Z������ͬ)	
	virtual void Offset3D( UGdouble dOffset);
	
	//! \brief ��ά����ƽ��
	//! \param vecOffset [in] ƽ�Ƶ�ƫ����(�ֱ���UGVector3d�е�x,y,z����X,Y,Z�����ƫ����)��
	virtual void Offset3D( const UGVector3d &vecOffset);	

	//! \brief ��ά������ת
	//! \param vecAxis [in] ��ת�� ��ԭ��
	//! \param dAngle [in] ��ת�Ƕ�
	virtual void Rotate3D(const UGVector3d& vecAxis, UGdouble dAngle);

	//! \brief ���㾵��
	//! \param pntMirror1 [in] ���ɾ���ĵ�һ����
	//! \param pntMirror2 [in] ���ɾ���ĵڶ�����
	//! \param pntMirror3 [in] ���ɾ���ĵ�������
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Mirror3D(const UGPoint3D &pntMirror1, const UGPoint3D &pntMirror2, const UGPoint3D &pntMirror3);
	
	
	//! \brief ����
	//! \param vecNormal [in] ����ķ�������	
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Mirror3D(const UGVector3d &vecNormal);

	//! \brief �õ����󳤶ȡ�
	//! \attention DimensionΪ1or2�Ķ����֧�֡�
	//! \return ���س��ȡ�
	//! \remarks ת��2ά��Geometry�󣬵������ķ���ʵ�֡�
	virtual UGdouble GetLength() const;	
	
	//! \brief �õ���ά���󳤶ȡ�
	//! \attention DimensionΪ1or2�Ķ����֧�֡�
	//! \return ���س��ȡ�
	//! \remarks �ڲ����ǰ���2ά��Geometry�Գ��ȵ��������ʵ�ֵġ�
	virtual UGdouble GetLength3D() const;

	//! \brief �õ���ά���󳤶ȡ�
	//! \pjType ��������
	//! \return ���س��ȡ�
	virtual UGdouble GetLength3D(EmPrjCoordSysType pjType);

	//! \brief ת��Ϊ�߶���
	//! \param geoLine[out] �õ����߶���
	//! \param nSegmentCount ������ת��Ϊ��ʱ,ÿһ���ö��ٸ�����ģ�⡣
	//! \return �ɹ�����true,ʧ�ܷ���false��
	virtual UGbool ConvertToLine( UGGeoLine &geoLine, UGint nSegmentCount = 0 ) const;
	
	//! \brief ת��Ϊ�����
	//! \param geoRegion[out] �õ��������
	//! \param nSegmentCount ������ת��Ϊ��ʱ,ÿһ���ö��ٸ�����ģ�⡣
	//! \return �ɹ�����true,ʧ�ܷ���false��
	virtual UGbool ConvertToRegion( UGGeoRegion &geoRegion, UGint nSegmentCount = 0 ) const;
	
	//! \brief ת���ɶ����󣬿��԰�3D�㡢3D������ת���ɶ�������ʾ��
	//! \param geoMultiPoint [out] �����㼸�ζ���
	//! \return �ɹ�����true,ʧ�ܷ���false��
	virtual UGbool ConvertToPoint( UGGeoMultiPoint &geoMultiPoint) const;	
	
	//! \brief ת����ͼƬ��3D���ͼ��ζ����Լ��û����ͼ��ζ������ͨ����ת����ͼƬ������ʾ��
	//! \param geoPicture [out] ���ͼƬ���ζ���
	//! \param dResolution [in] �ֱ��ʡ�
	//! \param dXAngle [in] ˮƽ��ǡ�
	//! \param dZAngle [in] ��ת��ǡ�
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool ConvertToPicture( UGGeoPicture &geoPicture, UGdouble dResolution, 
								UGdouble dXAngle = 0, UGdouble dZAngle = 0) const;	
		
public:
	//Projection..
	
	//! \brief ����ͶӰת���������ú�ת������Ҫ��, ����ͶӰת��
	//! \param pPJTranslator [in] ͶӰת����
	//! \param bForward [in] ת������, true�����UGRefTranslator��Դ(Src)ת����Ŀ��(Des), false���෴
	//! \remarks ת��2ά��Geometry�󣬵������ķ���ʵ��
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);

	//! \brief ������άͶӰ����ϵͳת��
	//! \attention ��δʵ�֡�
	virtual void PJConvert3D( UGRefTranslator *pPJTranslator, UGbool bForward = true);	

	
	//! \brief �Ӿ�γ����ϵͳת��ΪͶӰ����ϵͳ
	//! \param pCoordSys [in] ͶӰ����ϵͳ
	//! \remarks ת��2ά��Geometry�󣬵������ķ���ʵ��
	virtual void PJForward( UGPrjCoordSys *pCoordSys );
	
	//! \brief ��ͶӰ����ϵͳת��Ϊ��γ����
	//! \param pCoordSys ͶӰ����ϵͳ
	//! \remarks ת��2ά��Geometry�󣬵������ķ���ʵ��
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );

	//! \brief �Ӿ�γ����ϵͳת��Ϊ��άͶӰ����ϵͳ
	//! \param pCoordSys ͶӰ����ϵͳ
	virtual void PJForward3D( UGPrjCoordSys *pCoordSys );
	
	//! \brief ��ͶӰ����ϵͳת��Ϊ��γ����ϵ
	//! \param pCoordSys ͶӰ����ϵͳ
	virtual void PJInverse3D( UGPrjCoordSys *pCoordSys );

	//! \brief ����XML��ʽ����Ϣ
	//! \param versionType GML�İ汾
	//! \param nPace �����Ŀո���Ŀ,ʹ��xml�ַ������������˹��Ķ�; 
	//! ��Ҫ����������ص�xml�ַ�����һ�����ǩ�е�һ����, ͨ��ָ���ո���Ŀ,����ʹ�������
	//! \return ����ָ��GML�汾��xml�ַ���
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0) const;
	
	//! \brief ��XML�ַ���������Geometry
	//! \param strXML xml��ʽ�ַ���
	//! \param versionType xml�ַ�����GML�汾
	//! \return ����ָ��GML�汾��xml�ַ���
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType);
#ifndef OPENGL_ES_VERSION2
	//! \brief Geometry��Element��ת��
	//! \param pElement [in] ���ص�pElementָ���ں����ڷ����ڴ�,���渺��ɾ������������ڴ�й©
	//! \remarks ת��3ά��Geometry�󣬵������ķ���ʵ��
	virtual UGbool ToElement(OgdcElement*& pElement)  const;


	//! \brief Geometry��Element��ת��
	//! \param pElement [in] �����Element������޷�ת���򷵻�False�����򷵻�True
	virtual UGbool FromElement(const OgdcElement* pElement);
#endif
public:

	//! \brief �õ����ζ������͡�
	//! \return �̶�Ϊ GeoLine3D��
	virtual UGGeometry::Type GetType() const;	

	//! \brief ��ȡ��������ά�㡣
	//! \return ��ά�㡣
	virtual UGPoint3D GetInnerPoint3D() const;	

	//! \brief ��յ�������
	virtual void Clear();

	//! \brief �õ�ָ���Ӷ���ĵ㴮��ָ�롣
	//! \param nSubIndex [in] �Ӷ���������
	//! \return �����Ӷ���ĵ㴮��ָ�롣
	virtual const UGPoint3D* GetPoints(UGint nSubIndex=0) const;		
	
	//! \brief ����һ���Ӷ����GeoLine
	//! \param pPoints [in] �㴮ָ�롣
	//! \param nPntCount [in] �㴮�ĵ���Ŀ��
	//! \return ����С��2��,����false��
	virtual UGbool Make( const UGPoint3D* pPoints, UGint nPntCount );

	//! \brief �������Ӷ���ĸ���GeoLine
	//! \param pPoints [in] �㴮ָ�롣
	//! \param pPolyCount [in] �Ӷ����е��������顣
	//! \param nSubCount [in] �Ӷ�����Ŀ��
	//! \return �����Ӷ���ĵ�����С��2��,����false��
	virtual	UGbool Make( const UGPoint3D* pPoints, const UGint* pPolyCount, UGint nSubCount );	
	virtual	UGbool Make( const UGPoint2D* pPoints, const UGint* pPolyCount, UGint nSubCount );	

	//! \brief ��������GeoLine3D��
	//! \param geoLine3D [in] �����߶���
	//! \return �����߶���Ƿ�, ����false��
	virtual UGbool Make( const UGGeoLine3D& geoLine3D);

	//! \brief ����GeoLine3D��
	//! \param geoLine [in] �����߶���
	//! \return �����߶���Ƿ�, ����false��
	virtual UGbool Make( const UGGeoLine& geoLine);

	//! \brief ����GeoLine3D��
	//! \param geoLineEPS [in] �����߶���
	//! \return �����߶���Ƿ�, ����false��
	virtual UGbool Make( const UGGeoLineEPS& geoLineEPS);

	//! \brief ���������һ���Ӷ���
	//! \param pPoints [in] �㴮ָ�롣
	//! \param nPntCount [in] �㴮�ĵ���Ŀ��
	//! \return �㴮����С��2��, ����false��
	UGbool AddSub( const UGPoint3D* pPoints, UGint nPntCount );

	//! \brief �����Ӷ���
	//! \param nIndex [in] Ҫ�����λ��������
	//! \param pPoints [in] �㴮ָ�롣
	//! \param nPntCount [in] �㴮�е�ĸ�����
	//! \return �����С��2��������λ�÷Ƿ�,����false��
	UGbool InsertSub(UGint nIndex, const UGPoint3D* pPoints, UGint nPntCount);	

	//! \brief ɾ���Ӷ���
	//! \param nIndex [in] Ҫɾ�����Ӷ����λ��������
	//! \return �����Ƿ�, ����false��
	UGbool DelSub( UGint nIndex );	

	//! \brief ��GeoLine���ҵ����뿪ʼ��ָ�����ȵĵ㡣
	//! \param dDistance [in] ָ���ľ��볤��[in]��
	//! \return �ҵ��ĵ㡣
	//! \remarks dDistanceС��0ʱ���᷵����ʼ�㣻���dDistance�����ߵĳ��ȣ������ߵ���ֹ�㣻
	//! �����ж���Ӷ�����ߣ���ǰһ���Ӷ�����dDistanceû�����꣬������һ���Ӷ����м����ң�ʹ��ʣ���dDistance��
	//! ֱ��dDistance���꣬�ҵ���Ӧ�ĵ㣬���߷������һ���Ӷ������ֹ��
	//! \attention ���ҵĵ㲻һ�����ߵĽڵ㣨vertex���������������ϣ���������ĵ�
	UGPoint3D FindPointOnLineByDistance(UGdouble dDistance);	

	//! \brief ��ת�����Ĵ���
	//! \return �ɹ�����true,ʧ�ܷ���false
	//! \remarks ֻ��תÿ���Ӷ����еĵ�Ĵ���,������ת�Ӷ����˳��
	UGbool Reverse();

	//! \brief �õ��Ӷ�����Ŀ������ָ�롣
	//! \return �����Ӷ�����Ŀ������ָ�롣
	virtual const UGint* GetPolyCounts() const;	

	//! \brief �õ������Ӷ���ĵ�ĸ����ܺ͡�
	//! \return ���ظ�����
	virtual UGint GetPointCount() const;	

	//! \brief �õ��Ӷ���ĸ���
	//! \return ���ظ���
	virtual UGint GetSubCount() const;

	//! \brief �õ�ĳ���Ӷ���ĵ�ĸ�����
	//! \param nSubIndex [in] �Ӷ���������
	//! \return ���ظ�����
	virtual	UGint GetSubPntCount(UGint nSubIndex) const;	

	//! \brief ��ָ����λ�������õ�����ꡣ
	//! \param nIndex [in] λ��������
	//! \param point [in] �����ꡣ
	//! \return �����Ƿ�������������ԭʼ�㴮�ڣ�, ����false��
	//! \remarks �����Ӷ���ĵ���һ�������������, ������û�������Ӷ���, ��ͷ��ʼ����������
	UGbool SetPoint( UGint nIndex, const UGPoint3D& point );	

	//! \brief ͨ��ָ�����ߵ������͵��������е�����λ�ý��в��롣
	//! \param nSubIndex [in] �Ӷ���������
	//! \param nPointIndex [in] Ҫ������λ�á�
	//! \param &pnt [in] Ҫ����ĵ㡣
	UGbool InsertPoint(UGint nSubIndex, UGint nPointIndex, UGPoint3D &pnt);	


	// fansc 2012-11-8
	//! \brief ����һ��GeoLine3D
	//! \param pGeoLine3D Ҫ�����ӵ�GeoLine3D
	//! \remarks ����GeoLine3D������ֻ��һ���Ӷ���; ���Ӻ��γ�һ���������Ӷ���
	//!			����ʱ,�������Ӷ�����ͷ����ȽϽ�����������; 
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Joint(UGGeoLine3D* pGeoLine3D);
	
	virtual UGint GetXYZAtPos(UGdouble dPos, UGPoint3D& pntXYZ);

	//! \brief ��һ��geometryת��Ϊһ��GeoLine3D������������
	//! \return �ɹ�����true,ʧ�ܷ���false
	UGbool ConvertFromGeometry(UGGeometry* pGeometry);
public:
	//added by xielin ^_^ �༭��غ���,�ѱ༭��geometryͳһ
	
	//! \brief ��ñ༭����ľ������Ŀ
	//! \remarks ���ڹ̶��������Ϊ9�����˸ı��С��8�����Ƶ��һ����ת���Ƶ�
     virtual UGint  GetHandleCount();

	
	//nHandle:��ֵ����Ƶ�Ĺ�ϵ����ͼ                         
	//									1---+   	  +--2    	+----3	
	//                                      |         |         |  
	//                                      |         |         |  
	//										x---------x---------x     9
    //										|   ____________    |     |
    //										|  /            \   | x---+
	//									4---x |              |  x-----5
	//										|  \____________/   |
	//										|                   |
	//										x---------x---------x
	//										|		  |         |
	//										|		  |         |
	//								    6---+         +-----7   +-----8
	
	//! \brief ���ݾ�������Ӧ���Ƶ��ֵ
	//! \param nHandle ���Ƶ���
	//! \param point �����Ӧ�Ŀ��Ƶ������ֵ
	//! \return ���ظ����������
	 virtual UGint GetHandle( UGint nHandle, UGPoint2D& point);


	//! \brief �ƶ����Ƶ㵽ָ������,��Ҫ���ڻ��ƶ����޸Ķ���ڵ�Ȳ���
	//! \param nHandle ���Ƶ���
	//! \param point ���Ƶ�����
	virtual void MoveHandle( UGint nHandle, const UGPoint2D& pnt2D,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);

	//! \brief �ڵ�༭ʱ����������һ�����Ƶ�,Ҳ�������ڻ��ƶ���ʱ����ڵ�
	//! \param nHandle ����λ��
	//! \param pnt2D �����ĵ�������
	virtual void AddHandle( UGint nHandle, const UGPoint2D& pnt2D,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	
	//! \brief ɾ���༭�����ָ���ڵ�
	//! \param nHandle �ڵ���
     virtual UGuint DelNode( UGint nHandle );

	//! \brief ����������ʱ�ĸ����ߣ����ص���һ�����϶���
	//! \param pPoints �㴮
	//! \param nPntCount  ��ĸ���
	//! \param nEditType ���ƶ�������ͣ��ο�UGEditType
	//! \param pStyle	 �����ߵķ���������ΪNULL����Ĭ�ϵķ��
     virtual UGGeometry*  CalAssistantLine(const UGPoint2D* pPoints,UGint nPntCount,UGEditType::EditToolShape nEditType,UGStyle* pStyle=NULL);


	 //! \brief ����������ʱ�ĸ����㣬���ص��ǵ����Ŀ,nHandleType���ص��Ǹ����������,�ο�UGEditType::EditHandleType
	//! \param pPoints �㴮
	//! \param nPntCount  ��ĸ���
	//! \param eAssistantPoints �㴮,���صĸ�����㴮
	//! \param nEditType ���ƶ�������ͣ��ο�UGEditType
	void CalAssistantPoints(const UGPoint2D* pPoints,UGint nPntCount,UGArray<UGEditType::EditAssistantPoint>& eAssistantPoints,UGEditType::EditToolShape nEditType);

	//! \param pPoints [out]��
	//! \param pPolyCount ������ÿ���Ӷ�������������[out]��
	//! \param nSubCount �������Ӷ������[out]��
	//! \param nSegmentCount �Բ���������, ÿ�����ηָ��ĸ���[in]��
	//! \remarks ��������������ָ��ļ���,�����߲����ͷ��ڴ�ռ�
	//! \return �ɹ�����true,���򷵻�false��
	virtual UGbool GetSpatialData(UGAutoPtr<UGPoint2D>& pPoints, 
		UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const;



	 //! \brief ���ݴ���ĵ㴮���ɶ�����Ҫ���ڱ༭�еĲ�������û���ڲ����鱣��㴮�Ķ���
	 //Ҳ�����Զ������,�������ڲ����鱣��㴮�Ķ��󣬸ú���ֱ��return�ȿɣ�����GeoLine
	 //GeoLine�ȶ����ֱ����AddHandle�����ɣ�Ч�ʱȽϸ�,���������ƽ���ߣ�������������
	//! \param pPoints �㴮
	//! \param nPntCount  ��ĸ���
     virtual void MakeWithPoints(UGPoint2D* pPoints,UGint nPntCount,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	
	 //! \brief ��ȡ������Ҫ��׽�ĵ㴮
	//! \param aryPnts �㴮������ȥ��Ҫ��׽�ĵ㴮
	//! \return �����true��ʾ����Ҫ��׽�ĵ㴮���������false��ʾ�ö���û����Ҫ��׽�ĵ㴮
	virtual UGbool GetSnapPoints(UGArray<UGPoint2D>& aryPnts);

	//! \brief ��ȡ������Ҫ��׽���߶�����
	//! \param aryLines ��Ҫ��׽�������飨����ж��part����ôaryLines��Ӧ���ж��ٸ�count��
	//! \return �����true��ʾ����Ҫ��׽���ߣ��������false��ʾ�ö���û����Ҫ��׽����
	virtual UGbool GetSnapLines(UGLineArray& aryLines);
	 
	 //added by xielin ^_^ �༭��غ���,�ѱ༭��geometryͳһ end

	//! \brief ������������,�޶����µ�Bounds��
	//! \param rcNewBounds �µ�,�޶���Χ��Bounds
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Resize(const UGRect2D& rcNewBounds); 

	//! \brief ����̶���ê��
	void ComputeFixedAnchorPoints();

	//! \brief �����̶���ê��
	UGArray<UGPoint3D> m_AnchorPoints;

	//! \brief ��ȡ�����������
	UGPoint3D GetStartNode();

	//! \brief ��ȡ����β�����
	UGPoint3D GetEndNode();

	//! \brief ��ȡGeoLine����Ӱ�壬ָ���ⲿ�ͷ�
	//! \param sceneType ��������[in]
	//! \param fBottomHeight ��Ӱ��ĵײ��߶ȣ����ڼ����Χ�У����û�в�Ӱ����Ⱦ�������ܱ��ü�[in]
	//! \param fExtendHeight ��Ӱ�������߶ȣ����ڼ����Χ�У����û�в�Ӱ����Ⱦ�������ܱ��ü�[in]
	//! \param fReductionTolerance �����ޣ��������ΪĬ��ֵ0.0�򲻼�[in]
	//! \return �ɹ�������Ӱ��
	//! \attention ָ�����ⲿ�ͷš������Ӱ�����ߵĶ��㰴�վ��η�����������״����û��ָ���߶ȺͿ�ȣ���Ҫ����ɫ����ָ��[in]
	UGRenderOperationGeometry* GetBaseShadowVolume(SceneType sceneType, UGfloat fBottomHeight = 0.0f, UGfloat fExtendHeight = 0.0f, UGfloat fReductionTolerance = 0.0f);

	//! \brief ��ȡGeoLine����Ӱ�壬ָ���ⲿ�ͷ�
	//! \param sceneType ��������[in]
	//! \param centerMatrix ���ľ���[in]
	//! \param fBottomHeight ��Ӱ��ĵײ��߶ȣ����ڼ����Χ�У����û�в�Ӱ����Ⱦ�������ܱ��ü�[in]
	//! \param fExtendHeight ��Ӱ�������߶ȣ����ڼ����Χ�У����û�в�Ӱ����Ⱦ�������ܱ��ü�[in]
	//! \param fReductionTolerance �����ޣ��������ΪĬ��ֵ0.0�򲻼�[in]
	//! \return �ɹ�������Ӱ��
	//! \attention ָ�����ⲿ�ͷš������Ӱ�����ߵĶ��㰴�վ��η�����������״����û��ָ���߶ȺͿ�ȣ���Ҫ����ɫ����ָ��[in]
	UGRenderOperationGeometry* GetBaseShadowVolume(SceneType sceneType, const UGMatrix4d& centerMatrix, UGfloat fBottomHeight = 0.0f, UGfloat fExtendHeight = 0.0f, UGfloat fReductionTolerance = 0.0f);

	//! \brief ���������Ӱ���IndexPackage
	//! \param pIndexPackage ��������������[in]
	//! \param nPointCount �ߵĶ������[in]
	//! \param nSubCount ���߸���[in]
	//! \param pPolyCount ���ߵĶ�����[in]
	static void FillShadowVolumeIndexPackage(UGIndexPackage* pIndexPackage, UGint nPointCount, UGint nSubCount, const UGint* pPolyCount);

	//! \brief ��ȡ��ȡ��Ӱ��Ķ�������
	//! \param sceneType ��������[in]
	//! \param arrCenterVertex �����ߵĶ��������������ϵ�еĵѿ�����������[in]
	//! \param fReductionTolerance �����ޣ��������ΪĬ��ֵ0.0�򲻼�[in]
	//! \param arrShadowVolumeVertex �����Ӱ�嶥�������[out]
	static void ConstructShadowVolumeVertex(SceneType sceneType, UGArray<UGVector3d>& arrCenterVertex, UGfloat fReductionTolerance, UGArray<LineShadowVolumeVertex>& arrShadowVolumeVertex);

	//! \brief ������Ӱ��Ķ������ݰ�
	//! \param arrShadowVolumeVertex ������Ӱ�嶥�������[in]
	//! \param pVertexDataPackage �����Ӱ��Ķ������ݰ�[out]
	static void FillShadowVolumeVertexDataPackage(UGArray<UGArray<LineShadowVolumeVertex> >& arrShadowVolumeVertex, UGVertexDataPackage* pVertexDataPackage);
private:
	//! \brief ������Ӱ����������ݰ�
	//! \param nPointCount ���index��Ӧ����ԭʼ�Ķ�������[in]
	//! \param nIndexOffset ��ǰ��index������ƫ����[in/out]
	//! \param nVertexOffset ��ǰ��index�������Ķ���ƫ����[in]
	//! \param pIndexPackage �����Ӱ����������ݰ�[out]
	template<typename T>
	static void FillShadowVolumeIndex(UGint nPointCount, UGint& nIndexOffset, UGint nVertexOffset, T* pIndexes);
private:
	
	//! \brief ���ڲ�����ά������ת�ɶ�ά��
	//! \return ���ض�ά��ָ�룬����ע��ʹ�ú��ͷš�	
	const UGPoint2D* GetPoint2D() const;

	//! \brief �����ߵ����е㡣
	UGArray<UGPoint3D> m_Points;

	//! \brief �ߵ��Ӷ��������
	UGArray<UGint> m_PolyCounts;
};

}

#endif // !defined(AFX_UGGEOLINE3D_H__C9F9464F_CCB3_4297_B3CB_B7D5114B9CBE__INCLUDED_)



