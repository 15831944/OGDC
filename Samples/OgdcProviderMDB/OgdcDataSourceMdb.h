//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)           
//                                                           
//!  \file OgdcDataSourceMdb.h
//!  \brief ����Դ�Ľӿڶ��塣
//!  \details ����Դ���ֲ����Ľӿ�
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDCDATASOURCEMDB_H__F613A905_BFAD_4DA1_B1D0_1E00090CB62A__INCLUDED_)
#define AFX_OGDCDATASOURCEMDB_H__F613A905_BFAD_4DA1_B1D0_1E00090CB62A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDataSource.h"
#include "afxdao.h"

namespace OGDC
{

//! \brief OgdcMdb����Դ�Ľӿڡ�
class OGDC_API OgdcDataSourceMdb : public OgdcDataSource  
{
public:
	//! \brief ����ԴĬ�Ϲ��캯��
	OgdcDataSourceMdb();
	//! \brief ����ԴĬ����������
	virtual ~OgdcDataSourceMdb();

	// ���麯��
public:
	//! \brief ��������Դ,��ҪԤ�����ú�������Ϣ��
	virtual OgdcBool Create();
	
	//! \brief ������Դ,��ҪԤ�����ú�������Ϣ��
	virtual OgdcBool Open();
	
	//! \brief �ر�����Դ��
	virtual void Close();
	
	//! \brief �ж�����Դ�Ƿ��Ѿ��򿪡�
	//! \return �򿪷���TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool IsOpen() const;
	
	//! \brief ��ȡ���ݼ�������
	//! \return ���ݼ�������
	virtual OgdcInt GetDatasetCount() const;
	
	//! \brief ͨ����Ż�ȡ���ݼ�ָ�롣
	//! \return ���ݼ�ָ�롣
	virtual OgdcDataset* GetDataset(OgdcInt nIndex) const;
	
	//! \brief ��ȡָ�����Ƶ����ݼ�ָ�롣
	//! \param strDatasetName ���ݼ���[in]��
	//! \return ���ݼ�ָ�롣
	virtual OgdcDataset* GetDataset(const OgdcString& strDatasetName) const;
	
	//! \brief ͨ�����ݼ�����ɾ�����ݼ���
	//! \param strDatasetName ���ݼ�����[in]��
	//! \return �Ƿ�ɹ�ɾ�����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DeleteDataset(const OgdcString& strDatasetName);
	
	//! \brief ͨ��ʸ�����ݼ�������Ϣ�������ݡ�
	//! \param vInfo ʸ�����ݼ�������Ϣ����[in]��
	//! \return ʸ�����ݼ�ָ�롣
	virtual OgdcDatasetVector* CreateDatasetVector(const OgdcDatasetVectorInfo& vInfo);	
	
	//! \brief ͨ��դ�����ݼ�������Ϣ�������ݼ���
	//! \param rInfo դ�����ݼ�������Ϣ����[in]��
	//! \param bIsMBRaster �Ƿ��Զನ�η�ʽ�������ݼ�[in]��
	//! \return դ�����ݼ�ָ�롣
	virtual OgdcDatasetRaster* CreateDatasetRaster(const OgdcDatasetRasterInfo& rInfo,OgdcBool bIsMBRaster = FALSE);	
	
	//! \brief ͨ���������ݼ�ģ�崴�����ݼ���
	//! \param strNewName �����ݼ���[in]��
	//! \param pReferenceDataset �ο����ݼ�ָ�룬��ģ�崴�����ݼ�ָ��[in]��
	//! \return �����ݼ�ָ�롣
	virtual OgdcDataset* CreateDatasetFrom(const OgdcString &strNewName, OgdcDataset* pReferenceDataset);
	
	//! \brief �������ݼ���
	//! \param pSrcDataset Դ���ݼ�ָ��[in]��
	//! \param strDestDatasetName Ŀ�����ݼ���[in]��
	//! \param bBuildIndexOrPyramid �Ƿ��դ�����ݼ�������������Ĭ�ϲ���[in]��
	//! \return Ŀ�����ݼ�ָ�롣
	virtual OgdcDataset* CopyDataset(OgdcDataset* pSrcDataset, 
		const OgdcString& strDestDatasetName, OgdcBool bBuildIndexOrPyramid = FALSE);
	
	//! \brief ����������Ϣ��
	virtual OgdcBool SaveInfo();

public:	
	//! \brief ��ȡ����Դ���ơ�
	//! \return ��������Դ���ơ�
	virtual OgdcString GetName() const ;	

	//! \brief ����ͶӰ����ϵ��
	//! \param coordSys [in]��
	virtual OgdcBool SetCoordSys(const OgdcCoordSys& coordSys);	

	//! \brief �õ�ͶӰ����ϵ��
	virtual OgdcBool GetCoordSys(OgdcCoordSys& coordSys);	

	//! \brief ִ��SQL��䡣
	//! \param strSQL SQL���[in]��
	//! \return �Ƿ�ɹ�ִ�У��ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks ��Ҫ���������ݿ⼶ִ�е����ݲ�����
	virtual OgdcBool Execute(const OgdcString& strSQL);	
	
	//! \brief ����Դ�Ƿ���������ӡ�
	virtual OgdcBool IsConnected();
	
	//! \brief �����������ݿ�,��ˢ�����ݼ��ȡ�
	virtual OgdcBool Connect();	
	
	//! \brief ��ȡ������ʱ�䡣
	virtual OgdcTime GetDateLastUpdated();
	
	//! \brief ��ȡ����ʱ�䡣
	virtual OgdcTime GetDateCreated();	
	
	//! \brief �޸����롣
	//! \param strNewPassword ������[in]��
	//! \return �޸ĳɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool ChangePassword(const OgdcString& strNewPassword);
	
	//! \brief ��ȡ�������ơ�
	//! \return �������ơ�
	virtual OgdcString GetEngineName() const ;
	
	//! \brief ����һ������Դ��Ŀǰû�е����ݼ����֡�
	//! \param strDatasetName ָ��һ�����ݼ���[in]��
	//! \return ����ָ�������ɵļ���Ψһʶ������ݼ�����
	virtual OgdcString GetUnoccupiedDatasetName(const OgdcString& strDatasetName);	
	
	//! \brief �ж����ݼ������Ƿ�Ϸ���
	//! \param strDatasetName ���ݼ���[in]��
	//! \param nState ���ݼ����ֶ�������������[out]��
	//! \return �����Ƿ�Ϸ����Ƿ���TRUE�����򷵻�FALSE��
	virtual OgdcBool IsAvailableDatasetName(const OgdcString& strDatasetName);

	//! \brief ��ȡ����Դ�汾�š�
	//! \return ����Դ�汾�š�
	virtual OgdcInt GetVersion();		
	
	//! \brief ��ʼ����
	//! \return �Ƿ�ɹ���ʼ���񣬳ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool BeginTrans();
	
	//! \brief �ύ����
	//! \return �Ƿ�ɹ��ύ���񣬳ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual void Commit();
	
	//! \brief ��������
	//! \return �Ƿ�ɹ��������񣬳ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual void Rollback();
	
	//! \brief �ж������Ƿ�ʼ 
	virtual OgdcBool IsTransStarted() const ;
	
	//! \brief �ж�����Դ�Ƿ��޸ġ�
	//! \return ���޸ķ���TRUE�����򷵻�FALSE��
	virtual OgdcBool IsModified();

	//! \brief ��������Դ�Ƿ��޸ġ�
	//! \param bModified ����Դ�Ƿ��޸Ĳ���ֵ��Ĭ��Ϊ�޸�[in]��
	virtual void SetModifiedFlag(OgdcBool bModified = TRUE);
		
	//! \brief �жϴ�����ֶ���������Ƿ���á�
	//! \param �ֶ���������Ƿ���á�
	//! \param nState ���ݼ��������ֶ������������͡�
	//! \return	���÷���TRUE�������÷���FALSE��
	virtual OgdcBool IsValidFieldOrTableName(const OgdcString& strFieldOrTableName);
	
	//! \brief ��������Դ������Ϣ��
	//! \param strDescription ����Դ������Ϣ[in]��
	virtual void SetDescription(OgdcString strDescription);
	
	//! \brief ��ȡ����Դ������Ϣ��
	//! \return ����Դ������Ϣ��
	virtual OgdcString GetDescription();

	//! \brief ɾ����ǰ������Դ(���Զ�ɾ���������ݼ������ɾ������ϵͳ���ϵͳ����)
	//! \remarks ���ô˷����󣬿����ٴδ���ͬ����������Դ
	//! \attention �����ݿ����͵�����Դ��Ҫʵ�ִ˷������ļ�������Դ������
	virtual OgdcBool DropDataSource();
	
	//! \brief ��ȡ����Դ��Ϣ
	OgdcBool ReadInfo();

public:
	//! \brief Micorsoft Access MDB ���ݿ�� Database���൱�� SuperMap �е�����Դ
	CDaoDatabase m_daoDatabase; 
	
protected:
	//! \brief ���ݼ�ָ�����飬��ÿһ��ָ�����ݼ���ָ��
	OgdcArray <OgdcDataset*> m_datasets;

	//! \brief ����Դ�汾
	OgdcLong m_nVersion;

	//! \brief һ��ָ�����ռ��ָ�룬Workspace for access
	CDaoWorkspace* m_pDaoWorkspace;	
		
	//! \brief ����Դ�Ƿ�򿪵ı�־
	OgdcBool m_bOpened;
	
	//! \brief �����Ƿ�����
	OgdcBool m_bTransStarted;
	
	//! \brief �Ƿ��޸�
	OgdcBool m_bModified;
		
	//! \brief ����Դ������
	OgdcString	m_strDescription;
	
	//! \brief ����ϵ��Ϣ
	OgdcCoordSys m_coordSys;
	
};

extern "C" OGDC_API OgdcDataSource* CreateOgdcDataSource();
extern "C" OGDC_API OgdcFeature* CreateOgdcFeature();
}
// 
#endif // !defined(AFX_OGDCDATASOURCEMDB_H__F613A905_BFAD_4DA1_B1D0_1E00090CB62A__INCLUDED_)
