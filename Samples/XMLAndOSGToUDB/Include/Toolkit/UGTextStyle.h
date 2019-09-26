
/*!
   **************************************************************************************
    \file     UGTextStyle.h
   **************************************************************************************
    \author   �¹���
    \brief    �ı������                                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-07-06  �¹���    ��ʼ���汾.                                       <br>
   **************************************************************************************
*/

#ifndef UGTEXTSTYLE_H
#define UGTEXTSTYLE_H

#include "Stream/ugdefs.h"

namespace UGC {

//! \brief �ı������
class TOOLKIT_API UGTextStyle  
{
public:
	//! \brief
	UGTextStyle();
	//! \brief
	UGTextStyle(const UGTextStyle& textStyle);
	//! \brief
	~UGTextStyle();

	//! \brief
	UGTextStyle& operator=(const UGTextStyle& textStyle);
	//! \brief
	UGbool operator==(const UGTextStyle& textStyle) const;
	//! \brief
	UGbool operator!=(const UGTextStyle& textStyle) const;

public:
	//! \brief
	UGbool FromOgdcTextStyle(const OgdcTextStyle& ogdcTextStyle);
	//! \brief
	UGbool ToOgdcTextStyle(OgdcTextStyle& ogdcTextStyle) const;
	
	//! \brief  �õ�������ɫ
	UGColor GetForeColor() const;	
	//! \brief  ����������ɫ
	void SetForeColor(UGColor foreColor);	
	  
	//! \brief  ����ɫ����Ӱɫ�����ɫ
	UGColor	GetBackColor() const;
	//! \brief  ���ñ���ɫ,ͬʱҲ����Ӱɫ�����ɫ
	void SetBackColor(UGColor backColor);	
	  
	//! \brief  �õ���ת�Ƕȣ��Զ�Ϊ��λ����ʱ�뷽��
	UGdouble GetAngle() const;	
	//! \brief  ������ת�Ƕȣ��Զ�Ϊ��λ����ʱ�뷽��
	void SetAngle(UGdouble dAngle);

	//! \brief  �õ������ȣ�����λ
	UGdouble GetWidth() const;
	//! \brief  ���������ȣ�����λ
	void SetWidth(UGdouble dWidth);

	//! \brief  �õ�����߶ȣ�����λ
	UGdouble GetHeight() const;	
	//! \brief  ��������߶ȣ�����λ
	void SetHeight(UGdouble dHeight);
	// added by lidl 2008-9-10 16:43:20
	  
	//! \brief  �õ��ֺ�,��λ���� 
	UGdouble GetSize() const;
	//! \brief  �����ֺţ���λ����
	void SetSize(UGdouble dSize);	
	
	//! \brief �õ���������	
	UGString GetFaceName() const;
     //! \brief  ������������
	void SetFaceName(const UGString& strFaceName);
	
	//�ı��ķ��,   0x BYTE4 BYTE3 BYTE2 BYTE1 
	//�ɼ��������,	     |     |     |     |
	//��������ͼ:        |     |     |     +--Text Align
	//				     |     |     +--Text Style
	//				     |     +--Text Font Weight
	//                   +--Text Other Attribute 
	//========================================================
	//BYTE1 �ı��Ķ��뷽ʽ
	//	   ��  ��  ��
	// ��	0	1	2
	// ��	3	4	5
	// ��	6	7	8
	//--------------------------------------------------------
	//BYTE2 �ı���һ����	   ���ֽ�     ��m_lStyle��
	//����	(Bold)				0x01     ( 0x00000100 )
	//б��  (Italic)			0x02     ( 0x00000200 )
	//�»���(Underline)			0x04     ( 0x00000400 )
	//ɾ����(Stroke)			0x08     ( 0x00000800 )
	//--------------------------------------------------------
	//BYTE2 �ı��ĸ߼����	   ���ֽ�     ��m_lStyle��
	//�̶���С(FixedSize)		0x10     ( 0x00001000 )
	//�������(Opaque)			0x20     ( 0x00002000 )
	//��������(Outline)			0x40     ( 0x00004000 )    
	//��ʾ��Ӱ(Shadow)			0x80     ( 0x00008000 )    
	//--------------------------------------------------------
	//BYTE3 �ı��ıʻ���ϸ --> ��windowsһ��
	//--------------------------------------------------------
	//BYTE4�̶���С���ı��ĳߴ� ���ֽ�    ��m_lStyle��
	//�̶��Ĵ�С(FixedSize)		0xff     ( 0xff000000 )
	//========================================================
	//! \brief  �õ����з����Ϣ:���壬б�壬͸��������,���е�
	UGint GetStyle() const;			
	//! \brief �������еķ�񣬸߼��û�ʹ��!
	void SetStyle(UGint nStyle);	

	//! \brief Toolkit
	//! \brief  �Ƿ����
	UGbool IsBold() const;	
	//! \brief  �����Ƿ����
	void SetBold(UGbool bBold = true);				
	
	//! \brief  �Ƿ��»���
	UGbool IsUnderline() const;
	//! \brief  �����Ƿ��»���
	void SetUnderline(UGbool bUnderline = true);		
	  
	//! \brief  �Ƿ�б��
	UGbool IsItalic() const;	
	//! \brief  �����Ƿ�б��
	void SetItalic(UGbool bItalic = true);			
	
	//! \brief  �Ƿ�ɾ����
	UGbool IsStrikeOut() const;		
	//! \brief �����Ƿ�ɾ����
	void SetStrikeOut(UGbool bStrikeOut = true);
	
	//! \brief  �õ����뷽ʽ
	UGbyte GetAlign() const;				
	//! \brief  ���ö��뷽ʽ,��ϸ�ļ�SetStyle������ע
	void SetAlign(UGbyte nAlign = 0);
	
	//! \brief  �õ����뷽ʽ
	UGbyte GetStringAlign() const;				
	//! \brief  ���ö��뷽ʽ
	void SetStringAlign(UGbyte nAlign = 0);
	  
	//! \brief  �õ��ı��ıʻ����
	UGint GetWeight() const;					
	//! \brief  �����ı��ıʻ����
	void SetWeight(UGint nWeight);	
	  
	//! \brief  �Ƿ�̶���С
	UGbool IsFixedSize() const;			
	//! \brief �̶���С�����岻���ͼ�����Ŷ�����
	void SetFixedSize(UGbool bFixedSize=true);			
	
	//! \brief  �̶���С�ĳߴ磬mm��λ
	UGdouble GetSizeForFixed() const;			
	//! \brief ���ù̶���С�ĳߴ磬mm��λ
	void SetSizeForFixed(UGdouble dSize);		

	  
	//!  \brief �Ƿ񱳾���͸��, ע����,true��ʾ��͸��!!
	UGbool IsBackOpaque() const;				
	//! \brief  �����Ƿ񱳾���͸��
	void SetBackOpaque(UGbool bBackOpaque = false);				

	//! \brief �Ƿ���ʾ����
	UGbool IsHalo() const;			
	//! \brief  �����Ƿ���ʾ����
	void SetHalo(UGbool bHalo = true);	

	//! \brief  ����������ȣ��������굥λ����Χ0~5
	void SetHaloWidth(UGint nWidth);
	//! \brief  �õ��������
	UGint GetHaloWidth() const;

	//! \brief  �������ֱ������α�Ե�����ֱ�Ե�����ȣ��������굥λ��
	void SetBorderSpacingWidth(UGint nWidth);
	//! \brief  �õ����ֱ������α�Ե�����ֱ�Ե������
	UGint GetBorderSpacingWidth() const;

	//{{added by mahb at 20120716
	//! \brief  ���ñ�����͸����
	//! \params ucTransparency ͸���ȣ�0~255��0Ϊ͸����255Ϊ��͸��
	void SetBackTransparency(UGuchar ucTransparency);
	//! \brief  ��ȡ������͸����
	UGuchar GetBackTransparency() const;
	
	//! \brief  �Ƿ���ʾ��Ӱ
	UGbool IsShadow() const;	
	//! \brief  �����Ƿ���ʾ��Ӱ
	void SetShadow(UGbool bShadow = true);			
	
	UGbool FromXML(const UGString& strXML, UGint nVersion = 0);

	UGString ToXML(UGint nVersion = 0) const;

		//! \brief ��ȡ�ı��������hashcode
	UGint GetHashCode() const;

	//! \brief ��ȡ/�����ʼ�Ч��,����60��֮�䣬Ŀǰֻ�Ա�ǩר��ͼ��Ч��������Ƕ�Ϊ��λ
	UGdouble GetItalicAngle() const;
	void SetItalicAngle(UGdouble nItalicAngle);

	//! \brief  �õ�3D�ı���͸����
	//! \remarks �ò���������ά��ʹ�ã�֧�ֱ���ΪXMLUGC��Ϣ,SFC�汾�����棬���ݿ��в��������Ϣ��Ĭ��Ϊ100,��͸��,OGDC�в�����˷��
	UGint GetText3DOpaque() const;		
	//! \brief ����3D�ı��Ĳ�͸����
	void SetText3DOpaque(UGint nOpaque);
	
	//! \brief �õ�3D�ı������ű���
	//! \remarks �ò���������ά����ʱʹ�ã������棬OGDC�в�����˷��
	UGdouble  GetText3DScale() const;		
	//! \brief �����ı������ű���
	void SetText3DScale(UGdouble dScale);	

	//! \brief ��ȡ��ӰX����ƫ����
	 UGdouble GetShadowOffsetX() const;	
	//! \brief ������ӰX����ƫ����
	void SetShadowOffsetX(UGdouble nValue);

	//! \brief ��ȡ��ӰX����ƫ����
	UGdouble GetShadowOffsetY() const;	
	//! \brief ������ӰX����ƫ����
	void SetShadowOffsetY(UGdouble nValue);

	//! \brief ��ȡ��Ӱ��ɫ
	UGColor GetShadowColor() const;
	//! \brief ������Ӱ��ɫ
	//! \param clrColor ��Ӱ��ɫ
	void SetShadowColor(UGColor clrColor);

	//! \brief ����Style��Ĭ��ֵ,������ӿڵ�Ĭ��ֵ����һ��
	//! Ŀǰ��UGMap��m_showTimeTextStyleʹ�ã���������
	void SetDefault();

	//! \brief ��ȡ�����Ƿ�������б
	UGbool IsLeftItalic() const;
	void SetLeftItalic(UGbool isLeftItalic);

	// �ڲ�����ǩ���Ʊ���ʱʹ�õģ������κ�FromXML��ToXML����Ҫ������������; by gouyu 2014-8-18
public:
	UGint		m_backMode;				// ��ǩ������ʽ��Ŀǰֻ֧�־��κ�Բ�Ǿ��Σ��Ҵ�ɫ�ı���
	UGColor		m_backStyleLineColor;	// ��ǩ�����ı�����ɫ
	UGColor		m_backStyleRectColor;	// ��ǩ�����ı�����ɫ	
	UGbool		m_drawBack;				// �Ƿ���Ʊ����������IDΪ1ʱ����Ϊfalse���Ͳ����Ʊ���
	UGbool		m_drawLine;				// �Ƿ���Ʊ��ߣ�������IDΪ5ʱ����Ϊfalse���Ͳ����Ʊ���
	UGbyte		m_fillOpaqueRate;		// ����͸����

	// �廪ɽά UGGeoTextEPS ���ͷ���е�ʣ�����Ա
	UGint		m_nFontInterval;		//�ָ�
	UGdouble	m_dDownAngle;			//�ʼ�,�ֵ����½ǵ��ֵ����½�����ߵļн�(��)
	UGdouble	m_dWordAngle;			//�ֽǶ�,�ֵ����������ļн�(��)
	UGint		m_nBackBorderStyle;		//�߿���ʽ
	UGint		m_nBackLineWidth;		//�߿��߿�

private:
	UGColor		m_ForeColor;			//! ������ɫ
	UGColor		m_BackColor;			//! ����ɫ����Ӱɫ�����ɫ
	UGint		m_nAngle;				//! ��ת�Ƕȣ���0.1��Ϊ��λ,x����������Ϊ��ʼ����ʱ�뷽��
	UGint		m_nItalicAngle;			//! ��ת�Ƕȣ���0.1��Ϊ��λ,x����������Ϊ��ʼ����ʱ�뷽��
	UGdouble	m_dWidth;				//! �����ȣ�����λ
	UGdouble	m_dHeight;				//! ����߶ȣ�����λ
	UGString	m_strFaceName;			//! ��������
	UGint		m_nStyle;				//! ���:���壬б�壬͸��������,���е�	
	UGbyte      m_nText3DOpaque;
	UGdouble    m_dText3DScale;
	//UGdouble    m_dSize;				//! �����ֺ�

	//{{ added by mahb at 20120716
	UGuchar     m_ucBackTransparency;   //! ����͸����

	UGint		m_nHaloWidth;			//! �����Ŀ�ȣ����ص�λ����Χ�Ǵ�0~5����

	UGint		m_nBorderSpacingWidth;	//! �������ο��Ե�����ֱ�Ե�ļ�����룬���ص�λ

	//! \brief ��ӰX����ƫ����
	UGdouble	m_dShadowOffsetX;//���ص�λ
	//! \brief ��ӰY����ƫ����
	UGdouble	m_dShadowOffsetY;
	//! \brief ��Ӱ����ɫ
	UGColor		m_clrShadowColor;   

};

}

#endif

