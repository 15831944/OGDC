//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)         
//                                                           
//!  \file OgdcDatasetRasterMdb.h
//!  \brief դ�����ݼ��Ľӿڶ��塣
//!  \details դ�����ݼ��ĸ��ֽӿ�
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDCDATASETRASTERMDB_H__4FE7AE19_5388_451A_9C07_FC96405F8E5A__INCLUDED_)
#define AFX_OGDCDATASETRASTERMDB_H__4FE7AE19_5388_451A_9C07_FC96405F8E5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDatasetRaster.h"
#include "Base/OgdcDict.h"
#include "OgdcDataSourceMdb.h"
#include "Base/OgdcRect.h"

namespace OGDC
{

//! \brief դ�����ݼ�ʵ�ֵ���
//! \remarks դ�����ݼ�����Ӱ�����ݼ���Grid���ݼ���
class OGDC_API OgdcDatasetRasterMdb : public OgdcDatasetRaster  
{
	//! \brief ������Ԫ��
	friend class OgdcDataSourceMdb;

public:
	//! \brief դ�����ݼ���Ĭ�Ϲ��캯��
	OgdcDatasetRasterMdb();

	//! \brief ��ָ������Դָ��Ĺ��캯��
	//! \param pDataSource ָ������Դ��ָ��[in]��
	OgdcDatasetRasterMdb(OgdcDataSourceMdb *pDataSource);

	//! \brief դ�����ݼ�Ĭ����������
	virtual ~OgdcDatasetRasterMdb();
	
public:
	//! \brief �ж����ݼ��Ƿ��Ѿ��򿪡�
	//! \return �򿪷���TRUE�����򷵻�FALSE��
	virtual OgdcBool IsOpen() const ;

	//! \brief �����ݼ���
	//! \return �Ƿ�ɹ������ݼ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool Open() ;

	//! \brief �ر����ݼ���
	//! \return �Ƿ�ɹ��ر����ݼ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual void Close() ;	
	
	//! \brief ���������ݼ���
	//! \param strNewName �µ����ݼ���[in]��
	//! \return �Ƿ�ɹ����������ݼ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks ֻ�ı����ݼ���,�������䡣
	virtual OgdcBool Rename(const OgdcString& strNewName) ;
	
	//! \brief �жϵ�ǰ���ݼ��Ƿ�ɱ༭��
	//! \return �ɱ༭����TRUE�����ɷ���FALSE��
	virtual OgdcBool CanUpdate() ;
	
	//! \brief �����ݼ�������Ϣ���浽���ݿ��С�
	//! \return �Ƿ�ɹ����棬�ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SaveInfo() ;
	
	//! \brief ˢ�����ݼ���Ϣ��
	//! \return �Ƿ�ɹ�ˢ�£��ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks �����ݿ��ж�ȡ���ݼ��ĸ������ԣ�ˢ�µ�ǰ���ݼ�����Ϣ��
	virtual OgdcBool RefreshInfo() ;	

	//! \brief ����Ӱ���������
	//! \param bShhowProgress �Ƿ���ʾ������[in]��
	//! \return �Ƿ񴴽��ɹ����Ƿ���TRUE�����򷵻�FALSE��
	virtual OgdcBool BuildPyramid();	

	//! \brief �Ƴ�Ӱ���������
	//! \return �Ƿ��Ƴ��ɹ����Ƿ���TRUE�����򷵻�FALSE��
	virtual OgdcBool DropPyramid() ;
	
	//! \brief �ж��Ƿ��Ѿ�����Ӱ���������
	virtual OgdcBool IsBuildPyramid() const;

	//! \brief �õ�ɨ����
	virtual OgdcBool GetScanline(OgdcInt nRowIndex,OgdcRasterScanline& ScanLine, OgdcInt nStartCol = 0);

	//! \brief ͨ��������������ɨ����
	virtual OgdcBool SetScanline(OgdcInt nRowIndex,OgdcInt nColIndex,
		const OgdcRasterScanline& ScanLine);

	//! \brief ����ָ�������ݡ�
	//! \param nRowBlock Ӱ����к�[in]��
	//! \param nColBlock Ӱ����к�[in]��
	//! \return Ӱ���ָ�롣
	//! \attention ���صĵ�դ���ָ�������渺���ͷ�
	virtual OgdcRasterBlock* LoadBlock(OgdcInt nRowBlock, OgdcInt nColBlock);	
    
	//! \brief ��һ�ڴ��е�Ӱ��������̡�
	//! \param pImgBlock Ӱ���ָ��[in]��
	//! \return �Ƿ�ɹ����棬�ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SaveBlock(OgdcRasterBlock* pImgBlock);	
	
	//! \brief �ͷ����ڴ��е�����դ���
	virtual void ReleaseAllBlocks();
	
	//! \brief ��ȡӰ�����ݼ�ָ������ĳһ���ص����ɫֵ��
	//! \param nCol ���ص��к�[in]��
	//! \param nRow ���ص��к�[in]��
	//! \return ��ɫֵ��
	//! \remarks ��ɫֵ����ֵ�����ݼ������ظ�ʽ��ͬ����ͬ��
	virtual OgdcColor GetPixel(OgdcInt nCol, OgdcInt nRow);	
	
	//! \brief  ����Ӱ�����ݼ�ָ������ĳһ���ص����ɫֵ��
	//! \param nCol ���ص��к�[in]��
	//! \param nRow ���ص��к�[in]��
	//! \param nColor ��ɫֵ[in]��
	//! \remarks Ҫ�������ݼ������ظ�ʽ��ȷ�������ص����ɫֵ��
	virtual void SetPixel(OgdcInt nCol, OgdcInt nRow, OgdcColor nColor);	
	
	//! \brief ��ȡGrid���ݼ�ָ������ĳһ�������ֵ��
	//! \param nCol �����к�[in]��
	//! \param nRow �����к�[in]��
	//! \return ����ֵ��
	virtual OgdcDouble GetValue(OgdcInt nCol, OgdcInt nRow);
	
	//! \brief ����Grid���ݼ�ָ������ĳһ�������ֵ��
	//! \param nCol �����к�[in]��
	//! \param nRow �����к�[in]��
	//! \param dValue ����ֵ[in]��
	//! \remarks Ҫ�������ݼ��İ׻�ֵ��ȷ��������������ֵ��
	virtual void SetValue(OgdcInt nCol, OgdcInt nRow, OgdcDouble dValue);
	
	//! \brief ��ȡ�ɼ�դ���
	//! \param rcView ���ӷ�Χ[in]��
	//! \param nDeviceWidth �豸��ȣ���Ҫָ��ǰ���ڵĿ��[in]��
	//! \param nDeviceHeight �豸�߶ȣ���Ҫָ��ǰ���ڵĸ߶�[in]��
	//! \return ���ؿɼ�դ���ָ�롣
	//! \attention ���ص�ָ����������������ͷš�
	virtual OgdcRasterBlock* GetViewBlock(const OgdcRect2D& rcView, 
		OgdcInt nDeviceWidth, OgdcInt nDeviceHeight);

	//! \brief ��������Դָ��
	virtual OgdcDataSource* GetDataSource() const;

public:

	//! \brief �ж��Ƿ�Ϊդ�����ݼ�
	OgdcBool IsRaster();
				
	//! \brief �ж����ݼ��Ƿ��ڴ򿪺��й��޸ġ�
	//! \return �й��޸ķ���TRUE��û�з���FALSE��
	virtual OgdcBool IsModified() const;

	//! \brief �������ݼ��Ƿ��й��޸ġ�
	//! \param bModified ���ݼ��Ƿ��й��޸ģ�Ĭ�����޸�[in]��
	virtual void SetModifiedFlag(OgdcBool bModified = TRUE);

	//! \brief �������껻���������ꡣ
	//! \param rectXY [in]��
	//! \param rectImg [out]��
	void XYToImg(const OgdcRect2D& rectXY, OgdcRect& rectImg);

	//! \brief �������껻�ɵ�������
	//! \param rectImg [in]��
	//! \param rectXY [out]��
	void ImgToXY(const OgdcRect& rectImg, OgdcRect2D& rectXY);	
	
	//! \brief ��ȡ��Ӧ��Ľ�����
	//! \param nImgWidth [in]��
	//! \param nDeviceWidth [in]��
	//! \return ������ͼ���ָ�롣
	OgdcDatasetRasterMdb* GetPyramidTier(OgdcInt nImgWidth, OgdcInt nDeviceWidth);
	
	//! \brief ����������
	//! \param rInfo դ�����ݼ�������Ϣ����[in]��
	//! \param nLevel Ҫ�����Ľ������Ĳ���[in]��
	//! \return �����õĽ�����ͼ���ָ�롣
	OgdcDatasetRasterMdb* CreateDatasetPyramid(OgdcDatasetRasterInfo& rInfo, OgdcInt nLevel);

	//! \brief ����Grid���ݼ��ĵ�ɫ��
	//! \param pColorTable=NULL [in]��
	//! \return �����Ƿ����óɹ�
	OgdcBool SetGridColorTable(OgdcColorTable* pColorTable=NULL);

private:

	//! \brief �ͷ����н��������ݼ�
	//! \return �����Ƿ�ɾ���ɹ�
	//! \remarks ɾ�����ݼ����ڴ��е����н�����ͼ���ָ��
	OgdcBool ReleasePyramidDatasets();	

	//! �������ر߳�����λ����λ��
	OgdcBool ComDivAndMod();

protected:
	//! \brief ���ݼ���ID	
 	OgdcLong m_nID;

	//! \brief ָ������Դ��ָ��
	OgdcDataSourceMdb *m_pDataSource;
	
	//! \brief ���ݼ��Ƿ�򿪵ı�־
 	OgdcBool m_bOpened;
	
	//! \brief �Ƿ��޸ĵı�־	
	OgdcBool m_bModified;

	//! \brief ����װ���ص��ڴ���դ�����ֵ�
	//! \remarks �ֵ��nKeyΪդ���������
	OgdcDict<OgdcInt,OgdcRasterBlock*> m_rasterDict;

	//! \brief ��ʾ�ο�����
	OgdcRect2D m_rcViewGeoRef;	

	//! \brief ����������Ӱ��ӳ�����
	OgdcSize2D m_imgRatio;
	
	//! \brief ��Ÿ����������ָ������
	OgdcArray<OgdcDatasetRasterMdb*> m_pyramidDatasets;

	//! \brief ���������λ�Ʋ���
	OgdcUint m_nDiv;

	//! ���������ȡ�����
	OgdcUint m_nMod;

	//! ��¼��m_nDiv,m_nMod�Ƿ�׼����
	OgdcUint m_bInitImg;


};

}
#endif 
