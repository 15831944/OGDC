//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)       
//                                                           
//!  \file OgdcFeatureMdb.h
//!  \brief OgdcFeature �Ľӿڶ��塣
//!  \details OGDC����Ҫ����Ľӿڡ�
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDCFEATUREMDB_H__C646C050_13AF_4332_A835_9D5BE49B5571__INCLUDED_)
#define AFX_OGDCFEATUREMDB_H__C646C050_13AF_4332_A835_9D5BE49B5571__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDataSource.h"

namespace OGDC
{

//! \brief Ogdc ����Ҫ����	
class OGDC_API OgdcFeatureMdb : public OgdcFeature  
{
	//! \brief ������Ԫ��
	friend class OgdcRecordsetMdb;

public:
	//! \brief ����Ҫ����Ĭ�Ϲ��캯��
	OgdcFeatureMdb();
	//! \brief ����Ҫ����Ĭ����������
	virtual ~OgdcFeatureMdb();
	
public:
	//! \brief ��ȡ���ζ���ID��
	virtual OgdcInt GetID() const ;	
	
	//! \brief ���ü��ζ���ID��
	//! \param nID ���ζ���ID[in]��
	virtual void SetID(OgdcInt nID) ;	
	
	//! \brief ��ȡ���ζ������治���ͷš�
	//! \return �Ƿ�ȡ���ζ���ɹ����ɹ����ؼ��ζ���ʧ�ܷ���NULL��
	virtual OgdcElement* GetElement() ;	
	
	//! \brief ���õ�ǰ����Ҫ�صļ��ζ��������Ժ����治���ͷš�
	//! \param pElement ���ζ���ָ��[in]��
	virtual void SetElement(OgdcElement* pElement) ;	
	
	//! \brief �����ֶ���Ż�ȡ�ֶ�ֵ��
	//! \param nIndex �ֶ����[in]��
	virtual OgdcBool GetValue(OgdcInt nIndex, OgdcVariant& varValue) ;
	
	//! \brief �����ֶ�����ȡ�ֶ�ֵ��
	//! \param strFieldName �ֶ���[in]��
	virtual OgdcBool GetValue(const OgdcString& strFieldName, OgdcVariant& varValue) ;	
	
	//! \brief �����ֶ���������ֶ�ֵ��
	//! \param nIndex �ֶ����[in]��
	//! \param varValue �ֶ�ֵ [in]��
	//! \return �Ƿ����óɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SetValue(OgdcInt nIndex, const OgdcVariant& varValue) ;    
	
	//! \brief �����ֶ��������ֶ�ֵ��
	//! \param strFieldName �ֶ���[in]��
	//! \param varValue �ֶ�ֵ [in]��
	//! \return �Ƿ����óɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SetValue(const OgdcString& strFieldName, const OgdcVariant& varValue) ;		
	
public:
	//! \brief �����ֶ���Ϣ��
	//! \param fieldInfos �ֶ���Ϣ����[in]��
	virtual void SetFieldInfos(const OgdcFieldInfos& fieldInfos);	
	
	//! \brief �����ַ������뷽ʽ��
	//! \return ���ر���ķ�ʽ��
	virtual OgdcString::Charset GetCharset() const;	
	
	//! \brief �����ַ������뷽ʽ��
	//! \param nCharset [in]����
	virtual void SetCharset(OgdcString::Charset nCharset);

protected:
	//! \brief ����ÿ���ֶε�ֵ������
	OgdcArray<OgdcByte*> m_fieldValues;
	
	//! \brief ��������Ҫ�صļ��ζ���ָ��
	OgdcElement* m_pElement;

	//! \brief ��������Ҫ�ص�ID
	OgdcInt m_nID;

	//! \brief ���뷽ʽ��ֵ
	OgdcString::Charset m_nCharset;

};
}
#endif // !defined(AFX_OGDCFEATUREMDB_H__C646C050_13AF_4332_A835_9D5BE49B5571__INCLUDED_)
