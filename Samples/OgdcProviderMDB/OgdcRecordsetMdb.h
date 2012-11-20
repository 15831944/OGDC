//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)        
//                                                           
//!  \file OgdcRecordsetMdb.h
//!  \brief OGDC��¼���Ľӿڶ��塣
//!  \details OGDC��¼�����ֲ����Ľӿ�
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDCRECORDSETMDB_H__EE00C954_14D4_4C36_9BEA_84CED998068D__INCLUDED_)
#define AFX_OGDCRECORDSETMDB_H__EE00C954_14D4_4C36_9BEA_84CED998068D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcRecordset.h"
#include "OgdcDatasetVectorMdb.h"

namespace OGDC
{

//! \brief ��ѯ��¼������
//! \remarks ��Ҫ�Բ�ѯ��¼���и��ֲ����Ľӿ�
class OGDC_API OgdcRecordsetMdb : public OgdcRecordset  
{
	//! \brief ������Ԫ��
	friend class OgdcDatasetVectorMdb;

public:
	//! \brief ��¼����Ĭ�Ϲ��캯��
	OgdcRecordsetMdb();

	//! \brief ��ָ��ʸ�����ݼ�ָ��Ĺ��캯��
	//! \param pDataset ָ��ʸ�����ݼ���ָ��[in]��
	OgdcRecordsetMdb(OgdcDatasetVectorMdb *pDataset);

	//! \brief ��¼����Ĭ����������
	virtual ~OgdcRecordsetMdb();

public:
	//! \brief �Ƿ��¼��Ϊ��(û�м�¼)��
	//! \return ��¼��Ϊ�շ���TRUE���ǿշ���FALSE��
	virtual OgdcBool IsEmpty() ; 	
	
	//! \brief �жϵ�ǰ��¼ָ���Ƿ�ָ��ͷ��
	//! \return ָ��ָ��ͷ����TRUE�����򷵻�FALSE��
	virtual OgdcBool IsBOF() ;	
	
	//! \brief �жϵ�ǰ��¼ָ���Ƿ�ָ��β��
	//! \return ָ��ָ��β����TRUE�����򷵻�FALSE��
	virtual OgdcBool IsEOF() ;	
	
	//! \brief �رռ�¼��
	virtual void Close() ;
	
	//! \brief ͨ���ֶ�����ȡ�ֶ�ֵ��
	//! \param strName �ֶ���[in]��
	//! \param varVal �ֶ�ֵ[out]��
	//! \return �Ƿ�ɹ���ȡ���ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool GetFieldValue(const OgdcString& strName, OgdcVariant& varVal) ;	
	
	//! \brief ͨ���ֶ���Ż�ȡ�ֶ�ֵ��
	//! \param nIndex �ֶ����[in]��
	//! \param varVal �ֶ�ֵ[out]��
	//! \return �Ƿ�ɹ���ȡ���ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool GetFieldValue(OgdcInt nIndex,OgdcVariant& varVal) ;	
	
	//! \brief ͨ���ֶ������õ�ǰ��¼���ֶ�ֵ��
	//! \param strName �ֶ���[in]��
	//! \param varVal �ֶ�ֵ[in]��
	//! \return �Ƿ����óɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks �ֶ�ֵΪ��������
	virtual OgdcBool SetFieldValue(const OgdcString& strName,const OgdcVariant& varVal) ;	
	
	//! \brief ͨ���ֶ�������õ�ǰ��¼���ֶ�ֵ��
	//! \param nIndex �ֶ����[in]��
	//! \param varVal �ֶ�ֵ[in]��
	//! \return �Ƿ����óɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks �ֶ�ֵΪ�������͡�
	virtual OgdcBool SetFieldValue(OgdcInt nIndex,const OgdcVariant& varVal) ;	
	
	//! \brief ����ָ�������ļ�¼��
	//! \param strFilter Ϊ��ѯ���������� ��ID = 5",����IDΪ5�ļ�¼[in]��
	//! \param nFindMode Ϊ����ģʽ�����ҵ�ǰģʽ�����������ļ�¼��Ĭ��ΪFirst[in]��
	//! \return �Ƿ���ҳɹ���
	//! \remarks ����ģʽ First--��һ����Last--���һ����Next--��һ����Prev--ǰһ��  
	virtual OgdcBool Find(const OgdcString& strFilter, 
		OgdcRecordset::FindMode nFindMode = OgdcRecordset::First) ;	
	
	//! \brief ��¼���α��ƶ���ָ��λ�á�
	//! \param nFromPosition Moveλ�ã�Ĭ��ΪCurrent[in]��
	//! \param �ƶ��Ĵ���[in]��
	//! \return �Ƿ��Ѿ��ƶ���ָ��λ�á�
	//! \remarks Moveλ�ã�Current--��ǰλ�ã�Begin--��ͷ��End--ĩβ  
	virtual OgdcBool Move(OgdcRecordset::MovePosition nFromPosition = OgdcRecordset::Current, 
		OgdcInt nRows = 1) ;	
	
	//! \brief ��ȡ��¼������
	//! \return ��¼������
	virtual OgdcInt GetRecordCount() ;	
	
	//! \brief �ռ������ֶε���Ϣ��
	//! \param fieldInfos �����ռ������ֶε��ֶ���Ϣ���������[out]��
	//! \return �Ƿ��ռ��ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool GetFieldInfos(OgdcFieldInfos& fieldInfos) ;	
	
	//! \brief ͨ���ֶ�����ȡ�ֶ���Ϣ��
	//! \param strName �ֶ���[in]��
	//! \param fieldInfo �ֶ���Ϣ����[out]��
	//! \return �Ƿ��ȡ�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool GetFieldInfo(const OgdcString& strName,OgdcFieldInfo& fieldInfo)  ;			

	//! \brief ��ĳ��ͳ�Ʒ���ͳ��ĳ���ֶΡ�
	//! \param strFieldName ͳ�Ƶ��ֶ���[in]��
	//! \param nMode ͳ��ģʽ[in]��
	//! \return ͳ��ֵ��
	//! \remarks ��ͳ�Ƶ��ֶ�����Ϊ�����ͣ����ͣ������ͣ�����˫���ȸ�����
	virtual OgdcVariant Statistic(const OgdcString& strFieldName,
		OgdcStatisticMode nMode) ;	

	//! \brief ���²�ѯ��ˢ�¼�¼����
	//! \return �Ƿ�ɹ���ѯ���ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool ReQuery() ;	

	//! \brief �����¼���ĵ���Χ��
	//! \param rc2Bounds ��¼���ĵ���Χ[out]��
	//! \param &dMinZ ��¼����С�߳�[in]��
	//! \param &dMaxZ ��¼�����߳�[in]��
	//! \return �Ƿ����ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool ComputeBounds(OgdcRect2D &rc2Bounds,
		OgdcDouble &dMinZ, OgdcDouble &dMaxZ) ;	

public:
	//! \brief �����ֶ�ֵ��
	//! \param strSrcField Դ�ֶ���[in]��
	//! \param strDestField Ŀ���ֶ���[in]��
	//! \return �Ƿ�ɹ����ƣ��ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \attention strSrcField��trDestField���붼�������ֶ�����ƥ�䡣
	virtual OgdcBool CopyField(const OgdcString& strSrcExpression,
		const OgdcString& strDestFieldName) ;	
	
	//! \brief ��ȡ��ǰ��¼��ID��
	//! \return ��ǰ��¼��ID��
	virtual OgdcInt GetID() ;	

	//! \brief ��ȡ���ζ��󣬷��صļ��ζ���ָ���ں����ڷ����ڴ棬��
	//! \param pElement �ռ��ζ���ָ������ȡ�����ζ���[in]��
	//! \return �Ƿ�ȡ���ζ���ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \attention ���渺��ɾ������������ڴ�й©��
	virtual OgdcBool GetElement(OgdcElement*& pElement) ;	

	//! \brief ���õ�ǰ��¼�ļ��ζ���
	//! \param pElement ���ζ���ָ��[in]��
	//! \return �Ƿ����ü��ζ���ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SetElement(OgdcElement* pElement) ;	

	//! \brief �����¼�¼,�ɹ�������TRUEֵ��ʧ�ܷ���FALSEֵ��
	//! \param pGeometry [in] ��ӵ�Geometryָ��
	//! \param bReturnID=FALSE [in] �˲����Ѿ��������á�
	//! \return True �� False ��ֵ
	//! \remarks �����õ��¶����ID����ô���ϵ���GetId����
	virtual OgdcInt AddNew(OgdcElement *pElement, OgdcBool bReturnID=FALSE) ;

	//! \brief ȡ�����ݼ���ĳ������Ҫ�ء�
	//! \param nID ���ݼ���¼ID��[in]��
	//! \return ����Ҫ��ָ�롣
	//! \attention ���渺��ɾ������������ڴ�й©��
	virtual OgdcFeature* GetFeature() ;	

	//! \brief ������Ҫ�ظ��µ����ݼ��С�
	//! \param pFeature ����Ҫ��ָ��[in]��
	//! \return �Ƿ񱣴�ɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool UpdateFeature(const OgdcFeature* pFeature) ;
	
	//! \brief ������Ҫ��׷�ӵ����ݼ�δβ��
	//! \param pFeature ����Ҫ��ָ��[in]��
	//! \return �Ƿ�׷�ӳɹ����ɹ�����TRUE��ʧ�ܷ���FALSE��
	//! \remarks ׷��ʱ����Ҫ�ع��������ݼ���¼ID���������á�
	virtual OgdcBool AddFeature(const OgdcFeature* pFeature) ;

	//! \brief ͨ��ID��λ��¼ָ�롣
	//! \param nID ��¼ID[in]��
	//! \return ��λ�ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool SeekID(OgdcInt nID) ;	

	//! \brief ����¼�����µ����ݼ���
	//! \return ���¼�¼��ID��
	virtual OgdcInt Update() ;	

	//! \brief ȡ���޸ġ�
	//! \return �ɹ�ȡ������TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool CancelUpdate() ;	
	
	//! \brief ��ʼ�޸����ݡ�
	//! \return �ɹ���ʼ����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool Edit() ;	

	//! \brief �Ƿ�ɸ���
	//! \return �ɸ��·���TRUE�����򷵻�FALSE��
	virtual OgdcBool CanUpdate() ;	
	
	//! \brief ɾ����ǰ��¼��
	//! \return �Ƿ�ɹ�ɾ�����ɹ�����TRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool Delete() ;	

	//! \brief ɾ�����м�¼��
	//! \return ɾ���ɹ�����TRRUE��ʧ�ܷ���FALSE��
	virtual OgdcBool DeleteAll() ;
	
	//! \brief ��ȡ��ǰ���ݼ�ָ�롣
	//! \return ָ��ǰ���ݼ���ָ�롣
	virtual OgdcDatasetVector* GetDataset() ;	

protected:
	
	//! \brief �ڲ�ѯʱ���ü�¼����
	void SetRecordCount();

protected:
	//! \brief ָ��ǰ���ݼ���ָ��
	OgdcDatasetVectorMdb *m_pDataset;

	//! \brief ��ÿ���ֶ����ݵ�����
	OgdcArray<OgdcByte*> m_fieldValues;

	//! \brief ��¼��ID
	OgdcInt m_nID;

	//! \brief ��ѯMDBʱʹ��
	CDaoRecordset* m_pDaoRecordset;	   	
	
	//! \brief ���Բ�ѯ����
	OgdcString m_strFilter;

	//! \brief ���ݼ��ı���
	OgdcString m_strTableName;

	//! \brief ������־�Ƿ�ִ����Edit()����
	OgdcBool m_bEdited;   

	//! \brief Edit״̬
	//! \remarks 0--EditNone ;1--EditInprogress; 2--EditAdd; 3--EditOfGeometry
	OgdcInt	m_nEditMode; 

	// \brief ��ǰ������еļ�¼��Ŀ
	OgdcLong m_nRecordCount;

	//! \brief ��ӵļ�¼�Ƿ�Ϊ�׼�¼�ı�־
	OgdcBool m_bFirstAddNew;
	
	//! \brief ָ��ü�¼�ļ��ζ����ָ��
	OgdcElement* m_pElement;

};

}

#endif // !defined(AFX_OGDCRECORDSETMDB_H__EE00C954_14D4_4C36_9BEA_84CED998068D__INCLUDED_)
