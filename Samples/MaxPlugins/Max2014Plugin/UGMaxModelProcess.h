// ModelProcess.h: plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class �����ṩ��ϸ��ģ�ʹ��������Ǹ�״̬�࣬�ڲ�״̬�ᱣ�֡�
//!  \details ������δ���ģ�ͣ�����ģ�ͣ�����ģ�����ƺ�����Ѿ��������ģ����Ϣ��
//!  \author sunye��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

#ifndef _UGMaxModelProcess_H_
#define _UGMaxModelProcess_H_

#include "Stream/ugdefs.h"
#include "Stream/UGFile.h"
#include "UGMaxToolkit.h"
using namespace UGC;

class INode;
class SceneExport;
class Object;
class TriObject;
class ExpInterface;

class ObjectEntry {
public:
	INode *node;
	ObjectEntry *next;
	ObjectEntry(INode *e) 
	{ 
		node = e; 
		next = NULL;
	}

	~ObjectEntry()
	{
		node = NULL;

		if (next != NULL)
		{
			delete next;
			next = NULL;
		}
	}
};

struct UserField 
{
	//! \brief �Զ����ǩ��
	UGString strName;
	//! \brief ֵ
	UGString strValue;
};
struct  ModelProp
{
	UGint nSmID;
	UGint nSmUserID;
	UGString strName;
	UGString strPath;
	UGVector3d vPostion;
	UGPoint3D innerPoint3D;
	UGVector3d vScale;
	UGVector3d vRotate;
	UGVector3d vMin;
	UGVector3d vMax;
	UGRect2D rcBounds;
	//��m_arrUserField��Ӧ,����arrUserField.strValue��������ֵ
	UGArray<UserField> arrUserField;

};

struct LODInfo
{
	UGC::UGint m_nLevel;
	UGC::UGdouble m_dDistance;
	UGC::UGdouble m_dRecude;
	INode *node;
};

struct ModelLOD
{
	//! \brief ģ�ͷ��Ŷ�̬LOD�㼶��Ϣ
	UGArray<LODInfo> m_arrModelLODInfo;

	ModelLOD()
	{
		
	}

	~ModelLOD()
	{
		m_arrModelLODInfo.RemoveAll();
	}
};

class CtranslateFileName{
private:
	std::map<UGC::UGString,UGC::UGint> fileNameMap;
public:	
	void Add(UGC::UGString name){
		++fileNameMap[name];
	}
	UGC::UGString GetName(UGC::UGString name){
		TCHAR* pName=(TCHAR*)name.Cstr();
		UGC::UGint nameNumC=name.GetLength();
		TCHAR* newNameSta=new TCHAR[nameNumC+1];
		TCHAR* newName=newNameSta;
		memset(newName,0,nameNumC+1);
		while(*pName)
		{
			TCHAR charElement=*pName;
			if(charElement!='\\'&&charElement!='/'&&charElement!=':'&&charElement!='*'&&charElement!='\?'&&charElement!='\''&&charElement!='<'&&charElement!='>'&&charElement!='|')
			{
				*newName=*pName;
				newName++;
				pName++;
			}

			else	
				pName++;

		}
		*newName=0;
		UGC::UGString SnewName(newNameSta);
		if(SnewName.IsEmpty())
		{
			SnewName = _U("noname");//   Modify by lina 2014-3-4 �ַ�ת��
		}
		UGC::UGString strRealName = SnewName;
		SnewName.MakeUpper();
		delete[] newNameSta;
		++fileNameMap[SnewName];
		if(fileNameMap[SnewName]==1)
		{
			return strRealName;
		}
		UGC::UGString str;
		str.Format(_U("%d"),fileNameMap[SnewName]-1);
		UGC::UGString tempName=strRealName+_U("_")+str;
		return tempName;
	}
	std::map<UGC::UGString,UGC::UGint> SameNameList(){
		std::map<UGC::UGString,UGC::UGint>::const_iterator map_it=fileNameMap.begin();
		std::map<UGC::UGString,UGC::UGint> nameDict;
		while(map_it!=fileNameMap.end()){
			if(map_it->second>=2)
				nameDict[map_it->first]=map_it->second;
			map_it++;
		}
		return nameDict;
	}
	bool IsEmpty(){
		return fileNameMap.empty();
	} 
	void Clear(){
		fileNameMap.clear();
	}
};

class UGMaxModelProcess{
public:
//!  \������ʹ�õ�dllName�����ء�
	UGMaxModelProcess(UGC::UGString strDllName=_U("3dsexp"));

//!  \������ʹ�õ�dllName�����ء�
	~UGMaxModelProcess();

//!  \��ģ�ͽ���һЩ�ӹ��������ԭ��ȡ�
	bool ProcessNode(INode *pInNode);

//!  \��ԭProcessNode���������Ĳ�����������������һ��ProcessNode����
	void RecoveryNode();

//!  \������EI�а����Ľڵ���name�����Ʊ��浽Ӳ����
	int  ExportModel(const TCHAR *name,ExpInterface *ei);

//!  \��������ڲ��Ѿ�������Ĳ�������name��������
	void ProcessNodeName(TCHAR *name);

//!  \���ش�����ģ����Ϣ

	UGArray<ModelProp> GetModelsInfo();

//!  \��λ�������������Ϣ
	void Clear();

//!  \��ȡ��ǰ����ڵ������
	UGC::UGString GetCurrentNodeName();

//!  \��ȡ��ǰ����Ľڵ�
	INode* ProcessNodeByStep();

//!  \��λ�������������Ϣ
	void SetXYZ(double dInx,double dIny,double dInz){m_dX=dInx;m_dY=dIny;m_dZ=dInz;}

	ObjectEntry *Contains(Object *obj);

	void SetIsBIM(UGC::UGbool bIsBIM);

	std::map<UGC::UGString,UGC::UGString> GetModel2SGM();

	void SetTexPath(UGC::UGString strPath){m_strTexDest = strPath;}

	//�Ƿ���Ҫ����ʵ������
	UGC::UGbool AddInstanceObject(INode *pInNode);

	void SetModelInfo(UGC::UGString strName);
	//����S3MB
	void SaveS3MB(UGC::UGString filePath);

	//!\ ������ģ�����ݼ�
	void ExportModelDataset(ExportParameter para);


	UGC::UGString GetOSGBPath();

	//ʵ�����ڵ�
	std::map<UGC::UGString, INode *> m_mapInstanceNode;
	//ʵ�����ڵ��Ӧ�������б�
	std::map<UGC::UGString, std::vector<INode *>> m_mapRefernceNode;

	std::map<UGC::UGString, ModelLOD> m_mapNodeToLOD;

	//���ڵ���������
	std::map<UGC::UGString, UGC::UGString> m_mapParentName;

	//�û��Զ���id����
	std::map<UGC::UGString, int> m_mapId;

	//�����Ƿ񵼳�������ɫ
	void SetIsExportMaterialColor(UGC::UGbool bIsExport);

	//�����Ƿ񵼳�����
	void SetIsExportNormal(UGC::UGbool bIsExport);

private:

//! \ ͨ�����ݵ���������ȡ��׺��
	UGC::UGString GetExt(UGC::UGString strName);

//! \ �������ģ����Ϣ
	UGArray<ModelProp> m_arryModels;

//! \  Ҫʹ�õĵ��������
	SceneExport* m_pExportPlugin;

//��\   ģ�ͱ����ת������
	Matrix3 m_matrix;

//��\   ģ�����Ƽӹ���
	CtranslateFileName m_translateFile;

//��\   ���ڴ����NODE������
#ifdef _UGUNICODE
	const TCHAR *m_pNodeName;
#else
	TCHAR *m_pNodeName;
#endif
	

//��\   ���ڴ����NODE������
	INode *m_pNode;

//��\  ����ʱ�����ò���������ÿ��ģ�;������У�z�᲻���У���ԭ����ֵ����zֵ����Ȼ��ͳһ�ƶ������ֵ��
	double m_dX;
	double m_dY;
	double m_dZ;

//��\   ��ʶ�Խڵ�Ĳ����Ƿ���ϡ�
	bool m_bEnd;
	
//��\   ��ǰ�ڵ�����ơ�
	UGC::UGString m_strCurrentNodeName;

//��\   ��������������Ϣ��
	int m_nEndFlagInt;

//��\   ���ڴ����NODE����������
	Point3 m_pntNodeCoodinate;

	//��\   ģ�͵���ת��
	Point3 m_pntNodeRotate;

	//��\   ģ�͵�������
	Point3 m_pntNodeScale;

//��\   �ļ���׺��
	UGC::UGString m_strExt;

//��\   ����ģ�ʹ�����ɵ���ʱСģ��
	std::list <INode*> m_tempSmallModels;

//��\   ��ǰģ����Ϣ
	ModelProp m_modelInfo;

//��\   ����������
	ClassDesc* m_pExportClsDes;

	UGC::UGbool m_bIsBIM;

	ObjectEntry * m_pHead;

	std::map<UGC::UGString,UGC::UGString> m_mapModelToSGM;

	UGC::UGString m_strTexDest;
};

#endif
