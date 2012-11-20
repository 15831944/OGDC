//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)                
//                                                           
//!  \file  ViewerWnd.h
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Co., Ltd.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_VIEWERWND_H__944E6454_DD9D_4268_B4C1_CC322BCA0EB8__INCLUDED_)
#define AFX_VIEWERWND_H__944E6454_DD9D_4268_B4C1_CC322BCA0EB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Drawing.h"

class CViewerWnd  
{
public:
	enum ViewAction			//! ����Ĳ�����ʽ��
	{
		uaNull				=0,	//! ʲôҲ���ɡ�
		uaPan				=1,	//! ��ͼƽ�ơ�
		uaZoomIn			=2,	//! �Ŵ�
		uaZoomOut			=3,	//! ��С��
		uaPointSelect		=4,	//! ��ѡ��
	};
	
public:
	CViewerWnd();
	virtual ~CViewerWnd();

public:
	//! ��ʼ���͹رմ���
	void InitialUpdate(CWnd *pWnd);
	void OnClose();
	void AddDataset(OgdcDataset* pDataset, OgdcStyle& style, OgdcString& strName, BOOL bClear = FALSE);

	//! ���õ�ǰ��������Ĳ�����ʽ
	void SetViewAction(LONG nAction);
	LONG GetViewAction() const;

	//! �õ�ѡ��ID�����ݼ���
	LONG GetSelectID() const;
	OgdcDatasetVector* GetSelectDataset() const;
	//! �õ�ѡ�ж���ID��ѡ���з���-1��
	LONG HitTest(const OgdcPoint2D& pntHitTest);	
	LONG FindDataset(OgdcDataset* pDataset);

	//! ��������
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	//! ���ڴ�С�ı䡣
	void OnSize(UINT nType, int cx, int cy);
	//! ��ʾ����
	void OnDraw(CDC* pDC, const CRect& rcClient);
	//! ˢ�¡�
	void Refresh();

protected:
	//! �����ͼ��Χ��
	OgdcRect2D ComputeBounds();
	LONG HitTest(const OgdcPoint2D& pntHitTest, OgdcDatasetVector* pDtV);
	BOOL HitTest(const OgdcPoint2D& pntHitTest, OgdcElemRegion* pElemRegion, double dTolerance);
	BOOL HitTest(const OgdcPoint2D& pntHitTest, OgdcElemLine* pElemLine, double dTolerance);
	BOOL IsProjectOnLineSegment(const OgdcPoint2D& pntHitTest, const OgdcPoint2D& pntLinsectStart, 
		const OgdcPoint2D& pntLinsectEnd);
	
public:
	CDrawing m_drawing;
	OgdcArray<OgdcDataset*> m_datasets;
	OgdcArray<OgdcStyle> m_styles;
	OgdcArray<OgdcString> m_names;
	LONG m_nViewAction;
	LONG m_nSelectID;
	OgdcDatasetVector* m_pSelectDataset;

protected:
	BOOL m_bRefresh;
	BOOL m_bDowning;
	CPoint m_pntStart;

	CBitmap m_bitmap;
	CBitmap* m_pOldBitmap;
	CDC m_memDC;
	CWnd* m_pWnd;
};

#endif // !defined(AFX_VIEWERWND_H__944E6454_DD9D_4268_B4C1_CC322BCA0EB8__INCLUDED_)
