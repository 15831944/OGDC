/*! \file	 UGGeoTextEPS.h
 *  \brief	 �廪ɽά �ı�������
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
 *  All Rights Reserved
 *  \version $Id: UGGeoTextEPS.h,v 1.11 2010/03/17 06:16:11 majt Exp $
 */


#ifndef UGGEOTEXTEPS_H
#define UGGEOTEXTEPS_H

#include "GeometryCAD/UGGeometryEPS.h"
#include "Geometry/UGGeoText.h"
#include "Toolkit/UGTextStyle.h"

namespace UGC {

class GEOMETRYCAD_API UGGeoTextEPS : public UGGeometryEPS
{
private: //! �ڲ���������
	UGString  m_strNote;			//ע������
	UGfloat	  m_fStringAngle;		//���ĽǶ�,����ʱ�����ֽǶ�(��)//m_nAngle
	UGbyte	  m_byteHS;			//���뷽ʽ//m_nStyle

	//����Ϊԭm_FontInfo�м�¼��Ϣ
	UGString  m_szNumber;		//�����
	UGString  m_strFontName;	//������
	UGshort   m_unFontWidth;	//�ֿ�
	UGshort   m_unFontHeight;	//�ָ�
	UGshort   m_unFontInterval;	//�ָ�
	UGshort   m_unWeight;		//�ְ�ֵ
	UGfloat   m_fIlaticAngle;	//б��,�ֵ����½ǵ��ֵ����Ͻ�����ߵļн�(��) 
	UGfloat   m_fDownAngle;		//�ʼ�,�ֵ����½ǵ��ֵ����½�����ߵļн�(��)
	/*�ܲ���ϵͳ�������ƣ�б��ֻ��ʵ��б72�ȣ��ʼ���Windows98������ʵ��*/
	UGfloat	  m_fWordAngle;		//�ֽǶ�,�ֵ����������ļн�(��)
    UGbool	  m_bUnderLine;		//�Ƿ��»���
	
	//COLORREF  m_rgbColor;		    //������ɫ
	//ʹ�û����е�m_Color
	UGColor   m_ColorBorder;		//�߿���ɫ
	UGColor   m_ColorFill;		//�����ɫ
	
	UGshort   m_nBorderStyle;       //�߿���ʽ
	UGshort   m_nLineWidth;         //�߿��߿�
	UGshort   m_nThickness;         //�߿���(��̨, ��Ӱ��)

	UGString  m_strMemo;	     	//��ע

	UGTextStyle	m_textStyle;

public:
	//! \brief ���캯��
	UGGeoTextEPS();
	UGGeoTextEPS(const UGGeoTextEPS& geoText);
	
	//! \brief ��������
	virtual ~UGGeoTextEPS();
public: 

	//���ö��뷽ʽ
 	//���ڲ���: Alignment(���뷽ʽ)
	void SetAlignment(UGshort Alignment);
	//��ö��뷽ʽ
	//����ֵ: ���뷽ʽ
	UGshort GetAlignment() const;

	// ���ö��ע�Ƕ�λ��ʽ
 	//���ڲ���: nPosType(��λ��ʽ) 
	//          0 ��·�����ȷֲ�
	//          1 ·�����ֲ�
	void SetPosType( UGint nPosType );
	//��õ�ע�Ƕ�λ��ʽ
	//����ֵ: ��λ��ʽ
	UGint  GetPosType() const;

	//���ע������
	//����ֵ: ע������
	UGString GetStringText() const;
	//����ע������
 	//���ڲ���: strNote(��ע������)
	//����ֵ: ԭע������
	UGString SetStringText( UGString strNote);

	//���ע�Ǵ��ĽǶ�
	//����ֵ: ע�Ǵ��ĽǶ�
	UGfloat		GetStringAngle() const;
	//����ע�Ǵ��ĽǶ�
 	//���ڲ���: fAngle(���ĽǶ�)
	//����ֵ: ԭ���ĽǶ�
	UGfloat		SetStringAngle(UGfloat fAngle );

	//�����������
	//����ֵ: ��������
	UGString     GetFontName() const;
	//������������
 	//���ڲ���: strName(��������)
	//����ֵ: ԭ��������
	UGString     SetFontName(UGString strName);

	//��������ֿ�
	//����ֵ: �����ֿ�
	UGshort		GetFontWidth() const;
	//���������ֿ�
 	//���ڲ���: nWidth(�����ֿ�)
	//����ֵ: ԭ�����ֿ�
	UGshort		SetFontWidth(UGshort nWidth);

	//��������ָ�
	//����ֵ: �����ָ�
	UGshort		GetFontHeight() const;
	//���������ָ�
 	//���ڲ���: nHeight(�����ָ�)
	//����ֵ: ԭ�����ָ�
	UGshort		SetFontHeight(UGshort nHeight);

	//��������ְ�ֵ
	//����ֵ: �����ְ�ֵ
	UGshort       GetFontWeight() const;
	//���������ְ�ֵ
 	//���ڲ���: nWeight(�����ְ�ֵ)
	//����ֵ: ԭ�����ְ�ֵ
	UGshort       SetFontWeight(UGshort nWeight);
 
	//��������ָ�
	//����ֵ: �����ָ�
	UGshort		GetFontInterval() const;
	//���������ָ�
 	//���ڲ���: nInterval(�����ָ�)
	//����ֵ: ԭ�����ָ�
	UGshort		SetFontInterval(UGshort nInterval);

	//����ֽǶ�
	//����ֵ: �ֽǶ�
	UGfloat		GetWordAngle() const;
	//���������ֽǶ�
 	//���ڲ���: fAngle(�ֽǶ�)
	//����ֵ: ԭ�ֽǶ�
	UGfloat		SetWordAngle(UGfloat fAngle);

	//�����������
	//����ֵ: ��������
	UGString GetFontClass() const;
	//������������
 	//���ڲ���: szClass(��������)
	void SetFontClass(UGString szClass);
	//������������
 	//���ڲ���: nNumber(��������)
	void SetFontClass( UGuint nNumber);

	//���б��(�ֵ����½ǵ��ֵ����Ͻ�����ߵļн�)
	//����ֵ: б��
	UGfloat GetIlaticAngle() const;
	//����б��(�ֵ����½ǵ��ֵ����Ͻ�����ߵļн�)
 	//���ڲ���: fIlaticAngle(б��)
	//����ֵ: ԭб��
	UGfloat SetIlaticAngle(UGfloat fIlaticAngle);

	//����ʼ�(�ֵ����½ǵ��ֵ����½�����ߵļн�)
	//����ֵ: �ʼ�
	UGfloat GetDownAngle() const; 
	//�����ʼ�(�ֵ����½ǵ��ֵ����½�����ߵļн�)
 	//���ڲ���: fWownAngle(�ʼ�)
	//����ֵ: ԭ�ʼ�
	UGfloat SetDownAngle(UGfloat fWownAngle) ;  
	//����Ƿ��»���
	//����ֵ: TRUE��ʾ���»���,FALSE��ʾ�����»���
	UGbool GetUnderLine() const;
	//�����Ƿ��»���
 	//���ڲ���: nFlags(��ʶ)
	//����ֵ: ԭ�Ƿ��»��߱�ʶ
	UGbool SetUnderLine(UGbool nFlags); 

	//��ñ�ע��Ϣ
	//����ֵ: ��ע��Ϣ
	UGString GetFontMemo() const;
	//���ñ�ע��Ϣ
 	//���ڲ���: strMemo(��ע��Ϣ)
	void SetFontMemo(const UGString& strMemo );

	
	//! \brief ��յ�������
	virtual void Clear();
	
	//! \brief �õ�ά��, �̶�Ϊ-1
	virtual UGint GetDimension() const;
	
	//! \brief �õ�����,�̶�ΪGeoText
	virtual Type GetType() const;
	
	//! \brief �õ��ڵ㣨��Geometry�ڲ�����������ĵ㣩
	//! \return ���ص�һ���Ӷ����ê��
	virtual UGPoint2D GetInnerPoint() const;
	
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
	virtual void Rotate( const UGPoint2D& pntOrigin, UGdouble dCosAngle, UGdouble dSinAngle, double dAngle = 0);
	
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
	
public://��Ҫ����ʵ�ֵķ���
	
	//! \brief ���÷��
	//! \param pStyle ���ָ��
	//! \remarks ���pStyle==NULL,��Geometry�ڲ����ָ�뱻delete; ����Ḵ��һ�ݷ��
	//! �����ı������, ���÷��������,��Ϊ�ı��������Լ���TextStyle
	virtual void SetStyle(const UGStyle* pStyle);
	
	virtual UGint GetDataSize() const;

	const UGString& GetNote();
	void SetNote(UGString& strNote);

public: //! group �����ı�����
	//! \brief ͨ���ı�����/ê��/��ת�Ƕ��������ı�����
	//! \param strText [in] �ı����ݡ�
	//! \param pntAnchor [in] ê�㡣
	//! \param dAngle [in] ��ת�Ƕȡ�
	//! \return ����true��
	UGbool Make(const UGString& strText, const UGPointEPS& pntAnchor, UGdouble dAngle=0.0);

	//! \brief ͨ�����ƹ����ı�����
	//! \param geotext [in] ���е��ı�����
	//! \return ����true��
	UGbool Make(const UGGeoTextEPS& geotext);	

	//! \brief �����ı����
	//! \param textStyle [in] �ı����
	void SetTextStyle(const UGTextStyle& textStyle, UGbool bChangeSubTextAngle = false);	

	//! \brief �õ��ı����
	//! \return �����ı����
	const UGTextStyle& GetTextStyle();	
	//! \remarks 
	//! 1) ȥ��ǰ��� �ո�/�س�����/Tab ���ַ�
	//! 2) �м�� �ո�/�س�����/Tab , ���ǰ���� ����/���� ��, Ҳȥ��
	//! 3) ���ǰ���� Ӣ��(or���ֵ�ACSII��), �� ����һ���ո�(�س�����/Tab��Ҳת��Ϊһ���ո�)
	//! ԭ��: ����ӿھ������� ���� �ַ����Ƚϲ�ѯ��, �� �����ı����ݼ��� ToString ��, 
	//! ���浽�ı��ֶ���, Ȼ�� �û��Ϳ��Ժܷ���� ���ֶ��н��� ����, 
	//! �� ��ͼ����ʾ�� ��Ҫ д��" I am   \r\n a student.   ", �� �û������Ա��в�ѯʱ, 
	//! ֻ��Ҫ ���� "I am a student.", �ﵽ���뼴���� ��Ч��
	//!	��:��" I am   \r\n a student.   " ��Ϊ "I am a student."
    //!					 "Hello, \r�й� "  			  ��Ϊ "Hello,�й�"
    //!					 "Abc\rABC"					  ��Ϊ "Abc ABC"
	//! \return �����ı�����ĺϲ����
	//! \brief ȡ���ı������������(���е��Ӷ�������ִ��ĺϲ�,ȥ���ո񡢻��е�)
	UGString GetIndexString() const;		
	
	//! \brief ת��Ϊ�߶���
	//! \param geoLine[out] �õ����߶���
	//! \param nSegmentCount ������ת��Ϊ��ʱ,ÿһ���ö��ٸ�����ģ��
	//! \remarks �ı������޷�ת��,�̶�����false
	//! \return ����false
	virtual UGbool ConvertToLine( UGGeoLine &geoLine, UGlong nSegmentCount = 0 ) const;
	
	//! \brief ת��Ϊ�����
	//! \param geoRegion[out] �õ��������
	//! \param nSegmentCount ������ת��Ϊ��ʱ,ÿһ���ö��ٸ�����ģ��
	//! \remarks �ı������޷�ת��,�̶�����false
	//! \return ����false
	virtual UGbool ConvertToRegion( UGGeoRegion &geoRegion, UGlong nSegmentCount = 0 ) const;

	UGbool ConvertToGeoText(UGGeoText &geoText, UGlong nSegmentCount = 0 );

#if PACKAGE_TYPE==PACKAGE_UGC
		
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


	//! \brief ����������ʱ�ĸ����㣬���ص��ǵ����Ŀ,nHandleType���ص��Ǹ����������,�ο�UGEditType::EditHandleType
	//! \param pPoints �㴮
	//! \param nPntCount  ��ĸ���
	//! \param eAssistantPoints �㴮,���صĸ�����㴮
	//! \param nEditType ���ƶ�������ͣ��ο�UGEditType
	 virtual void CalAssistantPoints(const UGPoint2D* pPoints,UGint nPntCount,UGArray<UGEditType::EditAssistantPoint>& eAssistantPoints,UGEditType::EditToolShape nEditType);

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

	//added by xielin ^_^ �༭��غ���,�ѱ༭��geometryͳһ end
	
protected: //! ������Ҫʵ�ֵ�һЩ����������
	//! \brief 
	virtual UGRect2D ComputeBounds() const;
	/*virtual UGRect2D GetBoundsInside() const;
	virtual void SetBoundsInside(const UGRect2D & rcBounds);*/
	
	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE)  const;
	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData( UGStream& stream , UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );

	//! \brief ֻת�ؼ������ݲ���
	//! \param stream �� 
	//! \param iGuge �û����õ�Load��ʽ��nGuge�жϲ���
	//! \param eCodecType ���뷽ʽ
	//! \attention ����Ҫ���� UGbool bSDBPlus = FALSE �Ĳ���
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool LoadGeoData( UGStream& stream , UGint iGuge, UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE);
	
private:
	
	//! \brief �����ı���Bounds�������Ѿ��ṩ�㹻�����Ϣ��
	static UGRect2D ComputeTextBounds(const UGString& strText,
		double dFontHeight, double dFontWidth, 
		const UGPoint2D& pntAnchor, 
		UGint nAlign, double dRadian=0, UGbool bAlignOffset=false);
	
	//! \brief �����ı����뷽ʽ������ƫ��
	//! \remarks ���뷽ʽΪ3 4 5 ʱ��������������룬����Baseline
	static UGRect2D AlignOffset(const UGRect2D& rcBounds, 
		UGint nAlign, double dFontHeight);
	
	// �ı��� Align == 3 4 5 ʱ, ��ʾ�����Ǿ��е�, ����BaseLine, 
	// ��ʾλ��Ҫ���� ƫ��һЩ, ������һ��ͳһ�ĺ�������ƫ�Ʊ���
	static double GetTextAlignOffset(UGbyte nAlign, double dFontHeight);
	
	//! \brief �õ��һ�е��ַ�����,  �������ַ���������
	//! \return ����ֵ:	UGSize::cx = �һ�е��ַ�����
	//!					UGSize::cy = �����ַ���������	
	static UGSize GetTextSize(const UGString& strText);
	
	//!  ������, ������ת֮��ľ���
	//! \param bAlign: ���뷽ʽ, ͬbCenterType
	//! \param dRadian: ��λ�ǻ���
	static UGRect2D UnionRotate(const UGRect2D& rcBounds, UGbyte bAlign, UGdouble dRadian); 
	
	//! \brief ��תһ��Rect2D�����ͨ��pPntResult���أ�pPntResult������4����Ŀռ�
	static void RotateRect(const UGRect2D& rcBounds, UGbyte bCenterType, UGdouble dRadian,
							UGPoint2D *pPntResult);
	
	//! \brief ��ȡ�Ӷ���ı߽��
	void GetVertexes(UGint nIndex, UGPoint2D* pPoints) const;
};

}

#endif

