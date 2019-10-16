#pragma once
#include <string>
#include "Base3D/UGModelNodeEntities.h"
#include "FileParser/UGFileParseToolkit.h"
#include "Base3D/UGModelNodeShells.h"
#include "Geometry3D/UGGeoModelPro.h"
#include "Toolkit/UGImgToolkit.h"
using namespace std;
using namespace UGC;

struct SkeletonInfo
{
	//��������
	double *pVertices;
	//�������(pVertices����size��1/3)
	int nVerticesCount;
	//������������
	int *pVerticesIndex;
	//��������(pVerticesIndex����size)
	int nIndexCount;
	//��������
	float *pNormals;
	//���߸���(pNormals����size��1/3)
	int nNormalCount;
	//��������
	float *pUVs;
	//�����������(pUVS����size��1/2)
	int nUVCount;
	//�Ǽ�����
	string skeletonName;
};
class ModelTools
{
public:
	//�����Ǽ�
	static UGModelSkeleton* buildSkeleton(SkeletonInfo info);
	//��������
	static UGModelMaterial* buildMaterial(UGColorValue3D ugc_color,vector<string>& vecTexturePaths);
	//��������
	static UGModelTexture* buildTexture(string texturePath);
	//����Geodeʵ��
	static UGModelGeode* buildGeodeInstance(UGModelGeode*& pGeode, UGModelSkeleton*& pSkeleton, UGModelMaterial*& pMaterial, vector<UGModelTexture*>& vecTextures);
	//ͨ��Geodeʵ���;��󴴽���ʵ�����ùǼܣ����ʣ������Geode,GeodeName���п���
	static UGModelGeode* buildGeodeRef(UGModelGeode*& pGeodeInstance, UGMatrix4d matrix, UGString m_GeodeName = L"");
	//��Geode��ͬ��LOD��һͬʵ��������
	static vector<UGModelGeode*> buildGeodeRefWithLOD(vector<UGModelGeode*>& vecGeodeInstance, UGMatrix4d matrix, UGString m_geodeName = L"");
	//����ģ��
	static UGGeoModelPro* buildModelPro(vector<UGModelGeode*>vecModelLod,UGPoint3D position,bool isLonLat);
};