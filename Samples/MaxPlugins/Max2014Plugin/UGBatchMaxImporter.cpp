
#include "UGBatchMaxImporter.h"
#include "UGMaxLogFile.h"


void UGBatchMaxImporter::DoImport()
{
	m_dictPosToMaxFile.RemoveAll();
	m_dictAllMaxFiles.RemoveAll();

	//�������е��ļ�·���б�ȫ·����
	RecurAllFiles(m_strFolderBasePath);
	//��ȡ���е��ļ�λ����Ϣ���ļ�title��vector3d��dict��
	//GetAllPositionInfo();

	//�����ļ������
	OGDC::OgdcDict<UGC::UGString,UGMaxFileNameHongPei>::POSITION startPosition =m_dictAllMaxFiles.GetStartPosition();
	UGC::UGString strFirst;
	UGMaxFileNameHongPei hongpeiSecond;

	while(!m_dictAllMaxFiles.IsEOF(startPosition))
	{
		m_dictAllMaxFiles.GetNextAssoc(startPosition,strFirst,hongpeiSecond);

		//�ļ�title
		UGC::UGString strFileTitle =strFirst;
		UGC::UGVector3d v3dPos(exportPara.X, exportPara.Y, exportPara.Z);

		//����ҵ���λ����Ϣ
		//if (m_dictPosToMaxFile.Lookup(strFileTitle,v3dPos))
		{
			ExportMaxFileToDataset(hongpeiSecond.m_strRealName,v3dPos);
		}
	}
}

void UGBatchMaxImporter::RecurAllFiles(const UGC::UGString& strBasePath)
{
	UGArray<UGC::UGString> strFileArray;
	UGC::UGFile::ListFiles(strFileArray, strBasePath);
	UGC::UGint nFileCount = strFileArray.GetSize();

	for(UGC::UGint i = 0; i < nFileCount; i++)
	{
		UGC::UGString strFileName = strFileArray[i];
		UGC::UGint nPos =strFileName.Find(_U("."));

		//û���ҵ���.����Ϊ���ļ���
		if (-1 ==nPos)
		{
			RecurAllFiles(strBasePath+_U("\\")+strFileName);
		}
		else
		{
			if (strFileName.Right(4).CompareNoCase(_U(".max")) == 0)
			{
				//�������û�и������Ա���ļ�
				UGC::UGString strBaseName;
				UGC::UGint nValue =-1;
				//ͨ���ļ�����ȡ�ļ�������
				strFileName.MakeLower();
				GetRealNameByH(strFileName,strBaseName,nValue);

				//���û�С����״���ӵ�ʱ��
				UGMaxFileNameHongPei hongpeiFind;
				if (!m_dictAllMaxFiles.Lookup(strBaseName,hongpeiFind))
				{
					UGMaxFileNameHongPei hongpei;
					hongpei.m_strRealName =strBasePath + _U("\\") +strFileName;
					hongpei.nValue =nValue;

					m_dictAllMaxFiles.SetAt(strBaseName,hongpei);
				}
				else
				{
					//����ҵ��ˣ������������ڵ��ϣ�Ҫ�滻֮
					if (hongpeiFind.nValue <nValue)
					{
						UGMaxFileNameHongPei hongpei;
						hongpei.m_strRealName =strBasePath + _U("\\") +strFileName;
						hongpei.nValue =nValue;
						
						m_dictAllMaxFiles.SetAt(strBaseName,hongpei);
					}
				} //				if (!m_dictAllMaxFiles.LookUp(strBaseName,hongpeiFind))
			}//			if (!strFileName.Right(4).CompareNoCase(_U(".max")))
		}//		if (-1 !=nPos)
	}	//for(UGC::UGint i = 0; i < nFileCount; i++)
}

/*void UGBatchMaxImporter::GetAllPositionInfo()
{
	//�κβ���Ϊ�ռ�����
	if (m_strLonFieldName.IsEmpty() || m_strLatFieldName.IsEmpty() || m_strFileFieldName.IsEmpty())
	{
		return;
	}

	//��·�������ڼ�����
	if (!UGFile::IsExist(m_strFolderBasePath))
	{
		return;
	}

	//��ȡ���ݼ����ⲿ����
	UGDataset *pDataset =m_pImportInfoDatasetPtr;
	if (NULL ==pDataset)
	{
		return;
	}

	//�����ݼ�
	if (!pDataset->IsOpen())
	{
		pDataset->Open();
	}
	
	UGQueryDef querydef;
	UGRecordset* pRecordSet = static_cast<UGDatasetVector *>(pDataset)->Query(querydef);
	if(pRecordSet == NULL || pRecordSet->IsEmpty())
	{
		return;
	}
	pRecordSet->MoveFirst();

	while(!pRecordSet->IsEOF())//ѭ�����еļ��ζ���
	{
		UGdouble dLon;
		UGdouble dLat;
		UGString strFileName;
		UGVariant Var;

		//��ȡ������Ϣ
		pRecordSet->GetFieldValue(m_strLonFieldName,Var);
		dLon =Var.ToDouble();

		//��ȡγ����Ϣ
		pRecordSet->GetFieldValue(m_strLatFieldName,Var);
		dLat =Var.ToDouble();

		//��ȡģ���ļ�������Ϣ
		pRecordSet->GetFieldValue(m_strFileFieldName,Var);
		strFileName =Var.ToString();
		strFileName.MakeLower();
		
		//��ӵ��ֵ���
		UGVector3d v3d(dLon,dLat,10.0);
		m_dictPosToMaxFile.SetAt(strFileName,v3d);

		//��¼����
		pRecordSet->MoveNext();
	}
}*/

void UGBatchMaxImporter::ExportMaxFileToDataset(const UGC::UGString& strFileName,const UGC::UGVector3d& vecPos)
{


	//�����ǵ�����m_pExportDatasetPtr���ݼ�
// 	if (pDataset != NULL)
// 	{
		//��ģ�͵��뵽����
		GetCOREInterface()->LoadFromFile(strFileName.Cstr());
		//UGERROR2(-100,strFileName);	

		UGC::UGString strTextPath =UGC::UGFile::GetDir(strFileName);

		UGMaxModelProcess modelProcessor(_U("udb"));
		modelProcessor.SetIsExportMaterialColor(!exportPara.IgnoreMaterialColor);
		modelProcessor.SetIsExportNormal(!exportPara.WithoutNormal);
		modelProcessor.SetIsBIM(TRUE);

		UGC::UGString strModelDir = UGC::UGFile::GetDir(exportPara.DatasourceName);
		UGC::UGFile::MkDir(strModelDir);
		modelProcessor.SetTexPath(strModelDir);
		
		
		UGSingleNodeSceneExporter exporter(&modelProcessor,strModelDir,strTextPath, m_bExportAll,true,true);
		exporter.SetModelRelative(0.0,0.0,0); //������Ϊ10

		UGMaxProcessBar maxProcessBar(hInstance,GetCOREInterface()->GetMAXHWnd());
		maxProcessBar.Start();
		maxProcessBar.SetWeight(0.1f);
		exporter.SetProcessBar(&maxProcessBar);
		exporter.ExportModelDataset(exportPara);
}

void UGBatchMaxImporter::GetRealNameByH(const UGC::UGString& strRealName,UGC::UGString &strBaseName,UGC::UGint &nValue)
{
	//�����ļ�����������Ϊȥ����չ����ԭ�ļ���
	strBaseName =UGC::UGFile::GetTitle(strRealName);
	
	UGC::UGint nPos =strRealName.Find(_U("_h"));

	if (nPos ==-1)
	{
		nValue =-1;
		return;
	}

	UGC::UGString strTitle =UGC::UGFile::GetTitle(strRealName);

	//ǡ��Ϊ_h���������ֵ����
	UGC::UGString strExt =strTitle.Right(strTitle.GetLength() -nPos -2);
	if (strExt.IsEmpty())
	{
		strBaseName =strRealName.Left(nPos);
		nValue =0;
		return;
	}
	//Modify by lina,2014-3-4 U/��U������ת��
	//UGint nNum =atof(strExt.Cstr());
	UGC::UGint nNum =strExt.ToInt();

	if (nNum >=0 && nNum <100)
	{
		strBaseName =strRealName.Left(nPos);
		nValue =nNum;
	}
	else
	{
		nValue =-1;
	}
}

void UGBatchMaxImporter::SetParams(UGC::UGdouble dLon,UGC::UGdouble dLat,UGC::UGdouble dAlt,const UGC::UGString& strBaseFolderPath,UGC::UGString strDataSourceName,UGC::UGString strDataSetName
								   ,UGC::UGbool bPlanar,UGC::UGbool m_bIsIngore, UGC::UGbool m_bIsRemoveDupVertex, UGC::UGbool m_bIsExportNormal,UGC::UGbool m_bExportAll)
{
	
	exportPara.X = dLon;
	exportPara.Y = dLat;
	exportPara.Z = dAlt;
	m_strFolderBasePath =strBaseFolderPath;
	exportPara.DatasourceName = strDataSourceName;
	exportPara.DatasetName =strDataSetName;
	exportPara.IsPlanar = bPlanar;
	exportPara.IgnoreMaterialColor = m_bIsIngore;
	exportPara.RemoveDupVertex = m_bIsRemoveDupVertex;
	exportPara.WithoutNormal = !m_bIsExportNormal;
	this->m_bExportAll = m_bExportAll;
}

UGBatchMaxImporter::UGBatchMaxImporter()
{
	exportPara.X = 0;
	exportPara.Y = 0;
	exportPara.Z = 0;
	m_strFolderBasePath = L"";
	exportPara.DatasourceName = L"";
	exportPara.DatasetName = L"";
	exportPara.IsPlanar = FALSE;
	exportPara.IgnoreMaterialColor = TRUE;
	exportPara.RemoveDupVertex = FALSE;
	exportPara.WithoutNormal = TRUE;
}

UGBatchMaxImporter::~UGBatchMaxImporter()
{
}