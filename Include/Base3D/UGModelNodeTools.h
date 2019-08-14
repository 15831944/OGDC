#pragma once

#include "Base3D/UGMesh.h"
#include "Base3D/UGModelNode.h"

namespace UGC
{
class UGModelPagedLOD;
class UGModelNode;

class BASE3D_API UGModelNodeTools
{
public:
	//! \brief ���캯��
	UGModelNodeTools();

	~UGModelNodeTools();

public:
	//! \brief ���ϵ�ģ�ͽṹ����ʵ��(����Animation)
	//! \brief ��������ʵ��
	//! \brief arryMeshes[in]
	//! \brief arrMaterials[in]
	//! \brief pModelNode[in/out]
	//! \brief nGeoID[in] �����ID��Ϊ�˸��Ǽ�������
	static UGbool MakeModelNodeFromModelDataInfo(UGArray<UGMesh*>& arryMeshes, 
		UGArray<UGMaterial*>& arrMaterials, UGModelNode* pModelNode, const UGint nGeoID=0);

	//! \brief ����m_pntScale m_pntRotate m_pntPos�������
	//! \brief �� ����+ModelNode=UGGeoModelPro
	static UGMatrix4d GetLocalMatrix(const UGPoint3D& pntPos, const UGPoint3D& pntScale, \
		const UGPoint3D& pntRotate, const UGbool bSpherePlaced);

	//! \brief �Ƚ������Ǽ��Ƿ�һ��
	//! \brief �жϲ����������㡢�������ߵ�����
	static UGbool IsSame(UGModelSkeleton* pSkeleton1, UGModelSkeleton* pSkeleton2);

	//! \brief ��ModelNode����LOD��
	//! \brief arrModelNodes��0->N �ɾ�ϸ���ֲ�
	//! \brief ȡarrModelNodes[i]���ϸ��������ΪpModelModel��LOD
	static UGbool SetModelLODs(UGModelNode* pModelNode, \
		UGArray<UGModelNode*> arrModelNodes, UGArray<UGdouble> arrLODScales);

	//! \brief ��ModelNode ����LOD �ĿǶ�
	static void BuildLODShell(UGModelNode* pModelNode, const UGint nLODCount, UGModelEM* pEM=NULL);
	//! \brief Patchδ���ص�����£���EM��ȡ��Χ
	static UGBoundingSphere GetPatchBounds(UGModelEM* pEM, UGModelPagedPatch* pPatch);

	//! \brief �Ǽ��Ƴ��ظ��㣬���ɴ����Ե����������������ã�
	static UGint RemoveDuplicateVertex2(UGModelNode* pModelNodeSrc, UGModelNode* pModelNodeDes);

	//! \brief �Ǽ��Ƴ��ظ��㣬���ɴ����Ե���������Revit������ã�
	static UGint RemoveDuplicateVertex2(UGModelSkeleton* pSkeleton);

	//! \brief ��������ת�ֲ�����
	static void VertexSphere2Local(UGVertexDataPackageExact* pVertexPack, UGPoint3D &pntCenter);

	//! \brief vec��������ת��pntCenterΪ���ĵľֲ�����
	static UGVector3d VertexSphere2Local(const UGVector3d& vec, const UGPoint3D& pntCenter);

	//! \brief vec��������ת��pntCenterΪ���ĵľֲ�����
	static UGVector3d VertexSphere2Local(const UGVector3d& vec, const UGMatrix4d& matDest);

	//! \brief ���Patch��FileName
	static void ClearPatchFileName(UGModelNode* pModelNode);

	//! \brief ����ModelNode��mat���ú��BBox�����������Ƚ�
	static UGBoundingBox ComputeExtremZ(UGModelNode* pModelNode, UGMatrix4d& mat, UGbool b2Shpere);
	static UGBoundingBox ComputeExtremZ(UGModelPagedPatch* pPatch, UGMatrix4d& mat, UGbool b2Shpere);
	static UGBoundingBox ComputeExtremZ(UGModelGeode* pGeode, UGMatrix4d& mat, UGbool b2Shpere);

private:
	//! \brief MeshתSkeleton
	static UGModelSkeleton* MakeSkeletonFrom(UGMesh* pMesh, const UGString strSkeletonTag);

	//! \brief תMaterial3D
	static void MakeMaterialFrom(UGMaterial* pMaterial, PolygonFrontFace pff, UGint nDiffuseColorCount, \
		UGModelMaterial*& pMaterial3D, std::vector<UGModelTexture*>& vecTexture);

	//! \brief �Ƚ���������������Ƿ�һ��
	template<typename VertexPackage, typename TVertex>
	static UGbool IsSame(VertexPackage* pVertexPack1, \
		VertexPackage* pVertexPack2, UGdouble dbTolerance)
	{
		if(pVertexPack1->m_nVertexDimension != pVertexPack2->m_nVertexDimension ||
			pVertexPack1->m_nVerticesCount != pVertexPack2->m_nVerticesCount ||
			pVertexPack1->m_nNormalCount != pVertexPack2->m_nNormalCount ||
			pVertexPack1->m_nNormalDimension != pVertexPack2->m_nNormalDimension ||
			pVertexPack1->m_nVertexColorCount != pVertexPack2->m_nVertexColorCount ||
			pVertexPack1->m_nSecondVertexColorCount != pVertexPack2->m_nSecondVertexColorCount)
		{
			return FALSE;
		}
		for(UGint i = 0; i < SMSCN_MAX_TEXTURE_COORD_SETS; i++)
		{
			if(pVertexPack1->m_TexCoordCount[i] != pVertexPack2->m_TexCoordCount[i])
			{
				return FALSE;
			}
		}

		//����
		if(! UGModelNodeTools::CompareValue<TVertex>(pVertexPack1->m_pVertices, \
			pVertexPack2->m_pVertices, pVertexPack1->m_nVerticesCount, \
			pVertexPack1->m_nVertexDimension, dbTolerance))
		{
			return FALSE;
		}

		//����
		if(! UGModelNodeTools::CompareValue<UGfloat>(pVertexPack1->m_pNormals, \
			pVertexPack2->m_pNormals, pVertexPack1->m_nNormalCount, \
			pVertexPack1->m_nNormalDimension, dbTolerance))
		{
			return FALSE;
		}	

		//������ɫ
		if(! UGModelNodeTools::CompareValue<UGuint>(pVertexPack1->m_pVertexColor, \
			pVertexPack2->m_pVertexColor, pVertexPack1->m_nVertexColorCount))
		{
			return FALSE;
		}
		if(! UGModelNodeTools::CompareValue<UGuint>(pVertexPack1->m_pSecondVertexColor, \
			pVertexPack2->m_pSecondVertexColor, pVertexPack1->m_nSecondVertexColorCount))
		{
			return FALSE;
		}

		//��������
		for(UGint i = 0; i < SMSCN_MAX_TEXTURE_COORD_SETS; i++)
		{
			UGfloat* pTexCoords1 = pVertexPack1->m_pTexCoords[i];
			UGfloat* pTexCoords2 = pVertexPack2->m_pTexCoords[i];
			if(pTexCoords1 == NULL)
			{
				continue;
			}

			UGint nDim = pVertexPack1->m_nTexDimensions[i];
			if(! UGModelNodeTools::CompareValue<UGfloat>(pTexCoords1, pTexCoords2, \
				pVertexPack1->m_TexCoordCount[i], nDim, dbTolerance))
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	//! \brief �Ƚ���������
	static UGbool IsSame(UGIndexPackage* pIndexPack1, UGIndexPackage* pIndexPack2);

	template<typename TType>
	static UGbool CompareValue(TType* pValue1, TType* pValue2, \
		UGint nCount, UGint nDim=1, UGdouble dbTolerance=0.0)
	{
		if(typeid(TType) == typeid(float) ||
			typeid(TType) == typeid(double))
		{
			for(UGint i=0; i<nCount; i++)
			{
				for(UGint j=0; j<nDim; j++)
				{
					if(!UGEQ(pValue1[nDim*i+j], pValue2[nDim*i+j], dbTolerance))
					{
						return FALSE;
					}
				}
			}
		}
		else
		{
			for(UGint i=0; i<nCount; i++)
			{
				for(UGint j=0; j<nDim; j++)
				{
					if(pValue1[nDim*i+j] != pValue2[nDim*i+j])
					{
						return FALSE;
					}
				}
			}
		}
		return TRUE;
	}
};

}
