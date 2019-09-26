/*! \file	 UGGeoRegion.h
 *  \brief	 �廪ɽά �� ���ζ���
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
 *  All Rights Reserved
 *  \version $Id: UGGeoRegionEPS.h,v 1.16 2009/10/28 02:40:05 machx Exp $
 *  \version $Id: UGGeoRegionEPS.h,v 1.16 2009/10/28 02:40:05 machx Exp $
*/


#ifndef UGGEOREGIONEPS_H
#define UGGEOREGIONEPS_H

#include "GeometryCAD/UGGeometryEPS.h"
#include "GeometryCAD/UGGeoCompoundRegion.h"

namespace UGC {


class GEOMETRYCAD_API UGGeoRegionEPS  : public UGGeometryEPS
{
public:
	//! \brief ���캯��
	UGGeoRegionEPS();

	//! \brief ��������
	virtual ~UGGeoRegionEPS();
	
public: //pure virtual 
	
	//! \brief ��ռ�������
	virtual void Clear();
	
	//! \brief �õ�ά��, Region�̶�Ϊ2ά
	//! \return ����ά��,�̶�Ϊ2
	virtual UGint GetDimension() const;
	
	//! \brief �õ�����, �̶�ΪGeoRegion
	//! \return ��������, �̶�ΪGeoRegion
	virtual Type GetType() const;
	
	//! \brief �õ��ڵ�
	//! \remarks �ڲ�����UGOpRegions::InnerPointʵ��
	//! \return �����ڵ�
	virtual UGPoint2D GetInnerPoint() const;
	
	//! \brief �õ����󳤶�
	//! \attention DimensionΪ1or2�Ķ����֧��
	//! \return ���س���
	virtual UGdouble GetLength() const;
	
	//! \brief ����õ����
	//! \return �������
	virtual UGdouble GetArea() const;

	//! \brief ����õ���ĳ��ͶӰϵͳ�µĵ������(�Ǽ������)
	//! \param pPJCoordSys ͶӰ����ϵ
	//! \return ������ͶӰ����ϵ�µĵ�������������λΪ��ƽ���ס�
	UGdouble GetArea(UGPrjCoordSys* pPJCoordSys);

	//! \brief ��ȷ����ͶӰ�ο�ϵ�¶���ε�����������λΪ��ƽ���ס�
	//! \param ͶӰ����ϵ
	//! \remark �÷�����SFC60����������ֲ������
	UGdouble GetPreciseArea(UGPrjCoordSys* pPJCoordSys);

	//! \brief �������, ���ڶ����ѡ
	//! \param pntHitTest ��������ѡ�еĵ�
	//! \param dTolerance ����
	//! \return ѡ�з���true, ���򷵻�false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;	
	
	//! \brief �õ��ռ�����, ��Ҫ������Ҫ����ά����ͬʱ
	//! ����ͳһ�����ʱ��, ����һЩ�ռ��жϺͲ������㷨
	//! \param pPoints �����ĵ���������[out]��
	//! \param pPolyCount ������ÿ���Ӷ�������������[out]��
	//! \param nSubCount �������Ӷ������[out]��
	//! \param nSegmentCount �Բ���������, ÿ�����ηָ��ĸ���[in]��
	//! \remarks ��������������ָ��ļ���,�����߲����ͷ��ڴ�ռ�
	//! \return �ɹ�����true,���򷵻�false��
	virtual UGbool GetSpatialData(UGAutoPtr<UGPoint2D>& pPoints, 
		UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const;

	UGbool GetSpatialData(UGAutoPtr<UGPoint3D>& pPoints, 
		UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const;

	UGbool GetPolyData(UGAutoPtr<UGPoint2D>& pPoints, 
		UGAutoPtr<UGint>& pMarkers, UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount) const;

	UGbool AddSub(const UGPointEPS* pPoints, UGint nPntCount);

	UGbool Combination(UGGeoRegionEPS *pGeoRegion);

	//! \brief �õ��Ӷ���ĸ���
	//! \return �����Ӷ���ĸ���
	virtual UGint GetSubCount() const;
	
	//! \brief ���ζ����Ƿ���Ч
	//! \return ��Ч����true,��Ч����false
	virtual UGbool IsValid()const;
	
	//! \brief ����
	//! \param dRatioX X�������ű���
	//! \param dRatioY Y�������ű���
	virtual void Inflate( UGdouble dRatioX, UGdouble dRatioY);
	
	//! \brief ����
	//! \param dRatio ���ű���(X,Y������ͬ)
	virtual void Inflate( UGdouble dRatio);
	
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
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dCosAngle, UGdouble dSinAngle, double dAngle = 0);
	
	//! \brief ������������,�޶����µ�Bounds��
	//! \param rcNewBounds �µ�,�޶���Χ��Bounds
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Resize(const UGRect2D& rcNewBounds); 
	
//public:
//	//! \brief ����ͶӰת���������ú�ת������Ҫ��, ����ͶӰת��
//	//! \param pPJTranslator ͶӰת����
//	//! \param bForward ת������, true�����UGRefTranslator��Դ(Src)ת����Ŀ��(Des), false���෴
//	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);
//	virtual UGbool PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward ,UGbool bClip );
//
//	//! \brief �Ӿ�γ����ϵͳת��ΪͶӰ����ϵͳ
//	//! \param pCoordSys ͶӰ����ϵͳ
//	virtual void PJForward( UGPrjCoordSys *pCoordSys );
//
//	//! \brief ��ͶӰ����ϵͳת��Ϊ��γ����
//	//! \param pCoordSys ͶӰ����ϵͳ
//	virtual void PJInverse( UGPrjCoordSys *pCoordSys );
	
public:
	//! \brief �����������
	//! \param pPoints [in] �㴮ָ�롣
	//! \param nPntCount [in] �㴮�ĵ���Ŀ��
	//! \remarks �γ�һ���Ӷ��󣬴���ĵ�ĸ�������Ҫ3��; ���û�бպϣ������ڲ����Զ��պ�
	//! \return ����С��3��,����false��
	UGbool Make(const UGPointEPS* pPoints, UGint nPntCount);
	
	//! \brief ��������GeoRegion
	//! \param geoRegion [in] ���������
	//! \return ���������Ƿ�, ����false��
	UGbool Make(const UGGeoRegionEPS& geoRegion);
	
	//! \brief �õ������Ӷ���ĵ�ĸ����ܺ͡�
	//! \return ���������Ӷ���ĵ�ĸ����ܺ͡�
	UGint GetPointCount() const;
	
	//! \brief �õ�ָ���Ӷ���ĵ㴮��ָ�롣
	//! \param nSubIndex [in] �Ӷ���������
	//! \return �����Ӷ���ĵ㴮��ָ�롣
	const UGPointEPS* GetPoints() const;

	//! \brief ��ָ����λ�������õ�����ꡣ
	//! \param nIndex [in] λ��������
	//! \param point [in] �����ꡣ
	//! \return �����Ƿ�, ����false��
	//! \remarks �����Ӷ���ĵ���һ�������������, ������û�������Ӷ���, ��ͷ��ʼ����������
	UGbool SetPoint( UGint nIndex, const UGPointEPS& point );
	UGint AddPoint(const UGPointEPS& point);
	UGbool InsertPoint(UGint nIndex, const UGPointEPS& point);
	UGbool RemovePoint(UGint nIndex);
	
	//! \brief ɾ���ٽ��㷽��
	//! \param dInterval�����ٽ�������
	//! \return �ɹ�����true��ʧ��Ϊfalse�����������������ٽ�����Ϊfalse��
	UGbool DelClosedNode(UGdouble dInterval = EP);

	// fansc 2015.07.17
	// ������
	UGbool InsertPoint(UGint nSubIndex, UGint nPointIndex, const UGPoint2D& pntInsert);
	
	//! \brief �Ƴ�ָ���ڵ㣬���ƶ����ϱ༭Ҫ֧�ּ������������3�����������ؼӽӿ����ڴ���
	//! \param nHandle �ڵ���
	UGuint RemoveNode( UGint nHandle );


public:
	//! \brief �жϵ��Ƿ�������
	//! \param &point [in] Ҫ�жϵĵ㡣
	//! \param bBorder [in] �ж�ʱ�Ƿ�����߽硣
	//! \return ��������(bBorderΪtrueʱ,�ڱ߽�Ҳ��)ʱ,����true;���򷵻�false��
	//modified by shuxl	��������ж�!!
	UGbool PtInRegion(const UGPoint2D &point, UGbool bBorder = true, UGdouble dInterval = EP);	

	//! \brief �洢��Stream��
	//! \remarks �ο�UGGeometry��˵��
	virtual UGbool SaveGeoData(UGStream& stream, UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE)  const;

	//! \brief ��Stream������Geometry
	//! \remarks �ο�UGGeometry��˵��
	virtual UGbool LoadGeoData( UGStream& stream , UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );

	//! \brief ֻת�ؼ������ݲ���
	//! \param stream �� 
	//! \param iGuge �û����õ�Load��ʽ��nGuge�жϲ���
	//! \param eCodecType ���뷽ʽ
	//! \attention ����Ҫ���� UGbool bSDBPlus = FALSE �Ĳ���
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool LoadGeoData( UGStream& stream , UGint iGuge, UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE);

	void SaveIndexData(UGStream& stream);
	void LoadIndexData(UGStream& stream);

	void GetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGushort> >& arrIndexes);
	void SetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGushort> >& arrIndexes);

	void GetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGuint> >& arrIndexes);
	void SetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGuint> >& arrIndexes);
	
	//! \brief �ж���֮�䵺����ϵ�ĺ���
	//! \attention ������Ǻ�GeoRegion���ܰ�, ����ŵ� UGOpRegions������, GeoRegion��ʹ�þͿ�����.
	void CheckPolygon(const UGPoint2D *pPoints, const UGint *plPolyCounts, UGint nSubCount, UGint *plPolyArea) const;

	//! \brief �ж���֮�䵺����ϵ�ĺ���
	void CheckPolygon(const UGPoint2D *pPointsBak, const UGint *pMarkersBak, const UGint *plPolyCounts, UGint nSubCount, UGint *plPolyArea) const;

	//! \brief �ж϶����ָ���Ӷ����ǵ����Ƕ���Ӧ�������������	 add by shuxl 09.1.7
	//! \param nSubID �Ӷ���ID
	//! \return ������true,������false
	UGbool CheckSubPolygon(UGint nSubID) const;

	//! \brief �滻�Ӷ���	 add by shuxl 09.3.5
	//! \param lSubObjID �Ӷ���ID
	//! \param	pPoint �滻�����ʼ��ַ
	//! \param	lPointCount �滻��ĸ���
	//! \return 
	UGbool SetSub( UGint lSubObjID, UGPoint2D * pPoint ,UGint lPointCount);
	
	//! \brief �ж��Ӷ���ε�����
	//! \param nIndex �Ӷ�������
	//! \remarks ����-1��������쳣������0 ˳ʱ�룻����1 ��ʱ�룻
	UGint IsCounterClockwise(UGint nIndex);

	//! \brief �ж��Ƿ��ж�
	//! \return ������Ч����ֻ��һ���Ӷ���ʱ����-1,���ж���Ӷ��󵫲���������0�����ж���Ӷ��󵫺��ж�����1
	UGint HasHollow();

	//! \brief ����ĳ���Ӷ����е��˳��
	//! \param nSubIndex [in] Ҫ������Ӷ���������
	//! \return �����Ƿ�,����false��
	UGbool Reverse(UGint nSubIndex);	

	virtual UGint GetDataSize() const;

#if PACKAGE_TYPE==PACKAGE_UGC
public:		
			
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
		
	//! \brief ���㾵��
	//! \param pntMirror1 ���ɾ���ĵ�һ����
	//! \param pntMirror2 ���ɾ���ĵڶ�����
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Mirror(const UGPoint2D &pntMirror1, const UGPoint2D &pntMirror2);
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS) 
	//! \brief Geometry��Element��ת��
	//! \param pElement,���ص�pElementָ���ں����ڷ����ڴ�,���渺��ɾ������������ڴ�й©
	virtual UGbool ToElement(OgdcElement*& pElement)  const;

	//! \brief Geometry��Element��ת��
	//! \param pElement,�����Element������޷�ת���򷵻�False�����򷵻�True
	virtual UGbool FromElement(const OgdcElement* pElement);
#endif

#endif // end declare ugc sdk
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

	//! \brief ���ݴ���ĵ㴮���ɶ�����Ҫ���ڱ༭�еĲ�������û���ڲ����鱣��㴮�Ķ���
	//Ҳ�����Զ������,�������ڲ����鱣��㴮�Ķ��󣬸ú���ֱ��return�ȿɣ�����GeoLine
	//GeoLine�ȶ����ֱ����AddHandle�����ɣ�Ч�ʱȽϸ� 
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
	
	//! \brief �ϲ�����
	//! \param 
	//! \return 
	UGbool Combination(UGGeoRegion *pGeoRegion);

	//! \brief ���󱣻��Էֽ�
	//! \param arrOutRegion	���صı��ֽ�Ķ���
	//! \return 
	UGbool ProtectedDecomposeEx(UGArray<UGGeoRegion*> &arrOutRegion);

	//added by xielin ^_^ �༭��غ���,�ѱ༭��geometryͳһ end
protected:
	//! \brief ��Χ�͵����
	struct BoundsNode 
	{
		UGint  lNumber;
		UGRect2D  rcBounds;
		UGdouble GetArea() { return rcBounds.Width() * rcBounds.Height(); }
		void operator =(BoundsNode node) { lNumber = node.lNumber; rcBounds = node.rcBounds; };
	};

	typedef UGArray<BoundsNode*> BoundsNodes;

	//! \brief �ж���֮�䵺����ϵ�ĺ���
	//! \attention ������Ǻ�GeoRegion���ܰ�, ����ŵ� UGOpRegions������, GeoRegion��ʹ�þͿ�����.
	void CheckPolyCounts( const UGPoint2D *pPoints, const UGint *plPolyCounts, UGint nSubCount,UGint* plPolyArea ) const; 

	//! \brief �ж���֮�䵺����ϵ�ĺ���
	//! \attention ������Ǻ�GeoRegion���ܰ�, ����ŵ� UGOpRegions������, GeoRegion��ʹ�þͿ�����.
	void CheckPolygon( const UGPoint2D *pPoints, const UGint *pPolyCounts1, const UGint *pPolyCounts2, BoundsNodes &Polygons, UGint *pPolyCountsAll, UGint nSubCount ) const;

	//���ù���������׼�����������϶�������
	//! \brief �������һЩ���������������� û����ȫ�չ��������ı�׼
	//! \param ͶӰ����ϵ
	//! \remark �÷�����SFC60����������ֲ������
	double GetPreciseArea2(UGPrjCoordSys* pPJCoordSys);

protected: //! �ڲ���������

	//��������
	UGushort* m_pIndexes;

	//������������
	UGbool m_bUseIndexUint;


	//ÿ���ʷֵ�λ�� ��������
	UGuint* m_pSubIndexCounts;

	//ÿ���ʷֵ�λ�� SubRegion����
	UGuint* m_pSubRegionCounts;

	//��С�ʷֵ�λ����
	UGuint m_nSubCount;
	
protected: //! ������Ҫʵ�ֵ�һЩ����������
	//! \brief ʵ�ʼ���Bounds
	virtual UGRect2D ComputeBounds() const;
	/*virtual UGRect2D GetBoundsInside() const;
	virtual void SetBoundsInside(const UGRect2D & rcBounds);*/
};

}

#endif

