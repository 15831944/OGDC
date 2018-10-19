//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)          
//                                                           
//!  \file OgdcDatasetVectorMdb.h
//!  \brief ʸ�����ݼ��Ľӿڶ��塣
//!  \details ʸ�����ݼ��ĸ��ֽӿ�
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDCDATASETVECTORMDB_H__681E6C4F_B683_41E1_A7AF_B91345DAB853__INCLUDED_)
#define AFX_OGDCDATASETVECTORMDB_H__681E6C4F_B683_41E1_A7AF_B91345DAB853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDatasetVector.h"
#include "OgdcDataSourceMdb.h"

namespace OGDC
{

//! \brief ʸ�����ݼ�ʵ�ֵ���
//! \remarks Ϊ���õĵ㣬�ߣ��棬�ı����������ݼ�
class OGDC_API OgdcDatasetVectorMdb : public OgdcDatasetVector  
{
	//! \brief ������Ԫ��
	friend class OgdcDataSourceMdb;
	friend class OgdcRecordsetMdb;	 
	
public:
	//! \brief ʸ�����ݼ�Ĭ�Ϲ��캯��
	OgdcDatasetVectorMdb();

	//! \brief ��ָ������Դָ��Ĺ��캯��
	//! \param pDataSource ָ������Դ��ָ��[in]��
	OgdcDatasetVectorMdb(OgdcDataSourceMdb *pDataSource);

	//! \brief ʸ�����ݼ�Ĭ����������
	virtual ~OgdcDatasetVectorMdb();

	// ���麯��	
public:
	//! \brief �ж����ݼ��Ƿ��Ѿ��򿪡�
	//! \return �򿪷���TRUE�����򷵻�FALSE��
	virtual OgdcBool IsOpen() const ;
	
	//! \brief �����ݼ���
	//! \return �Ƿ�ɹ������ݼ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool Open() ;
	
	//! \brief �ر����ݼ���
	//! \return �Ƿ�ɹ��ر����ݼ����ɹ�����TRUE��ʧ�ܷ���FALSE��
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

	//! \brief ��ȡ���ݼ��ж��������
	//! \param  [in]��
	//! \return ���������
	//! \remarks �ٶ���,��ֵ�Ƚ���ȷ��
	//! \attention ͨ��Register���ȡ��
	virtual OgdcInt GetObjectCount() ;

	//! \brief ���ؼ�¼��������
	//! \return ��¼��������
	virtual OgdcInt GetRecordsetCount() ;	
	
	//! \brief ͨ����¼��ָ���ͷż�¼���ڴ�ռ䡣
	//! \param pRecordset ��¼��ָ��[in]��
	//! \return �Ƿ��ͷųɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool ReleaseRecordset(OgdcRecordset *pRecordset) ;	

	//! \brief �ͷ����м�¼��
	virtual void ReleaseAllRecordsets() ;	

	//! \brief ȡ�����ݼ���ĳ������Ҫ�ء�
	//! \param nID ���ݼ���¼ID��[in]��
	//! \return ������Ҫ��ָ�롣
	virtual OgdcFeature* GetFeature(OgdcInt nID) ;	
	virtual UGC::UGFeature* GetFeatureEx(OgdcInt nID);

	//! \brief ������Ҫ�ظ��µ����ݼ��С�
	//! \param pFeature ����Ҫ��ָ��[in]��
	//! \return �Ƿ񱣴�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool UpdateFeature(const OgdcFeature* pFeature) ;
	virtual OgdcBool UpdateFeature(const UGC::UGFeature* pFeature);
	
	//! \brief ������Ҫ��׷�ӵ����ݼ�δβ��
	//! \param pFeature ����Ҫ��ָ��[in]��
	//! \return �Ƿ�׷�ӳɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks ׷��ʱ����Ҫ�ع��������ݼ���¼ID���������á�
	virtual OgdcBool AddFeature(const OgdcFeature* pFeature) ;	
	virtual OgdcBool AddFeature(const UGC::UGFeature* pFeature);

	//! \brief ������Ҫ�ش����ݼ���ɾ����
	//! \param nID ���ݼ���¼ID��[in]��
	//! \return �Ƿ�ɾ���ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DeleteFeature(OgdcInt nID) ;	
	
	//! \brief ͨ��ID����ɾ�����ݼ��еļ�¼��
	//! \param pIDs ID����ָ��[in]��
	//! \param nCount ID����Ԫ�ظ���[in]��
	//! \return �ɹ�ɾ������TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DeleteFeatures(const OgdcInt* pIDs, OgdcInt nCount) ;	
	
	//! \brief ɾ�������������ݡ�
	//! \return �Ƿ�ɾ���ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks ��ձ����е��ֶ���Ȼ������
	virtual OgdcBool Truncate() ;	

	//! \brief ���ݵ�ǰ����״̬�ؽ�����
	//! \return �Ƿ��ؽ��ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool BuildSpatialIndex() ;
	
	//! \brief ����ռ�����,Ϊû��������״̬
	//! \return �Ƿ�����ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DropSpatialIndex() ;
	
	//! \brief �Ƿ���Ҫ�ؽ��ռ�����
	//! \return ��Ҫ�ؽ�����TRUE������Ҫ����FALSE��
	//! \remarks �涨:���û����������FALSE,�����������������
	virtual OgdcBool IsSpatialIndexDirty() ;

	//! \brief ��ѯͨ����ڣ��õ���¼����
	virtual OgdcRecordset* Query(const OgdcQueryDef& querydef) ;
	
	//! \brief ͨ�����ʽ�����ֶ�ֵ��
	//! \param strFieldName ���µ��ֶ���[in]��
	//! \param strExpress ����������ʽ�ַ�����
	//! �ֶ�ֵ��ĳ������������ʽ��ֵ����strFieldName = Col1 + col2 * 2[in]��
	//! \param strFilter �����ֶ�ʱ�������еĹ���������
	//! Ĭ�Ϲ��������ÿգ��������м�¼[in]��
	//! \return �Ƿ�����ֶ�ֵ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool UpdateField(
		const OgdcString& strFieldName,
		const OgdcString& strExpress,
		const OgdcString& strFilter = _U("")) ;	
	
	//! \brief �����ֶ�ֵ,strSrcField�͡�
	//! \param strSrcFieldName Դ�ֶ�����[in]��
	//! \param strDestFieldName Ŀ���ֶ�����[in]��
	//! \return �Ƿ����ֶγɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \attention Ŀ���ֶ������붼������Ŀ���ֶ�Ҫ��Դ�ֶ�����ƥ�䡣
	virtual OgdcBool CopyField(
		const OgdcString& strSrcFieldName,
		const OgdcString& strDestFieldName) ;	
	
	//! \brief ������ͨ������
	//! \param strFieldNameList �����������ֶ��б�����ֶ��м���","����[in]��
	//! \param strIndexName ������[in]��
	//! \return ������ͨ�����Ƿ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool CreateFieldIndex(
		const OgdcString& strFieldNameList,
		const OgdcString& strIndexName) ;	

	//! \brief ɾ��������
	//! \param strIndexName ������[in]��
	//! \return ɾ�������Ƿ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DropFieldIndex(const OgdcString& strIndexName) ;	
	
	//! \brief ��������ֶΡ�
	//! \param fieldInfos �ֶ�������Ϣ��������[in]��
	//! \return ��������ֶ��Ƿ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool CreateFields(const OgdcFieldInfos& fieldInfos) ;	
		
	//! \brief ͨ���ֶ�����ɾ���ֶΡ�
	//! \param strFieldName �ֶ���[in]��
	//! \return �Ƿ�ɾ���ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DeleteField(const OgdcString& strFieldName) ;
	
	//! \brief ��ȡ���ݱ��������ֶε�������Ϣ��
	//! \param fieldInfos ���ݱ��������ֶε�������Ϣ����[out]��
	//! \param bSystemFieldExcluded �Ƿ��ų�ϵͳ�ֶΣ�Ĭ�ϲ��ų�[in]��
	//! \return �Ƿ��ȡ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool GetFieldInfos(
		OgdcFieldInfos& fieldInfos,
		OgdcBool bSystemFieldExcluded = FALSE) ;	
	
	//! \brief ͨ���ֶ�����ȡ�ֶ�������Ϣ��
	//! \param strFieldName �ֶ���[in]��
	//! \param fieldInfo �ֶ�������Ϣ[out]��
	//! \return �Ƿ��ȡ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool GetFieldInfo(
		const OgdcString& strFieldName,
		OgdcFieldInfo& fieldInfo) ;
	
	//! \brief ͨ���ֶ��������ֶ���Ϣ��
	//! \param strFieldName �ֶ���[in]��
	//! \param fieldInfo �ֶ�������Ϣ��������[in]��
	//! \return �Ƿ����óɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SetFieldInfo(
		const OgdcString& strFieldName,
		const OgdcFieldInfo& fieldInfo) ;	
	
	//! \brief ͳ���ֶ�ֵ��
	//! \param strFieldName �ֶ���[in]��
	//! \param nMode ͳ��ģʽ[in]��
	//! \return ͳ��ֵ��
	//! \remarks ��ͳ�Ƶ��ֶ�����Ϊ�����ͣ����ͣ������ͣ�����˫���ȸ�����
	virtual OgdcVariant Statistic(
		const OgdcString& strFieldName,
		OgdcRecordset::OgdcStatisticMode nMode) ;	

	//! \brief ��������Դָ��
	virtual OgdcDataSource* GetDataSource() const;

public:
		
	//! \brief �ж����ݼ��Ƿ���դ�����ݼ�
	//! \return ��դ�����ݼ�����TRUE�����Ƿ���FALSE��
	virtual OgdcBool IsRaster();

	//! \brief ��ȡ���ݼ��ĵ���Χ��
	//! \return ���ݼ��ĵ���Χ��
	virtual OgdcRect2D GetBounds();
			
	//! \brief �õ�δ��ռ�õ��ֶ�����
	//! \param strFieldName ָ����һ���ֶ���[in]��
	//! \return δ��ռ�õ��ֶ�����
	virtual OgdcString GetUnoccupiedFieldName(const OgdcString& strFieldName);

	//! \brief �ж��ֶ����Ƿ���Ч��
	//! \param strFieldName �ֶ���[in]��
	//! \return ��Ч����TRUE����Ч����FALSE��
	virtual OgdcBool IsAvailableFieldName(const OgdcString& strFieldName);

	//! \brief �ж����ݼ��Ƿ��ڴ򿪺��й��޸ġ�
	//! \return �й��޸ķ���TRUE��û�з���FALSE��
	virtual OgdcBool IsModified() const;

	//! \brief �������ݼ��Ƿ��й��޸ġ�
	//! \param bModified ���ݼ��Ƿ��й��޸ģ�Ĭ�����޸�[in]��
	virtual void SetModifiedFlag(OgdcBool bModified = TRUE);

	//! \brief ����ͶӰ����ϵ��
	//! \brief ��Provider��֧���ڴ�������ͶӰ��Ϣ����δ���档
	//! \param coordSys [in]��
	virtual OgdcBool SetCoordSys(const OgdcCoordSys& coordSys);	

	//! \brief �õ�ͶӰ����ϵ��
	virtual OgdcBool GetCoordSys(OgdcCoordSys& coordSys) const;			

	//! \brief ʸ�����ݼ�����������Provider�����Ƿ�֧����ز�ѯ
	virtual OgdcBool IsSupportQueryType(OgdcQueryDef::QueryType queryType) const;

	//! \brief ���������ݼ�
	OgdcBool CreateSubDatasetVector(OgdcDatasetVectorInfo& vInfo);

protected:

	//! \brief ָ������Դ��ָ��
	OgdcDataSourceMdb* m_pDataSource;

	//! \brief ʸ�����ݼ��ж���ĸ���
	OgdcInt m_nObjectCount;

	//! \brief CDaoTableDefָ��
	//! \remarks ͨ��CDaoTableDefͨ����ڽ������ݿ����
	CDaoTableDef* m_pDaoTableDef;	

	//! \brief ��¼��ID
	OgdcInt m_nID;

	//! \brief OgdcFieldInfos���ͽṹ��
	//! \remarks ��ÿ��OgdcFieldInfo���ͣ������ֶ���Ϣ
	OgdcFieldInfos m_fieldInfos;
	
	//! \brief �Ƿ��޸ĵı�־
	OgdcBool m_bModified;

	//! \brief ��ÿ����ѯ��¼����ָ��
	OgdcArray <OgdcRecordset*> m_recordsets;

	//! \brief ���ݼ��Ƿ�򿪵ı�־
	OgdcBool m_bOpened;

	OgdcCoordSys m_cordsys;
	 
};

}

#endif // !defined(AFX_OGDCDATASETVECTORMDB_H__681E6C4F_B683_41E1_A7AF_B91345DAB853__INCLUDED_)
