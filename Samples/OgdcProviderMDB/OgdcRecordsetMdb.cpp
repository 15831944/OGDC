//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)         
//                                                           
//!  \file OgdcRecordsetMdb.cpp
//!  \brief OGDC��¼���Ľӿ�ʵ�֡�
//!  \details OGDC��¼�����ֲ����ӿڵ�ʵ��
//!  \author yangchao��
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#include "OgdcRecordsetMdb.h"
#include "OgdcHelperMdb.h"
#include "OgdcDataSourceMdb.h"
#include "OgdcMacroDefineMdb.h"
#include "OgdcDatasetVectorMdb.h"
#include "OgdcFeatureMdb.h"
#include "Element/OgdcElemPoint.h"
#include "Element/OgdcElemLine.h"
#include "Element/OgdcElemText.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace OGDC
{

OgdcRecordsetMdb::OgdcRecordsetMdb()
{
	m_nID = 0;
	m_bEdited = FALSE;
	m_pDataset = NULL;
	m_strFilter = OGDCPCTSTR("");
	m_strTableName = OGDCPCTSTR("");
	m_nRecordCount = 0;
	m_nEditMode = dbEditNone;
	m_bFirstAddNew = FALSE; 
	m_pElement = NULL;
	m_pDaoRecordset = NULL;
}

OgdcRecordsetMdb::OgdcRecordsetMdb( OgdcDatasetVectorMdb *pDataset )
{
	m_nID = 0;
	m_bEdited = FALSE;
	m_pDataset = pDataset;
	m_strTableName = pDataset->m_info.m_strName;
	m_strFilter = OGDCPCTSTR("");
	m_pDataset = pDataset;
	m_nRecordCount = 0;
	m_nEditMode = dbEditNone;
	m_pElement = NULL;
	m_bFirstAddNew = FALSE; 
	m_pDaoRecordset = NULL;
}

OgdcRecordsetMdb::~OgdcRecordsetMdb()
{
	Close();
}

OgdcBool OgdcRecordsetMdb::IsEmpty()
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return TRUE;
	}
	return	(m_pDaoRecordset->GetRecordCount()<=0);
}

OgdcBool OgdcRecordsetMdb::IsBOF()
{
	if (!m_pDaoRecordset->IsOpen())
		return FALSE;
	try
	{
		return m_pDaoRecordset->IsBOF ();
		
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}	
}

OgdcBool OgdcRecordsetMdb::IsEOF()
{
	if (!m_pDaoRecordset->IsOpen())
		return FALSE;
	try
	{
		return m_pDaoRecordset->IsEOF();
		
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
}

void OgdcRecordsetMdb::Close()
{
	if(m_pDaoRecordset == NULL)
	{
		return;
	}

	if (m_pDaoRecordset->IsOpen())
	{
		try
		{
			if(m_bEdited && m_nEditMode != dbEditNone)
			{
				m_pDaoRecordset->Update ();
				//�ڲ�ʹ�� AddNew �� Edit ������£����� (Update) 
			}
			m_pDaoRecordset->Close();
		}
		catch (CDaoException* e)
		{
			e->Delete();
		}
	}
	
	delete m_pDaoRecordset;
	m_pDaoRecordset = NULL;

	m_bEdited = FALSE;
	m_nEditMode = dbEditNone;
	
	if (m_pElement != NULL)
	{
		//m_pElement �ǵ�ǰ�༭�������ⲿ����Ķ���ָ��
		m_pElement = NULL;
	}
}

OgdcBool OgdcRecordsetMdb::GetFieldValue( const OgdcString& strName, OgdcVariant& varVal )
{
 	if (!m_pDaoRecordset->IsOpen())
 	{
 		return FALSE;
 	}
	
	if (IsBOF())
	{
		return FALSE;
	}
	if (IsEOF())
	{
		return FALSE;
	}
	COleVariant cOleVar;
	try
	{
		m_pDaoRecordset->GetFieldValue(strName, cOleVar);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	OgdcHelperMdb::COleVariant2OgdcVariant(cOleVar, varVal);

	return TRUE;
}

OgdcBool OgdcRecordsetMdb::GetFieldValue( OgdcInt nIndex,OgdcVariant& varVal )
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	//��ǰ��¼��Ч
    if (IsBOF())
	{
		return FALSE;
	}
	if (IsEOF())
	{
		return FALSE;
	}
	COleVariant cOleVar;
	try
	{
		m_pDaoRecordset->GetFieldValue(nIndex, cOleVar);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	
	OgdcHelperMdb::COleVariant2OgdcVariant(cOleVar, varVal);
	
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::SetFieldValue( const OgdcString& strName, const OgdcVariant& varVal )
{
	if (OgdcHelperMdb::IsSystemField(strName))
		return FALSE;

	OgdcVariant myVarValue = varVal;
	COleVariant var;
	OgdcString strSQL;
	strSQL.Format(OGDCPCTSTR("UPDATE [%s] set %s = '%s' WHERE OGID = %d "),
		OGDCPCTSTR(m_strTableName), OGDCPCTSTR(strName),
		OGDCPCTSTR(myVarValue.ToString()), GetID());

	try
	{
		m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);
	}
	catch(CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::SetFieldValue( OgdcInt nIndex,const OgdcVariant& varVal )
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	
	if (!Edit())
	{
		return FALSE;
	}
	CDaoFieldInfo fieldInfo;
	m_pDaoRecordset->GetFieldInfo(nIndex,fieldInfo);
	OgdcVariant myVarValue = varVal;
	COleVariant var;
	try
	{
		OgdcHelperMdb::OgdcVariant2COleVariant(myVarValue, var);
		m_pDaoRecordset->SetFieldValue(nIndex, var);
		m_pDaoRecordset->Update();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	
	
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::Find( const OgdcString& strFilter, OgdcRecordset::FindMode nFindMode /*= OgdcRecordset::First*/ )
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	//�ƶ�ʱ��ǰ��AddNew��Editȡ��
	CancelUpdate();
	//Ϊ�˷�ֹ�Ҳ������ȼ�¼��ǰ��λ���Ա�ָ�
	COleVariant varValue;
	try
	{
		m_pDaoRecordset->GetFieldValue(0, varValue);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	OgdcBool bResult;
	if (nFindMode == FindMode::First)
	{
		try
		{
			bResult = m_pDaoRecordset->FindFirst(strFilter);
			bResult = TRUE;
		}
		catch (CDaoException* e)
		{
			e->Delete();
			bResult = FALSE;
		}
	}
	else if (nFindMode==FindMode::Last)
	{
		try
		{
			bResult = m_pDaoRecordset->FindLast(strFilter);
			bResult = TRUE;
		}
		catch (CDaoException* e)
		{
			e->Delete();
			bResult =  FALSE;
		}
	}
	else if (nFindMode == FindMode::Next)
	{
		try
		{
			bResult = m_pDaoRecordset->FindNext(strFilter);
			bResult = TRUE;
		}
		catch (CDaoException* e)
		{
			e->Delete();
			bResult = FALSE;
		}
	}
	else if (nFindMode==FindMode::Prev)
	{
		try
		{
			bResult = m_pDaoRecordset->FindPrev(strFilter);
			bResult = TRUE;
		}
		catch (CDaoException* e)
		{
			e->Delete();
			bResult = FALSE;
		}
	}


	//����Ҳ����Ļ����ָ�Recordset��ָ��
	if (!bResult) 
	{
		SeekID(varValue.lVal);
	}
	
	return bResult;
}

OgdcBool OgdcRecordsetMdb::Move( OgdcRecordset::MovePosition nFromPosition /*= OgdcRecordset::Current*/, 
	OgdcInt nRows /*= 1*/ )
{
	if( !m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	//��ǰ��¼��Ϊ��
	if (IsEmpty ())
	{
		return FALSE;
	}
		
	//�ƶ�ʱ��ǰ��AddNew��Editȡ��
	CancelUpdate();
	
	//if (!m_pDaoRecordset->IsBOF() && !m_pDaoRecordset->IsEOF())
	try
	{
		if (nFromPosition == MovePosition::Begin)
		{
			m_pDaoRecordset->MoveFirst();
			if (nRows)
			{
				m_pDaoRecordset->Move(nRows);
			}
		}
		else if (nFromPosition == MovePosition::End)
		{
			m_pDaoRecordset->MoveLast();
			if (nRows)
			{
				//���move�������������������ƶ�
				m_pDaoRecordset->Move(-nRows);
			}

		}
		else if (nFromPosition == MovePosition::Current)
		{
			m_pDaoRecordset->Move(nRows);	
		}
		else
		{
			return FALSE;
		}
		
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}

OgdcInt OgdcRecordsetMdb::GetRecordCount()
{
// 	if( !m_pDaoRecordset->IsOpen())
// 	{
// 		return -1;
// 	}
// 	if (m_pDaoRecordset->IsEOF()&&m_pDaoRecordset->IsBOF())
// 	{
// 		return 0;
// 	}
// 	m_pDaoRecordset->MoveLast();
// 	m_nRecordCount = m_pDaoRecordset->GetRecordCount();
// 	m_pDaoRecordset->MoveFirst();
	return OgdcInt(m_nRecordCount);
}

void OgdcRecordsetMdb::SetRecordCount()
{
	if( !m_pDaoRecordset->IsOpen())
	{
		return;
	}
	if (m_pDaoRecordset->IsEOF()&&m_pDaoRecordset->IsBOF())
	{
		return;
	}
	m_pDaoRecordset->MoveLast();
	m_nRecordCount = m_pDaoRecordset->GetRecordCount();
	m_pDaoRecordset->MoveFirst();
}

OgdcBool OgdcRecordsetMdb::GetFieldInfos( OgdcFieldInfos& fieldInfos )
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	
	fieldInfos.RemoveAll();
	
	OgdcInt m_nFields = m_pDaoRecordset->GetFieldCount();
	CDaoFieldInfo info;
	OgdcFieldInfo fieldInfo;
	fieldInfos.SetSize(m_nFields);
	for (OgdcInt i = 0; i < m_nFields; i++)
	{	
		try
		{
			m_pDaoRecordset->GetFieldInfo( OgdcInt(i), info);
			OgdcHelperMdb::CDaoFieldInfo2OgdcFieldInfo(info, fieldInfo);
		}
		catch (CDaoException* e)
		{
			e->Delete();
			return FALSE;
		}
		
		//OgdcHelperMdb::CDaoFieldInfo2OgdcFieldInfo(info, fieldInfo);
		OgdcHelperMdb::SetFieldSign(fieldInfo);
		fieldInfos.SetAt(i, fieldInfo);
		fieldInfo.m_nFieldSign = OgdcFieldInfo::signNone;
		fieldInfo.m_bSystem = FALSE;
	}
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::GetFieldInfo( const OgdcString& strName,OgdcFieldInfo& fieldInfo )
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	CDaoFieldInfo info;
	try
	{
		if (strName.CompareNoCase(OGDCPCTSTR("SMID")) == 0)
		{
			m_pDaoRecordset->GetFieldInfo("OGID", info);
		}
		else
		{
			m_pDaoRecordset->GetFieldInfo(strName, info);
		}
		OgdcHelperMdb::CDaoFieldInfo2OgdcFieldInfo(info, fieldInfo);
		OgdcHelperMdb::SetFieldSign(fieldInfo);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	return TRUE;	
}

OgdcVariant OgdcRecordsetMdb::Statistic( const OgdcString& strFieldName, OgdcStatisticMode nMode )
{

	OgdcVariant ogdcVar;
	OgdcVariant errorVar = 0;
	
	OgdcString strOGFieldName = "OGID";
	if (strFieldName.CompareNoCase(OGDCPCTSTR("SMID")) == 0)
		strOGFieldName = "OGID";
	else
		strOGFieldName = strFieldName;

	OgdcFieldInfo fieldInfo;
	GetFieldInfo(strFieldName, fieldInfo);
	if (!(fieldInfo.m_nType == OgdcFieldInfo::INT16
		|| fieldInfo.m_nType == OgdcFieldInfo::INT32
		|| fieldInfo.m_nType == OgdcFieldInfo::INT64
		|| fieldInfo.m_nType == OgdcFieldInfo::Float
		|| fieldInfo.m_nType == OgdcFieldInfo::Double))
	{
		return errorVar;
	}

	OgdcString strSQL;
	switch(nMode)
	{
	case OgdcStatisticMode::smMax:
		if(!m_strFilter.IsEmpty ()) 
		{
			strSQL.Format(OGDCPCTSTR("SELECT Max(%s) FROM [%s] WHERE %s "),
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName),
				OGDCPCTSTR(m_strFilter));
		}
		else
		{
			strSQL.Format(OGDCPCTSTR("SELECT Max(%s) FROM [%s] "),
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName));
		}
		break;
	case OgdcStatisticMode::smMin:
		if (!m_strFilter.IsEmpty ())
		{
			strSQL.Format(OGDCPCTSTR("SELECT MIN(%s) FROM [%s] WHERE %s "),
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName),
				OGDCPCTSTR(m_strFilter));
		}
		else
		{
			strSQL.Format(OGDCPCTSTR("SELECT MIN(%s) FROM [%s] "), 
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName));
		}
		break;
	case OgdcStatisticMode::smAvg:
		if (!m_strFilter.IsEmpty ())
		{
			strSQL.Format(OGDCPCTSTR("SELECT AVG(%s) FROM [%s] WHERE %s"), 
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName), 
				OGDCPCTSTR(m_strFilter));
		}
		else
		{
			strSQL.Format(OGDCPCTSTR("SELECT AVG(%s) FROM [%s] "), 
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName));
		}
		break;
	case OgdcStatisticMode::smSum:
		if (!m_strFilter.IsEmpty ())
		{
			strSQL.Format(OGDCPCTSTR("SELECT SUM(%s) FROM [%s] WHERE %s"),
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName), 
				OGDCPCTSTR(m_strFilter));
		}
		else
		{
			strSQL.Format(OGDCPCTSTR("SELECT SUM(%s) FROM [%s] "),
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName));
		}
		break;
	case OgdcStatisticMode::smStdev:
		if (!m_strFilter.IsEmpty ())
		{
			strSQL.Format(OGDCPCTSTR("SELECT StDev(%s) FROM [%s] WHERE %s "), 
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName),
				OGDCPCTSTR(m_strFilter));
		}
		else
		{
			strSQL.Format(OGDCPCTSTR("SELECT StDev(%s) FROM [%s] "), 
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName));
		}
		break;
	case OgdcStatisticMode::smVar:
		if (!m_strFilter.IsEmpty ())
		{
			strSQL.Format(OGDCPCTSTR("SELECT Var(%s) FROM [%s] WHERE %s "),
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName),
				OGDCPCTSTR(m_strFilter));
		}
		else
		{
			strSQL.Format(OGDCPCTSTR("SELECT Var(%s) FROM [%s] "), 
				OGDCPCTSTR(strOGFieldName), OGDCPCTSTR(m_strTableName));
		}
		break;
	default:
		return ogdcVar;
	}
	
	CDaoRecordset recordset(&(m_pDataset->m_pDataSource->m_daoDatabase));

	try
	{
		if (m_pDaoRecordset->IsOpen())
			m_pDaoRecordset->Close();
		m_pDaoRecordset->Open(dbOpenDynaset, strSQL);
		COleVariant varlue;
		m_pDaoRecordset->GetFieldValue (0, varlue);
		OgdcHelperMdb::COleVariant2OgdcVariant(varlue, ogdcVar);
		m_pDaoRecordset->Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		m_pDaoRecordset->Close();
		return errorVar;
	}

	return ogdcVar;
}

OgdcBool OgdcRecordsetMdb::ReQuery()
{
	if (!m_pDaoRecordset->IsOpen())
		return	FALSE;
	
	else
	{
		try
		{
			m_pDaoRecordset->Requery();		
		}
		catch (CDaoException* e)
		{
			e->Delete();
			return FALSE;
		}
		
	}
	return TRUE;

}

OgdcBool OgdcRecordsetMdb::ComputeBounds( OgdcRect2D &rc2Bounds, OgdcDouble &dMinZ, OgdcDouble &dMaxZ )
{
	//��ֵ
	rc2Bounds.SetEmpty();
	dMinZ = dMaxZ = 0;
	//����
	if (!(m_pDataset)->IsOpen() 
		|| m_pDataset->m_info.m_nType == OgdcDataset::Tabular
		|| IsEmpty())
	{
		return FALSE;
	}
	
	OgdcDouble MinW, MaxE, MinS, MaxN;
	if (m_pDataset->GetType() == OgdcDataset::Point)
	{
		//����ǵ㣬��ʼ��boundsΪ����Χ�ľ���10�ľ���
		m_pDaoRecordset->MoveFirst();
		COleVariant varValue;
		m_pDaoRecordset->GetFieldValue(OG_X, varValue);
		MinW = varValue.dblVal - 10;
		m_pDaoRecordset->GetFieldValue(OG_Y, varValue);
		MaxN = varValue.dblVal + 10;
		m_pDaoRecordset->GetFieldValue(OG_X, varValue);
		MaxE = varValue.dblVal + 10;
		m_pDaoRecordset->GetFieldValue(OG_Y, varValue);
		MinS = varValue.dblVal - 10;
		
		while (!m_pDaoRecordset->IsEOF())
		{
			m_pDaoRecordset->GetFieldValue(OG_X, varValue);
			MinW = varValue.dblVal < MinW ? varValue.dblVal : MinW;
			m_pDaoRecordset->GetFieldValue(OG_Y, varValue);
			MaxN = varValue.dblVal > MaxN ? varValue.dblVal : MaxN;
			m_pDaoRecordset->GetFieldValue(OG_X, varValue);
			MaxE = varValue.dblVal > MaxE ? varValue.dblVal : MaxE;
			m_pDaoRecordset->GetFieldValue(OG_Y, varValue);
			MinS = varValue.dblVal < MinS ? varValue.dblVal : MinS;
			m_pDaoRecordset->MoveNext();
		}
		m_pDaoRecordset->MoveFirst();
	}
	else
	{
		m_pDaoRecordset->MoveFirst();
		COleVariant varValue;
		m_pDaoRecordset->GetFieldValue(OG_SDRI_W, varValue);
		MinW = varValue.dblVal;
		m_pDaoRecordset->GetFieldValue(OG_SDRI_N, varValue);
		MaxN = varValue.dblVal;
		m_pDaoRecordset->GetFieldValue(OG_SDRI_E, varValue);
		MaxE = varValue.dblVal;
		m_pDaoRecordset->GetFieldValue(OG_SDRI_S, varValue);
		MinS = varValue.dblVal;
		
		while (!m_pDaoRecordset->IsEOF())
		{
			m_pDaoRecordset->GetFieldValue(OG_SDRI_W, varValue);
			MinW = varValue.dblVal < MinW ? varValue.dblVal : MinW;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_N, varValue);
			MaxN = varValue.dblVal > MaxN ? varValue.dblVal : MaxN;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_E, varValue);
			MaxE = varValue.dblVal > MaxE ? varValue.dblVal : MaxE;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_S, varValue);
			MinS = varValue.dblVal < MinS ? varValue.dblVal : MinS;
			m_pDaoRecordset->MoveNext();
		}
		m_pDaoRecordset->MoveFirst();
	}

	rc2Bounds.left = MinW;
	rc2Bounds.right = MaxE;
	rc2Bounds.top = MaxN;
	rc2Bounds.bottom = MinS;
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::CopyField( const OgdcString& strSrcExpression, const OgdcString& strDestFieldName )
{
	if (!m_pDaoRecordset->IsOpen())
	{
		//�����
		return FALSE;
	}
	OgdcFieldInfo fiSrc,fiDest;
	CDaoFieldInfo daoFirst,daoEest;
	try
	{
		//�ж��ֶ��Ƿ����
		m_pDaoRecordset->GetFieldInfo(strSrcExpression, daoFirst, AFX_DAO_ALL_INFO);
		m_pDaoRecordset->GetFieldInfo(strDestFieldName, daoEest, AFX_DAO_ALL_INFO);
		if (daoFirst.m_strName != strSrcExpression || daoEest.m_strName != strDestFieldName)
		{
			return FALSE;
		}
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	
	OgdcString strSQL;

	if (m_strFilter.IsEmpty())
	{
		strSQL.Format(OGDCPCTSTR("UPDATE %s SET %s = %s"),
			OGDCPCTSTR(m_strTableName), OGDCPCTSTR(strDestFieldName),
			OGDCPCTSTR(strSrcExpression));
	}
	else
	{	
		strSQL.Format(OGDCPCTSTR("UPDATE %s SET %s = %s WHERE %s"), 
			OGDCPCTSTR(m_strTableName), OGDCPCTSTR(strDestFieldName),
			OGDCPCTSTR(strSrcExpression), OGDCPCTSTR(m_strFilter));
	}
	try
	{
		m_pDataset->m_pDataSource->m_daoDatabase.Execute (strSQL);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	return TRUE;
}

OgdcInt OgdcRecordsetMdb::GetID()
{
	if( !m_pDaoRecordset->IsOpen())
	{
		//�����
		return -1;
	}

	COleVariant varValue;
	try
	{
		m_pDaoRecordset->GetFieldValue(0, varValue);
		m_nID = varValue.lVal;
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return 0;
	}

	return m_nID;	
}

OgdcBool OgdcRecordsetMdb::GetElement( OgdcElement*& pElement )
{
	if (IsBOF())
	{
		return FALSE;
	}
	if (m_pDataset->GetType() == OgdcDataset::Tabular)
	{
		return FALSE;
	}

	//�õ���ǰ��ID
	OgdcInt nID = GetID();
	if (nID == 0) 
	{
		return FALSE;
	}

	COleVariant var;

	//�����ݿ���ȡ����������
	COleVariant varArray;
	BSTR HUGEP *pbstr = NULL;
	long lLBound,lUBound;
	OgdcByte *pData = NULL;
	OgdcByte *pDataMirror = NULL;

	if (m_pDataset->GetType() != OgdcDataset::Point)
	{
		m_pDaoRecordset->GetFieldValue(OG_GEOMETRY,varArray);
		
		if (FAILED(SafeArrayGetLBound(varArray.parray, 1, &lLBound)))
		{
			return FALSE;
		}
		if (FAILED(SafeArrayGetUBound(varArray.parray, 1, &lUBound)))
		{
			return FALSE;
		}
		if (FAILED(SafeArrayAccessData(varArray.parray, (void HUGEP* FAR*)&pbstr)))
		{
			return FALSE;
		}
		
		long dataSize = lUBound - lLBound + 1;
		pData = new BYTE[dataSize];
		memcpy( pData, pbstr, dataSize);

		SafeArrayUnaccessData(varArray.parray);

		pDataMirror = pData;
	}

	OgdcInt i = 0;
	switch (m_pDataset->GetType())
	{
	case OgdcDataset::Point:
		{
			if (NULL == pElement || pElement->GetType() != OgdcElement::ElemPoint)
			{
				delete pElement;
				pElement = new OgdcElemPoint();
			}
			m_pDaoRecordset->GetFieldValue(OG_OBJ_ID, var);
			((OgdcElemPoint*)pElement)->m_nID = var.lVal;
			m_pDaoRecordset->GetFieldValue(OG_X, var);
			((OgdcElemPoint*)pElement)->m_point.x = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_Y, var);
			((OgdcElemPoint*)pElement)->m_point.y = var.dblVal;
			pElement->m_nID = nID;
		}
		break;
	case OgdcDataset::Line:
		{
			if (NULL == pElement || m_pDataset->GetType() != OgdcElement::ElemLine)
			{
				delete pElement;
				pElement = new OgdcElemLine();
			}

			OgdcInt nPointCount=0, nSubCount=0;
			
			((OgdcElemLine*)pElement)->m_nID = nID;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_W, var);
			((OgdcElemLine*)pElement)->m_rcBounds.left = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_N, var);
			((OgdcElemLine*)pElement)->m_rcBounds.top = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_E, var);
			((OgdcElemLine*)pElement)->m_rcBounds.right = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_S, var);
			((OgdcElemLine*)pElement)->m_rcBounds.bottom = var.dblVal;
			
			memcpy(&nPointCount, pDataMirror, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			memcpy(&nSubCount, pDataMirror, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			((OgdcElemLine*)pElement)->m_polyCounts.SetSize(nSubCount);
			((OgdcElemLine*)pElement)->m_points.SetSize(nPointCount);	
			for (i = 0; i< nSubCount; i++)
			{
				memcpy(&((OgdcElemLine*)pElement)->m_polyCounts[i], pDataMirror, 
					sizeof(OgdcInt));
				pDataMirror += sizeof(OgdcInt);
			}
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(&((OgdcElemLine*)pElement)->m_points[i].x, pDataMirror, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(&((OgdcElemLine*)pElement)->m_points[i].y, pDataMirror, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}
		}
		break;
	case OgdcDataset::Region:
		{
			if (NULL == pElement || m_pDataset->GetType() != OgdcElement::ElemRegion)
			{
				delete pElement;
				pElement = new OgdcElemRegion;
			}

			OgdcInt nPointCount=0, nSubCount=0;

			((OgdcElemRegion*)pElement)->m_nID = nID;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_W, var);
			((OgdcElemRegion*)pElement)->m_rcBounds.left = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_N, var);
			((OgdcElemRegion*)pElement)->m_rcBounds.top = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_E, var);
			((OgdcElemRegion*)pElement)->m_rcBounds.right = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_S, var);
			((OgdcElemRegion*)pElement)->m_rcBounds.bottom = var.dblVal;
			
			memcpy(&nPointCount, pDataMirror, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			memcpy(&nSubCount, pDataMirror, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			((OgdcElemRegion*)pElement)->m_polyCounts.SetSize(nSubCount);
			((OgdcElemRegion*)pElement)->m_points.SetSize(nPointCount);	
			for(i = 0; i < nSubCount; i++)
			{
				memcpy(&((OgdcElemRegion*)pElement)->m_polyCounts[i], pDataMirror, 
					sizeof(OgdcInt));
				pDataMirror += sizeof(OgdcInt);
			}
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(&((OgdcElemRegion*)pElement)->m_points[i].x, pDataMirror, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(&((OgdcElemRegion *)pElement)->m_points[i].y, pDataMirror, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}
		}
		break;
	case OgdcDataset::Text:
		{
		
			OgdcElemText *pElementText = new OgdcElemText();
			
			((OgdcElemText*)pElementText)->m_nID = nID;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_W, var);
			((OgdcElemText*)pElementText)->m_rcBounds.left = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_N, var);
			((OgdcElemText*)pElementText)->m_rcBounds.top = var.dblVal;
			m_pDaoRecordset->GetFieldValue(OG_SDRI_E, var);
			((OgdcElemText*)pElementText)->m_rcBounds.right = var.dblVal;
	 		m_pDaoRecordset->GetFieldValue(OG_SDRI_S, var);
	 		((OgdcElemText*)pElementText)->m_rcBounds.bottom = var.dblVal;
			OgdcInt i = 0;
			//{{ȡ���ֱ�־
			//��¼��ĸ���
			OgdcInt nPointCount;
			memcpy( &nPointCount, pDataMirror, 4 );
			pDataMirror += 4;
			//��¼���ı��ĸ�����Angles�ĸ��������Ӷ������
			OgdcInt nStrCount;
			memcpy( &nStrCount, pDataMirror, 4 );
			pDataMirror += 4;
			//��¼ÿ�����ı��ĳ���
			OgdcArray<OgdcInt> nStrLength;
			nStrLength.SetSize(nStrCount);
			//��ȡÿ�����ı��ĳ���
			for (i = 0; i < nStrCount; i++)
			{
				memcpy( &nStrLength.ElementAt(i), pDataMirror, 4 );
				pDataMirror += 4;
			}
			//��¼�ı�����У��������ֵĳ���
			OgdcInt nStrFaceNameLength;
			memcpy( &nStrFaceNameLength, pDataMirror, 4 );
			pDataMirror += 4;
			//}}ȡ���ֱ�־

			//���²���ȡ�ı����Ĳ���
			((OgdcElemText*)pElementText)->m_points.SetSize(nPointCount);
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(&((OgdcElemText*)pElementText)->m_points[i].x, pDataMirror, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);

				memcpy(&((OgdcElemText*)pElementText)->m_points[i].y, pDataMirror, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}

			((OgdcElemText*)pElementText)->m_strTexts.SetSize(nStrCount);
			OgdcString *str = new OgdcString;
			char *ch = new char;
			for (i = 0; i < nStrCount; i++)
			{
				((OgdcElemText*)pElementText)->m_strTexts[i].SetLength(nStrLength.GetAt(i));
				for (OgdcInt j = 0; j < nStrLength.GetAt(i); j++)
				{
					memcpy(ch, pDataMirror ,1);
					pDataMirror += 1;
					((OgdcElemText*)pElementText)->m_strTexts[i].SetAt(j, *ch);
				}
			}

			delete str;
			str = NULL;

			((OgdcElemText*)pElementText)->m_angles.SetSize(nStrCount);
			OgdcDouble *pDouble=new OgdcDouble;
			for (i = 0; i < nStrCount; i++)
			{
			
				memcpy(pDouble, pDataMirror, sizeof(OgdcDouble));
				((OgdcElemText*)pElementText)->m_angles.SetAt(i, *pDouble);
				pDataMirror += sizeof(OgdcDouble);
			}
			delete pDouble;
			pDouble = NULL;
			////////////////
			//1
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_clrFore, pDataMirror, 4);
			pDataMirror += 4;
			//2
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_clrBack, pDataMirror, 4);
			pDataMirror += 4;
			//3
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_dAngle, pDataMirror, 8);
			pDataMirror += 8;
			//4
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_dItalicAngle, pDataMirror, 8);
			pDataMirror += 8;
			//5
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_dWidth, pDataMirror, 8);
			pDataMirror += 8;
			//6
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_dHeight, pDataMirror, 8);
			pDataMirror += 8;
			//7
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_nWeight, pDataMirror, 4);
			pDataMirror += 4;
			//8
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_nStyle, pDataMirror, 4);
			pDataMirror += 4;
			//9
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_nAlign, pDataMirror, 1);
			pDataMirror += 1;
			//10
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bBold, pDataMirror, 1);
			pDataMirror += 1;
			//11
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bUnderline, pDataMirror, 1);
			pDataMirror += 1;
			//12
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bItalic, pDataMirror, 1);
			pDataMirror += 1;
			//13
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bStrikeOut, pDataMirror, 1);
			pDataMirror += 1;
			//14
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bFixedSize, pDataMirror, 1);
			pDataMirror += 1;
			//15
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bBackOpaque, pDataMirror, 1);
			pDataMirror += 1;
			//16
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bHalo, pDataMirror, 1);
			pDataMirror += 1;
			//17
			memcpy(&((OgdcElemText*)pElementText)->m_textStyle.m_bShadow, pDataMirror, 1);
			pDataMirror += 1;
			//18
			((OgdcElemText*)pElementText)->m_textStyle.m_strFaceName.SetLength(nStrFaceNameLength);
			for (i = 0; i < nStrFaceNameLength; i++)
			{				
				memcpy(ch, pDataMirror ,1);
 				pDataMirror += 1;
				((OgdcElemText*)pElementText)->m_textStyle.m_strFaceName.SetAt(i, *ch);
			}
			delete ch;
			ch = NULL;
			///////////////////////
			pElement = pElementText;
			pElementText = NULL;
		}
		break;
	default:
		return FALSE;
		break;
	}

	if (m_pDataset->GetType() != OgdcDataset::Point)
	{
		delete[] pData;
		pData = NULL;
	}

	return TRUE;	
}

OgdcBool OgdcRecordsetMdb::SetElement( OgdcElement* pElement )
{	
	if (!Edit())
	{
		return FALSE;
	}
	if (m_pDataset->GetType() == OgdcDataset::Point)
	{
		try
		{
			m_pDaoRecordset->SetFieldValue (OG_X, ((OgdcElemPoint *)pElement)->m_point.x);
			m_pDaoRecordset->SetFieldValue (OG_Y, ((OgdcElemPoint *)pElement)->m_point.y);
			m_pDaoRecordset->Update();
		}
		catch (CDaoException* e)
		{
			e->Delete();
			return FALSE;
		}		
	}
	else
	{
		
		OgdcRect2D bound = pElement->GetBounds();
		double dGranule = (bound.Width() > bound.Height() ? bound.Width() : bound.Height());
		CByteArray arr;

		if (m_pDataset->GetType() == OgdcDataset::Text)
		{
			OgdcInt i = 0;
			//��¼��ĸ���
			OgdcInt nPointCount = ((OgdcElemText*)pElement)->m_points.GetSize();
			//��¼���ı��ĸ�����Angles�ĸ��������Ӷ������
			OgdcInt nStrCount = ((OgdcElemText*)pElement)->m_strTexts.GetSize();
			//��¼ÿ�����ı��ĳ���
			//OgdcInt nStrLength[nStrCount];
			OgdcArray<OgdcInt> nStrLength;
			nStrLength.SetSize(nStrCount);
			//��¼�ı�����У��������ֵĳ���
			OgdcInt nStrFaceNameLength = ((OgdcElemText*)pElement)->m_textStyle .m_strFaceName.GetLength();
			//��ȡÿ�����ı��ĳ���
			for (i = 0; i < nStrCount; i++)
			{
				nStrLength[i]=((OgdcElemText*)pElement)->m_strTexts.GetAt(i).GetLength();
			}
			//����Count���ֽ���
			OgdcInt lSize = 4 + 4 + 4 * nStrCount + 4;
			//���е���ֽ���
			lSize += nPointCount * 16;
			//�������ı��ĳ���
			for (i = 0; i < nStrCount; i++)
			{
				lSize += nStrLength[i];
			}
			//����angele���ֽ���
			lSize += nPointCount * 8;
			//�ı�����У��������ֵ��ֽ���
			lSize += nStrFaceNameLength;
			//�ı�����У������������ֽ���
			lSize += 57;
			
			BYTE *pData = new BYTE[lSize];
			BYTE *pDataMirror = pData;
			//{{�����ֱ�־
			memcpy(pDataMirror, &nPointCount, 4);
			pDataMirror += 4;
			memcpy(pDataMirror, &nStrCount, 4);
			pDataMirror += 4;
			for (i = 0; i < nStrCount; i++)
			{
				OgdcInt *pOgdcInt = new OgdcInt;
				*pOgdcInt = nStrLength.GetAt(i);
				memcpy(pDataMirror, pOgdcInt, 4);
				pDataMirror += 4;
				delete pOgdcInt;
				pOgdcInt = NULL;
			}
			memcpy(pDataMirror, &nStrFaceNameLength, 4);
			pDataMirror += 4;
			//}}�����ֱ�־

			//���²��Ǵ��ı����Ĳ���
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_points[i].x,
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_points[i].y,
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}
			for (i = 0; i < nStrCount; i++)
			{
				for (OgdcInt j = 0; j < nStrLength.GetAt(i); j++)
				{
					OgdcChar ch = ((OgdcElemText*)pElement)->m_strTexts[i].GetAt(j);
					memcpy(pDataMirror, &ch, 1);
					pDataMirror += 1;
				}
			}
			for (i = 0; i < nStrCount; i++)
			{
				OgdcDouble *pDouble = new OgdcDouble;
				*pDouble = ((OgdcElemText*)pElement)->m_angles.GetAt(i);
				memcpy(pDataMirror, pDouble, sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				delete pDouble;
				pDouble = NULL;
			}
			////////////////
			//1
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_clrFore, 4);
			pDataMirror += 4;
			//2
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_clrBack, 4);
			pDataMirror += 4;
			//3
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dAngle, 8);
			pDataMirror += 8;
			//4
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dItalicAngle, 8);
			pDataMirror += 8;
			//5
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dWidth, 8);
			pDataMirror += 8;
			//6
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dHeight, 8);
			pDataMirror += 8;
			//7
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_nWeight, 4);
			pDataMirror += 4;
			//8
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_nStyle, 4);
			pDataMirror += 4;
			//9
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_nAlign, 1);
			pDataMirror += 1;
			//10
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bBold, 1);
			pDataMirror += 1;
			//11
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bUnderline, 1);
			pDataMirror += 1;
			//12
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bItalic, 1);
			pDataMirror += 1;
			//13
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bStrikeOut, 1);
			pDataMirror += 1;
			//14
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bFixedSize, 1);
			pDataMirror += 1;
			//15
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bBackOpaque, 1);
			pDataMirror += 1;
			//16
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bHalo, 1);
			pDataMirror += 1;
			//17
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bShadow, 1);
			pDataMirror += 1;
			//18
			for (i = 0; i < nStrFaceNameLength; i++)
			{
				OgdcChar ch = ((OgdcElemText*)pElement)->m_textStyle.m_strFaceName.GetAt(i);
				memcpy(pDataMirror, &ch, 1);
				pDataMirror += 1;
			}
			///////////////////////
			//��pdataһ���ֽ�һ���ֽڵ�װ��CBYteArray�����У�����ole��������
			
			arr.SetSize(lSize);
			for (i = 0; i < lSize; i++)
			{
				arr.SetAt(i, pData[i]);
			}
			delete pData;
			pData = NULL;
			nStrLength.RemoveAll();

		}
		else if(m_pDataset->GetType() == OgdcDataset::Line)
		{
			//ogdc��û��getdata�������������Լ����㼸�ζ������ڴ��еĴ�С�����ҿ������ݽ�pdata
			OgdcInt nPointCount = ((OgdcElemLine*)pElement)->m_points.GetSize();
			OgdcInt nSubCount = ((OgdcElemLine*)pElement)->m_polyCounts.GetSize();
			OgdcInt lSize = 4 * 2; 
			lSize += nPointCount * 16;
			lSize += nSubCount * 4;
			
			int i = 0;
			BYTE *pData = new BYTE[lSize];
			BYTE *pDataMirror = pData;
			//��һ��int�������ĸ���
			memcpy(pDataMirror,&nPointCount, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			//��һ��int�������Ӷ���ĸ���
 	    	memcpy(pDataMirror,&nSubCount, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			for(i = 0; i < nSubCount; i++)
			{
				memcpy(pDataMirror, &(((OgdcElemLine*)pElement)->m_polyCounts[i]), 
					sizeof(OgdcInt));
				pDataMirror += sizeof(OgdcInt);
			}
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(pDataMirror, &(((OgdcElemLine*)pElement)->m_points[i].x), 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(pDataMirror, &(((OgdcElemLine*)pElement)->m_points[i].y), 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}

			//��pdataһ���ֽ�һ���ֽڵ�װ��CBYteArray�����У�����ole��������
		
			arr.SetSize(lSize);
			for (i = 0; i < lSize; i++)
			{
				arr.SetAt(i, pData[i]);
			}

			delete pData;
			pData = NULL;
						
		}
		else if (m_pDataset->GetType() == OgdcDataset::Region)
		{
			//ogdc��û��getdata�������������Լ����㼸�ζ������ڴ��еĴ�С�����ҿ������ݽ�pdata
			OgdcInt nPointCount = ((OgdcElemRegion*)pElement)->m_points.GetSize();
			OgdcInt nSubCount = ((OgdcElemRegion*)pElement)->m_polyCounts.GetSize();
			OgdcInt lSize = 4 * 2; 
			lSize += nPointCount * 16;
			lSize += nSubCount * 4;
			
			OgdcInt i = 0;
			BYTE *pData = new BYTE[lSize];
			BYTE *pDataMirror = pData;
			//��һ��int�������ĸ���
			memcpy(pDataMirror, &nPointCount, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			//��һ��int�������Ӷ���ĸ���
			memcpy(pDataMirror,&nSubCount,sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			for (i = 0; i < nSubCount; i++)
			{
				memcpy(pDataMirror, &((OgdcElemRegion*)pElement)->m_polyCounts[i], 
					sizeof(OgdcInt));
				pDataMirror += sizeof(OgdcInt);
			}
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(pDataMirror, &((OgdcElemRegion*)pElement)->m_points[i].x, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(pDataMirror, &((OgdcElemRegion*)pElement)->m_points[i].y, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}
			//��pdataһ���ֽ�һ���ֽڵ�װ��CBYteArray�����У�����ole��������
			
			arr.SetSize(lSize);
			for (i = 0; i < lSize; i++)
			{
				arr.SetAt(i, pData[i]);
			}

			delete pData;
			pData = NULL;
			
		}
		COleVariant varOle(arr);

		//�����ǻ�ȡelement���ݵĲ��֣���Ҫд��һ�������У��ȴ��Ľ�
		try
		{
			m_pDaoRecordset->SetFieldValue (OG_GEOMETRY, varOle);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_W, bound.left);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_N, bound.top);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_E, bound.right);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_S, bound.bottom);
			m_pDaoRecordset->Update();
		}
		catch (CDaoException* e)
		{
			e->Delete();
			//û�гɹ���Cancel
			m_pDaoRecordset->CancelUpdate();
			return -1;
		}
	
	/*	m_recordset->SetFieldValue (LF_GRANULE, dGranule);*/	
	}
	

	//�޸�EditMode
	m_pElement = pElement;
	
	m_bEdited = TRUE;
	m_nEditMode = EditSetGeometry;
	m_pDataset->SetModifiedFlag(TRUE);
	return Update();	
}

OgdcInt OgdcRecordsetMdb::AddNew( OgdcElement *pElement, OgdcBool bReturnID/*=FALSE*/ )
{
	if(pElement == NULL)
	{
		return -1;
	}

	OgdcString strSQL;
	strSQL.Format(OGDCPCTSTR("SELECT MAX(%s) FROM [%s]"),OG_OBJ_ID, 
		OGDCPCTSTR(m_strTableName));

	CDaoRecordset recordset1(&(m_pDataset->m_pDataSource->m_daoDatabase));
	recordset1.Open (dbOpenDynaset,strSQL);
	COleVariant varlue;
	recordset1.GetFieldValue ((short)0,varlue);
	OgdcLong nID = varlue.lVal + 1;
	pElement->m_nID=OgdcInt(nID);
	if (nID == 1)
	{
		m_bFirstAddNew = TRUE;
	}
	recordset1.Close();
	try
	{	
		m_pDaoRecordset->AddNew();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		m_pDaoRecordset->Close();
		return -1;
	}

	//******************************************
	//�����Ա�Ĵ���(�����ռ�����
	if (pElement->GetType() == 0)
	{
		try
		{
			m_pDaoRecordset->SetFieldValue(OG_OBJ_ID, long(nID));				
		}
		catch (CDaoException* e)
		{
			e->Delete();
			m_pDaoRecordset->CancelUpdate();
			return -1;
		}
		m_bEdited = TRUE;
		m_nEditMode = dbEditAdd;
		m_pDataset->SetModifiedFlag(TRUE);
		m_pElement = pElement;
		Update();
		return OgdcInt(nID);
	}
	//}�����Ա�Ĵ���(�����ռ�����
	//******************************************

	//****************************

	//{{�ռ����ݱ�Ĵ���������ת���ɶ�����װ�����ݿ�
	if (m_pDataset->GetType() == OgdcDataset::Point)
	{
		try
		{
			m_pDaoRecordset->SetFieldValue (OG_OBJ_ID,long(nID));
			m_pDaoRecordset->SetFieldValue (OG_X,((OgdcElemPoint *)pElement)->m_point.x);
			m_pDaoRecordset->SetFieldValue (OG_Y,((OgdcElemPoint *)pElement)->m_point.y);
			m_pDaoRecordset->Update();
	//		m_recordset->Close();
//			table.Close();
		}
		catch (CDaoException* e)
		{
			e->Delete();
			//û�гɹ���Cancel
			m_pDaoRecordset->CancelUpdate();
			return -1;
		}

	}
	else
	{
		
		OgdcRect2D bound = pElement->GetBounds();
		double dGranule = (bound.Width() > bound.Height() ? bound.Width() : bound.Height());
		CByteArray arr;
		BYTE *pDataMirror = NULL;
		if (m_pDataset->GetType() == OgdcDataset::Text)
		{
			OgdcInt i = 0;
			//��¼��ĸ���
			OgdcInt nPointCount = ((OgdcElemText*)pElement)->m_points.GetSize();
			//��¼���ı��ĸ�����Angles�ĸ��������Ӷ������
			OgdcInt nStrCount = ((OgdcElemText*)pElement)->m_strTexts.GetSize();
			//��¼ÿ�����ı��ĳ���
			//OgdcInt nStrLength[nStrCount];
			OgdcArray<OgdcInt> nStrLength;
			nStrLength.SetSize(nStrCount);
			//��¼�ı�����У��������ֵĳ���
			OgdcInt nStrFaceNameLength = ((OgdcElemText*)pElement)->m_textStyle .m_strFaceName.GetLength();
			//��ȡÿ�����ı��ĳ���
			for (i = 0; i < nStrCount; i++)
			{
				nStrLength[i]=((OgdcElemText*)pElement)->m_strTexts.GetAt(i).GetLength();
			}
			//����Count���ֽ���
			OgdcInt lSize = 4 + 4 + 4 * nStrCount + 4;
			//���е���ֽ���
			lSize += nPointCount * 16;
			//�������ı��ĳ���
			for (i = 0; i < nStrCount; i++)
			{
				lSize += nStrLength[i];
			}
			//����angele���ֽ���
			lSize += nPointCount*8;
			//�ı�����У��������ֵ��ֽ���
			lSize += nStrFaceNameLength;
			//�ı�����У������������ֽ���
			lSize += 57;
			
			arr.SetSize(lSize);
			BYTE *pDataMirror = arr.GetData();
			//{{�����ֱ�־
			memcpy(pDataMirror, &nPointCount, 4);
			pDataMirror += 4;
			memcpy(pDataMirror, &nStrCount, 4);
			pDataMirror += 4;
			for (i = 0; i < nStrCount; i++)
			{
				OgdcInt *pOgdcInt = new OgdcInt;
				*pOgdcInt = nStrLength.GetAt(i);
				memcpy(pDataMirror, pOgdcInt, 4);
				pDataMirror += 4;
				delete pOgdcInt;
				pOgdcInt = NULL;
			}
			memcpy(pDataMirror, &nStrFaceNameLength, 4);
			pDataMirror += 4;
			//}}�����ֱ�־

			//���²��Ǵ��ı����Ĳ���
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_points[i].x, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_points[i].y, 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}
			for (i = 0; i < nStrCount; i++)
			{
				for (OgdcInt j = 0; j < nStrLength.GetAt(i); j++)
				{
					OgdcChar ch = ((OgdcElemText*)pElement)->m_strTexts[i].GetAt(j);
					memcpy(pDataMirror, &ch, 1);
					pDataMirror += 1;
				}
			}
			for (i = 0; i < nStrCount; i++)
			{
				OgdcDouble *pDouble=new OgdcDouble;
				*pDouble=((OgdcElemText*)pElement)->m_angles.GetAt(i);
				memcpy(pDataMirror, pDouble, sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				delete pDouble;
				pDouble = NULL;
			}
			////////////////
			//1
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_clrFore, 4);
			pDataMirror += 4;
			//2
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_clrBack, 4);
			pDataMirror += 4;
			//3
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dAngle, 8);
			pDataMirror += 8;
			//4
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dItalicAngle, 8);
			pDataMirror += 8;
			//5
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dWidth, 8);
			pDataMirror += 8;
			//6
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_dHeight, 8);
			pDataMirror += 8;
			//7
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_nWeight, 4);
			pDataMirror += 4;
			//8
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_nStyle, 4);
			pDataMirror += 4;
			//9
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_nAlign, 1);
			pDataMirror += 1;
			//10
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bBold, 1);
			pDataMirror += 1;
			//11
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bUnderline, 1);
			pDataMirror += 1;
			//12
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bItalic, 1);
			pDataMirror += 1;
			//13
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bStrikeOut, 1);
			pDataMirror += 1;
			//14
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bFixedSize, 1);
			pDataMirror += 1;
			//15
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bBackOpaque, 1);
			pDataMirror += 1;
			//16
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bHalo, 1);
			pDataMirror += 1;
			//17
			memcpy(pDataMirror, &((OgdcElemText*)pElement)->m_textStyle.m_bShadow, 1);
			pDataMirror += 1;
			//18
			for (i = 0; i < nStrFaceNameLength; i++)
			{
				OgdcChar ch = ((OgdcElemText*)pElement)->m_textStyle.m_strFaceName.GetAt(i);
				memcpy(pDataMirror, &ch, 1);
				pDataMirror += 1;
			}
			///////////////////////

			nStrLength.RemoveAll();
		}
		else if (m_pDataset->GetType() == OgdcDataset::Line)
		{
			//ogdc��û��getdata�������������Լ����㼸�ζ������ڴ��еĴ�С�����ҿ������ݽ�pdata
			OgdcInt nPointCount = ((OgdcElemLine*)pElement)->m_points.GetSize();
			OgdcInt nSubCount = ((OgdcElemLine*)pElement)->m_polyCounts.GetSize();
			OgdcInt lSize = 4*2; 
			lSize += nPointCount * 16;
			lSize += nSubCount * 4;
			
			OgdcInt i=0;
			arr.SetSize(lSize);
			BYTE *pDataMirror = arr.GetData();
			//��һ��int�������ĸ���
			memcpy(pDataMirror,&nPointCount,sizeof(OgdcInt));
			pDataMirror+=sizeof(OgdcInt);
			//��һ��int�������Ӷ���ĸ���
 	    	memcpy(pDataMirror,&nSubCount,sizeof(OgdcInt));
			pDataMirror+=sizeof(OgdcInt);
			for (i = 0; i < nSubCount; i++)
			{
				memcpy(pDataMirror, &(((OgdcElemLine*)pElement)->m_polyCounts[i]), 
					sizeof(OgdcInt));
				pDataMirror += sizeof(OgdcInt);
			}
			for (i = 0; i < nPointCount; i++)
			{
				memcpy(pDataMirror, &(((OgdcElemLine*)pElement)->m_points[i].x), 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
				memcpy(pDataMirror, &(((OgdcElemLine*)pElement)->m_points[i].y), 
					sizeof(OgdcDouble));
				pDataMirror += sizeof(OgdcDouble);
			}
		}
		else if (m_pDataset->GetType() == OgdcDataset::Region)
		{
			//ogdc��û��getdata�������������Լ����㼸�ζ������ڴ��еĴ�С�����ҿ������ݽ�pdata
			OgdcInt nPointCount = ((OgdcElemRegion*)pElement)->m_points.GetSize();
			OgdcInt nSubCount = ((OgdcElemRegion*)pElement)->m_polyCounts.GetSize();
			OgdcInt lSize = 4 * 2; 
			lSize += nPointCount * 16;
			lSize += nSubCount * 4;
			
			OgdcInt i = 0;
			arr.SetSize(lSize);
			BYTE *pDataMirror = arr.GetData();

			//��һ��int�������ĸ���
			memcpy(pDataMirror, &nPointCount, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			//��һ��int�������Ӷ���ĸ���
			memcpy(pDataMirror, &nSubCount, sizeof(OgdcInt));
			pDataMirror += sizeof(OgdcInt);
			for(i=0; i<nSubCount; i++)
			{
				memcpy(pDataMirror, &((OgdcElemRegion*)pElement)->m_polyCounts[i], 
					sizeof(OgdcInt));

				pDataMirror += sizeof(OgdcInt);
			}
			for(i = 0; i<nPointCount; i++)
			{
				memcpy(pDataMirror, &((OgdcElemRegion*)pElement)->m_points[i].x,
					sizeof(OgdcDouble));

				pDataMirror += sizeof(OgdcDouble);

				memcpy(pDataMirror, &((OgdcElemRegion*)pElement)->m_points[i].y, 
					sizeof(OgdcDouble));

				pDataMirror += sizeof(OgdcDouble);
			}	
		}
		COleVariant varValue = arr;
		try
		{
			m_pDaoRecordset->SetFieldValue (OG_OBJ_ID, long(nID));
			m_pDaoRecordset->SetFieldValue (OG_GEOMETRY, varValue);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_W, bound.left);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_N, bound.top);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_E, bound.right);
			m_pDaoRecordset->SetFieldValue (OG_SDRI_S, bound.bottom);
			m_pDaoRecordset->Update();
			pDataMirror = NULL;
		}
		catch (CDaoException* e)
		{
			e->Delete();
			//û�гɹ���Cancel
			m_pDaoRecordset->CancelUpdate();
			pDataMirror = NULL;
			return -1;
		}
	}

	//�޸�EditMode

	m_bEdited = TRUE;
	m_nEditMode = dbEditAdd;
	m_pDataset->SetModifiedFlag(TRUE);
	m_pElement = pElement;
	Update();
	m_nID = OgdcInt(nID);

	// ֱ��Seek������
	SeekID(nID);
// 	m_pDaoRecordset->Close();
// 	strSQL.Format(OGDCPCTSTR("SELECT * FROM [%s] WHERE OGID = %d"),
// 		OGDCPCTSTR(m_strTableName), nID);
// 	m_pDaoRecordset->Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
	return OgdcInt(nID);
}

OgdcFeature* OgdcRecordsetMdb::GetFeature()
{
	if (!((OgdcDatasetVectorMdb*)m_pDataset)->IsOpen())
	{
		return FALSE;
	}
	
	//��ǰ��¼��Ϊ�գ�ֱ�ӷ���FALSE
	if (IsEmpty())
	{
		return FALSE;
	}
	if (IsBOF() || IsEOF())
	{
		return FALSE;
	}
	
	OgdcElement *pElement = NULL;
	if (!GetElement(pElement) && m_pDataset->m_info.m_nType == OgdcDataset::Tabular)
	{
		delete pElement;
		pElement = NULL;
		return NULL;
	}
	
	OgdcFeatureMdb *pFeature = new OgdcFeatureMdb();
	pFeature->SetElement(pElement);
	pFeature->SetID(GetID());
	pFeature->SetCharset(m_pDataset->GetCharset());

	OgdcFieldInfos filedInfos;
	OgdcFieldInfo info;
	CDaoFieldInfo daoFieldInfo;
	COleVariant var;	
	OgdcVariant varValue;
	pFeature->m_fieldDefines.SetSize(m_pDaoRecordset->GetFieldCount());
	pFeature->m_fieldValues.SetSize(m_pDaoRecordset->GetFieldCount());
	for (OgdcInt i = 0; i < m_pDaoRecordset->GetFieldCount(); i++)
	{
		m_pDaoRecordset->GetFieldInfo(i, daoFieldInfo);
		OgdcHelperMdb::CDaoFieldInfo2OgdcFieldInfo(daoFieldInfo, info);
		pFeature->m_fieldDefines[i].m_strName = info.m_strName;
		pFeature->m_fieldDefines[i].m_nType = info.m_nType;
		pFeature->m_fieldDefines[i].m_nSize = info.m_nSize;
		filedInfos.Add(info);
		m_pDaoRecordset->GetFieldValue(i, var);
		OgdcHelperMdb::COleVariant2OgdcVariant(var, varValue);
		pFeature->SetValue(i, varValue);
	}
	//����forѭ���ﶼ�Ѿ���ֵ�ˣ������ٵ�OgdcFeature�ĺ�����
//	pFeature->SetFieldInfos(filedInfos);

	return pFeature;
}

OgdcBool OgdcRecordsetMdb::UpdateFeature( const OgdcFeature* pFeature )
{
	if (pFeature == NULL || m_nEditMode != EditNone)
	{
		return FALSE;	
	}

	if ( !Edit() )
	{
		return FALSE;
	}

	OgdcElement* pElement = ((OgdcFeatureMdb*)pFeature)->GetElement();
	if (pElement->GetType() != OgdcDataset::Tabular && pElement == NULL)
	{
		return FALSE;
	}
	//���ü��ζ���
	SetElement(pElement);

	OgdcVariant val;
	OgdcString strField;
	OgdcFieldInfo fieldInfo;
	for (OgdcInt i = 0; i < pFeature->m_fieldDefines.GetSize(); i++)
	{
		//��������
		strField = pFeature->m_fieldDefines.GetAt(i).m_strName;
		if (OgdcHelperMdb::IsSystemField(strField))
		{
			continue;
		}
		
		if (!((OgdcFeatureMdb*)pFeature)->GetValue(strField, val))
		{
			continue;
		}
		SetFieldValue(strField, val);
		val.Clear();
	}
	m_pElement = pElement;
	return Update();
}

OgdcBool OgdcRecordsetMdb::AddFeature( const OgdcFeature* pFeature )
{
	if (pFeature == NULL || m_nEditMode != EditNone)
	{
		return FALSE;	
	}
	OgdcElement *pElement = ((OgdcFeature*)pFeature)->GetElement();
	if (m_pDataset->GetType() == OgdcDataset::Tabular && pElement == NULL)
	{
		return FALSE;
	}

	m_nID = AddNew(pElement);
	
	OgdcVariant val;
	OgdcString strField;
	OgdcFieldInfo fieldInfo;
	COleVariant varValue;
	for (OgdcInt i = 0; i < pFeature->m_fieldDefines.GetSize(); i++)
	{
		//��������
		strField = pFeature->m_fieldDefines.GetAt(i).m_strName;
		if (OgdcHelperMdb::IsSystemField(strField))
		{
			continue;
		}

		if (strField.Left(2).CompareNoCase(OGDCPCTSTR("Sm")) == 0) 
		{
			continue;
		}
		
		if (!((OgdcFeatureMdb*)pFeature)->GetValue(strField, val))
		{
			continue;
		}

		SetFieldValue(strField, val);
	}
	
//	return Update();
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::SeekID( OgdcInt nID )
{
	if( !m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	
	//�ƶ�ʱ��ǰ��AddNew��Editȡ��
	
	CancelUpdate();

	OgdcString strFilter;
	strFilter.Format("OGID = %d", nID);
	OgdcBool bFind;
	try			
	{
		//���ƶ�ָ�뵽�׼�¼����������
		m_pDaoRecordset->MoveFirst();
		bFind = m_pDaoRecordset->Find(AFX_DAO_FIRST, strFilter);
		m_nID = nID;
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	
	return bFind;	
}

OgdcInt OgdcRecordsetMdb::Update()
{
	//���û������Addnew��Edit,����FALSE
	if (m_nEditMode == dbEditNone)
	{
		return FALSE;
	}
	try
	{	
		if (m_nEditMode == dbEditAdd)
		{	
			m_nRecordCount ++;		
			m_pDataset->m_nObjectCount += 1;	
		}
		OgdcRect2D rcBounds;
		rcBounds.SetEmpty();

		if (m_pElement != NULL)
		{
			rcBounds = m_pDataset->GetBounds();
			if(rcBounds.IsNull() || m_bFirstAddNew)
			{
				if (m_pDataset->GetType() != OgdcDataset::Point)
				{
					rcBounds = m_pElement->GetBounds();
					//m_bFirstAddNew = FALSE;
				}
				else
				{
					rcBounds.left = ((OgdcElemPoint*)m_pElement)->m_point.x;
					rcBounds.right = ((OgdcElemPoint*)m_pElement)->m_point.x;
					rcBounds.top = ((OgdcElemPoint*)m_pElement)->m_point.y;
					rcBounds.bottom = ((OgdcElemPoint*)m_pElement)->m_point.y;
				}
				m_bFirstAddNew = FALSE;
			}
			else
			{
				if (m_pDataset->GetType() != OgdcDataset::Point)
				{
					rcBounds.Union(m_pElement->GetBounds());
				}
				else
				{
					rcBounds.left = rcBounds.left < ((OgdcElemPoint*)m_pElement)->m_point.x
						? rcBounds.left : ((OgdcElemPoint*)m_pElement)->m_point.x;
					rcBounds.right = rcBounds.right > ((OgdcElemPoint*)m_pElement)->m_point.x
						? rcBounds.right : ((OgdcElemPoint*)m_pElement)->m_point.x;
					rcBounds.top = rcBounds.top > ((OgdcElemPoint*)m_pElement)->m_point.y
						? rcBounds.top : ((OgdcElemPoint*)m_pElement)->m_point.y;
					rcBounds.bottom = rcBounds.bottom < ((OgdcElemPoint*)m_pElement)->m_point.y
						? rcBounds.bottom : ((OgdcElemPoint*)m_pElement)->m_point.y;
				}
			}
			m_pDataset->SetBounds(rcBounds);
			m_pElement = NULL;
		}
		//���������ע���

		OgdcString strSQL;
		strSQL.Format (OGDCPCTSTR("UPDATE OGRegister "
			"SET OGLeft = %f, OGRight = %f, OGTop = %f, OGBottom = %f "
			"WHERE OGDatasetName = '%s'"), rcBounds.left, 
			rcBounds.right, rcBounds.top, rcBounds.bottom, OGDCPCTSTR(m_strTableName)); 
		try
		{
			m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);
			if (m_nEditMode == dbEditAdd)
			{
			
				strSQL.Format(OGDCPCTSTR("UPDATE OGRegister "
					"SET OGRecordCount = OGRecordCount + 1 "
				"WHERE OGDatasetName = '%s'"), OGDCPCTSTR(m_strTableName));

				m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);

			}

			COleDateTime dt = COleDateTime::GetCurrentTime();
			OgdcVariant var = OgdcTime(dt.GetYear(), dt.GetMonth(), 
				dt.GetDay(), dt.GetHour(),dt.GetMinute(),dt.GetSecond());

			strSQL.Format(OGDCPCTSTR("UPDATE OGRegister "
				"SET OGLastUpdate = '%s' WHERE OGDatasetName = '%s'"),
				OGDCPCTSTR(var.ToString()), OGDCPCTSTR(m_strTableName));

			m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);	
		}
		catch (CDaoException* e)
		{
			e->Delete();
			return FALSE;
		}
		
	}
	catch (CDaoException* e)
	{
		CancelUpdate();
		m_nEditMode = dbEditNone;
		m_bEdited = FALSE;
		e->Delete();
		return FALSE;
	}
	m_nEditMode = dbEditNone;
	m_bEdited = FALSE;
	return TRUE;	
}

OgdcBool OgdcRecordsetMdb::CancelUpdate()
{
	if (!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	
	if (m_nEditMode == dbEditNone)
	{
		return TRUE;
	}
	try
	{
		m_nEditMode = dbEditNone;
		m_pDaoRecordset->CancelUpdate();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	m_bEdited = FALSE;
	return TRUE;	
}

OgdcBool OgdcRecordsetMdb::Edit()
{	
	if (!m_pDaoRecordset->IsOpen() || !CanUpdate())
	{
		return FALSE;
	}
	
	if (m_nEditMode != dbEditNone)
	{
		return TRUE;
	}
// 	m_recordset->Close();
// 	CDaoTableDef tableDef(&m_pDataset->m_pDataSource->m_daoDatabase);
// 	tableDef.Open()
	try
	{
		m_pDaoRecordset->Edit();
		m_bEdited = TRUE;
	}
	catch (CDaoException* e)
	{	
		e->Delete();
		return FALSE;
	}	
	//�������Editʧ����Ӧ������edit��־�����������ƶ������
	m_nEditMode = dbEditInProgress;
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::CanUpdate()
{
	if(!m_pDaoRecordset->IsOpen())
	{
		return FALSE;
	}
	else
	{
		return m_pDataset->CanUpdate();
	}
}

OgdcBool OgdcRecordsetMdb::Delete()
{

	if (m_bEdited && (!Update()))
	{
		return FALSE;
	}
	
	if (!CanUpdate())	
	{
		return FALSE;
	}

	try
	{

	//	m_recordset->Delete ();	
		//m_nRecordCount = OgdcRecordsetMdb::GetRecordCount()-1;
		m_nRecordCount -= 1;
		m_pDataset->m_nObjectCount -= 1;
		OgdcString strSQL;
		strSQL.Format(OGDCPCTSTR("UPDATE OGRegister "
			"SET OGRecordCount = OGRecordCount-1 WHERE OGDatasetName = '%s'"),
			OGDCPCTSTR(m_strTableName));
		m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);

		strSQL.Format(OGDCPCTSTR("DELETE FROM [%s] WHERE OGID = %d"),
			OGDCPCTSTR(m_strTableName), GetID());
		//��¼ָ��ָ����һ����¼
		m_pDaoRecordset->MoveNext();
		m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);
		m_pDaoRecordset->Requery();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}
	return TRUE;
}

OgdcBool OgdcRecordsetMdb::DeleteAll()
{
	if (!CanUpdate()) 
	{
		return FALSE;	//���ܱ༭
	}
	
	if (m_nEditMode != dbEditNone) //���ڱ༭
	{
		return FALSE;
	}
	OgdcInt nCount = GetRecordCount();
	OgdcString strSQL;
	if (m_strFilter.IsEmpty())
	{
		strSQL.Format(OGDCPCTSTR("DELETE * FROM [%s] "), OGDCPCTSTR(m_strTableName));
	}
	else
	{
		strSQL.Format(OGDCPCTSTR("DELETE * FROM [%s] WHERE %s"), 
			OGDCPCTSTR(m_strTableName), OGDCPCTSTR(m_strFilter));
	}
	try
	{
		m_pDataset->m_pDataSource->m_daoDatabase.Execute (strSQL);

		m_nRecordCount = 0;
		m_pDataset->m_nObjectCount -= nCount;
		strSQL.Format(OGDCPCTSTR("UPDATE OGRegister "
			"SET OGRecordCount = OGRecordCount - %d "
			"WHERE OGDatasetName = '%s'"), nCount, OGDCPCTSTR(m_strTableName));

		m_pDataset->m_pDataSource->m_daoDatabase.Execute(strSQL);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}

	return TRUE;
}

OgdcDatasetVector* OgdcRecordsetMdb::GetDataset()
{
	return m_pDataset;	
}	


}