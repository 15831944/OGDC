/*! \file	 UGGeometryEPS.h
 *  \brief	 �廪ɽά CGeoBase ����
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
 *  All Rights Reserved
 *  \version $Id: UGGeoPoint.h,v 1.8 2009/09/07 10:33:28 duxm Exp $
 */


#ifndef UGGEOMETRYEPS_H
#define UGGEOMETRYEPS_H

#include "Geometry/UGGeometry.h"

namespace UGC {

//float:
#define  ZERO_FLOAT (+1.401298E-45)
#define  MIN_FLOAT	(-3.402823E+38)
#define  MAX_FLOAT	(+3.402823E+38)

//double:
#define  ZERO_DOUBLE   (+4.94065645841247E-324)
#define  MIN_DOUBLE	 (-1.79769313486232E+308)
#define  MAX_DOUBLE	 (+1.79769313486232E+308)

//int:
#define  MIN_SHORT	-32768
#define  MAX_SHORT	+32767

//long:
#define  MIN_LONG	-2147483648
#define  MAX_LONG   +2147483647

//�����ݲ��������ݲ�
#define MINI_COORDINATE	0.001
#define MINI_FLOAT	0.000001
#define MINI_DOUBLE 0.0000000001

typedef enum ObjStatusEnum
{
	e_Valid          =  0x0001,   //�Ƿ���Ч
	e_Explode        =  0x0002,   //�Ƿ��Ѵ�ɢ
	e_Screen         =  0x0004,   //�Ƿ�����
	e_Duplicate		 =  0x0008,   //�Ƿ񱻸���Ʒ
	e_Quote          =  0x0010,   //�Ƿ�����
	e_Hidden         =  0x0020,   //�Ƿ�����
	e_Selected       =  0x0040,   //�Ƿ���ѡ�� 
	e_Editable       =  0X0080,   //�Ƿ�ɱ༭
	e_Highlight      =  0X0100,   //�Ƿ����
	e_Gray           =  0X0200,   //�Ƿ���
	e_Edited         =  0X0400,   //�Ƿ��޸�
	e_Refrence       =  0X0800,   //�ο�ͼ��
	e_Opaque         =  0X1000,   //�Ƿ�ѹ��
	e_Mirror         =  0X2000,   //�Ƿ���
	e_Virtual        =  0X4000,   //�Ƿ����������
};


class GEOMETRYCAD_API UGGeometryEPS : public UGGeometry
{
protected:

	UGString 			m_strLayer;           //���������û�����
	UGshort				m_Status;	        //����״̬---����,��ɾ��
	UGuint				m_SymbolRef;        //���Ż��ο�

	UGString		    m_strObjName;			//��������
	UGPointEPSs			m_Points;			//����
	UGArray<UGint>		m_relGeoIDs;			//��ϵ

	UGColor				m_Color;			//��ɫ
	UGColor             m_FillColor;        //�����ɫ

	UGint		        m_Code;             //����������
	UGshort		        m_LineWidth;	    //�߿�
	UGshort		        m_LineType;	        //�������ͣ�0�������1�����ߡ�2�����ߡ�3��Բ����4��Բ��
									        //��Ϊ����0�������1��һ������㣬2������㣬3����㡣

	UGString            m_strMemoData;        //�ⲿ��������
	UGString            m_strDataMark;        //���ݱ�ʶ�ַ���
	UGString            m_strByname;          //����

	UGuint              m_nGroupID;			//���ʶ
	UGdouble            m_dCreateTime;      //����ʱ��
	UGdouble            m_dEditTime;        //�޸�ʱ��
	UGdouble            m_dReference;       //����

	UGArray<UGbyte>     m_GraphicInfo;     //ͼ������


	//! \brief ���캯��
	UGGeometryEPS();
	
	//! \brief ��������
	virtual ~UGGeometryEPS();
	
public: //pure virtual 

	//! \brief ���Geometry�ڲ�����
	virtual void Clear() = 0;
	
	//! \brief �õ�ά��, �̶�Ϊ0
	virtual UGint GetDimension() const = 0;
	
	//! \brief �õ�����, �̶�Ϊ GeoPoint
	virtual Type GetType() const = 0;
	
	//! \brief �õ��ڵ㣨��Geometry�ڲ�����������ĵ㣩, ��Ϊ����ĵ�
	//! \return �����ڵ�
	virtual UGPoint2D GetInnerPoint() const = 0;

	//������ID
	void SetGroupID( UGuint id );
	UGuint GetGroupID( ) const;

	//������������
	void SetCode( UGint code );
	UGint GetCode( ) const;

	//�û�ʹ�õķ����־
	//���ڲ���: strDataMark(�û�ʹ�õķ����־)
	void    SetUserID( const UGString& strUserID );
	//����ֵ: �û�ʹ�õķ����־
	UGString GetUserID();

	//����״̬
	//���ڲ���: bFlag(�Ƿ��Ǵ�״̬),eInfo(״̬��Ϣ)
	void SetStatus(UGbool bFlag, ObjStatusEnum eInfo) ;
	//���ڲ���: eInfo(״̬��Ϣ)
	//����ֵ: TRUE��ʾ�Ǵ�״̬,FALSE��ʾ���Ǵ�״̬
    UGbool GetStatus( ObjStatusEnum eInfo) const;

	//��ȡ�����õ���״̬��Ա
	UGshort GetObjStatus() const;
    void SetObjStatus( UGshort eInfo) ;

	//���ʱ��
	//���ڲ���: nType(0����ʱ��,1�޸�ʱ��)
	//����ֵ: ʱ�����
	UGTime GetDateTime( UGuint nType = 1 );
	//����ʱ��
	//���ڲ���: DateTime(ʱ�����),nType(0����ʱ��,1�޸�ʱ��)
	void SetDateTime( UGTime& DateTime , UGuint nType = 1 ) ;

	//���ʱ��
	//���ڲ���: nType(0����ʱ��,1�޸�ʱ��)
	//����ֵ: ʱ����ֵ
    UGdouble GetDblDateTime( UGuint nType = 1 );

	//����ʱ��
	//���ڲ���: DateTime(ʱ����ֵ),nType(0����ʱ��,1�޸�ʱ��)
	void SetDblDateTime( UGdouble DateTime ,UGuint nType = 1 );

	// �����߿�
	//���ڲ���: lineWidth(�߿�)
	UGshort SetLineWidth(UGshort lineWidth);
	//����߿�
	//����ֵ: �߿�
	UGshort GetLineWidth() const;

	//�������ͷ����Ա
 	//���ڲ���: nStyle(���ͷ����Ա)
	void SetStyleDirection( UGshort nType );
	//������ͷ����Ա
	//����ֵ: ���ͷ����Ա
	UGshort GetStyleDirection() const ;

	// ��������
	//���ڲ���: lineType(����)
	UGshort SetLineType(UGshort lineType) ;
	//�������
	//����ֵ: ����
	UGshort GetLineType() const ;

	//��������ʽ ( ����, ������, �����... )
	//���ڲ���: lineStyle(����ʽ)
	UGshort SetLineStyle(UGshort lineStyle) ;
	//�������ʽ
	//����ֵ: ����ʽ
	UGshort GetLineStyle() const ;

	//���������ζ�����(��ѡֵ(0,1,2,3~16)/16 LC��������һ������, Y, P�����һ�߶γ���)
	//���ڲ���: scale(�ζ�����)
	UGshort SetLShapeOffset(UGshort scale) ;
	//����ζ�����
	//����ֵ: �ζ�����
	UGshort GetLShapeOffset() const ;

	//���������ܶȱ���
	//��scale <= 1/8 ʱ, Ϊʵ���� 
	//��scale >=  8  ʱ, �����(����) 

	//�������������ܶȱ���
	//���ڲ���: scale(����ܶȱ���)
	UGdouble SetHatchDensityScale( UGdouble scale );
	//������������ܶȱ���
	//����ֵ: ���������ܶȱ���
	UGdouble GetHatchDensityScale() const ;

	//����ϵͳ��������ʽ
	//���ڲ���: nStyle(��������ʽ)
	UGshort  SetSysHatchStyle( UGshort nStyle );
	//����������������ʽ
	//����ֵ: ��������ʽ
	UGshort  GetSysHatchStyle() const;

	// ������ɫ
 	//���ڲ���: color(��ɫ)
	UGColor SetColor(UGColor color) ;
	//�����ɫ
	//����ֵ: ��ɫ
	UGColor GetColor() const;

	//�������ɫ
 	//���ڲ���: color(���ɫ)
	UGColor SetFillColor(UGColor color) ;
	//������ɫ
	//����ֵ: ���ɫ
	UGColor GetFillColor() const ;

	//��ȡ���еĵ���
	UGint   GetPointSize() const;
	//��ȡ����
	//���ڲ���: Points(��λ����)
	void  GetPointList( UGPointEPSs& Points);
	//���õ���
 	//���ڲ���: pointList(�����µ���)
	void  SetPointList(const UGPointEPSs &pointList) ;

	// �õ�ָ������ĵ㴮��ָ�롣
	// ���ض���ĵ㴮��ָ�롣
	const UGPointEPS* GetPoints() const;

	//��ȡһ���㿽��
	//���ڲ���: index(������ָ���±�), index = -1 ָ���һ����
	//����ֵ: ��
	UGPointEPS& GetPoint(UGint index ) ;

	//������м�һ����	
	//���ڲ���: Point(�����ĵ�)
	bool    SetPoint( UGint index, UGPointEPS point );

	//������м�һ����	
	//���ڲ���: Point(�����ĵ�)
	int    AddPoint( UGPointEPS Point ) ;

	//������в���һ����	
	//���ڲ���: Point(�����ĵ�)
	bool InsertPoint(UGint index, UGPointEPS point);

	//�Ƴ�������ָ���ĵ�	
	bool RemovePoint(UGint index);

	//�Ƴ����������еĵ�	
	void    RemoveAllPoint();

	//��ú����������
	//����ֵ: �����������
	virtual UGdouble GetScaleX();
	//��������������
	//����ֵ: �����������
	virtual UGdouble GetScaleY() ;
	//��������������
	//����ֵ: �����������
	virtual UGdouble GetScaleZ() ;
	//���ú����������
 	//���ڲ���: dScaleX(�����������)
	virtual void SetScaleX( UGdouble dScaleX) ;
	//���������������
 	//���ڲ���: dScaleY(�����������)
    virtual void SetScaleY( UGdouble dScaleY) ;
	//���������������
 	//���ڲ���: dScaleZ(�����������)
	virtual void SetScaleZ( UGdouble dScaleZ) ;

	//��ýǶ�(��������ת��)
	//����ֵ: �Ƕ�
	UGfloat GetAngle() const;
	//���ýǶ�(��������ת��)
	//���ڲ���: newAngle(�½Ƕ�)
	//����ֵ: ԭ�Ƕ�
	UGfloat SetAngle( UGfloat newAngle); 

	//����
	//���ڲ���: strName(��������)
	void SetName( UGString& strName );
	//����ֵ: ��������
	UGString GetName() const;

	//����
	//���ڲ���: dReference(����)
	void SetReference( UGdouble dReference );
	//����ֵ: ����
	UGdouble GetReference( ) const;

	//���Ż��ο�
	//���ڲ���: SymbolRef(���Ż��ο�)
	void SetSymbolRef( UGuint SymbolRef );
	//����ֵ: ���Ż��ο�
	UGuint GetSymbolRef( ) const;

	//���÷��ų���
	//���ڲ���: shDirection(���ų���)
	void SetDirection( UGshort shDirection );
	//��÷��ų���
	//����ֵ: ���ų���
    UGshort GetDirection() const;

	//����������Ϣ
	void SetMemoData( const UGStrings& strFields, const UGStrings& strValues );
	void SetMemoData( UGStrings& strValues );
	void SetMemoData( UGString& strValues );

	int  GetMemoData( UGStrings& strFields, UGStrings& strValues );
	UGbool GetMemoData( UGStrings& strValues ) const;
	UGString GetMemoData() const;
	UGString GetMemoData( const UGString& strField );

	void SetGraphicInfo( UGArray<UGbyte>& bytes );
 	UGbool GetGraphicInfo( UGArray<UGbyte>& bytes ) const;

	UGbool IsContainsPointType(PointEPSType pointType) const;

	//����RelationID����
 	//���ڲ���: relArr(RelationID����)
	void    SetRelation( const UGArray<UGint>& relArr );

	//���RelationID����
	//����ֵ: RelationID����
	void    GetRelations( UGArray<UGint>& relArr ) const;

	//! \brief �������, ���ڶ����ѡ
	//! \param pntHitTest ��������ѡ�еĵ�
	//! \param dTolerance ����
	//! \return ѡ�з���true, ���򷵻�false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const = 0;
	
	//! \brief �õ��ռ�����, ��Ҫ������Ҫ����ά����ͬʱ
	//! ����ͳһ�����ʱ��, ����һЩ�ռ��жϺͲ������㷨
	//! \param pPoints �����ĵ���������[out]��
	//! \param pPolyCount ������ÿ���Ӷ�������������[out]��
	//! \param nSubCount �������Ӷ������[out]��
	//! \param nSegmentCount �Բ���������, ÿ�����ηָ��ĸ���[in]��
	//! \remarks ��������������ָ��ļ���,�����߲����ͷ��ڴ�ռ�
	//! \return �ɹ�����true,���򷵻�false��
	virtual UGbool GetSpatialData(UGAutoPtr<UGPoint2D>& pPoints, 
		UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const = 0;
	
	//! \brief ���ζ����Ƿ���Ч
	//! \return ����true; ��Ϊ�޷��ж��Ƿ���Ч
	virtual UGbool IsValid()const = 0;
	
	//! \brief ����
	//! \param dRatioX X�������ű���
	//! \param dRatioY Y�������ű���
	virtual void Inflate( UGdouble dRatioX, UGdouble dRatioY) = 0;
	
	//! \brief ����
	//! \param dRatio ���ű���(X,Y������ͬ)
	virtual void Inflate( UGdouble dRatio) = 0;
	
	//! \brief ƽ��
	//! \param dX ƽ�Ƶ�Xƫ����
	//! \param dY ƽ�Ƶ�Yƫ����
	virtual void Offset( UGdouble dX, UGdouble dY) = 0;
	
	//! \brief ƽ��
	//! \param ƫ����(X,Y������ͬ)
	virtual void Offset( UGdouble dOffset) = 0;
	
	//! \brief ƽ��
	//! \param ƽ�Ƶ�ƫ����(�ֱ���UGSize2D�е�x,y����X,Y�����ƫ����)
	virtual void Offset( const UGSize2D &szOffset) = 0;
	
	//! \brief ��ת
	//! \param pntOrigin ��ת�����ĵ�(ê��,������)
	//! \param dAngle ��ת�Ƕ�
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dAngle) {};
	
	//! \brief ��ת,����һЩ����,�Ա��ڲ����Բ��ý���cos,sin, �����������ʱ�����������Ч��
	//! \remarks dAngle���ƶ���,��GeoText��Ҫ,����Ҫ����
	//! \param pntOrigin ��ת�����ĵ�(ê��,������)
	//! \param dCosAngle ��ת��cosֵ
	//! \param dSinAngle ��ת��sinֵ
	//! \param dAngle ��ת�Ƕ�
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dCosAngle,
						UGdouble dSinAngle, UGdouble dAngle = 0) = 0;
	
	//! \brief ������������,�޶����µ�Bounds��
	//! \param rcNewBounds �µ�,�޶���Χ��Bounds
	//! \remarks ������ΪBounds�����ĵ�
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Resize(const UGRect2D& rcNewBounds) = 0; 
	
	//! \brief ���㾵��
	//! \param pntMirror1 ���ɾ���ĵ�һ����
	//! \param pntMirror2 ���ɾ���ĵڶ�����
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool Mirror(const UGPoint2D &pntMirror1, const UGPoint2D &pntMirror2) {return FALSE;};
	
public: // �õ���������Ϣ

	//! \brief �õ��Ӷ������
	//! \return �����Ӷ������
	//! \remarks �̶�Ϊ1��
	virtual UGint GetSubCount() const;	
	
	virtual UGint GetDataSize() const;

public:
	
	//! \brief ����ͶӰת���������ú�ת������Ҫ��, ����ͶӰת��
	//! \param pPJTranslator ͶӰת����
	//! \param bForward ת������, true�����UGRefTranslator��Դ(Src)ת����Ŀ��(Des), false���෴
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);
	virtual UGbool PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward ,UGbool bClip );

	//! \brief �Ӿ�γ����ϵͳת��ΪͶӰ����ϵͳ
	//! \param pCoordSys ͶӰ����ϵͳ
	virtual void PJForward( UGPrjCoordSys *pCoordSys );

	//! \brief ��ͶӰ����ϵͳת��Ϊ��γ����
	//! \param pCoordSys ͶӰ����ϵͳ
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );

#if PACKAGE_TYPE==PACKAGE_UGC

	//! \brief ����XML��ʽ����Ϣ
	//! \param versionType GML�İ汾
	//! \param nPace �����Ŀո���Ŀ,ʹ��xml�ַ������������˹��Ķ�; 
	//! ��Ҫ����������ص�xml�ַ�����һ�����ǩ�е�һ����, ͨ��ָ���ո���Ŀ,����ʹ�������
	//! \return ����ָ��GML�汾��xml�ַ���
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0) const {return _U("");};

	//! \brief ��XML�ַ���������Geometry
	//! \param strXML xml��ʽ�ַ���
	//! \param versionType xml�ַ�����GML�汾
	//! \return ����ָ��GML�汾��xml�ַ���
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType = SML) {return FALSE;};
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief Geometry��Element��ת��
	//! \param pElement,���ص�pElementָ���ں����ڷ����ڴ�,���渺��ɾ������������ڴ�й©
	virtual UGbool ToElement(OgdcElement*& pElement)  const {return FALSE;};

	//! \brief Geometry��Element��ת��
	//! \param pElement,�����Element������޷�ת���򷵻�False�����򷵻�True
	virtual UGbool FromElement(const OgdcElement* pElement) { return FALSE;};
#endif

#endif // end declare ugc sdk

public:
	
	//! \brief ��ñ༭����ľ������Ŀ
	//! \remarks ���ڹ̶��������Ϊ9�����˸ı��С��8�����Ƶ��һ����ת���Ƶ�
	virtual UGint  GetHandleCount(){return 0;};

	
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
	virtual UGint GetHandle( UGint nHandle, UGPoint2D& point){return 0;};


	//! \brief �ƶ����Ƶ㵽ָ������,��Ҫ���ڻ��ƶ����޸Ķ���ڵ�Ȳ���
	//! \param nHandle ���Ƶ���
	//! \param point ���Ƶ�����
	virtual void MoveHandle( UGint nHandle, const UGPoint2D& pnt2D,UGEditType::EditToolShape nEditType=UGEditType::ET_Default){};

	//! \brief �ڵ�༭ʱ����������һ�����Ƶ�,Ҳ�������ڻ��ƶ���ʱ����ڵ�
	//! \param nHandle ����λ��
	//! \param pnt2D �����ĵ�������
	virtual void AddHandle( UGint nHandle, const UGPoint2D& pnt2D,UGEditType::EditToolShape nEditType=UGEditType::ET_Default){};
	
	//! \brief ɾ���༭�����ָ���ڵ�
	//! \param nHandle �ڵ���
	virtual UGuint DelNode( UGint nHandle ) {return 0;};

	//! \brief ����������ʱ�ĸ����ߣ����ص���һ�����϶���
	//! \param pPoints �㴮
	//! \param nPntCount  ��ĸ���
	//! \param nEditType ���ƶ�������ͣ��ο�UGEditType
	//! \param pStyle	 �����ߵķ���������ΪNULL����Ĭ�ϵķ��
	virtual UGGeometry*  CalAssistantLine(const UGPoint2D* pPoints,UGint nPntCount,UGEditType::EditToolShape nEditType,UGStyle* pStyle=NULL){return NULL;};
	
protected: //! ������Ҫʵ�ֵ�һЩ����������
	//! \brief 
	virtual UGRect2D ComputeBounds() const = 0;

	virtual void CopyBaseData(const UGGeometryEPS& geo);
	
	//! \brief �洢��Stream��
	virtual UGbool SaveGeoData(UGStream& stream, UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;
	//! \brief ��Stream������Geometry
	virtual UGbool LoadGeoData( UGStream& stream , UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );
	//! \brief ֻת�ؼ������ݲ���
	//! \param stream �� 
	//! \param iGuge �û����õ�Load��ʽ��nGuge�жϲ���
	//! \param eCodecType ���뷽ʽ
	//! \attention ����Ҫ���� UGbool bSDBPlus = FALSE �Ĳ���
	//! \return �ɹ�����true,ʧ�ܷ���false
	virtual UGbool LoadGeoData( UGStream& stream , UGint iGuge, UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE);
};


}

#endif

