//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file ��¼���һ�ε���ʱ����ĻͶӰ��Ϣ,����ģʽ
//!  \brief 
//!  \details 
//!  \author sunye��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef UGMAXLOGFILE_H
#define UGMAXLOGFILE_H
#include "Stream/ugdefs.h"
class UGMaxLogFile
{
public:
	~UGMaxLogFile();
	static UGMaxLogFile* GetMaxLogFile();

	//! \brief ������һ�ζԻ�������ʾ�ľ���ֵ
	//! \param strLongtitude [in]
	void SetLontitude(UGC::UGString strLongtitude);

	//! \brief ������һ�ζԻ�������ʾ��ά��ֵ
	//! \param strLatitude [in]
	void SetLatitude(UGC::UGString strLatitude);

	//! \brief ������һ�ζԻ�������ʾ�ĸ߶�ֵ
	//! \param strAltitude [in]
	void SetAltitude(UGC::UGString strAltitude);

	//! \brief ��ȡ��һ�ζԻ�������ʾ�ľ���ֵ
	UGC::UGString GetLontitude();

	//! \brief ��ȡ��һ�ζԻ�������ʾ��ά��ֵ
	UGC::UGString GetLatitude();

	//! \brief ��ȡ��һ�ζԻ�������ʾ�ĸ߶�ֵ
	UGC::UGString GetAltitude();

	//-----------------------Add by lina 2014-3-31
	//! \brief ������һ�ζԻ�������ʾ��ƽ������Xֵ
	//! \param strLongtitude [in]
	void SetPlaneX(UGC::UGString strPlaneX);

	//! \brief ������һ�ζԻ�������ʾ��ƽ������Yֵ
	//! \param strLatitude [in]
	void SetPlaneY(UGC::UGString strPlaneY);

	//! \brief ������һ�ζԻ�������ʾ��ƽ������Zֵ
	//! \param strAltitude [in]
	void SetPlaneZ(UGC::UGString strPlaneZ);

	//! \brief ��ȡ��һ�ζԻ�������ʾ��ƽ������Xֵ
	UGC::UGString GetPlaneX();

	//! \brief ��ȡ��һ�ζԻ�������ʾ��ƽ������Yֵ
	UGC::UGString GetPlaneY();

	//! \brief ��ȡ��һ�ζԻ�������ʾ��ƽ������Zֵ
	UGC::UGString GetPlaneZ();
	//--------------------------------------------
	//! \brief ����֧�ֵ��������
	UGC::UGint GetMaxTextureSize(void) const;

	//! \brief ����֧�ֵ��������
	//! \param nMaxTextureSize [in] 
	void SetMaxTextureSize(UGC::UGint nMaxTextureSize);

	//! \brief ��������ű�
	UGC::UGint GetTextureScaling(void) const;

	//! \brief ������������ű�
	//! \param nTextureScaling [in]
	void SetTextureScaling(UGC::UGint nTextureScaling);

	//! \brief ����֧�ֵ��������
	//! \param strBatchTextureSize [in] 
	void SetBatchTextureSize(UGC::UGString& strBatchTextureSize);

	//! \brief ����֧�ֵ��������
	UGC::UGString GetBatchTextureSize(void) const;

	//! \brief ����֧�ֵ������ο���
	//! \param nBatchTerrainSize [in] 
	void SetBatchTerrainSize(UGC::UGString& strBatchTerrainSize);

	//! \brief ����֧�ֵ������ο���
	UGC::UGString GetBatchTerrainSize(void) const;	

	//! \\����tif��ʱ�����ڼ�¼���ĺ����������
	UGDict<UGC::UGString,UGC::UGint>& GetMapName();

	//! \brief ���������ǰ׺,�������ݿ�ʱ���ڱ�ʶ����
	UGC::UGString GetTexPerfix();

	//! \brief ������ʱĿ¼,ֻ�е������ݿ����Ҫ
	UGC::UGString GetTempDir();

private:
	UGC::UGString GetMaxFilePathMapCode();

	UGC::UGuint GetMapCode( const UGC::UGString& strkey );
	
private:
	UGMaxLogFile();
	UGC::UGString m_strLongtitude;
	UGC::UGString m_strLatitude;
	UGC::UGString m_strAltitude;
	//add by lina ƽ������
	UGC::UGString m_strPlaneX;
	UGC::UGString m_strPlaneY;
	UGC::UGString m_strPlaneZ;

	//! \brief ���ű���
	UGC::UGuint m_nTextureScaling;

	//! \brief ֧�ֵ��������
	UGC::UGuint m_nMaxTextureSize;

	//! \���������ʱ����Ӧ�ĵ�������������ο鶥��ĸ�����С
	UGC::UGString m_strBatchTextureSize;
	UGC::UGString m_strBatchTerrainSize;

	UGDict<UGC::UGString,UGC::UGint> m_dicttMapName;

	UGC::UGString m_strPrefix;

	static UGMaxLogFile* m_pMaxLogFile;

};
#endif
