#include "ModelTools.h"

UGC::UGModelSkeleton* ModelTools::buildSkeleton(SkeletonInfo info)
{
	UGModelSkeleton* pSkeleton = new UGModelSkeleton();
	//����
	UGVertexDataPackageExact* m_pVertexPackExact = new UGVertexDataPackageExact();
	m_pVertexPackExact->SetVertexNum(info.nVerticesCount);
	for (int i = 0; i < info.nVerticesCount * 3; i++)
	{
		m_pVertexPackExact->m_pVertices[i] = info.pVertices[i];
	}
	//��������
	UGIndexPackage* m_pIndexPack = new UGIndexPackage();
	//���info.nVerticesCount == info.nUVCount ������� IT_16BIT_2 �� IT_32BIT_2 �ֱ��ΪIT_16BIT �� IT_32BIT
	//Ȼ�󽫵ڶ����Ϊ m_pIndexPack->SetIndexNum(info.nIndexCount);
	//��ȥ��if��else�еĵڶ���forѭ��
	m_pIndexPack->m_enIndexType = info.nVerticesCount < 65536 ? IT_16BIT_2 : IT_32BIT_2;
	m_pIndexPack->SetIndexNum(info.nIndexCount * 2);
	if (m_pIndexPack->m_enIndexType == IT_16BIT_2)
	{
		for (int i = 0; i < info.nIndexCount; i++)
		{
			m_pIndexPack->m_pIndexes[i] = (UGushort)info.pVerticesIndex[i];
		}
		for (int i =0;i < info.nIndexCount ; i++)
		{
			m_pIndexPack->m_pIndexes[i+info.nIndexCount] = i;
		}
	}
	else
	{
		UGuint* pUintIndex = (UGuint*)m_pIndexPack->m_pIndexes;
		for (int i = 0; i < info.nIndexCount; i++)
		{
			pUintIndex[i] = info.pVerticesIndex[i];
		}
		for (int i =0;i < info.nIndexCount ; i++)
		{
			m_pIndexPack->m_pIndexes[i+info.nIndexCount] = i;
		}
	}
	//����
	if (m_pVertexPackExact != NULL && info.pNormals != NULL)
	{
		if (m_pVertexPackExact->m_pNormals != NULL)
		{
			delete[] m_pVertexPackExact->m_pNormals;
		}
		m_pVertexPackExact->m_pNormals = info.pNormals;
		m_pVertexPackExact->m_nNormalCount = info.nNormalCount;
	}
	//UV
	//Ĭ��UVΪ��ά����
	int nDim = 2;
	if (m_pVertexPackExact != NULL && info.pUVs != NULL)
	{
		m_pVertexPackExact->m_nTexDimensions[0] = nDim;
		m_pVertexPackExact->m_TexCoordCount[0] = info.nUVCount;
		if (m_pVertexPackExact->m_pTexCoords[0] != NULL)
		{
			delete[] m_pVertexPackExact->m_pTexCoords[0];
		}
		m_pVertexPackExact->m_pTexCoords[0] = info.pUVs;
	}
	//���ùǼ�����
	pSkeleton->m_strName.FromStd(info.skeletonName,UGString::Default);
	pSkeleton->SetExactDataPackRef(m_pVertexPackExact, m_pIndexPack);
	pSkeleton->ComputerBoundingBox();
	return pSkeleton;
}

UGC::UGModelMaterial* ModelTools::buildMaterial(UGColorValue3D ugc_color, vector<string>& vecTexturePaths)
{
	UGModelMaterial* pMaterial = new UGModelMaterial();
	UGString materialName;
	UGString Temp;
	vector<UGString> UGtexturePaths;
	for (int i = 0; i < vecTexturePaths.size(); i++)
	{
		Temp.FromStd(vecTexturePaths[i],UGString::Default);
		UGtexturePaths.push_back(Temp);
		materialName += Temp;
	}
	Temp.FromStd(std::to_string(ugc_color.GetAsLongRGBA()),UGString::Default);
	materialName += Temp;
	//���ò��ʵĲ�����������Ψһ
	pMaterial->m_strName = materialName;
	pMaterial->MakeDefault();
	if (pMaterial->getNumTechniques() == 0)
	{
		pMaterial->createTechnique();
	}
	UGTechnique* pTech = pMaterial->getTechnique(0);
	if (pTech->getNumPasses() == 0)
	{
		UGPass* pPassCreate = pTech->createPass();
		//ͨ�������������һ��
		pPassCreate->m_strName = pMaterial->m_strName;
	}
	UGPass* pPass = pTech->getPass(0);
	//������ʱ���Ž���ɫ����
	if (vecTexturePaths.size() == 0)
	{
		//��m_Diffuse�⣬Pass�д��ڸ�����ɫ����
		pPass->m_Diffuse = ugc_color;
	}
	return pMaterial;
}

UGC::UGModelTexture* ModelTools::buildTexture(string texturePath)
{
	UGModelTexture* pTexture = new UGModelTexture();
	UGString strFileName;
	strFileName.FromStd(texturePath,UGString::Default);
	if (pTexture->m_strName.IsEmpty())
	{
		pTexture->m_strName = UGFile::GetTitle(strFileName);
	}
	UGFileParseToolkit::GetTextureData(strFileName, pTexture->m_pTextureData);
	return pTexture;
}

UGC::UGModelGeode* ModelTools::buildGeodeInstance(UGModelGeode*& pGeode, UGModelSkeleton*& pSkeleton, UGModelMaterial*& pMaterial, vector<UGModelTexture*>& vecTextures)
{
	//�Ǽ�����ʰ�
	pSkeleton->SetMaterialName(pMaterial->m_strName);
	vector<UGString> vecTextureNames;
	for (int i = 0; i < vecTextures.size(); i++)
	{
		vecTextureNames.push_back(vecTextures[i]->m_strName);
	}
	//�����������
	pMaterial->SetTextureName(vecTextureNames);
	pGeode->AddSkeleton((UGModelSkeletonPtr)pSkeleton);
	pGeode->AddMaterial((UGModelMaterialPtr)pMaterial);
	if (vecTextures.size() > 0)
	{
		for (int i = 0; i < vecTextures.size(); i++)
		{
			if (vecTextures[i] != NULL)
			{
				pGeode->AddTexture((UGModelTexturePtr)vecTextures[i]);
			}
		}
	}
	return pGeode;
}

UGC::UGModelGeode* ModelTools::buildGeodeRef(UGModelGeode*& pGeodeInstance, UGMatrix4d matrix, UGString m_GeodeName)
{
	UGModelGeode* pGeodeRef = new UGModelGeode();
	pGeodeRef->SetPosition(matrix);
	pGeodeRef->ComputeBoundingBox();
	//���ֿ��п���
	if (!m_GeodeName.IsEmpty())
	{
		pGeodeRef->m_strName = m_GeodeName;
	}
	for (UGint nSkeleton = 0; nSkeleton < pGeodeInstance->GetEntityNames(UGModelEntity::METype::etSkeleton).size(); nSkeleton++)
	{
		//ָ��ͬһ���ã�ʵ�������Ĳ�����
		pGeodeRef->AddSkeleton(pGeodeInstance->GetSkeleton(pGeodeInstance->GetEntityNames(UGModelEntity::METype::etSkeleton)[nSkeleton]));
	}
	for (UGint nTexture = 0; nTexture < pGeodeInstance->GetEntityNames(UGModelEntity::METype::etTexture).size(); nTexture++)
	{
		//ָ��ͬһ���ã�ʵ�������Ĳ�����
		pGeodeRef->AddTexture(pGeodeInstance->GetTexture(pGeodeInstance->GetEntityNames(UGModelEntity::METype::etTexture)[nTexture]));
	}
	for (UGint nMaterial = 0; nMaterial < pGeodeInstance->GetEntityNames(UGModelEntity::METype::etMaterial).size(); nMaterial++)
	{
		//ָ��ͬһ���ã�ʵ�������Ĳ�����
		pGeodeRef->AddMaterial(pGeodeInstance->GetMaterial(pGeodeInstance->GetEntityNames(UGModelEntity::METype::etMaterial)[nMaterial]));
	}
	return pGeodeRef;
}

std::vector<UGModelGeode*> ModelTools::buildGeodeRefWithLOD(vector<UGModelGeode*>& vecGeodeInstances, UGMatrix4d matrix, UGString m_geodeName /*= NULL*/)
{
	vector<UGModelGeode*> vecGeodeRefs;
	for (int i = 0;i<vecGeodeInstances.size();i++)
	{
		vecGeodeRefs.push_back(buildGeodeRef(vecGeodeInstances[i], matrix, m_geodeName));
	}
	return vecGeodeRefs;
}

UGC::UGGeoModelPro* ModelTools::buildModelPro(vector<UGModelGeode*>vecModelLod, UGPoint3D position, bool isLonLat)
{
	if (vecModelLod.size() < 1)
	{
		return NULL;
	}
	UGGeoModelPro* pGeometry = new UGGeoModelPro();
	//���ģ�ͽ��
	UGModelNode* pModelNode = pGeometry->GetModelNode();
	//��ϸ��
	UGModelPagedPatch* pPath = pModelNode->CreatePatch();
	pPath->AddGeode(vecModelLod[0]);

	//Lod��
	if (vecModelLod.size() > 1)
	{
		for (int i = 1; i < vecModelLod.size(); i++)
		{
			UGModelPagedLOD* pPagedLod = pModelNode->AddPagedLOD();
			UGdouble dDistance = UGMIN(1024, 5 * pPath->GetBoudingSphere().GetRadius()*pow(2.0, 4 - i - 1));
			UGModelPagedPatch* pPatchLod = pPagedLod->CreatePagedPatch(dDistance);
			pPatchLod->AddGeode(vecModelLod[i]);
		}
	}
	if (pModelNode->GetSkeletonCount(-1) > 0)
	{
		//����ģ���Ƿ񵼳������泡��
		pGeometry->SetSpherePlaced(isLonLat);
		pGeometry->SetPosition(position);
	}
	return pGeometry;
}
