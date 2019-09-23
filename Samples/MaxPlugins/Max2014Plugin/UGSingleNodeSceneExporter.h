// UGSingleNodeSceneExporter.h: plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class ��������ĳ����ࡣ
//!  \details ����ֻ����һ���ڵ�ĳ�����Ϊ�˽��е���ģ�͵ĵ��������з�װ�ĳ�����
//!  \author sunye��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

#ifndef UGSingleModelExport_H
#define UGSingleModelExport_H

#include "Max.h"
#include "UGMaxModelProcess.h"
#include "stdmat.h"
#ifdef MAX9_2010
#include "bmmlib.h"
#endif
#include "bitmap.h"
#include "UGMaxProcessBar.h"
#include "UGMaxToolkit.h"
#include "UGMaxLogFile.h"
#include <ilayer.h> 

#define BILLBOARDLAYER _U("BillBoard")
#define REGION3DLAYER _U("Region3D")


//! \һ���ڵ�ĳ�����
class SingleNodeScene:public IScene{
private: INode *node;
public:
#ifdef MAX2016
	int  EnumTree (ITreeEnumProc *proc,bool bIncludeXRef = false){
		if(proc->callback(node)==TREE_ABORT) return 1;
		else return 0;
	}
#else
	int  EnumTree (ITreeEnumProc *proc){
		if(proc->callback(node)==TREE_ABORT) return 1;
		else return 0;
	}
#endif
	void  FlagFGSelected (TimeValue t){}
	void  FlagFGAnimated (TimeValue t){}
	void  FlagFGDependent (TimeValue t, BaseObject *obj){}
	void SetNode(INode *onode){
		node=onode;
	}
};

//! \һ���ڵ�ĵ����ӿ���

class SingleNodeExpInterface: public ExpInterface{
public:
	SingleNodeExpInterface()
	{
		theScene = NULL;
	}

	void InitScene()
	{
		if (!theScene)
		{
			theScene= new SingleNodeScene();
		}
	}

	void ResetIScene(INode *onode)
	{
		((SingleNodeScene* )theScene)->SetNode(onode);
	}

	~SingleNodeExpInterface()
	{
		if (theScene != NULL)
		{
			delete theScene;
			theScene = NULL;
		}
	}
};
//! \brief ��ȡ�������ж��ٸ��ڵ㣬Ϊ�˽�������Ϣ
class CGetNodeNum:public ITreeEnumProc
{
public:
	CGetNodeNum()
	{
		m_nNumNode = 0;
	}
	int callback( INode *node )
	{
		m_nNumNode++;
		INode* pNode = node;
		if(pNode==NULL)return TREE_CONTINUE;
		Object *originObj = pNode->EvalWorldState(0).obj;
		if(!originObj->CanConvertToType(triObjectClassID))return TREE_CONTINUE;
		if(pNode->GetName()==NULL)return TREE_CONTINUE;
		TriObject *obj=(TriObject *)originObj->ConvertToType(0, triObjectClassID);//��objectת��ΪTriObjectָ��

		Mesh mesh=obj->GetMesh();
		if(mesh.numVerts<=0)
		{
			if(originObj!=obj)
				obj->DeleteMe();
			return TREE_CONTINUE;
		}
		mesh.buildBoundingBox();
		Box3 box3 =  mesh.getBoundingBox(&pNode->GetObjectTM(0));
		m_box3 += box3;
		return TREE_CONTINUE;
	}
	int GetNumNode()
	{
		return m_nNumNode;
	}
	Box3 GetBoundingBox()
	{
		return m_box3;
	}
private:
	int m_nNumNode;
	Box3 m_box3;
};
class UGSingleNodeSceneExporter:public ITreeEnumProc
{
public:
	UGSingleNodeSceneExporter() { }
	//! \brief ����������Ĺ��캯��
	//! \param pInModelProcess ָ���������������ĵ���������
	//! \param inStrDest �ļ����ɵ�Ŀ���ַ
	//! \param inTexSrc �������ڵ�·��
	//! \param bCopyTex �Ƿ�Ҫ��������
	UGSingleNodeSceneExporter(UGMaxModelProcess *pInModelProcess,UGC::UGString strTexDest,UGC::UGString strTexSrc, UGC::UGbool bExportAll, UGC::UGbool bCopyTex=TRUE, UGC::UGbool bIsBIM = FALSE);

	void InitParams(UGMaxModelProcess *pInModelProcess,UGC::UGString strTexDest,UGC::UGString strTexSrc,UGC::UGbool bExportAll, UGC::UGbool bCopyTex=TRUE, UGC::UGbool bIsBIM = FALSE);
	//!\ 3DMAX���б����ڵ�ʱ��ִ�еĲ���������ʵ��
	virtual int	callback( INode *pNode );

	//!\ ���ý�����
	void SetProcessBar(UGMaxProcessBar * pMaxProcessBar){m_pMaxProcessBar = pMaxProcessBar;}

	//!\ ���õ�������ģ���ļ��ĵ�����
	void SetModelProcess(UGMaxModelProcess *pInModelProcess){m_pModelProcess=pInModelProcess;}

	//!\ ���õ���ģ�͵������ڵĸ�Ŀ¼
	void SetDirPath(UGC::UGString inFilePath){m_strTexDest=inFilePath;}

	//!\ �������������ƶ���һ��λ��
	void SetModelRelative(double dx, double dy, double dz){ m_pModelProcess->SetXYZ(dx,dy,dz);}

	//!\ ��ȡ������ģ����Ϣ
	UGArray<ModelProp> GetModelsInfo(){return m_pModelProcess->GetModelsInfo();}

	std::map<UGC::UGString,UGC::UGString> GetModel2SGM(){return m_pModelProcess->GetModel2SGM();}

	//!\ ִ�е�������
	void StartExport();
	//!\ BIM����OSGB����
	void ExportOSGB();
	//!\ BIM����DAE����
	void ExportDAE();
	//!\ BIM����S3MB����
	void ExportS3MB();
	//!\ ������ģ�����ݼ�
	void ExportModelDataset(ExportParameter para);

	UGMaxModelProcess *m_pModelProcess;
private:
	void ProcessTexture(Mtl* mtl,UGC::UGString strTexSrc,UGC::UGString strDest);
	
	//! \ ��������ĺ���
	void ReallyCopyTexture(Mtl* mtl);

	//! \ ��������
	void CopyTexture(INode *pNode );
	
	SingleNodeExpInterface myExpInterface;
	UGC::UGString m_strTexDest;
	UGC::UGString m_strTexSrc;
	UGMaxProcessBar * m_pMaxProcessBar;
	//! \ �Ƿ񿽱�����
	UGC::UGbool m_bCopyTexture;
	//!\ ��ʾ�Ƿ���BIM����
	UGC::UGbool m_bIsBIM;
	//!\ ��ʾ�Ƿ�ȫ������
	UGC::UGbool m_bExportAll;
};
#endif
