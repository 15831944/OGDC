#pragma once
#include"UGMaxModelProcess.h"
#include "Stream/ugdefs.h"

class TriObject;
class Mtl;
class CtranslateFileName;
//class UGMaxModelProcess;
namespace UGC{
	struct meshIndex
	{
		UGint meshNum;
		std::list<UGString> meshIndexs;
	};
	struct NodeMultiTex
	{
		INode* pNode;
		//��NODEʹ���˸�value��Ӧ�Ĳ��ʣ����ǲ�����pNode�����ڵ�����λ�ã�-1��ʾpNodeʹ�õ��ǷǶ�����
		UGint nIndexMtl;
		//pNode��������������Ƭ���ݣ�deleteTriObj˵��triObj�Ƿ���Ҫɾ��
		TriObject* pTriObj;
		UGbool bDeleteTriObj;
	};
	class MtlToNode:public ITreeEnumProc
	{
		friend class UGSGMExporter;
		friend class UGBIMExporter;
	public:

		MtlToNode(UGint timeStart)
		{
			m_nMeshNum = 0;
			m_nTimeStart = timeStart;
		}
		~MtlToNode();
		virtual int callback( INode *pNode );
		std::map<Mtl*,std::list<NodeMultiTex*>>& GetMtlToNode()
		{
			return mtlToNode;
		}
		int ProcessMtl(Mtl* mtl, INode *pNode, TriObject *pObj, UGbool bDeleteTriObj = FALSE);
	private:
		std::map<Mtl*,std::list<NodeMultiTex*>> mtlToNode;
		UGint m_nMeshNum;
		std::list<INode*> m_NoFatherNodes;
		std::list<INode*> m_animationList;
		/*UGint m_nAnimationNum;*/
		//д�����б�������������������ͬ�����⡣
		std::map<INode*,UGString> m_nodeToNameMap;

		CtranslateFileName m_translateFileName;
		UGint m_nTimeStart;
	};
}
