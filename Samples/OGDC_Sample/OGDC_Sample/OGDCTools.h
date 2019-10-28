#pragma once
#include "OGDC/OgdcDataSource.h"
#include "OGDC/OgdcProviderManager.h"
#include "ModelTools.h"
using namespace UGC;
class OGDCTools
{
public:
	//������������Դ
	static OgdcDataSource* CreateAndOpenDataSource(OgdcString sever);
	//�������ȡ�Ѵ������ݼ�
	static OgdcDatasetVector* CreateOrOpenDataSetVector(OgdcDataSource*& pUDBDataSource,OgdcString DatasetName,bool isLonLat);
	//������¼��
	static OgdcRecordset* CreateRecordset(OgdcDatasetVector*& pDatasetVector);
	//��¼������
	static void UpdateRecordset(OgdcRecordset*& pRecordset,UGGeoModelPro*& pGeometry);
};