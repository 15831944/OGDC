//////////////////////////////////////////////////////////////////////////
//                     ____    ____   ____     ____                    
//   Project          / _  \  / ___) |  _ \   / ___)                   
//                   | | | | | | __  | | \ | | |                       
//                   | |_| | | |_\ | | |_/ | | \___                    
//                    \____/  \____| |____/   \ ___)             
//                                                           
//!  \file OgdcDataSourceMdb.cpp
//!  \brief ����Դ�Ľӿ�ʵ��
//!  \details ����Դ�и��ֲ����Ľӿڵ�ʵ��
//!  \attention 
//!   Copyright (c) 2007-2012 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 1.0(2012)
//////////////////////////////////////////////////////////////////////////

#include "afxdao.h"
#include "OgdcDataSourceMdb.h"
#include "OgdcMacroDefineMdb.h"
#include "OgdcHelperMdb.h"
#include "OgdcDatasetRasterMdb.h"
#include "OgdcDatasetVectorMdb.h"
#include "OgdcFeatureMdb.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace OGDC
{

OgdcDataSourceMdb::OgdcDataSourceMdb()
{
	AfxGetAppModuleState()->m_dwVersion=0x0601;
	m_nVersion = -1;
	m_pDaoWorkspace = NULL;
	m_bModified = FALSE;
	m_bTransStarted = FALSE;
	m_bOpened = FALSE;
 	m_strDescription = "" ;
	m_connection.m_nType = 1001;	
	m_nEngineClass = 2;
	m_strPostfix = "*.mdb";
}

OgdcDataSourceMdb::~OgdcDataSourceMdb()
{
	Close();
	//ɾ��Access�����ռ�
	if(m_pDaoWorkspace != NULL)
	{
		m_pDaoWorkspace->Close();
		delete m_pDaoWorkspace;
		m_pDaoWorkspace = NULL;
 	}
}

OgdcBool OgdcDataSourceMdb::Create()
{
 	if (m_connection.m_strServer.IsEmpty())
 	{
 		return FALSE;
 	}
 	
 	if (m_daoDatabase.IsOpen())
 	{
 		Close();
		return FALSE;
 	}
 	
	// �ж����ݿ��ļ��Ƿ����
 	CFileStatus status;
	status.m_size = 0;
 	CFile::GetStatus(OGDCPCTSTR(m_connection.m_strServer), status);
 	if (status.m_size > 0)
 	{
		//���Ŀ�����ݿ��Ѿ�����,��ɾ�����ݿ�
		if (!DropDataSource())
		{
			return	FALSE;
		}		
 	}

 	//����Access�Ĺ����ռ�
 	OgdcLong dwName = GetTickCount();
 	OgdcString strName;
 	strName.Format("%u",dwName);
 	m_pDaoWorkspace = new CDaoWorkspace;
  	try
  	{
  		m_pDaoWorkspace->Create(strName, OGDCPCTSTR("admin"),
			OGDCPCTSTR(m_connection.m_strPassword));
 		m_pDaoWorkspace->Append();
  	}
  	catch (CDaoException* e)
  	{
  		delete m_pDaoWorkspace;
  		m_pDaoWorkspace = NULL;
		e->Delete();
  		return FALSE;
  	}
  	m_daoDatabase.m_pWorkspace = m_pDaoWorkspace;
	try
	{
		 
 		//�����Ҫ���������ݿ��������룬����м���
  		if (m_connection.m_bEncrypt)
  		{
  			m_daoDatabase.Create(OGDCPCTSTR(m_connection.m_strServer),
				dbLangGeneral, dbEncrypt);
  			COleVariant varOld(OGDCPCTSTR(""), VT_BSTRT);
  			COleVariant varNew(OGDCPCTSTR(m_connection.m_strPassword), VT_BSTRT);
  			DAO_CHECK(m_daoDatabase.m_pDAODatabase->NewPassword(
				varOld.bstrVal, varNew.bstrVal));
  		}
  		else
  		{		
			m_daoDatabase.Create(OGDCPCTSTR(m_connection.m_strServer));	
  		}
	}
	catch (CDaoException* e)
	{
		e->Delete();
		m_daoDatabase.Close();
		return FALSE;
	}
	
	//{{����ϵͳ�� 
	CDaoTableDef pDaoTableDef(&m_daoDatabase);
	OgdcFieldInfos fieldInfos;
	fieldInfos.RemoveAll ();
	//��Ҫ�������ֶμ���OgdcFieldInfos��һ������
 	fieldInfos.AddField (OGRF_ID, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_DATASET_NAME, OgdcFieldInfo::Text, 64, 0, TRUE, FALSE);
 	fieldInfos.AddField (OGRF_DATASET_TYPE, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_LEFT, OgdcFieldInfo::Double,
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_RIGHT, OgdcFieldInfo::Double,
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_TOP, OgdcFieldInfo::Double, 
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_BOTTOM, OgdcFieldInfo::Double, 
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_RECORDCOUNT, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE, OGDCPCTSTR("0"));
  	fieldInfos.AddField (OGRF_LASTUPDATE, OgdcFieldInfo::Date, 
		sizeof(OgdcFieldInfo::Date), 0, FALSE, FALSE);

 	//��ȡ�������ֶεĸ���
	OgdcInt nFields = fieldInfos.GetSize();
	try
	{
		//������¼ʸ�����ݼ��ı�
		pDaoTableDef.Create(OG_REGISTER_TABLE);
		for (OgdcInt i = 0; i < nFields; i++)
		{
			CDaoFieldInfo info;
 			/* OGDC2Dao()��ogdcHelperMdb�еķ�����Ŀ����
 			��OgdcFieldInfos���͵ļ��Ϻ�CDaoFieldInfo�ṹ������ݽ���ת�� */
			OgdcHelperMdb::OgdcFieldInfo2CDaoFieldInfo(fieldInfos.GetAt(i),info);
			pDaoTableDef.CreateField(info );
		}
		pDaoTableDef.Append();
		pDaoTableDef.Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		pDaoTableDef.Close();
		m_daoDatabase.Close();
		return FALSE;
	}

 	//���µĶ����Ǽ�¼դ������ݼ�����Ϣ���������Ϣ�Ǽ�¼ʸ�����ݼ�����Ϣ��
 	// OGImgRefister

 	fieldInfos.RemoveAll ();
	fieldInfos.AddField (OGRF_ID, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGRF_DATASET_NAME, OgdcFieldInfo::Text, 64, 0, TRUE, FALSE);
 	fieldInfos.AddField (OGRF_DATASET_TYPE, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32),0,FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_PIXELFORMAT, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGIRF_WIDTH, OgdcFieldInfo::INT32, 
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_HEIGHT, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_EBLOCKSIZE, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_PYRAMID, OgdcFieldInfo::Text, 64, 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_PYRAMIDLEVEL, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGIRF_BLOCKSIZES, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);
	fieldInfos.AddField (OGIRF_MINZ, OgdcFieldInfo::Double,
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE, OGDCPCTSTR("0"));
	fieldInfos.AddField (OGIRF_MAXZ, OgdcFieldInfo::Double, 
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE, OGDCPCTSTR("0"));
 	fieldInfos.AddField (OGIRF_PALETTE, OgdcFieldInfo::Binary, 0, 0, FALSE, FALSE);
	fieldInfos.AddField (OGIRF_LEFT, OgdcFieldInfo::Double,
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_TOP, OgdcFieldInfo::Double, 
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_RIGHT, OgdcFieldInfo::Double,
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE);
 	fieldInfos.AddField (OGIRF_BOTTOM, OgdcFieldInfo::Double,
		sizeof(OgdcFieldInfo::Double), 0, FALSE, FALSE);

	nFields = fieldInfos.GetSize();
	try
	{
		pDaoTableDef.Create(OG_IMGREGISTER_TABLE);
		for (OgdcInt i = 0; i < nFields; i++)
		{ 
			CDaoFieldInfo info;
			OgdcHelperMdb::OgdcFieldInfo2CDaoFieldInfo(fieldInfos.GetAt(i), info);
			pDaoTableDef.CreateField(info);
		}	
		pDaoTableDef.Append();	
		pDaoTableDef.Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		pDaoTableDef.Close();
		m_daoDatabase.Close();
		return FALSE;
	}

	fieldInfos.RemoveAll ();
	fieldInfos.AddField (OG_DF_FLAG, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);
	fieldInfos.AddField (OG_DF_VERSION, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);
	fieldInfos.AddField (OG_DF_COORDSYS, OgdcFieldInfo::INT32,
		sizeof(OgdcFieldInfo::INT32), 0, FALSE, FALSE);

	nFields = fieldInfos.GetSize();

	try
	{
		//��������Դ��Ϣ��
		pDaoTableDef.Create(OG_DATASOURCE_INFO);
		for (OgdcInt i = 0; i < nFields; i++)
		{ 
			CDaoFieldInfo info;
			OgdcHelperMdb::OgdcFieldInfo2CDaoFieldInfo(fieldInfos.GetAt(i), info);
			pDaoTableDef.CreateField(info);			
		}

		pDaoTableDef.Append();	
		pDaoTableDef.Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		pDaoTableDef.Close();
		m_daoDatabase.Close();
		return FALSE;
	}
	m_bOpened = TRUE;
	return TRUE;
}

OgdcBool OgdcDataSourceMdb::Open()
{
	//���Ѿ��򿪣�����
	if (IsOpen())	
	{
		return TRUE;
	}
	
	SetAlias(m_connection.m_strAlias);
	if (m_connection.m_strServer.IsEmpty())
	{	
		m_bOpened = FALSE;
		return FALSE;
	}
	else
	{
		try
		{
			//������벻ΪΪ��
			if (!OgdcString(m_connection.m_strPassword).IsEmpty())
			{
				OgdcString pwd = OGDCPCTSTR(";PWD=") + m_connection.m_strPassword;
				m_daoDatabase.Open(m_connection.m_strServer, TRUE, FALSE, pwd);
			}
			else
			{	
				m_daoDatabase.Open(m_connection.m_strServer, TRUE, FALSE);
 			}
		}
		catch (CDaoException* e)
		{
			e->Delete();
			return	FALSE;	
		}
	}

	//��ȡ����Դ����Ϣ��������ϵ��Ϣ��ͶӰ��Ϣ��
	if (!ReadInfo())
	{
		return FALSE;
	}

	//�����ݼ�����OgdcDatasetָ������
 	OgdcDatasetRasterMdb* pRaster;
	OgdcDatasetVectorMdb* pVecter;
	CDaoTableDef tableDef(&m_daoDatabase);
	try
	{
		tableDef.Open("OGRegister");
 		COleVariant varValue;
		CDaoRecordset recordset;
		recordset.Open(&tableDef);
		OgdcInt i=0;
		for (i = 0; i < recordset.GetRecordCount(); i++ )
		{
			pVecter = new OgdcDatasetVectorMdb(this);
			recordset.GetFieldValue(OGRF_ID, varValue);
			pVecter->m_nID = varValue.lVal;
 			recordset.GetFieldValue(OGRF_DATASET_NAME, varValue);
 			pVecter->m_info.m_strName = OgdcString((LPCTSTR)varValue.bstrVal);
			recordset.GetFieldValue(OGRF_DATASET_TYPE, varValue);
			pVecter->m_info.m_nType = (OgdcDataset::Type)varValue.lVal;
			recordset.GetFieldValue(OGRF_LEFT, varValue);
			pVecter->m_info.m_rcBounds.left = varValue.dblVal;
			recordset.GetFieldValue(OGRF_RIGHT, varValue);
			pVecter->m_info.m_rcBounds.right = varValue.dblVal;
			recordset.GetFieldValue(OGRF_TOP, varValue);
			pVecter->m_info.m_rcBounds.top = varValue.dblVal;
			recordset.GetFieldValue(OGRF_BOTTOM, varValue);
			pVecter->m_info.m_rcBounds.bottom = varValue.dblVal;
			recordset.GetFieldValue(OGRF_RECORDCOUNT, varValue);
			pVecter->m_nObjectCount = varValue.lVal;
 			m_datasets.Add(pVecter);
			recordset.MoveNext();
		}
		recordset.Close();
		tableDef.Close();

		tableDef.Open("OGImgRegister");
		recordset.Open(&tableDef);
		for (i = 0; i < recordset.GetRecordCount(); i++ )
		{
			pRaster = new OgdcDatasetRasterMdb(this);
			recordset.GetFieldValue(OGRF_ID,varValue);
			pRaster->m_nID = varValue.lVal;
			recordset.GetFieldValue(OGRF_DATASET_NAME, varValue);
			//COleVariant�Ķ���ת����OgdcString����
			pRaster->m_info.m_strName = OgdcString((LPCTSTR)varValue.bstrVal);
			recordset.GetFieldValue(OGRF_DATASET_TYPE, varValue);
			pRaster->m_info.m_nType = (OgdcDataset::Type)varValue.lVal;
			recordset.GetFieldValue(OGIRF_LEFT, varValue);
			pRaster->m_info.m_rcBounds.left = varValue.dblVal;
			recordset.GetFieldValue(OGIRF_RIGHT, varValue);
			pRaster->m_info.m_rcBounds.right = varValue.dblVal;
			recordset.GetFieldValue(OGIRF_TOP, varValue);
			pRaster->m_info.m_rcBounds.top = varValue.dblVal;
			recordset.GetFieldValue(OGIRF_BOTTOM, varValue);
			pRaster->m_info.m_rcBounds.bottom = varValue.dblVal;
			recordset.GetFieldValue(OGIRF_WIDTH, varValue);
			pRaster->m_info.m_nWidth = varValue.lVal;
			recordset.GetFieldValue(OGIRF_HEIGHT, varValue);
			pRaster->m_info.m_nHeight = varValue.lVal;
			recordset.GetFieldValue(OGIRF_PIXELFORMAT, varValue);
			pRaster->m_info.m_nWidthBytes = (pRaster->m_info.m_nWidth 
				* OgdcInt(varValue.lVal) + 31) / 32 * 4;
			pRaster->m_info.m_nPixelFormat = (PixelFormat)varValue.lVal;
			recordset.GetFieldValue(OGIRF_EBLOCKSIZE, varValue);
			pRaster->m_info.m_nColBlocks = (OgdcInt)ceil(double(
				pRaster->m_info.m_nWidth) / double(varValue.lVal));
			pRaster->m_info.m_nRowBlocks = (OgdcInt)ceil(double(
				pRaster->m_info.m_nHeight) / double(varValue.lVal));
			pRaster->m_info.m_nBlockSize = (OgdcDatasetRasterInfo::IBSizeOption)varValue.lVal;
			recordset.GetFieldValue(OGIRF_MINZ, varValue);
			pRaster->m_info.m_dMinZ = varValue.dblVal;
			recordset.GetFieldValue(OGIRF_MAXZ, varValue);
			pRaster->m_info.m_dMaxZ = varValue.dblVal;
			
			recordset.GetFieldValue(OGIRF_PYRAMIDLEVEL, varValue);	
			if (OgdcInt(varValue.lVal) != 0)
			{
				OgdcInt nLevel = varValue.lVal;
				recordset.GetFieldValue(OGIRF_PYRAMID, varValue);
				OgdcString strName = OgdcString((LPCTSTR)varValue.bstrVal);
				OgdcDatasetRasterMdb* pTempRaster = NULL;
				pTempRaster = ((OgdcDatasetRasterMdb*)GetDataset(strName));
				if (pTempRaster != NULL)
				{
					pTempRaster->m_pyramidDatasets.Add(pRaster);
				}
				recordset.MoveNext();
				continue ;
			}
			
			m_datasets.Add(pRaster);
			recordset.MoveNext();
		}
		recordset.Close();
		tableDef.Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		tableDef.Close();
		m_daoDatabase.Close();
		return FALSE;
	}

	pRaster = NULL;
	pVecter = NULL;
	m_bOpened = TRUE;
	return TRUE;
}

void OgdcDataSourceMdb::Close()
{
	if (!IsOpen())
	{
//		AfxDaoTerm();
		return;
	}
	if (m_bModified)
	{
		SaveInfo();
	}

	//�ر����д򿪵�Dataset
	OgdcDataset * pDataset = NULL;
	OgdcInt nSize  =  m_datasets.GetSize();
	if (nSize>0)
	{
		for(OgdcInt i=0; i<nSize; i++)
		{
			pDataset  =  m_datasets.GetAt(i);
			pDataset->Close();
			delete pDataset;
			pDataset = NULL;
		}
		m_datasets.RemoveAll();
	}
	m_daoDatabase.Close();

	//ɾ��Access�����ռ�
 	if(m_pDaoWorkspace != NULL)
 	{
 		m_pDaoWorkspace->Close();
 		delete m_pDaoWorkspace;
 		m_pDaoWorkspace = NULL;
 	}	
//	AfxDaoTerm();
	m_bOpened = FALSE;
}

OgdcBool OgdcDataSourceMdb::IsOpen() const
{
	return m_bOpened;
}

OgdcInt OgdcDataSourceMdb::GetDatasetCount() const
{
	return m_datasets.GetSize();
}

OgdcDataset* OgdcDataSourceMdb::GetDataset( OgdcInt nIndex ) const
{
	return m_datasets.GetAt(nIndex);
}

OgdcDataset* OgdcDataSourceMdb::GetDataset( const OgdcString& strDatasetName ) const
{
	OgdcInt nDatasetCount = m_datasets.GetSize();
	for (OgdcInt i = 0; i < nDatasetCount; i++)
	{
		if (m_datasets.GetAt(i)->GetName() == strDatasetName)
		{
			return m_datasets.GetAt(i);
		}
	}

	return	NULL;
}

OgdcBool OgdcDataSourceMdb::DeleteDataset( const OgdcString& strDatasetName )
{
	if (!IsOpen())
	{
		return FALSE;
	}

	OgdcString strSQL;
	strSQL.Format(OGDCPCTSTR("SELECT OGDatasetName FROM OGRegister "
		"WHERE OGDatasetName = '%s'"), strDatasetName.Cstr());
	CDaoRecordset vectorRecord(&m_daoDatabase);

	try
	{
		vectorRecord.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		vectorRecord.Close();
		return FALSE;
	}
	OgdcInt nDatasetCount = m_datasets.GetSize();
	if (!vectorRecord.IsEOF())  //���ݼ�����������
	{
		try
	  	{	
			//�ȹر����ݼ�
			for (OgdcInt i = 0; i < nDatasetCount; i++)
			{
				if (strDatasetName == m_datasets.ElementAt(i)->GetName())
				{
					if (m_datasets.ElementAt(i)->IsOpen())
					{
						m_datasets.ElementAt(i)->Close();
					}
					delete m_datasets.ElementAt(i);
					m_datasets.ElementAt(i) = NULL;
					m_datasets.RemoveAt(i);
					break;
				}
			}

	  		strSQL.Format (OGDCPCTSTR("DELETE FROM OGRegister "
				"WHERE OGDatasetName = '%s'"), strDatasetName.Cstr());
	  		m_daoDatabase.Execute(strSQL);
			m_daoDatabase.DeleteTableDef(strDatasetName);
	  	}
	  	catch (CDaoException* e)
	  	{
	  		e->Delete();
			vectorRecord.Close();
			m_daoDatabase.Close();
			return FALSE;
	  	}

		vectorRecord.Close();
	}
	else
	{
		try
		{
			//�ȹر����ݼ�
			for (OgdcInt i = 0; i < nDatasetCount; i++)
			{
				if (strDatasetName == m_datasets.ElementAt(i)->GetName())
				{
					if (m_datasets.ElementAt(i)->IsOpen())
					{
						m_datasets.ElementAt(i)->Close();
					}
					delete m_datasets.ElementAt(i);
					m_datasets.ElementAt(i) = NULL;
					m_datasets.RemoveAt(i);
					break;
				}
			}

		 	strSQL.Format(OGDCPCTSTR("DELETE FROM OGImgRegister "
				"WHERE OGDatasetName LIKE '%s'"), strDatasetName.Cstr());
		 	m_daoDatabase.Execute(strSQL);
			m_daoDatabase.DeleteTableDef(strDatasetName);
		}
		catch (CDaoException* e)
		{
			m_daoDatabase.Close();
			e->Delete();
		}

		//ɾ��������  
		strSQL.Format(OGDCPCTSTR("SELECT OGDatasetName FROM OGImgRegister "
			"WHERE OGPyramid LIKE '%s'"), strDatasetName.Cstr());
		CDaoRecordset rasterRecord(&m_daoDatabase);
		try
		{
			rasterRecord.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
		}
		catch (CDaoException* e)
		{
			e->Delete();
			rasterRecord.Close();
			return FALSE;
		}
		
		COleVariant varValue;
		OgdcString strPyramidName;
		while (!rasterRecord.IsEOF())  
		{
			try
			{

				rasterRecord.GetFieldValue((short)0, varValue);
				strPyramidName = OgdcString((LPCTSTR)varValue.bstrVal);
				m_daoDatabase.DeleteTableDef(strPyramidName);
				strSQL.Format (OGDCPCTSTR("DELETE FROM OGImgRegister "
					"WHERE OGDatasetName LIKE '%s'"), strPyramidName.Cstr());
				m_daoDatabase.Execute (strSQL);
				rasterRecord.MoveNext();
			}
			catch (CDaoException* e)
			{
				e->Delete();
				rasterRecord.MoveNext();
			}
			
		}
		rasterRecord.Close();
	}

	return TRUE;
}

OgdcDatasetVector* OgdcDataSourceMdb::CreateDatasetVector( const OgdcDatasetVectorInfo& vInfo )
{
	//������ݼ��Ƿ�Ϸ�
	if (!IsAvailableDatasetName(vInfo.m_strName))
	{
		return NULL;
	}
	if (!IsOpen())
	{
		return NULL;
	}

	OgdcDatasetVectorMdb* pDatasetVector = new OgdcDatasetVectorMdb(this);

	//�Ƿ�����
	CDaoRecordset recordset(&m_daoDatabase);
	OgdcString strSQL;
	strSQL.Format(OGDCPCTSTR("SELECT COUNT(*) FROM OGRegister "
		"WHERE OGDatasetName = '%s'"),
	OGDCPCTSTR(vInfo.m_strName));		
	try
	{
		recordset.Open(dbOpenSnapshot, strSQL);
		COleVariant varCount;
		recordset.MoveFirst();
		recordset.GetFieldValue(0, varCount);
		recordset.Close();
		if ( varCount.lVal != 0 )
		{	
			delete pDatasetVector;
			pDatasetVector = NULL;
			return NULL;
		}
	}
	catch (CDaoException* e)
	{
		delete pDatasetVector;
		pDatasetVector = NULL;
		e->Delete();
		recordset.Close();
		return NULL;
	}

	OgdcFieldInfos fieldInfos;
	fieldInfos.AddField (OG_OBJ_ID,OgdcFieldInfo::INT32, 
		sizeof(dbLong), 0, FALSE, FALSE);
	if (vInfo.m_nType == OgdcDataset::Point)
	{
		fieldInfos.AddField (OG_X,OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField (OG_Y,OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
	}
	else if (vInfo.m_nType != OgdcDataset::Tabular)   
	{
		fieldInfos.AddField (OG_GEOMETRY, 
			OgdcFieldInfo::LongBinary, 0, 0, FALSE, FALSE);
		fieldInfos.AddField (OG_SDRI_W, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField (OG_SDRI_N, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField (OG_SDRI_E, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField (OG_SDRI_S, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));	
	}
	//����ͼ������������Ӧϵͳ�ֶ�
	switch (vInfo.m_nType)
	{
	case OgdcDataset::Tabular:
	case OgdcDataset::Point:
		fieldInfos.AddField(OG_USER_ID, OgdcFieldInfo::INT32,
			sizeof(dbLong),0, FALSE, FALSE, OGDCPCTSTR("0"));
		break;

	case OgdcDataset::Line:
		fieldInfos.AddField(OG_USER_ID, OgdcFieldInfo::INT32,
			sizeof(dbLong), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField(OG_LENGTH, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		break;

	case OgdcDataset::Region:
		fieldInfos.AddField(OG_USER_ID, OgdcFieldInfo::INT32,
			sizeof(dbLong), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField(OG_AREA, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		fieldInfos.AddField(OG_PERIMETER, OgdcFieldInfo::Double,
			sizeof(dbDouble), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		break;

	case OgdcDataset::Text:
		fieldInfos.AddField(OG_USER_ID, OgdcFieldInfo::INT32,
			sizeof(dbLong), 0, FALSE, FALSE, OGDCPCTSTR("0"));
		break;

	default:
		break;
	}
	//�����ֶ�
	//�������ݼ�

	CDaoTableDef daoTableDef(&m_daoDatabase);
	if (!IsAvailableDatasetName(vInfo.m_strName))
	{
		return	FALSE;
	}
	
	OgdcLong nFields = fieldInfos.GetSize();
	CDaoFieldInfo info;
	try
	{
		daoTableDef.Create(OGDCPCTSTR(vInfo.m_strName));
		for (OgdcLong i = 0; i < nFields; i++)
		{ 
			OgdcHelperMdb::OgdcFieldInfo2CDaoFieldInfo(fieldInfos.GetAt(OgdcInt(i)),info);
			daoTableDef.CreateField(info);	
		}
		//����һ��OGId�ֶε�����
		CDaoIndexInfo indexInfo;
		CDaoIndexFieldInfo indexFieldInfo;
		indexFieldInfo.m_strName = OG_OBJ_ID;
		indexFieldInfo.m_bDescending = FALSE;
		indexInfo.m_strName = OGDCPCTSTR("OGID_Index");
		indexInfo.m_pFieldInfos = &indexFieldInfo;
		indexInfo.m_nFields = 1;
		indexInfo.m_bPrimary = TRUE;
		daoTableDef.CreateIndex(indexInfo);
		
		if (vInfo.m_nType != OgdcDataset::Point && vInfo.m_nType != OgdcDataset::Tabular)
		{
			//����������������
			CDaoIndexInfo indexInfo1;
			CDaoIndexFieldInfo indexFieldInfo1[4];
			indexFieldInfo1[0].m_strName = OG_SDRI_W;
			indexFieldInfo1[0].m_bDescending = FALSE;
			indexFieldInfo1[1].m_strName = OG_SDRI_N;
			indexFieldInfo1[1].m_bDescending = FALSE;
			indexFieldInfo1[2].m_strName = OG_SDRI_E;
			indexFieldInfo1[2].m_bDescending = FALSE;
			indexFieldInfo1[3].m_strName = OG_SDRI_S;
			indexFieldInfo1[3].m_bDescending = FALSE;
			indexInfo1.m_strName = OGDCPCTSTR("idx_") + indexInfo1.m_strName;
			indexInfo1.m_pFieldInfos = indexFieldInfo1;
			indexInfo1.m_bClustered = TRUE;
			indexInfo1.m_nFields = 4;
			indexInfo1.m_bPrimary = FALSE;
			indexInfo1.m_bUnique = FALSE;
			daoTableDef.CreateIndex(indexInfo1);
		}

		daoTableDef.Append();
		daoTableDef.Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		daoTableDef.Close();
		return FALSE;
	} 
	
	//�õ����ݼ������ID
	COleVariant lRecordMaxId;
	strSQL.Format(OGDCPCTSTR("SELECT MAX(OGDatasetID) FROM OGRegister"));
	try
	{
		recordset.Open(dbOpenSnapshot,strSQL);
		lRecordMaxId = recordset.GetFieldValue(0);
		recordset.Close ();
	}
	catch (CDaoException* e)
	{
		//��ȡ���ID����Ϊ������¼ʱ����ȡopen�쳣����ʾû�м�¼
		e->Delete( );
	}
	lRecordMaxId.intVal++;
	OgdcInt nID = lRecordMaxId.intVal;
	
	pDatasetVector->m_nID = nID;
	pDatasetVector->m_info = vInfo;
	//��rcBoundsΪ�գ���Ĭ����Ϊ(0,0,2000,2000)
	pDatasetVector->SetBounds(vInfo.m_rcBounds);
 	if (vInfo.m_rcBounds.IsEmpty())
 	{
 		pDatasetVector->m_info.m_rcBounds.left = 0.0;
		pDatasetVector->m_info.m_rcBounds.top = 2000.0;
		pDatasetVector->m_info.m_rcBounds.right = 0.0;
		pDatasetVector->m_info.m_rcBounds.bottom = 2000.0;
 	}
	
	//����ע���
	CDaoRecordset record;
	CDaoTableDef tableDef(&m_daoDatabase);
	try
	{
		tableDef.Open(OG_REGISTER_TABLE);
		record.Open(&tableDef);
		record.AddNew ();
		//���setFieldValue�����ΪOgdcInt��OgdcLong����Ҫ��longǿ��ת��
		record.SetFieldValue (OGRF_ID, long(nID));
		record.SetFieldValue (OGRF_DATASET_NAME, 
			COleVariant(vInfo.m_strName, VT_BSTRT));
		record.SetFieldValue (OGRF_DATASET_TYPE, long(vInfo.m_nType));
		record.SetFieldValue (OGRF_LEFT, pDatasetVector->m_info.m_rcBounds.left);
		record.SetFieldValue (OGRF_RIGHT, pDatasetVector->m_info.m_rcBounds.right);
		record.SetFieldValue (OGRF_TOP, pDatasetVector->m_info.m_rcBounds.top);
		record.SetFieldValue (OGRF_BOTTOM, pDatasetVector->m_info.m_rcBounds.bottom);
		record.SetFieldValue (OGRF_LASTUPDATE, COleDateTime::GetCurrentTime()); 
		record.Update ();
		record.Close (); 
		tableDef.Close();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		record.Close (); 
		tableDef.Close();
		return FALSE;
	}
	
	pDatasetVector->m_info.m_strName = vInfo.m_strName;
	m_bOpened = TRUE;
	m_datasets.Add(pDatasetVector);

	return pDatasetVector;	
}

OgdcDatasetRaster* OgdcDataSourceMdb::CreateDatasetRaster( 
	const OgdcDatasetRasterInfo& rInfo, OgdcBool bIsMBRaster /*= FALSE*/ )
{
	if (!IsAvailableDatasetName(rInfo.m_strName))
	{
		return	NULL;
	}
	if (!IsOpen())
	{
		return NULL;
	}

	CDaoRecordset recordsetCheck(&m_daoDatabase);
	OgdcString strSqlCheck;
	strSqlCheck.Format(OGDCPCTSTR("SELECT COUNT(*) FROM OGImgRegister "
		"WHERE OGDatasetName = '%s'"),
		OGDCPCTSTR(rInfo.m_strName));		
	try
	{
		recordsetCheck.Open(dbOpenSnapshot, strSqlCheck);
		COleVariant varCount;
		recordsetCheck.MoveFirst ();
		recordsetCheck.GetFieldValue(0, varCount);
		recordsetCheck.Close();
		if (varCount.lVal != 0)
		{	
			recordsetCheck.Close();
			return NULL;
		}
	}
	catch (CDaoException* e)
	{	
		e->Delete();
		recordsetCheck.Close();
		return NULL;
	}
	
	OgdcDatasetRasterMdb* pDatasetRaster = new OgdcDatasetRasterMdb(this);

	//��ɫ��,����Ǻڰף�Ĭ�ϼ��ϵ�ɫ��
	if (rInfo.m_nPixelFormat == IPF_MONO)
	{
		PALETTEENTRY paletteentry;
		paletteentry.peRed = 0;
		paletteentry.peGreen = 0;
		paletteentry.peBlue = 0;
		paletteentry.peFlags = 0;
		pDatasetRaster->m_colorTable.Add(paletteentry.peRed,
			paletteentry.peGreen, paletteentry.peBlue);
		paletteentry.peRed = 255;
		paletteentry.peGreen = 255;
		paletteentry.peBlue = 255;
		paletteentry.peFlags = 255;
		pDatasetRaster->m_colorTable.Add(paletteentry.peRed,
			paletteentry.peGreen, paletteentry.peBlue);
	}
	
	CDaoTableDef rasterTable(&m_daoDatabase);
	OgdcFieldInfos fieldInfos;

	fieldInfos.AddField (OGDCPCTSTR("OGRow"), OgdcFieldInfo::INT32,
		sizeof(OgdcLong), 0, FALSE, FALSE);
	fieldInfos.AddField (OGDCPCTSTR("OGColumn"), OgdcFieldInfo::INT32,
		sizeof(OgdcLong), 0, FALSE, FALSE);
	fieldInfos.AddField (OGDCPCTSTR("OGSize"), OgdcFieldInfo::INT32,
		sizeof(OgdcLong), 0, FALSE, FALSE);
	fieldInfos.AddField (OGDCPCTSTR("OGRaster"),
		OgdcFieldInfo::LongBinary, 0, 0, FALSE, FALSE);

	OgdcLong nFields = fieldInfos.GetSize();
	CDaoFieldInfo info;
	try
	{
		rasterTable.Create(rInfo.m_strName);
		for (OgdcLong i = 0; i < nFields; i++)
		{ 
			OgdcHelperMdb::OgdcFieldInfo2CDaoFieldInfo(fieldInfos.GetAt(OgdcInt(i)), info);
			rasterTable.CreateField(info);	
		}

		//����OGRow��OGColumn��������
		CDaoIndexInfo indexInfo;
		CDaoIndexFieldInfo indexFieldInfo[2];
		indexFieldInfo[0].m_strName = OG_DIRF_ROW;
		indexFieldInfo[0].m_bDescending = FALSE;
		indexFieldInfo[1].m_strName = OG_DIRF_COLUMN;
		indexFieldInfo[1].m_bDescending = FALSE;
		indexInfo.m_strName = OGDCPCTSTR("idx_") + rInfo.m_strName;
		indexInfo.m_pFieldInfos = indexFieldInfo;
		indexInfo.m_bClustered = TRUE;
 		indexInfo.m_nFields = 2;
		indexInfo.m_bPrimary = true;
		rasterTable.CreateIndex(indexInfo);

		rasterTable.Append();
		rasterTable.Close();
	}
	catch ( CDaoException* e )
	{
		e->Delete();
		rasterTable.Close();
		return NULL;
	} 
	
	//��ע�����д����Ϣ
	OgdcInt m_blockSizes;
 	switch (rInfo.m_nPixelFormat)
 	{
 	case IPF_MONO ://1λ,��ɫz
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize / 8;
 		break;
 	case IPF_FBIT:		//4λ,16ɫ
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize / 2;
 		break;
 	case IPF_BYTE :		//8λ,256ɫ
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize;
 		break;
 	case IPF_TBYTE :		//16λ,��ɫ
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 2;
 		break;
 	case IPF_RGB :		//24λ,���ɫ
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 3;
 		break;
 	case IPF_RGBA :		//32λ,��ǿ���ɫ,�ߵ��洢
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 4;
 		break;
 	case IPF_LONG :	//64λ,����,���ߵ��洢
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 4;
 		break;
 	case IPF_LONGLONG :	//64λ,������
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 8;
 		break;
 	case IPF_FLOAT :	//32λ,������
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 4;
 		break;
 	case IPF_DOUBLE : //64λ,˫���ȸ�����
 		m_blockSizes = rInfo.m_nBlockSize * rInfo.m_nBlockSize * 8;
 		break;
 	default:	
 		break;
 	}
	//�õ����ֵ
	CDaoRecordset recordset(&m_daoDatabase);
	COleVariant lRecordMaxId;
	CString strSQL;
	strSQL.Format (OGDCPCTSTR("SELECT MAX(OGDatasetID) FROM OGImgRegister"));
	try
	{
		recordset.Open(dbOpenSnapshot,strSQL);
		lRecordMaxId = recordset.GetFieldValue(0);
		recordset.Close();
	}
	catch(CDaoException* e )
	{
		e->Delete();
		recordset.Close();
		return NULL;
	}

	OgdcLong lMaxID;
	if (lRecordMaxId.vt == VT_NULL || lRecordMaxId.vt == VT_EMPTY)
	{
		lMaxID = 0;
	}
	else
	{
		lMaxID = lRecordMaxId.lVal;
	}
	lMaxID++;

	//����ע���
	CDaoTableDef table(&m_daoDatabase);
	try
	{		
		table.Open(OGDCPCTSTR(OG_IMGREGISTER_TABLE));
		recordset.Open(&table);
 		recordset.AddNew ();

 		recordset.SetFieldValue (OGRF_ID, long(lMaxID));
 		recordset.SetFieldValue (OGRF_DATASET_NAME, COleVariant(rInfo.m_strName, VT_BSTRT));
 		recordset.SetFieldValue (OGRF_DATASET_TYPE, long(rInfo.m_nType));
 		recordset.SetFieldValue (OGIRF_PIXELFORMAT, (long)(rInfo.m_nPixelFormat));
 		recordset.SetFieldValue (OGIRF_WIDTH, long(rInfo.m_nWidth));	
 		recordset.SetFieldValue (OGIRF_HEIGHT, long(rInfo.m_nHeight));
 		recordset.SetFieldValue (OGIRF_EBLOCKSIZE, (long)(rInfo.m_nBlockSize));
	//	recordset.SetFieldValue (IRF_PYRAMID, OGDCPCTSTR(""));
		//CHENZhao 2009.11.09
//����ط�ԭ����д��(long)0��ȥ�������ص�ָ��������Ǹ��������������ڴ���ͨ�����������ת����
		recordset.SetFieldValue (OGIRF_PYRAMIDLEVEL, COleVariant(long(0), VT_I4));
		recordset.SetFieldValue (OGIRF_BLOCKSIZES, long(m_blockSizes));
		recordset.SetFieldValue (OGIRF_LEFT, rInfo.m_rcBounds.left);
		recordset.SetFieldValue (OGIRF_TOP, rInfo.m_rcBounds.top);
		recordset.SetFieldValue (OGIRF_RIGHT, rInfo.m_rcBounds.right);
		recordset.SetFieldValue (OGIRF_BOTTOM, rInfo.m_rcBounds.bottom);

		recordset.Update();
		recordset.Close();
		table.Close();	
	}
	catch (CDaoException* e)
	{
		e->Delete();
		recordset.Close();
		table.Close();
		return NULL;
	}
	//ע����޸���ϣ�

	//��ʼ���
 	OgdcLong lWidthRemain = rInfo.m_nWidth % rInfo.m_nBlockSize;
 	OgdcLong lHeightRemain = rInfo.m_nHeight % rInfo.m_nBlockSize;
 	if (lWidthRemain == 0)
 	{
 		lWidthRemain = rInfo.m_nBlockSize;
 	}
 	if (lHeightRemain == 0)
 	{
 		lHeightRemain = rInfo.m_nBlockSize;
 	}

	OgdcInt m_nColBlocks = (rInfo.m_nWidth + rInfo.m_nBlockSize - 1) 
		/ rInfo.m_nBlockSize;
    OgdcInt m_nRowBlocks = (rInfo.m_nHeight + rInfo.m_nBlockSize - 1) 
		/ rInfo.m_nBlockSize;
 	strSQL.Format(OGDCPCTSTR("SELECT *  from [%s]"), rInfo.m_strName.Cstr());//�ѵ��׺в��Բ�����������̣�
	
	CDaoRecordset RsNew(&m_daoDatabase);
	try
 	{
 		RsNew.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
 		
 		OgdcSize szValid;
 		CByteArray btEmptyData; 
 		btEmptyData.Add((BYTE) - 1);
 		for(OgdcLong i = 0; i < m_nRowBlocks; i++)
		{
 			for(OgdcLong j = 0; j < m_nColBlocks; j++)
 			{
 				RsNew.AddNew();
 				RsNew.SetFieldValue(OG_DIRF_ROW,(long)i);
 				RsNew.SetFieldValue(OG_DIRF_COLUMN,(long)j);
 							
 				//��Ч����
 				szValid.cx = OgdcInt((j == rInfo.m_nColBlocks - 1)
					? lWidthRemain : rInfo.m_nBlockSize);
 				szValid.cy = OgdcInt((i == rInfo.m_nRowBlocks - 1)
					? lHeightRemain : rInfo.m_nBlockSize);
 				long lSize = (szValid.cx << 16) + szValid.cy;
 				RsNew.SetFieldValue(OG_DIRF_SIZE,lSize);
 				
 				COleVariant var(btEmptyData);
 				//Block����
 				RsNew.SetFieldValue(OG_DIRF_RASTER, var);
 				RsNew.Update();
 			}
		}		
 		RsNew.Close();
 	}
 	catch (CDaoException* e)
 	{
 		e->Delete();
		RsNew.Close();
		return FALSE;
 	}
 	m_bOpened = TRUE;

	pDatasetRaster->m_info = rInfo;
	pDatasetRaster->m_info.m_nColBlocks = m_nColBlocks;
	pDatasetRaster->m_info.m_nRowBlocks = m_nRowBlocks;
	pDatasetRaster->m_nID = lMaxID;
	m_datasets.Add(pDatasetRaster);

	return pDatasetRaster;  
}

OgdcDataset* OgdcDataSourceMdb::CreateDatasetFrom( const OgdcString &strNewName, OgdcDataset* pReferenceDataset )
{
	OgdcDatasetVector* pDataset = NULL;
	if (!m_daoDatabase.IsOpen())
	{
		return	NULL;
	}
	if (pReferenceDataset->IsRaster())
	{
		return NULL;
	}
	else
	{
		OgdcDatasetVectorInfo vInfo;
		vInfo = ((OgdcDatasetVector*)pReferenceDataset)->m_info;
		vInfo.m_strName = GetUnoccupiedDatasetName(strNewName);
		pDataset = CreateDatasetVector(vInfo);
		if(pDataset == NULL)
		{
			return FALSE;
		}

		//������ϵͳ�ֶΣ����Զ����ֶ�
		OgdcFieldInfos fieldInfos;
		((OgdcDatasetVector*)pReferenceDataset)->GetFieldInfos(fieldInfos);
		pDataset->CreateFields(fieldInfos);
	}
		
	return pDataset;	
}

OgdcDataset* OgdcDataSourceMdb::CopyDataset( OgdcDataset* pSrcDataset, 
	const OgdcString& strDestDatasetName, OgdcBool bBuildIndexOrPyramid /*= FALSE*/ )
{
	OgdcDataset	*pDataset = NULL;
	if (!m_daoDatabase.IsOpen())
	{
		return	NULL;
	}

	if (!pSrcDataset->IsOpen() && !pSrcDataset->Open())
	{
		return NULL;
	}

	//դ��
	if (pSrcDataset->IsRaster())
	{
		OgdcDatasetRasterInfo rInfo;
		OgdcDatasetRaster* pRaster;
		pRaster = ((OgdcDatasetRaster*)pSrcDataset);
		rInfo = pRaster->m_info;
		rInfo.m_strName = GetUnoccupiedDatasetName(strDestDatasetName);
		pDataset = (OgdcDatasetRasterMdb*)CreateDatasetRaster(rInfo);
		((OgdcDatasetRasterMdb*)pDataset)->SetModifiedFlag(TRUE);
		OgdcRasterBlock* pBlock;
		for (OgdcInt i = 0; i < pRaster->m_info.m_nRowBlocks; i++)
		{
			for (OgdcInt j =0; j < pRaster->m_info.m_nColBlocks; j++)
			{
				pBlock = pRaster->LoadBlock(i, j);
				((OgdcDatasetRasterMdb*)pDataset)->SaveBlock(pBlock) ;
				pBlock->Empty();
				delete pBlock;
				pBlock = NULL;
			}
		}
		
		((OgdcDatasetRasterMdb*)pDataset)->m_colorTable = pRaster->m_colorTable;
		//���߳��ֶθ�ֵ
		((OgdcDatasetRasterMdb*)pDataset)->m_info.m_dMinZ = pRaster->m_info.m_dMinZ;
		((OgdcDatasetRasterMdb*)pDataset)->m_info.m_dMaxZ = pRaster->m_info.m_dMaxZ;
		((OgdcDatasetRasterMdb*)pDataset)->SaveInfo();
		if (bBuildIndexOrPyramid)
		{
			((OgdcDatasetRasterMdb*)pDataset)->BuildPyramid();
		}

		pRaster = NULL;
	}

	//�����ʸ��
	else
	{
		OgdcQueryDef queryOgdc;
		queryOgdc.m_nCursorType = OgdcQueryDef::OpenStatic;
		queryOgdc.m_nOptions = OgdcQueryDef::Both;
		OgdcRecordset* pOGRecord = ((OgdcDatasetVector*)pSrcDataset)->Query(queryOgdc);
		if(pOGRecord == NULL)
		{
			return FALSE;
		}

		pDataset = (OgdcDatasetVectorMdb*)CreateDatasetFrom(strDestDatasetName, pSrcDataset);
		if(pDataset == NULL)
		{
			return FALSE;
		}

		OgdcQueryDef queryMdb;
		queryMdb.m_nCursorType = OgdcQueryDef::OpenDynamic;
		queryOgdc.m_nOptions = OgdcQueryDef::Both;

		OgdcRecordset* pMdbRecord = ((OgdcDatasetVectorMdb*)pDataset)->Query(queryMdb);
		if(pMdbRecord == NULL)
		{
			((OgdcDatasetVector*)pSrcDataset)->ReleaseRecordset(pOGRecord);
			((OgdcDatasetVectorMdb*)pDataset)->ReleaseRecordset(pMdbRecord);
			return FALSE;
		}

		OgdcFieldInfos fInfos;
		pMdbRecord->GetFieldInfos(fInfos);

		OgdcElement* pElement = NULL;
		OgdcVariant valValue;
		while (!pOGRecord->IsEOF())
		{
			if(pDataset->GetType() != OgdcDataset::Tabular && !pOGRecord->GetElement(pElement))
			{
				((OgdcDatasetVector*)pSrcDataset)->ReleaseRecordset(pOGRecord);
				((OgdcDatasetVectorMdb*)pDataset)->ReleaseRecordset(pMdbRecord);
				return FALSE;
			}
			pMdbRecord->AddNew(pElement);
			for(OgdcInt i=0; i<fInfos.GetSize(); i++)
			{
				if (fInfos.GetAt(i).m_strName.Left(2).CompareNoCase(OGDCPCTSTR("Sm")) == 0
					|| OgdcHelperMdb::IsSystemField(fInfos.GetAt(i).m_strName)) 
				{
					continue;
				}
				
				if (!pOGRecord->GetFieldValue(OGDCPCTSTR(fInfos.GetAt(i).m_strName), valValue))
				{
					continue;
				}
				
				pMdbRecord->SetFieldValue(OGDCPCTSTR(fInfos.GetAt(i).m_strName), valValue);
				
			}
			pMdbRecord->Update();
			
			pOGRecord->Move();
		}
		delete pElement;
		pElement = NULL;
		((OgdcDatasetVector*)pSrcDataset)->ReleaseRecordset(pOGRecord);
		((OgdcDatasetVectorMdb*)pDataset)->ReleaseRecordset(pMdbRecord);
	}

	return pDataset;	
}

OgdcBool OgdcDataSourceMdb::SaveInfo()
{
	if (!m_daoDatabase.IsOpen())
	{
		return FALSE;
	}
	//�ж�����Դ�Ƿ���ֻ����
	if (m_connection.m_bReadOnly == TRUE)
	{
		return FALSE;
	}

	//��û�ж�����Դ���й��޸ģ�����Ҫ���д˺�������
 	if (!IsModified())
 	{	
 		SetModifiedFlag(FALSE);
 		return FALSE;	
 	}

	//����Ͱ��������δ���
	for (OgdcInt i = 0; i < GetDatasetCount(); i++)
	{
 		if (GetDataset(i)->IsRaster())
 		{
			OgdcDatasetRasterMdb* pRaster;
			pRaster = (OgdcDatasetRasterMdb*)GetDataset(i);
			if (pRaster->IsModified())
			{
				pRaster->SaveInfo();
			}		
		}
  		else
		{
			OgdcDatasetVectorMdb* pVector;
			pVector = (OgdcDatasetVectorMdb* )GetDataset(i);
			if (pVector->IsModified())
			{
				pVector->SaveInfo();
			}				
		}
	}
	return TRUE;	
}

OgdcBool OgdcDataSourceMdb::SetCoordSys( const OgdcCoordSys& coordSys )
{
	m_coordSys = coordSys;	
	SetModifiedFlag(TRUE);
	return TRUE;
}

OgdcBool OgdcDataSourceMdb::GetCoordSys( OgdcCoordSys& coordSys )
{
	coordSys = m_coordSys;
	return TRUE;	
}

OgdcBool OgdcDataSourceMdb::Execute( const OgdcString& strSQL )
{
	if (!IsOpen())
	{
		return FALSE;
	}
	try
	{
		m_daoDatabase.Execute(strSQL);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		m_daoDatabase.Close();
		return FALSE;
	}
	
	return TRUE;	
}

OgdcBool OgdcDataSourceMdb::IsConnected()
{
	if (!IsOpen())
	{
		return FALSE;
	}
	try
	{
		if (m_daoDatabase.CanTransact() && m_daoDatabase.CanUpdate())
		{
			return TRUE;
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
}

OgdcBool OgdcDataSourceMdb::Connect()
{
	if (IsOpen())
	{
		return FALSE;
	}
	
	try
	{
		//������벻ΪΪ��
		if (!OgdcString(m_connection.m_strPassword).IsEmpty())
		{
			OgdcString pwd = OGDCPCTSTR(";PWD=") + m_connection.m_strPassword;
			m_daoDatabase.Open(m_connection.m_strServer, TRUE, FALSE, pwd);
		}
		else
		{	
			m_daoDatabase.Open(m_connection.m_strServer, TRUE, FALSE);
		}
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;	
	}
	m_bOpened = TRUE;
	return TRUE;
}

OgdcTime OgdcDataSourceMdb::GetDateLastUpdated()
{
	OgdcTime dateLastUpdated;
	CFileStatus filestatus;
	if (!m_daoDatabase.IsOpen())
	{
		return dateLastUpdated;
	}
	if (!CFile::GetStatus(m_daoDatabase.GetName(), filestatus))
	{
		return OgdcTime(time_t(0));
	}

	dateLastUpdated.SetDateTime(filestatus.m_mtime.GetYear(),
		filestatus.m_mtime.GetMonth(),
		filestatus.m_mtime.GetDay(),
		filestatus.m_mtime.GetHour(),
		filestatus.m_mtime.GetMinute(),
		filestatus.m_mtime.GetSecond());
	
	return dateLastUpdated;
}

OgdcTime OgdcDataSourceMdb::GetDateCreated()
{
	OgdcTime dateCreate;
	CFileStatus filestatus;
	if (!m_daoDatabase.IsOpen())
	{
		return dateCreate;
	}
	if (!CFile::GetStatus(m_daoDatabase.GetName(), filestatus))
	{
		return OgdcTime(time_t(0));	
	}
	dateCreate.SetDateTime(filestatus.m_ctime.GetYear(),
		filestatus.m_ctime.GetMonth(),
		filestatus.m_ctime.GetDay(),
		filestatus.m_ctime.GetHour(),
		filestatus.m_ctime.GetMinute(),
		filestatus.m_ctime.GetSecond());

	return dateCreate;
}

OgdcBool OgdcDataSourceMdb::ChangePassword( const OgdcString& strNewPassword )
{

	if (!IsOpen())
	{
		return FALSE;
	}
	//Ĭ���û���admin
	COleVariant varOldPwd(this->GetPassword(), VT_BSTRT);
	COleVariant varNewPwd(strNewPassword, VT_BSTRT);

	if (!this->IsConnected())
	{
		return FALSE;
	}
	try
	{	
		if (GetPassword().IsEmpty())
		{
			DAO_CHECK(m_daoDatabase.m_pDAODatabase->NewPassword(
				NULL, V_BSTR( &varNewPwd )));
		}
		else
		{
			DAO_CHECK(m_daoDatabase.m_pDAODatabase->NewPassword(
				V_BSTR( &varOldPwd ), V_BSTR( &varNewPwd )));
		}
	}
	catch (CDaoException* e)
	{
		e->Delete();
		m_daoDatabase.Close();
		return FALSE;
	}

	return TRUE;	
}

OgdcString OgdcDataSourceMdb::GetEngineName() const 
{	
	return "Microsoft Access Database";
}

//����һ������Դ��Ŀǰû�е����ݼ����֡�
OgdcString OgdcDataSourceMdb::GetUnoccupiedDatasetName( const OgdcString& strDatasetName )
{
	OgdcString strDsName = strDatasetName;
	OgdcString strName = strDatasetName;

	//���û�д����ַ���������Ĭ�ϵ�"T_"����
	if (strName.IsEmpty())
	{
		strName = "T";
	}
	OgdcString	strVSQL,strRSQL;
	OgdcString subStr = "";
	OgdcString strNull = "";
	OgdcInt i = 1;	
	if (!IsAvailableDatasetName(strDatasetName))
	{
		return	strNull;
	}
	if (!m_daoDatabase.IsOpen())
	{
		return strNull;
	}

	while (1)
	{	
		CDaoRecordset vectorRecord(&m_daoDatabase);
		CDaoRecordset rasterRecord(&m_daoDatabase);		
		strVSQL.Format(OGDCPCTSTR("SELECT OGDatasetName FROM OGRegister "
			"WHERE OGDatasetName = '%s'"), strName.Cstr());
		strRSQL.Format(OGDCPCTSTR("SELECT OGDatasetName FROM OGImgRegister "
			"WHERE OGDatasetName = '%s'"), strName.Cstr());
		try
		{	
			vectorRecord.Open(AFX_DAO_USE_DEFAULT_TYPE, strVSQL);
			rasterRecord.Open(AFX_DAO_USE_DEFAULT_TYPE, strRSQL);
		}
		catch (CDaoException* e)
		{
			e->Delete();
			vectorRecord.Close();
			rasterRecord.Close();
			return strNull;
		}

		if (vectorRecord.IsEOF() && rasterRecord.IsEOF())
		{
			return strName;
		}
		subStr.Format("_%d", i++);
		strName = strDsName + subStr;			
	}			
}

//�ж����ݼ������Ƿ�Ϸ���
OgdcBool OgdcDataSourceMdb::IsAvailableDatasetName( const OgdcString& strDatasetName )
{
	if (strDatasetName.IsEmpty())
	{
		return FALSE;
	}

	if (OgdcHelperMdb::IsKeyWord(strDatasetName))
	{
		return FALSE;
	}

	if(strDatasetName.GetLength() > 30 ) 
	{
		//����>30���ַ�
		return FALSE;
	}

	OgdcBool bResult = TRUE;
	OgdcBool bNumber = FALSE;//�Ƿ�������
	OgdcBool bLetter = FALSE; //�Ƿ�����ĸ
	OgdcBool bUnderline = FALSE;//�Ƿ����»���

	OgdcString strTemp(strDatasetName);
	OgdcInt nSize = strTemp.GetLength();
	OgdcChar *pChar = NULL;

	for(OgdcInt i=0;i<nSize;i++)
	{
		OgdcWchar charW = strTemp.GetAt(i);
		pChar = (OgdcChar *) &charW;
		if ( pChar[0] == 0 || pChar[1] == 0 )
		{
			OgdcInt n = 0;
			if( pChar[0] == 0 )	// UGC_ISBIGENDIAN
			{
			  if(sizeof(OgdcWchar) ==2)
			  {
				  n = 1;
			  }
			  else if(sizeof(OgdcWchar) == 4)
			  {
				  n = 3;
			  }
			}
			bNumber = (pChar[n] >= 48 && pChar[n] <= 57);//����0-9��ASCII��:48-57
			bLetter = (pChar[n] >= 65 && pChar[n] <= 90)||(pChar[n] >= 97 && pChar[n] <= 122);//A-z,a-z��ASCII��
			bUnderline = (pChar[n] == 95);//'_'��ASCII����95
			if( (bNumber||bLetter||bUnderline)  == FALSE )
			{//�зǷ��ַ�
				bResult = FALSE;
				break;
			}
			else if(i == 0)
			{
				if(bNumber||bUnderline)
				{//��һ���ַ����������ֻ��»���
					bResult = FALSE;
					break;
				}
			}
		}
	}

	return bResult;
}

OgdcInt OgdcDataSourceMdb::GetVersion()
{
	return OgdcInt(m_nVersion);	
}

OgdcBool OgdcDataSourceMdb::BeginTrans()
{
	if (m_bTransStarted) 
	{
		return FALSE;
	}
	
	if (!IsOpen())
	{
		return FALSE;
	}
	if (!IsTransacted()) 
	{
		return FALSE;
	}
	try
	{
		m_daoDatabase.m_pDAODatabase->BeginTrans();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return FALSE;
	}

	m_bTransStarted = TRUE;
	return TRUE;
}

void OgdcDataSourceMdb::Commit()
{
	if (!m_daoDatabase.IsOpen())
	{
		return;
	}
	if (!IsTransacted() || m_connection.m_bReadOnly == TRUE)
	{
		return;
	}

	if (!IsTransStarted())
	{
		return;
	}
	try
	{
		m_daoDatabase.m_pDAODatabase->CommitTrans(0);
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return;
	}

	m_bTransStarted = FALSE;
}

void OgdcDataSourceMdb::Rollback()
{
	if (!IsOpen() || !IsTransacted() || m_connection.m_bReadOnly == TRUE)
	{
		return;
	}
	if (!IsTransStarted())
	{
		return;
	}
	try
	{
		m_daoDatabase.m_pDAODatabase->Rollback();
	}
	catch (CDaoException* e)
	{
		e->Delete();
		return;
	}
	
	m_bTransStarted = FALSE;
	m_bModified = FALSE;
}

OgdcBool OgdcDataSourceMdb::IsTransStarted() const
{
	return	m_bTransStarted;	
}

OgdcBool OgdcDataSourceMdb::IsModified()
{
	return	m_bModified;	
}

void OgdcDataSourceMdb::SetModifiedFlag( OgdcBool bModified /*= TRUE*/ )
{
	m_bModified = bModified;
}

OgdcBool OgdcDataSourceMdb::IsValidFieldOrTableName( const OgdcString& strFieldOrTableName )
{
	if (strFieldOrTableName.IsEmpty())
	{
		return FALSE;
	}

	if (OgdcHelperMdb::IsSystemField(strFieldOrTableName)) 
	{
		return FALSE;
	}

	if (OgdcHelperMdb::IsKeyWord(strFieldOrTableName))
	{
		return FALSE;
	}
	
	if(strFieldOrTableName.GetLength() > 30 ) 
	{
		//����>30���ַ�
		return FALSE;
	}

	OgdcBool bResult = TRUE;
	OgdcBool bNumber = FALSE;//�Ƿ�������
	OgdcBool bLetter = FALSE; //�Ƿ�����ĸ
	OgdcBool bUnderline = FALSE;//�Ƿ����»���

	OgdcString strTemp(strFieldOrTableName);
	OgdcInt nSize = strTemp.GetLength();
	OgdcChar *pChar = NULL;

	for(OgdcInt i=0;i<nSize;i++)
	{
		OgdcWchar charW = strTemp.GetAt(i);
		pChar = (OgdcChar *) &charW;
		if ( pChar[0] == 0 || pChar[1] == 0 )
		{
			OgdcInt n = 0;
			if( pChar[0] == 0 )	// UGC_ISBIGENDIAN
			{
			  if(sizeof(OgdcWchar) ==2)
			  {
				  n = 1;
			  }
			  else if(sizeof(OgdcWchar) == 4)
			  {
				  n = 3;
			  }
			}
			bNumber = (pChar[n] >= 48 && pChar[n] <= 57);//����0-9��ASCII��:48-57
			bLetter = (pChar[n] >= 65 && pChar[n] <= 90)||(pChar[n] >= 97 && pChar[n] <= 122);//A-z,a-z��ASCII��
			bUnderline = (pChar[n] == 95);//'_'��ASCII����95
			if( (bNumber||bLetter||bUnderline)  == FALSE )
			{//�зǷ��ַ�
				bResult = FALSE;
				break;
			}
			else if(i == 0)
			{
				if(bNumber||bUnderline)
				{//��һ���ַ����������ֻ��»���
					bResult = FALSE;
					break;
				}
			}
		}
	}
	
	return bResult;
}

void OgdcDataSourceMdb::SetDescription( OgdcString strDescription )
{
	m_strDescription = strDescription;
	m_bModified = TRUE;
}

OgdcString OgdcDataSourceMdb::GetDescription()
{
	return m_strDescription;		
}

OgdcBool OgdcDataSourceMdb::DropDataSource()
{
	CFile delFile;
	OgdcString file = m_connection.m_strServer;
	if (m_daoDatabase.IsOpen())
	{
		Close();
	}
 	try
 	{
 		delFile.Remove(file);
 		return TRUE;
 	}
 	catch(CFileException* e)
	{
		e->Delete();
		return FALSE;
	}
}

OgdcBool OgdcDataSourceMdb::ReadInfo()
{
	if (!m_daoDatabase.IsOpen())
	{
		return FALSE;
	}
	OgdcString strSQL;
	COleVariant varValue;
	OgdcString strDSInfo;
	CDaoRecordset recordset(&m_daoDatabase);
	strSQL.Format(OGDCPCTSTR("SELECT * FROM OGDataSourceInfo"));
	try
	{
		recordset.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
		if ((!recordset.IsBOF()) && (!recordset.IsEOF()))
		{
			recordset.MoveFirst();
			//version
			recordset.GetFieldValue(OG_DF_VERSION, varValue);
			if ((varValue.vt != VT_NULL) && (varValue.vt != VT_EMPTY))
			{
				m_nVersion = varValue.lVal;
			}	
			else
			{
				m_nVersion = 10000;
			}

			//CoordSys
			recordset.GetFieldValue(OG_DF_COORDSYS,varValue);
	
			switch(varValue.lVal)
			{
			case 0:
				m_coordSys.SetPlanar(m_coordSys.m_nUnit);
				break;
	
			case 1:
				m_coordSys.SetEarth(m_coordSys.m_dPriAxis,
					m_coordSys.m_dFlatten, m_coordSys.m_nUnit);
				break;
			case 2:
				m_coordSys.SetCoordSys(m_coordSys.m_ProjectionType, 
					m_coordSys.m_PrjParams, m_coordSys.m_dPriAxis,
					m_coordSys.m_dFlatten, m_coordSys.m_dPrimeMeridian,
					m_coordSys.m_nUnit, m_coordSys.m_nDistUnit);
				break;
			default:
				break;		
			}

			recordset.Close();
		}
		else
		{
			recordset.Close();
		}

	}
	catch (CDaoException* e)
	{
		e->Delete();
		recordset.Close();
		return FALSE;
	}
	return TRUE;
}

OGDC::OgdcString OgdcDataSourceMdb::GetName() const
{
	return m_connection.m_strDatabase;	
}

OgdcDataSource* CreateOgdcDataSource()
{
	OgdcDataSource* pDataSource = new OgdcDataSourceMdb();
	return pDataSource;
}

OgdcFeature* CreateOgdcFeature()
{
	OgdcFeature* pOgdcFeature = NULL;
	return pOgdcFeature;	
}

}
