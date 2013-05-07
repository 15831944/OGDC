//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)                
//                                                           
//!  \file  Drawing.h
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Co., Ltd.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_DRAWING_H__1B26EFAF_FF51_4B33_B1E2_4F440DB032C5__INCLUDED_)
#define AFX_DRAWING_H__1B26EFAF_FF51_4B33_B1E2_4F440DB032C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base/OgdcRect.h"
#include "Element/OgdcElemPoint.h"
#include "Element/OgdcElemMultiPoint.h"
#include "Element/OgdcElemLine.h"
#include "Element/OgdcElemText.h"
#include "Element/OgdcElemPoint3D.h"
#include "Element/OgdcElemLine3D.h"
#include "Element/OgdcElemRegion3D.h"

class CDrawing  
{
public:
	CDrawing();
	virtual ~CDrawing();

public:
	//! ��ʾ���ݼ���
	BOOL DrawDataset(CDC* pDC, OgdcDataset* pDataset);

	//! ��ʾ���ζ���
	BOOL DrawElement(CDC* pDC, OgdcElement* pElement, BOOL bSelected=FALSE);
	
	//! ȫ����
	void ViewEntire();
	
	//! ƽ�ơ�
	void Pan(double dOffsetX, double dOffsetY);
	
	//! ���š�
	void Zoom(double dRatio);

	//! �ı�ͻ�����С��
	void ChangeClient(const CRect& rcClient);

	//! ��������ת��ϵ����
	void SetCoordRatio(double dCoordRatio);

	//! �������굽�豸����ת����
	BOOL GeoToDevice(OgdcPoint2D* pPoint2Ds, int nCount, CPoint*& pPoints);	

	//! �������굽�豸����ת����
	BOOL GeoToDevice(OgdcPoint3D* pPoint3Ds, int nCount, CPoint*& pPoints);	

	//! �豸���굽��������ת����
	BOOL DeviceToGeo(CPoint* pPoints, int nCount, OgdcPoint2D*& pPoint2Ds);

protected:
	//! ��ʾ���ݼ���
	BOOL DrawVector(CDC* pDC, OgdcDatasetVector* pDatasetV);
	BOOL DrawRaster(CDC* pDC, OgdcDatasetRaster* pDatasetR);

	//! ��ʾ���ζ���
	BOOL DrawElement(CDC* pDC, OgdcElemPoint* pElemPoint, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemMultiPoint* pElemMultiPoint, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemLine* pElemLine, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemRegion* pElemRegion, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemText* pElemText, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemPoint3D* pElemPoint3D, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemLine3D* pElemLine3D, BOOL bSelected=FALSE);
	BOOL DrawElement(CDC* pDC, OgdcElemRegion3D* pElemRegion3D, BOOL bSelected=FALSE);

	unsigned short BitCount(PixelFormat pixelFormat);
	BOOL DrawRasterBlock(CDC* pDC, OgdcRasterBlock* pIBlock, OgdcDatasetRaster* pDatasetR, BITMAPINFO* pBitmapInfo);

public:
	OgdcRect2D m_rcBounds;			// ȫ����Χ���������ꡣ
	OgdcRect2D m_rcViewBounds;		// ��ʾ��Χ���������ꡣ
	CRect m_rcClient;				// �ͻ�����Χ���豸���ꡣ
	double m_dCoordRatio;			// �������굽�豸�����ת��ϵ����
	OgdcStyle m_curStyle;

};

#endif // !defined(AFX_DRAWING_H__1B26EFAF_FF51_4B33_B1E2_4F440DB032C5__INCLUDED_)
