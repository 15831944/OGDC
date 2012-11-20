//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)               
//                                                           
//!  \file OgdcHelperMdb.h
//!  \brief OGDC����������Ľӿڶ��塣
//!  \details ����һЩOGDC���������������������͵�ת��
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDCHELPERMDB_H__A37C8A53_6D17_4F8E_9CD0_C85821085D7D__INCLUDED_)
#define AFX_OGDCHELPERMDB_H__A37C8A53_6D17_4F8E_9CD0_C85821085D7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDataSource.h"
#include "../../Include/Base/OgdcDict.h"
#include "afxdao.h"

namespace OGDC
{
	
//! \brief OgdcProviderMdb�İ�����
//! \remarks �ṩ��OGDC��MFC��DAO�������ݵ�ת�������������ȹ���
class OGDC_API OgdcHelperMdb  
{
public:
	//! \brief �����ӿ���Ĭ�Ϲ��캯��
	OgdcHelperMdb();	
	//! \brief �����ӿ���Ĭ����������
	virtual ~OgdcHelperMdb();
	
public:
	//! \brief ��OGDC����ת��ΪOLE���塣
	//! \param ogdcVariant Դֵ[in]��
	//! \param coleVariant Ŀ��ֵ[out]��
	static void OgdcVariant2COleVariant(const OgdcVariant& ogdcVariant, COleVariant& coleVariant);
	
	//! \brief ��OLE����ת��ΪOGDC���塣��
	//! \param coleVariant Դֵ[in]��
	//! \param ogdcVariant Ŀ��ֵ[in]��
	static void COleVariant2OgdcVariant(const COleVariant& coleVariant, OgdcVariant& ogdcVariant);
	
	//! \brief ��OgdcFieldInfo����ת����CDaoFieldInfo���͡�
	//! \param fieldInfo Դֵ[in]��
	//! \param daoFieldInfo Ŀ��ֵ[in]��
	//! \remarks DAO�������ݿ������ʱ��Ҫ��CDaoFieldInfo���͡�
	static void OgdcFieldInfo2CDaoFieldInfo(const OgdcFieldInfo& fieldInfo, CDaoFieldInfo& daoFieldInfo);
	
	//! \brief ��CDaoFieldInfo����ת����OgdcFieldInfo���͡�
	//! \param fieldInfo Դֵ[in]��
	//! \param daoFieldInfo Ŀ��ֵ[in]��
	//! \remarks DAO�������ݿ������ʱ��Ҫ��CDaoFieldInfo���͡�
	static void CDaoFieldInfo2OgdcFieldInfo(const CDaoFieldInfo& daoFieldInfo, OgdcFieldInfo& fieldInfo);	
	
	//! \brief �ж�strName�Ƿ�Ϊϵͳ�ֶΡ�
	//! \param strName [in]��
	//! \remarks �����ϵͳ�ֶ�ͳһ��OG��ͷ��
	static OgdcBool IsSystemField(const OgdcString& strName);	
	
	//! \brief �ж�strName�Ƿ�ΪAccess�Ĺؼ��֡�
	//! \param strName [in]��
	//! \remarks Access�ؼ����ڵ�һ�ε���ʱ��ʼ����
	static OgdcBool IsKeyWord(const OgdcString& strName);
	
	//! \brief ��ʼ��Access�Ĺؼ���
	//! \remarks ����Access�ؼ��ֵ��ֵ���
	static void InitKeyWords();

	//! \brief �����ֶα�ʶ
	static void SetFieldSign(OgdcFieldInfo& fieldInfo);

	static OgdcBool IsOGID(OgdcString strName);

	static OgdcBool IsGeoField(OgdcString strName);
	
private:
	
	//! \brief Access�ؼ��ֵ��ֵ��Ƿ��ʼ���ı�־
	static OgdcBool m_bInited;
};


}
#endif 
