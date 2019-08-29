
// UGBIMExporter.h: plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class ������BIM�Ĳ���ࡣ
//!  \details ��3DMAX����ȡ���ݣ����ɹ�˾֧�ֵ���άģ�ͣ�����Ϊ����࣬DoExport����������Ҫ�ĺ������ڽ��е���ʱʹ�õ�MAX�����õĽӿڡ�
//!  \author sunye��
//!  \attention 3DMax���������mapChannel��Ĭ�ϵ�1����ΪDiff��ͨ����������Ϊ3DMAX��SDK���ܵĹ��ڶ��������ʹ����ʾ�Ķ����������һЩì��
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#include "max.h"
#include "stdmat.h"
#include "Stream/UGFileStream.h"
#include <map>
#include <list>
#include "Base3D/UGNode.h"
#include "UGMaxModelProcess.h "
#include "UGMtlToNode.h"
#include "Base3D/UGRenderOperationGroup.h"
#include "Base3D/UGModelNodeShells.h"
#include "UGMaxProcessBar.h"
#include "OGDC/OgdcDataSource.h"
#include "OGDC/OgdcProviderManager.h"
namespace UGC
{
	using namespace std;
	struct MeshParamInfos
	{
		UGString strID;
		UGint mtlID;
		std::vector<UGuint> indexs;
		std::vector<UGfloat> verts;
		std::vector<UGfloat> colors;
		std::vector<UGfloat> texCoords;
		UGbool bTwoSided;
	};
	class UGBIMExporter : public SceneExport 
	{
		//friend INT_PTR CALLBACK BIMExporterProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	public:
		UGBIMExporter();
		~UGBIMExporter();	
		int				ExtCount();					// Number of extensions supported                     // TRUE if generating extra verts for mismatched UV coords
		const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		const TCHAR *	AuthorName();				// ASCII Author name
		const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		const TCHAR *	OtherMessage1();			// Other message #1
		const TCHAR *	OtherMessage2();			// Other message #2
		unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
		void			BeforeExport(Interface *i);
		void			WriteNodes(UGNode& rootNode ,MtlToNode& mtlToNode);
		void			WriteAnimation(std::list<INode*>& nodeInScene,UGFileStream& fStream,std::map<INode*,UGString>& nodeToString,Interface *ip);
		int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options);	// Export file
		BOOL			SupportsOptions(int ext, DWORD options);
		//���Ϸ�������SceneExport���ɶ����ĺ���

		//------------------------------------------------------------------------------------
		//��Max�в���ת����UGMaterial����д����
		void			WriteMtl(Mtl *mtl,UGFileStream& fStream);
		//�� \����һ��UGMESH
		//�� \nodeTex ����max�е�һ���ڵ�
		//�� \mtlID UGMeshʹ�õĲ���ID
		//�� \mtlToNode �Բ�����֯�����ݽṹnode�б�
		//�� \����һ��UGMESH�б�
		MeshParamInfos WriteMesh(NodeMultiTex*  nodeTex,UGint mtlID,MtlToNode& mtlToNode,Mtl* std = NULL);
		//�� \�ڲ��Ż�ʹ�ã����������㹲���Ƿ��Ƿ�Ҫ����һ��������붥������
		//�� \����һ������ֵ���������-1��˵��Ҫ����ö��㣬�����ֱ�ӷ�������ֵ����
		UGint			NeedAddVertAttribute(UGint faceIndex,UGint vertIndex,Mesh& mesh,std::map<UGint,UGint>&oldToNewPos,std::map<UGint,UGint>&oldToNewTex,std::map<UGint,UGint>&oldToNewMultiTex,int nSecondID,UGint size);
		//�� \�����µĶ�������Ҫ����Ĳ���
		void			WriteIndex(std::vector<UGuint>&indexs,std::vector<UGfloat>&verts,std::vector<UGfloat>&colors,std::vector<UGfloat>&texCoords,UGint faceIndex,UGint vertIndex,Mesh &mesh,INode* pNode,std::list<int>& mapIDList,Mtl* std = NULL);
		//�� \����������Ϣ
		//�� \pMapNode UGC���Ľڵ㣬��Ҫ���й��������ĸ�
		//�� \pNode max�еĽڵ㣬��Դ���ݣ���Ҫ���п���ת���Ľڵ�
		//�� \nodeToString �ڵ㵽���Ƶ�ӳ�䣬������Ϣ��Ҫmesh��Ӧ�����ƣ������ĸ��ڵ���
		void            BuildNodeTree(UGNode* pMapNode,INode* pNode,std::map<INode*,UGString>& nodeToString);
	
		//! \brief ����S3MB����
		int ExportS3MB(const TCHAR *name, ExpInterface *ei, Interface *i);

		//! \brief ����S3MB����
		int ExportUDB(const TCHAR *name, ExpInterface *ei, Interface *i);

#pragma region ���ݲ㵼��ģ������
		UGbool UGBIMExporter::ReadModelData(ExpInterface *ei, Interface *inf, UGC::UGModelGeode* pGeode);
		UGModelSkeleton* UGBIMExporter::BuildSkeleton(MeshParamInfos& meshInfo,vector<UGint> &isDDS);
		void ProcessRefernceNode(UGModelGeode* pGeode);
#pragma endregion

		UGModelMaterial* BuildMaterial(Mtl *mtl, UGbool bIsTwoSide,std::vector<UGint> &isDDS);

		//! \brief ��ȡ��������
		UGTextureData* GetTextureData(UGString& strTexPath);

		//! \brief ����ģ��LOD��Ϣ
		void SetLodInfo(ModelLOD& lodInfo);

		//! \brief ��������Node
		void SetRefernceNode(std::vector<INode *>& vecNode);

		UGbool SaveS3MB(UGString strFilePath);

		//! \brief ������ģ�����ݼ�
		UGbool ExportModelDataset(ExportParameter para,std::map<UGC::UGString, int> m_mapId);

		UGbool ExportCADDataSet(ExportParameter para);

		//! \brief �������ȡģ�����ݼ�
		OGDC::OgdcDatasetVector* GetModelDatasetVector(OGDC::OgdcDataSource* pDatasource,ExportParameter para);

		UGString MaterialHashFunc(UGPass* pPass);

		//! \brief �����Ƿ񵼳�������ɫ
		void SetIsExportMaterialColor(UGbool bIsExport);

		//! \brief �����Ƿ񵼳�����
		void SetIsExportNormal(UGbool bIsExport);

		//! \brief ���ý�����
		void SetMaxProgressBar(UGMaxProcessBar* pMaxProcessBar);

	private:
		//! \�����ֶ�����
		UGString m_strModelName;
		UGString m_strParentName;
		UGString m_strId;

		//�� \�Ƿ񵼳�����
		BOOL m_bExportAnimation;

		//�� \��ǰ�������������ID
		UGint m_nCurrentMeshID;

		std::map<INode*,UGString> m_NodeIndexMap;
		UGint timeStart;

		//�� \Դ����·��
		UGString m_strTexPath;

		//�� \Ŀ������·��
		UGString m_strDestTexPath;

		//�� \��Χ��ֵ
		UGVector3d vecMax,vecMin;

		BOOL m_bShowPrompts;

		//����ID�Ŷ�Ӧ��ͨ��ID��ͨ��ID��Ӧ����UGMesh�ж�Ӧ����������洢˳��
		std::map<int,std::list<int>> m_mtlIDToChannels;

		//���ڵ����Ĳ���ID��
		int m_mtlIDNow;

		//��־�Ƿ���ԭ��Index���wangxinhe Ϊ��ʹ���������ݼ���ȷ 20120607
		UGbool m_bIsExportVertexNormal;

		//! \brief �����б�
		std::map<int,std::vector<UGfloat>> m_multiTexList;

		//! \brief LOD��Ϣ
		ModelLOD m_LodInfo;

		//! \brief �Ƿ񵼳�������ɫ
		UGbool m_bIsExportMaterialColor;

		//! \brief �Ƿ񵼳�����
		UGbool m_bIsExportNormal;

		std::vector<INode*> m_vecNode;

		//! \brief ���ݲ�ָ��
		UGModelGeode* m_Geode;

		//! \brief �洢��Ҫ������ģ��
		std::vector<UGModelGeode*> m_ModelGroup;

		//! \brief ������
		UGMaxProcessBar* m_pMaxProcessBar;
	};
}

