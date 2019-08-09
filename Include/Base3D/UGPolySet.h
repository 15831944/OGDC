// UGPolySet.h: interface for the PolySet class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGPolySet.h
//!  \brief ����������ģģ�ͽṹ��
//!  \details �ļ���ϸ��Ϣ��
//!  \author ����ɡ�
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGPOLYSET_H__F8C91F88_9FBD_40F7_AB5D_17220764D627__INCLUDED_)
#define AFX_UGPOLYSET_H__F8C91F88_9FBD_40F7_AB5D_17220764D627__INCLUDED_
// {F8C91F88-9FBD-40F7-AB5D-17220764D627}

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base3D/UGPolysDataPackage.h"
#include "Base3D/UGPlane.h"
#include "Base3D/UGModelNode.h"

namespace UGC
{
	class UGTINPoint;

	//! \brief ���������ԡ�
	typedef std::pair<UGuint, UGuint> UGIndexPair;
	typedef std::vector<UGIndexPair> UGIndexPairs;

	//! \brief ������Ϊ������������ְ���
	typedef std::list<std::pair<UGVector3d, UGPolyList> > UGPolysPackage;

	//! \brief ����μ��ϡ�
	//! \attention UGPolySet����洢͹����Ρ�
	class BASE3D_API UGPolySet
	{
	public:
		//! \brief ���캯���� 
		UGPolySet(UGuint nDimension = 3);

		//! \brief �������캯����
		UGPolySet(const UGPolySet& copy);

		UGPolySet& operator=(const UGPolySet& other);

		//! \brief ����������
		virtual ~UGPolySet();

		//! \brief ��ơ�
		// \brief ��ȸ������ݰ���
		virtual UGPolySet* Copy() const;
		virtual UGPolySet& Copy(const UGPolySet& ps);

		//! \brief ǳ���ơ�
		//! \remark �������ݰ�ָ�롣
		virtual UGPolySet* ShallowCopy() const;
		virtual UGPolySet& ShallowCopy(const UGPolySet& ps);

		//! \brief ���Ʋ�����
		//! \remark ���������ݰ�ָ�롣
		virtual UGPolySet* CopyParam() const;
		virtual UGPolySet& CopyParam(const UGPolySet& ps);

		//! \brief �����尼͹����(��ά)��
		enum Type { unknown = -1, concave = 0, convex = 1 };
		//! \brief ��ȡ�����尼͹����(��ά)��
		Type GetType() const { return m_eType; }
		//! \brief ���ö����尼͹����(��ά)��
		void SetType(Type type) { m_eType = type; }
		//! \brief �Ƿ�Ϊ͹������(��ά)��
		UGbool IsConvex() const { return m_eType == convex; }

		//! \brief ���ơ�
		void SetName(const UGString& strName) { m_strName = strName; }
		const UGString& GetName() const { return m_strName; }

		//! \brief ���á�
		virtual void Reset();

		//! \brief ��մ洢���ݡ�
		virtual void Clear();

		//! \brief ����μ��ϴ洢��ģ������ά�ȡ�
		UGuint GetDimension() const { return m_nDimension; }
		void SetDimension(UGuint nDimension) { m_nDimension = nDimension; }

		//! \brief ��Ƭ������
		void SetFragments(UGuint nFragments) { m_nFragments = nFragments; }
		UGuint GetFragments() const { return m_nFragments; }

		//! \brief ����LOD�л����ء�
		static UGdouble CalculateSwitchPixels(
			UGdouble dBoundingSphereRadius,
			UGdouble dBottomRadius, 
			UGuint nFragments, UGuint nPixelCount = 5);

		//! \brief ��������������ࡣ
		UGPrimitiveParam& GetPrimitiveParam() { return m_priParam; }
		const UGPrimitiveParam& GetPrimitiveParam() const { return m_priParam; }
		void SetPrimitiveParam(const UGPrimitiveParam& param) { m_priParam = param; }

		//! \brief ������ͼ�����ࡣ
		UGUVWMapParam& GetUVWMapParam() { return m_uvwParam; }
		const UGUVWMapParam& GetUVWMapParam() const { return m_uvwParam; }
		void SetUVWMapParam(const UGUVWMapParam& param) { m_uvwParam = param; }

		//! \brief ģ�Ͷ������͡�
		void SetCoordsType(UGCoordinatesType type) { m_eCoordsType = type; }
		UGCoordinatesType GetCoordsType() const { return m_eCoordsType; }

		//! \brief �����������ꡣ
		UGbool IsGenerateMappingCoords() const { return m_bGenerateMappingCoords; }
		UGbool GetGenerateMappingCoords() const { return m_bGenerateMappingCoords; }
		void SetGenerateMappingCoords(UGbool bGenerateMappingCoords) { m_bGenerateMappingCoords = bGenerateMappingCoords; }

		//! \brief �Ƿ����ɷ��ߡ�
		UGbool IsGenerateNormal() const { return m_bGenerateNormal; }
		UGbool GetGenerateNormal() const { return m_bGenerateNormal; }
		void SetGenerateNormal(UGbool bGenerateNormal) { m_bGenerateNormal = bGenerateNormal; }

		//! \brief �Ƿ�������ɫ��
		UGbool IsGenerateColor() const { return m_bGenerateColor; }
		UGbool GetGenerateColor() const { return m_bGenerateColor; }
		void SetGenerateColor(UGbool bGenerateColor) { m_bGenerateColor = bGenerateColor; }

		//! \brief �Ƿ�zֵ��Ϊ���Բ��������㡣
		UGbool IsZValAsAttribute() const { return m_bZValAsAttribute; }
		void SetZValAsAttritute(UGbool bZValAsAttribute) { m_bZValAsAttribute = bZValAsAttribute; }

		//! \brief �Ƿ���w�ֶΡ�
		UGbool HasW() const { return m_bHasW; }
		void SetW(UGbool bHasW) { m_bHasW = bHasW; }

	public:
		//! \brief Spherical_LonLat -> Spherical_Cartesian��
		UGbool LonLatToCartesian();

		//! \brief Spherical_Cartesian -> Spherical_LonLat��
		UGbool CartesianToLonLat();

		//! \brief Spherical_ENU -> Spherical_LonLat��
		UGbool ENUToLonLat();

		//! \brief Spherical_LonLat -> Spherical_ENU��
		UGbool LonLatToENU(
			const UGVector3d& vPosition, 
			const UGVector3d& vScale = UGVector3d::UNIT_SCALE, 
			const UGVector3d& vRotate = UGVector3d::ZERO);

		//! \brief Spherical_ENU -> Spherical_Cartesian��
		UGbool ENUToCartesian();

		//! \brief Spherical_Cartesian -> Spherical_ENU��
		UGbool CartesianToENU(
			const UGVector3d& vPosition, 
			const UGVector3d& vScale = UGVector3d::UNIT_SCALE, 
			const UGVector3d& vRotate = UGVector3d::ZERO);

		//! \brief Spherical_LonLat -> Pseudo_Cartesian��
		UGbool LonLatToPseudoCartesian(UGdouble dFactor = GLOBAL_RADIUS);

		//! \brief Pseudo_Cartesian -> Spherical_LonLat��
		UGbool PseudoCartesianToLonLat(UGdouble dFactor = GLOBAL_RADIUS);

		//! \brief Spherical_ENU -> Pseudo_Cartesian��
		UGbool ENUToPseudoCartesian(UGdouble dFactor = GLOBAL_RADIUS);

		//! \brief Pseudo_Cartesian -> Spherical_ENU��
		UGbool PseudoCartesianToENU(
			const UGVector3d& vPosition, 
			const UGVector3d& vScale = UGVector3d::UNIT_SCALE, 
			const UGVector3d& vRotate = UGVector3d::ZERO,
			UGdouble dFactor = GLOBAL_RADIUS);

		//! \brief Ellipsoidal_ENU -> Spherical_LonLat��
		UGbool EllipsoidalENUToLonLat();

		//! \brief Spherical_LonLat -> Ellipsoidal_ENU��
		UGbool LonLatToEllipsoidalENU(
			const UGVector3d& vPosition, 
			const UGVector3d& vScale = UGVector3d::UNIT_SCALE, 
			const UGVector3d& vRotate = UGVector3d::ZERO);

		//! \brief Local_Cartesian -> Global_Cartesian��
		UGbool CartesianToGlobalCartesian();

		//! \brief Global_Cartesian -> Local_Cartesian��
		UGbool GlobalCartesianToCartesian(
			const UGVector3d& vPosition, 
			const UGVector3d& vScale = UGVector3d::UNIT_SCALE, 
			const UGVector3d& vRotate = UGVector3d::ZERO);

	public:
		//! \brief ����档
		void BeginSurface();
		void EndSurface();

		//! \brief ��Ӷ��㡣
		void AddVertex(const UGPolyVertex& v);
		void AddVertices(const UGPolyVertices& arrPts);

		//! \brief �Ƿ����
		UGbool IsError() const;
		void RollBack();

		//! \brief ����档
		void BeginFacet();
		void EndFacet();

		//! \brief ������ڵ�������
		void AddFacetId(UGPolyIndex id);
		void AddFacet(const UGPolyIndices& arrIds);
		void AddFacets(const UGPolyFacets& arrFacets);

		//! \brief ��ȡ��������
		UGUVWs& GetTexCoords(const UGPosition2& pos);

		//! \brief ��ȡ��������չλ��
		std::vector<UGdouble>& GetRealExt(const UGPosition2& pos);

		//! \brief ��ȡ��������չλ��
		std::vector<UGuint>& GetIntegerExt(const UGPosition2& pos);

	public:
		//! \brief ��ȡ���ݰ��е�����������
		const UGPolyFacets& GetFacets() const;

		const UGPolysDataPackage* GetPolysDataPackage() const;

		UGbool IsOrient() const;
		void SetOrient(UGbool bOrient);

		//! \brief ��ȡ���ݰ��еĶ������
		const UGPolyVertices& GetPts() const;
		UGPolyVertex& GetPtOfMutability(UGPolyIndex id);
		const UGPolyVertex& GetPt(UGPolyIndex id) const;

		//! \brief ��ȡ������Polys��λ����Ϣ��
		const UGPolyVertexPositions& GetPtPositions() const;

		//! \brief ��ȡ���ݰ��ж���������
		UGuint GetNumPts() const;

		//! \brief ��ȡ���ݰ���������������
		UGuint GetNumFacetsIds() const;

		//! \brief ��ȡ���ݰ��ж��������������
		UGuint GetNumPolysPts() const;

		//! \brief ��ȡ���ݰ��еĶ��������ݡ�
		const UGPolys& GetPolys() const;
		UGPolys& GetPolysOfMutability();

		//! \brief ��ȡ��������
		const UGUVWs& GetTexCoords(const UGPosition2& pos) const;

		//! \brief ��ȡ��������չ�ֶ�
		const std::vector<UGdouble>& GetRealExt(const UGPosition2& pos) const;

		//! \brief ��ȡ��������չ�ֶ�
		const std::vector<UGuint>& GetIntegerExt(const UGPosition2& pos) const;

		//! \brief ��ȡ���洢�Ķ����������
		UGuint GetNumPolys() const;

		//! \brief ���洢�Ķ���������Ƿ�Ϊ�ա�
		UGbool IsEmpty() const;

		//! \brief �Ƿ�����У����
		UGbool IsSanitized() const { return m_bSanitized; }

		//! \brief ��������У��״̬(��ά)��
		void SetSantized(UGbool bSantized) { m_bSanitized = bSantized; }

		//! \brief �Ƿ����ǻ���
		UGbool IsTriangulated() const { return m_bTriangulated; }

		//! \brief �������ǻ�״̬��
		void SetTriangulated(UGbool bTriangulated) { m_bTriangulated = bTriangulated; }

	public:
		//! \brief ׷��Ĭ�϶���Ρ�
		void AppendPoly();

		//! \brief ׷�Ӷ����
		//! \param poly [in] ����Ρ�
		void AppendPoly(const UGPoly& poly);

		//! \brief ׷�Ӷ��㡣
		//! \param x [in] ��������X������
		//! \param y [in] ��������Y������
		//! \param z [in] ��������Z������
		//! \param uvws [in] �������ꡣ
		//! \param iAttribute [in] �������ԡ�
		void AppendVertex(
			const UGdouble& x, 
			const UGdouble& y, 
			const UGdouble& z,
			const UGUVWs& uvws = UGUVWs(),
			const UGAttribute& iAttribute = UGAttribute());

		//! \brief ׷�Ӷ��㡣
		//! \param vertex [in] �������ꡣ
		//! \param uvws [in] �������ꡣ
		//! \param iAttribute [in] �������ԡ�
		void AppendVertex(
			const UGVector3d& vertex, 
			const UGUVWs& uvws = UGUVWs(), 
			const UGAttribute& iAttribute = UGAttribute());

		//! \brief ׷�Ӷ��㡣
		//! \param pt [in] ����ṹ��
		void AppendVertex(const UGPolyPoint& pt);

		//! \brief ���붥�㡣
		//! \param x [in] ��������X������
		//! \param y [in] ��������Y������
		//! \param z [in] ��������Z������
		//! \param uvws [in] �������ꡣ
		//! \param iAttribute [in] �������ԡ�
		void InsertVertex(
			const UGdouble& x, 
			const UGdouble& y, 
			const UGdouble& z,
			const UGUVWs& uvws = UGUVWs(), 
			const UGAttribute& iAttribute = UGAttribute());

		//! \brief ���붥�㡣
		//! \param vertex [in] �������ꡣ
		//! \param uvw [in] �������ꡣ
		//! \param iAttribute [in] �������ԡ�
		void InsertVertex(
			const UGVector3d& vertex, 
			const UGUVWs& uvws = UGUVWs(), 
			const UGAttribute& iAttribute = UGAttribute());

		//! \brief ���붥�㡣
		//! \param pt [in] ����ṹ��
		void InsertVertex(const UGPolyPoint& pt);

		//! \brief ׷�Ӷ���μ��ϡ�
		void Append(const UGPolySet& ps);

		//! \brief ׷�Ӷ������Ρ�
		void AppendPolys(const UGPolys& polys);

	public:
		//! \brief ƽ�ơ�
		//! \param vecTranslation [in] ƽ��������
		void Translate(const UGVector3d& vOffset);
		void Translate(const UGdouble& x, const UGdouble& y, const UGdouble& z);

		//! \brief ��ת��
		//! \param vecNormal [in] Ŀ��ƽ�淨������
		//! \attention ��������Ϊ��λ������
		void Rotate(const UGVector3d& vNormal);
		void Rotate(const UGVector3d& vToNormal, const UGVector3d& vFromNormal);

		//! \brief ���š�
		//! \param vecScale [in] ���Ų�����
		void Scale(const UGVector3d& vScale);
		void Scale(const UGdouble& x, const UGdouble& y, const UGdouble& z);

		//! \brief ����
		//! \param normal [in] �������������
		void Mirror(const UGPlane& plane);

		//! \brief ��ת��
		void Reverse(UGbool bSplitFirst = TRUE);

		//! \brief λ������
		void SetPosition(const UGVector3d& vPos) { m_vPosition = vPos; }
		void SetPosition(UGdouble dX, UGdouble dY, UGdouble dZ) { m_vPosition = UGVector3d(dX, dY, dZ); }
		const UGVector3d& GetPosition() const { return m_vPosition; }
		UGVector3d& GetPosition() { return m_vPosition; }

		//! \brief ��������
		void SetScale(const UGVector3d& vScale) { m_vScale = vScale; }
		void SetScale(UGdouble dX, UGdouble dY, UGdouble dZ) { m_vScale = UGVector3d(dX, dY, dZ); }
		const UGVector3d& GetScale() const { return m_vScale; }
		UGVector3d& GetScale() { return m_vScale; }

		//! \brief ��ת����
		void SetRotate(const UGVector3d& vRotate) { m_vRotate = vRotate; }
		void SetRotate(UGdouble dX, UGdouble dY, UGdouble dZ) { m_vRotate = UGVector3d(dX, dY, dZ); }
		const UGVector3d& GetRotate() const { return m_vRotate; }
		UGVector3d& GetRotate() { return m_vRotate; }

		//! \brief ���ö���μ��Ͼ���
		//! \param matTransform [in] ģ�;���
		void Transform(const UGMatrix3d& matTransform);
		void Transform(const UGMatrix4d& matTransform);

		//! \brief ��ȡ�Ѿ����ǻ���ģ�Ͷ����������
		//! \param pVertexDataPackage [out] ģ�Ͷ������顣
		//! \param arrIndexPackage [out] ģ��������
		//! \param bSimple [in] �Ƿ񾫼򶥵����顣
		//! \attention �������pVertexDataPackage����ΪNULL��
		void GetTriMesh(UGVertexDataPackage* pVertexDataPackage, UGArray<UGIndexPackage*>& arrIndexPackage) const;
		void GetTriMesh(UGVertexDataPackageExact* pVertexDataPackage, UGArray<UGIndexPackage*>& arrIndexPackage) const;

		void GetTriMesh(std::vector<UGTINPoint>& arrPts, std::vector<UGuint>& arrIds) const;

		UGbool FromTriMesh(const UGVertexDataPackage* pVertexDataPackage, const UGArray<UGIndexPackage*>& arrIndexPackage);
		UGbool FromTriMesh(const UGVertexDataPackageExact* pVertexDataPackage, const UGArray<UGIndexPackage*>& arrIndexPackage);

		UGbool FromTriMesh(const std::vector<UGTINPoint>& arrPts, const std::vector<UGuint>& arrIds, UGbool bHasUV = FALSE, UGbool bIgnoreInvalid = FALSE);

		//! \brief ����ϸ�֡�
		//! \param dGranularity [in] ϸ�����ȣ���γ�Ȱ�������ƽ�����갴�ס�
		//! \return -1�������0����δ�޸ģ�1�������޸ġ�
		UGOperationResult ComputeLineSubDivision(UGdouble dGranularity = DTOR);
		UGOperationResult ComputeRegionSubDivision(UGdouble dGranularity = DTOR);
		UGOperationResult ComputeTINSubDivision(UGdouble dGranularity = DTOR);

		//! \brief �����ȡ�
		//! \param dGranularity [in] �����ȣ���������
		//! \return -1�������0����δ�޸ģ�1�������޸ġ�
		UGOperationResult ReduceLineSubDivision(UGdouble dGranularity = DTOR);
		UGOperationResult ReduceRegionSubDivision(UGdouble dGranularity = DTOR);
		UGOperationResult ReduceTINSubDivision(UGdouble dGranularity = DTOR);

		//! \brief ��������
		void QuantizeVertices();
		
		//! \brief ���ǻ������塣
		UGbool Tessellate();

		//! \brief ���ǻ��ռ��е�ƽ�����Ρ�
		UGbool TessellateFace();

		//! \brief ��Լ���ߵ��ʷ�(��ά)��
		//! \param arrIndex [out] �����ʷֺ������ֵ��
		//! \param arrVertice [in / out] �������飬��Լ�����ཻ������»ᶼ���ӵ㡣
		//! \param idsEdge [in] ����Լ���ߵĶ���������
		static UGbool FreeDelaunay(
			std::vector<UGuint>& arrIndex,
			UGPoly& arrVertice, 
			const std::vector<UGuint>& idsEdge);
		static UGbool FreeDelaunay(
			std::vector<UGuint>& arrIndex,
			UGPoly& arrVertice, 
			const UGIndexPairs& idsEdgePairs = UGIndexPairs());

		//! \brief ����ģ�Ͷ����������������μ��ϡ�
		//! \param pVertexDataPackage [in] ģ�Ͷ������顣
		//! \param arrIndexPackage [in] ģ��������
		//! \attention ���ص�ָ����Ҫ���û��ͷţ����������ڴ�й¶��
		static UGPolySet* Make(const UGVertexDataPackage* pVertexDataPackage, const UGArray<UGIndexPackage*>& arrIndexPackage);
		static UGPolySet* Make(const UGVertexDataPackageExact* pVertexDataPackage, const UGArray<UGIndexPackage*>& arrIndexPackage);

		//! \brief �ɱ߽���ڲ����Ƶ㹹���պ��塣
		//! \param vecBorderPt [in] ��߽�㣬��ʱ��˳��
		//! \param vecInnerPt [in] �ڲ��㡣
		//! \param dZ [in] ���ɱպ����zֵ�߶ȡ�
		//! \return ���ؿ��ٽ�ģģ�ͽṹָ�롣
		static UGPolySet* Make(const UGdouble& dZ, UGPoly& vecBorderPt, const UGPoly& vecInnerPt = UGPoly());

		//! \brief �ɱ߽���ڲ����Ƶ㹹����������
		//! \param vecBorderPt [in] ��߽磬��ʱ��˳��
		//! \param vecInnerPt [in] �ڲ����Ƶ㡣
		//! \return ���ؿ��ٽ�ģģ�ͽṹָ�롣
		static UGPolySet* Make(const UGPoly& vecBorderPt, const UGPoly& vecInnerPt = UGPoly());

		//! \brief ��TIN���������������������
		static UGPolySet* Make(const std::vector<UGTINPoint>& arrPts, const std::vector<UGuint>& arrIds, UGbool bHasUV = FALSE, UGbool bIgnoreInvalid = FALSE);

		//! \brief ����ģ��UGModelNode����ٽ�ģģ�͵��໥ת����
		//! \remark ����bHighPrecision��ʾ�Ƿ���ø߾��ȣ�TRUE��ʾ����double˫���ȣ�FALSE��ʾ����float�����ȡ�
		static UGModelNode* CreateModelNodeFromPolySet(const UGPolySet* pPolySet, UGbool bHighPrecision = TRUE);
		static UGModelGeode* CreateGeodeFromPolySet(const UGPolySet* pPolySet, UGbool bHighPrecision = TRUE);
		static UGModelSkeleton* CreateSkeletonFromPolySet(const UGPolySet* pPolySet, UGbool bHighPrecision = TRUE);

		static UGPolySet* CreatePolySetFromModelNode(/*const */UGModelNode* pModelNode);
		static UGPolySet* CreatePolySetFromPatch(UGModelPagedPatch* pPatch);
		static UGPolySet* CreatePolySetFromGeode(UGModelGeode* pGeode);
		static UGPolySet* CreatePolySetFromSkeleton(/*const */UGModelSkeleton* pSkeleton, const UGMatrix4d& mGeodeTrans = UGMatrix4d());
		static UGPolySet* CreatePolySetFromROGeometry(/*const */UGRenderOperationGeometry* pGeometry, const UGMatrix4d& mGeodeTrans = UGMatrix4d());

		UGbool FromSkeleton(UGModelSkeleton* pSkeleton);
		UGbool ToSkeleton(UGModelSkeleton* pSkeleton) const;

		//! \brief �ӵ����д�����������
		static UGPolySet* CreatePolySetFromPtCloud(UGPoly& pts);

	public:
		//! \brief �������졣
		//! \remark �ֳ� ���졢��������XYƽ���ϵĶ�ά���������ָ����������������άģ�͡�
		virtual UGbool LinearExtrude(const UGLinearExtrudeParam& param, UGPolySetObjs& arrObjs);

		//! \brief ��ת���졣
		//! \remark �ֳ� ת�塢��������XYƽ���ϵĶ�ά���������ָ���Ƕ���ת������άģ�͡�
		virtual UGbool RotateExtrude(const UGRotateExtrudeParam& param, UGPolySetObjs& arrObjs);

		//! \brief ��״���졣
		//! \remark �ֳ� ��������XYƽ���ϵĶ�ά���������ָ����·����������άģ�͡�
		virtual UGbool PipeExtrude(const UGPoly& spine, const UGPipeExtrudeParam& param, UGPolySetObjs& arrObjs);

		//! \brief ������
		//! \param pCrossSections [in] ��������档
		//! \param vecLoftPath [in] ����·���㡣
		//! \param bCreateTexCoordight [in] �Ƿ�������������
		//! \param uChamferFactor [in] ƽ��������ȡֵ��Χ[0, 100]��
		//! \param bIsSym [in] FALSEΪ��Բ��ƽ����TRUEΪԲ��ƽ����
		virtual UGbool Loft(
			const std::vector<UGVector3d>& vecLoftPath, 
			UGbool bCreateTexCoord = false,
			UGuint uChamferFactor = 10, 
			UGbool bIsSym = FALSE);

		//! \brief 3D���潨ģ��
		//! \param bParametric [in] �Ƿ��������ģ��
		//! \return 3D����ģ�͡�
		virtual UGbool MakeSurfaceMesh(const UGSurfaceMeshParam& param);

		//! \brief �ںϡ�
		//! \param arrPolySets [in] ���ں϶���
		//! \param bAddPolys [in] �Ƿ������������
		virtual UGbool Blend(
			const UGPolySets& arrPolySets,
			UGbool bAddPolys = TRUE);

		//! \brief ƽ��ͶӰ��
		//! \remark ��XYƽ���ͶӰ��
		virtual UGbool Project(UGbool bCut = FALSE, const UGPlane& pPlane = UGPlane::PlaneXY);

		//! \brief 2.5ά��ͼ��
		virtual UGbool Project2Dot5Map(const UGPlane& plane);

		//! \brief ƽ��ͶӰ�塣
		//! \param vecDirection [in] ͶӰ����/Ͷ���ӵ�λ�á�
		//! \param bPerspective [in] �Ƿ����͸��ͶӰ��
		//! \param projectType [in] ͶӰ��Ľ�����͡�
		//! \return ������Ӱ������Ƿ�ɹ���
		virtual UGbool ShadowVolume(UGVector3d vecDirection, UGShadowVolumeType shadowType, UGProjectResultType projectType = shadowVolume);
		
		//! \brief ��չ�����(��ά)��
		//! \remark ����Զ�ά����Ρ�
		//! \param dOffset [in] ��չ���롣
		//! \param type [in] ���ر��ν����͡�
		virtual UGbool PolygonOffsetting(UGdouble dOffset, UGJoinType type = Miter);

		//! \brief ģ��������
		//! \param dZ [in] ���ɱպ����zֵ�߶ȡ�
		//! \param dTolarence [in] �߶���Χ
		//! \param bHasTextureCoord [in]�Ƿ����߽��������ꡣ
		virtual UGbool Envelop(UGdouble dZ, UGdouble dTolarence = 0.0, UGbool bHasTextureCoord = FALSE);

		//! \brief ����β�������(��ά)��
		UGbool BooleanOperation2D(const UGPolySet& ps, UGBooleanOperationType opType);

	public:
		//! \brief �޸�ģ�͡�
		//! \param pOperationPolys [in] �޸Ĳ������ݡ�
		//! \param params [in] �޸Ĳ�����
		//! \param pClipedTris [in] �Ƿ������޸ĵ�����������
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ����ܡ�
		//! \return failure�������ʧ�ܣ�nothing����ȫ��������success������¡�
		UGOperationResult Operate(
			const void* pOperationPolys,
			const UGOperationParam* pOperationParam,
			UGPolySet* pReserve = NULL,
			UGdouble dTol = EP);

		//! \brief Ӱ��ģ�͡�
		UGOperationResult Effect(
			void* pEffectPolys,
			const UGOperationParam* pEffectParam,
			UGPolySet* pReverse = NULL,
			UGdouble dTol = EP);

	private:
		//! \brief �ü���������
		//! \param arrClipPolys [in] �ü��漯��
		//! \param params [in] �ü�������
		//! \param pClipedTris [in] �Ƿ������ü�������������
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ����ܡ�
		//! \return failure�������ʧ�ܣ�nothing����ȫ��������success�����ֱ�������ȫ���ü�����
		UGOperationResult OperateSurface(
			const UGClipPolys& arrClipPolys,
			const UGClipOperationParam& param,
			UGPolySet* pClipedTris = NULL,
			UGdouble dTol = EP);

		//! \brief �޳���������
		//! \param arrCullPolys [in] �޳��漯��
		//! \param params [in] �޳�������
		//! \param pCulledTris [in] �Ƿ������޳�������������
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ����ܡ�
		//! \return failure�������ʧ�ܣ�nothing����ȫ��������success�����޳��ɹ���
		UGOperationResult OperateSurface(
			const UGPolySets& arrCullPolys,
			const UGCullOperationParam& param,
			UGPolySet* pCulledTris = NULL,
			UGdouble dTol = EP);

	public:
		//! \brief �ü���
		//! \param arrClipPolys [in] �ü��档
		//! \param eKeepType [in] �������͡�
		//! \param eConstraintType [in] Լ�����͡�
		//! \param pClipedTris [in] �Ƿ������ü����������Ρ�
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ��ٶȡ�
		//! \return failure�������ʧ�ܣ�nothing����δ����success������¡�
		UGOperationResult Clip(
			const UGPolySets& arrClipPolys, 
			UGKeepType eKeepType = KeepInside, 
			UGConstraintType eConstraintType = SoftConstraint,
			UGPolySet* pClipedTris = NULL,
			UGdouble dTol = EP);

		//! \brief ѹƽ��
		//! \param arrFlattenPolys [in] ѹƽ�档
		//! \param eKeepType [in] �������͡�
		//! \param eConstraintType [in] Լ�����͡�
		//! \param dFlattenHigh [in] ѹƽ�߶ȡ�
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ��ٶȡ�
		//! \return failure�������ʧ�ܣ�nothing����δ����success������¡�
		UGOperationResult Flatten(
			const UGPolySets& arrFlattenPolys,
			UGKeepType eKeepType = KeepInside, 
			UGConstraintType eConstraintType = SoftConstraint,
			UGdouble dFlattenHigh = 0.0,
			UGdouble dTol = EP);

		//! \brief �滻��
		//! \param arrReplacePolys [in] �滻�档
		//! \param eConstraintType [in] Լ�����͡�
		//! \param pReplacedTris [in] �Ƿ������滻���������Ρ�
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ��ٶȡ�
		//! \return failure�������ʧ�ܣ�nothing����δ����success������¡�
		UGOperationResult Replace(
			const UGPolySets& arrReplacePolys,
			UGConstraintType eConstraintType = SoftConstraint,
			UGPolySet* pReplacedTris = NULL,
			UGdouble dTol = EP);

		//! \brief ��Ƕ��
		//! \param arrMosaicPolys [in] ��Ƕ�档ӲԼ����
		//! \param arrRefOffsettings [in] �ο������档���ɴ����µ���Ƕ��ʱ����ָ����
		//! \param dSlopeRadius [in] �¶Ȼ�����룬��ѡ��Ż����ܡ�
		//! \param arrOffsettings [in] �����档��Լ������ѡ��Ż����ܡ�
		//! \param dTol [in] �ݲӰ�쾫�Ⱥ��ٶȡ�
		//! \return failure�������ʧ�ܣ�nothing����δ����success������¡�
		UGOperationResult Mosaic(
			const UGPolySets& arrMosaicPolys,
			const UGPolySets& arrRefOffsettings = UGPolySets(),
			UGdouble dSlopeRadius = 0.0,
			const UGPolySets& arrOffsettings = UGPolySets(),
			UGdouble dTol = EP);

		//! \brief ��ֵ�߶ȡ�
		//! \param arrInterPolys [in] ����ֵ���ݡ�
		//! \return failure�������ʧ�ܣ�nothing����δ����success������¡�
		UGOperationResult InterpHigh(
			const UGPolySets& arrInterpPolys,
			const UGMatchOperationParam& param) const;

	private:
		//! \brief ���뷶Χ�����������Ρ�
		static UGbool SplitPolysInBounds(UGPolyList& in, UGPolyList& out, const UGPolys& polys, const UGRect2D& bound);

		//! \brief ���ӲԼ���档
		UGbool FitSurface(
			const UGPolySets& arrHardPolys);

		//! \brief �����ӲԼ���档
		UGbool FitSurface(
			const UGPolySets& arrHardPolys,
			const UGPolySets& arrSoftPolys);

		 //! \brief ��ֵ�߶ȡ�
		UGOperationResult InterpHigh(
			std::vector<UGdouble>& vecZValues,
			const std::vector<UGPoint2D>& vecXYValues,
			const UGMatchOperationParam& param,
			const UGRect2D& rcXYBounds = UGRect2D()) const;

	public:
		//! \brief ��ȡ�������ı߽�㡣
		//! \remark ���������������ı߽�㹹����β�պϵı߽�����
		//! \param bHasTextureCoord [in]�Ƿ����߽��������ꡣ
		//! \attention ���صıպϱ߽磬����֮�����û���߼�������ϵ������ʹ�ñ����Էֽ⡣
		UGPolySet* ExtractBorderFromTIN(UGbool bHasTextureCoord = FALSE) const;

		//! \brief �ӵ㼯����ȡ�߽����ڲ��㡣
		static UGbool ExtractPtAttribute(UGPoly& pts, std::vector<UGuint>& borderPtIds, std::vector<UGuint>& innerPtIds);

		//! \brief ��ȡ��·��
		//! \brief edgeIndex [in] �߶ζ˵������Ŷ�Ӧ��
		//! \brief pVert [in] �������顣
		static UGPolySet* ExtractLoops(
			const std::vector<UGuint>& indices, 
			const UGPolyPoint* pPt, 
			UGuint nPtCount, 
			UGbool bHasTextureCoord = FALSE);
		static UGPolySet* ExtractLoops(
			const std::vector<std::vector<UGuint> >& edgeIdsLoops, 
			const UGPolyPoint* pPt, 
			UGuint nPtCount, 
			UGbool bHasTextureCoord = FALSE);

		//! \brief ����Բ�İ뾶��Ƭ����������Բ��
		//! \param pCircle [out] ����Բ�ĵ��
		//! \param dRadius [in] Բ�İ뾶��
		//! \param nFragments [in] Ƭ��������
		//! \attention �������pCircle����ΪNULL����Ҫ�û���������ΪnFragments��С�����顣
		static void GenerateCircle(UGVector3d* pCircle, const UGdouble& dRadius, UGuint nFragments);

		//! \brief ������Բ��뾶��Ƭ������������Բ��
		//! \param pEllipse [out] ������Բ�ĵ��
		//! \param dPriAxis [in] ��Բ��X��İ뾶��
		//! \param dThiAxis [in] ��Բ��Y��İ뾶��
		//! \param nFragments [in] Ƭ��������
		//! \attention �������pEllipse����ΪNULL����Ҫ�û���������ΪnFragments��С�����顣
		static void GenerateEllipse(UGVector3d* pEllipse, const UGdouble& dPriAxis, const UGdouble& dThiAxis, UGuint nFragments);

		//! \brief ����һ��˳�����������ķ��ߡ�
		//! \param p0 [in] �����0��
		//! \param p1 [in] �����1��
		//! \param p2 [in] �����2��
		//! \attention �����˳��˳ʱ�������ʱ�롣
		static UGVector3d CalculateNormal(const UGVector3d& p0, const UGVector3d& p1, const UGVector3d& p2);

		//! \brief �������η���(��ά����ά)��
		//! \brief �����ڶ�ά����ά����Ρ�
		//! \param bZValAsAttribute [in] ����Zֵ�Ƿ���Ϊ���ԡ�
		UGVector3d GetPolyNormal() const;
		static UGVector3d GetPolyNormal(const UGPoly& poly, UGbool bZValAsAttribute = FALSE);

		//! \brief �����������ĵ�(��ά����ά)��
		//! \remark �����ڶ�ά����ά����Ρ�
		UGVector3d GetPolyCenter() const;
		static UGVector3d GetPolyCenter(const UGPoly& poly);

		//! \brief ������ά���������ĵ㡣
		const UGVector3d& GetPolyhedronCenter() const;

		//! \brief �����������ݻ���
		//! \brief ģ���Ǳպ���������塣
		UGdouble GetPolyhedronVolume() const;

		//! \brief ���߹ս��׹�ƽ������
		//! \param vecCurved [out] �׹�ƽ����ĵ㡣
		//! \param vecLine [in] ����·����
		//! \param uFactor [in] ƽ��������ȡֵ��Χ[0, 100]��
		//! \param bIsSym [in] FALSEΪ��Բ��ƽ����TRUEΪԲ��ƽ����
		static void Chamfer(std::vector<UGVector3d>& vecCurved, 
			const std::vector<UGVector3d>& vecLine, 
			UGuint uFactor = 10, 
			UGbool bIsSym = FALSE,
			UGuint nSlice = 5);

		//! \brief �Ƿ�Ϊ�������ߴ����Ķ���Ρ�
		UGbool IsComplexPolygon() const { return m_nDimension == 2 && GetNumPolys() > 1; }

		//! \brief ���ض���ΰ�Χ�С�
		static UGBoundingBox GetBoundingBox(const UGPoly& polygon);

		//! \brief ���ض������Χ�С�
		const UGBoundingBox& GetBoundingBox() const;

		//! \brief ��ȡ�������Χ��
		UGBoundingSphere GetBoundingSphere() const;

		//! \brief ���ط�Χ��
		UGRect2D GetBounds() const;
		static UGRect2D GetBounds(const UGPoly& poly);
		static UGRect2D GetBounds(const UGPolys& polys);

		//! \brief ����������СZֵ��
		void GetHigh(UGdouble& dMax, UGdouble& dMin) const;

		//! \brief �ж�������Χ���Ƿ��ཻ��
		static UGbool IsIntersected(const UGBoundingBox& box1, const UGBoundingBox& box2);

		//! \brief �����ļ���
		UGbool ImportOFF(const UGString& strFileName);
		UGbool ImportDXF(const std::string& path);

		//! \brief �����ļ���
		UGbool ExportOFF(const UGString& strFileName) const;
		UGbool ExportDXF(const std::string& path) const;

		//! \brief ���UGPolySet���ݡ�
		UGbool Save(const std::string& strFilePath) const;

		//! \brief �ж϶����͹����(��ά����ά)��
		//! \remark �����ڶ���ά����Ρ�
		//! \param poly [in] ����Ρ�
		//! \param bZValAsAttribute [in] �Ƿ�zֵ��Ϊ���Բ��������㡣
		//! \return TRUEΪ͹����Σ�FALSEΪ������Ρ�
		static UGbool IsConvex(const UGPoly& poly, UGbool bZValAsAttribute = FALSE);

		//! \brief ��������͹����
		//! \param poly [in] ����Ρ�
		//! \param bZValAsAttribute [in] �Ƿ�zֵ��Ϊ���Բ��������㡣
		static UGPoly CalculateConvexHull(const UGPoly& polygon2d, UGbool bZValAsAttribute = FALSE);

		//! \brief �ж϶���ε�˳��(��ά����ά)��
		//! \param poly [in] ����Ρ�
		//! \param bZValAsAttribute [in] �Ƿ�zֵ��Ϊ���Բ��������㡣
		//! \return ��ʱ�뷵��TRUE��˳ʱ�뷵��FALSE��
		static UGbool IsCCWContour(const UGPoly& poly, UGbool bZValAsAttribute = FALSE);

		//! \brief ����һ��Բ��������Ƭ��
		//! \param dRadius [in] Բ�İ뾶��
		//! \param nResolution [in] �ֱ��ʡ�
		//! \param nFragmentSize [in] Ƭ�δ�С����λ���ס�
		//! \param nFragmentAngle [in] Ƭ�νǶȣ���λ�ȡ�
		static UGuint GetFragments(const UGdouble& dRadius, 
			UGuint nResolution = 0, UGuint nFragmentSize = 2, UGuint nFragmentAngle = 12);

		//! \brief �ռ��е��������Ƿ��ܹ��������Ρ�
		static UGbool IsTriangle(const UGVector3d& p0, const UGVector3d& p1, const UGVector3d& p2);

		//! \brief �ж��������Ƿ��ߡ�
		static UGbool IsColinear(const UGVector3d& p0, const UGVector3d& p1, const UGVector3d& p2);

		//! \brief �ж϶�����Ƿ��档
		static UGbool IsCoplanar(UGPlane& plane, const UGPolys& polys);

		//! \brief ��ȡ����ε����(��ά)��
		static UGdouble GetPolyArea(const UGPoly& poly);
		//! \brief ��ȡ����ε����(��ά)��
		UGdouble GetPolyArea() const;

		//! \brief ���������߶εĽ���(��ά)��
		//! \param resultPt [out] �������ꡣ
		//! \param line0Pt0 [in] �߶�0�Ķ���0���ꡣ
		//! \param line0Pt1 [in] �߶�0�Ķ���1���ꡣ
		//! \param line1Pt0 [in] �߶�1�Ķ���0���ꡣ
		//! \param line1Pt1 [in] �߶�1�Ķ���1���ꡣ
		//! \param bCross [in] �������໥��Խ�Ľ��㡣
		//! \return ���������߶��Ƿ��ཻ��
		//! \remark �������߶��ཻʱ�����صĽ�������������塣
		static UGbool IntersectLineSegs(
			UGVector3d& resultPt,
			const UGVector3d& line0Pt0,
			const UGVector3d& line0Pt1,
			const UGVector3d& line1Pt0,
			const UGVector3d& line1Pt1,
			UGbool bCross = FALSE);

		//! \brief �жϵ��Ƿ����߶���(��ά)��
		static UGbool PointInLine(const UGVector3d& pt, const UGVector3d& linePt0, const UGVector3d& linePt1);

		//! \brief �жϵ��Ƿ��ڶ�����ڲ�(��ά)��
		//! \param pt [in] ���жϵ㡣
		//! \param poly [in] �򵥶���Ρ�
		//! \param bBorderPt [in] ���ڶ���α߽��������ڻ���������, Ϊtrueʱ�������ڣ�Ϊfalseʱ�������⡣
		//! \return ���ڶ�����ڷ���true�����򷵻�false��
		static UGbool PointInPolygon(const UGVector3d& pt, const UGPoly& poly, UGbool bBorderPt = TRUE);
		//! \brief �жϵ��Ƿ��ڶ�����ڲ�(��ά)��
		//! \param pt [in] ���жϵ㡣
		//! \param poly [in] �򵥶���λ��߸��Ӷ����(һ�����а���N��С����С��)��
		//! \param bBorderPt [in] ���ڶ���α߽��������ڻ���������, Ϊtrueʱ�������ڣ�Ϊfalseʱ�������⡣
		//! \return ���ڶ�����ڷ���true�����򷵻�false��
		static UGbool PointInPolygonWithHoles(const UGVector3d& pt, const UGPolys& polys, UGbool bBorderPt = TRUE);

		//! \brief �߶��Ƿ��ڶ����(��ά)��
		static UGbool LineInPolygon(const UGVector3d& startPt, const UGVector3d& endPt, const UGPoly& poly, UGbool bBorderPt = TRUE);
		static UGbool LineInPolygonWithHoles(const UGVector3d& startPt, const UGVector3d& endPt, const UGPolys& polys, UGbool bBorderPt = TRUE);

		//! \brief ���Ƿ��ڶ���α���(��ά)��
		static UGbool PointInPolygonBorder(const UGVector3d& pt, const UGPoly& poly);
		static UGbool PointInPolygonBorderWithHoles(const UGVector3d& pt, const UGPolys& polys);

		//! \brief �߶��Ƿ��ڶ���α���(��ά)��
		static UGbool LineInPolygonBorder(const UGVector3d& startPt, const UGVector3d& endPt, const UGPoly& poly);
		static UGbool LineInPolygonBorderWithHoles(const UGVector3d& startPt, const UGVector3d& endPt, const UGPolys& polys);

		//! \brief �߶��Ƿ�����������(��ά)��
		static UGbool LineDisjointPolygon(const UGVector3d& startPt, const UGVector3d& endPt, const UGPoly& poly);

		//! \brief �ж϶����Poly2�Ƿ���������Poly1(��ά)��
		//! \param poly1 [in] �򵥶����1��
		//! \param poly2 [in] �򵥶����2��
		//! \param bFully [in] �Ƿ��ϸ������
		//! \remark ����ΪTRUEʱ�������1�ĵ���붼�ڶ����2�ڲ����ڱ߽��Ϸ���FALSE��
		static UGbool Poly2ContainsPoly1(const UGPoly& poly1, const UGPoly& poly2, UGbool bFully = FALSE);
		//! \brief �ж϶����Poly2�Ƿ���������Poly1(��ά)��
		//! \param poly1 [in] �����1��
		//! \param poly2 [in] �򵥻��Ӷ����2(���Ӷ����ָһ�����а���N��С����С��)��
		//! \param bFully [in] �Ƿ��ϸ������
		//! \remark ����ΪTRUEʱ�������1�ĵ���붼�ڶ����2�ڲ����ڱ߽��Ϸ���FALSE��
		static UGbool Poly2WithHolesContainsPoly1(const UGPoly& poly1, const UGPolys& polys2, UGbool bFully = FALSE);

		//! \brief �����߶��Ƿ��໥��Խ(��ά)��
		static UGbool LineCrossLine(const UGVector3d& line0Pt0, const UGVector3d& line0Pt1, const UGVector3d& line1Pt0,const UGVector3d& line1Pt1);

		//! \brief �����߶��Ƿ�ƽ��(��ά)��
		static UGbool LineParallelLine(const UGVector3d& line0Pt0, const UGVector3d& line0Pt1, const UGVector3d& line1Pt0,const UGVector3d& line1Pt1);

		//! \brief �߶��Ƿ��Խ�����(��ά)��
		static UGbool LineCorssPoly(const UGVector3d& startPt, const UGVector3d& endPt, const UGPoly& poly, UGbool bBorderPt = TRUE);
		static UGbool LineCorssPolyWithHoles(const UGVector3d& startPt, const UGVector3d& endPt, const UGPolys& polys, UGbool bBorderPt = TRUE);

		//! \brief ������Ƿ��໥��Խ(��ά)��
		static UGbool Poly2CrossPoly1(const UGPoly& poly1, const UGPoly& poly2, UGbool bBorderPt = TRUE);
		static UGbool Poly2WithHolesCrossPoly1(const UGPoly& poly1, const UGPolys& polys2, UGbool bBorderPt = TRUE);

		//! \brief ������Ƿ��໥�Ӵ�(��ά)��
		static UGbool Poly2TouchPoly1(const UGPoly& poly1, const UGPoly& poly2);
		static UGbool Poly2WithHolesTouchPoly1(const UGPoly& poly1, const UGPolys& polys2);

		//! \brief �����Էֽ⣬���뵺����
		//! \attention ���ص����������ָ����Ҫ�û��ͷţ����������ڴ�й©��
		//! \param arrOutPolySet [out] ���طֽ��Ľ����
		void ProtectedDecompose(UGPolySets& arrOutPolySet) const;

		//! \brief ����ռ�㵽�ռ�ֱ�ߵľ��롣
		//! \param linePt0 [in] ֱ���ϵĵ�Pt0��
		//! \param linePt1 [in] ֱ���ϵĵ�Pt1��
		//! \param pt [in] �ռ���һ�㡣
		//! \return ���롣
		static UGdouble Distance(const UGVector3d& linePt0, const UGVector3d& linePt1, const UGVector3d& pt);
		static UGdouble Distance2(const UGVector3d& linePt0, const UGVector3d& linePt1, const UGVector3d& pt);

		//! \brief ���������󹹽���
		virtual void CreateGeometry();

		//! \brief ��ֵ������������һ�����������ֵ��
		//! \remark ��֪��������Ͷ����ϵ����������Լ������ڵ�һ���������꣬��ֵ�����������ꡣ
		static UGPolyPoint Interp(const UGPolyPoint& pt0, const UGPolyPoint& pt1, const UGPolyPoint& pt2, const UGVector3d& v);

		//! \brief ����ͶӰ��������ݡ�
		//! \param pTopPolySet [in] ͶӰ�ϱ��档
		//! \param pBotPolySet [in] ͶӰ�±��档
		//! \param pDesPolySet [in/out] ͶӰ�������ݡ�
		//! \return �����Ƿ񴴽��ɹ���
		static UGbool CreateProjectVolume(UGPolySet* pTopPolySet, UGPolySet* pBotPolySet, UGPolySet* pDesPolySet);

		//! \brief �����������ꡣ
		UGbool GenerateTexCoord();

	private:
		//! \brief �����淨�߽���ְ���
		//! \param package [out] ������ְ����ݡ�
		//! \param dAngle [in] �淨���ݲ������ȡֵ��Χ[0, 180]��
		UGbool SplitPolysPackage(UGPolysPackage& package, UGdouble dAngle = 0.0) const;

		//! \brief �������������Խ���ְ���
		UGbool SplitPolysPackage(std::list<UGPolyList>& package) const;

	public:
		//! \brief ȥ����Ч�����棬ǰ��������Ѿ����ǻ���
		UGOperationResult RemoveInvalidPoly();

		//! \brief �Ƴ��ظ����档
		//! \return ����-1�������ʧ�ܣ�0����û���ظ����棬1�����Ѿ����Ƴ��ɹ���
		UGOperationResult RemoveDuplicatePoly();

		//! \brief У�����ˡ�
		//! \return ����-1�������ʧ�ܣ�0����û�п�У�����棬1�����Ѿ�У���ɹ���
		UGOperationResult CorrectTopology();

	private:
		//! \brief ���Ρ�
		void CreateRectGeometry();

		//! \brief Բ�Ρ�
		void CreateCircleGeometry();

		//! \brief ��Բ�Ρ�
		void CreateEllipseGeometry();
		
		//! \brief �����塣
		void CreateBoxGeometry();

		//! \brief Բ���塣
		void CreateCylinderGeometry();

		//! \brief �����塣
		void CreateEllipsoidGeometry();

		//! \brief ��������
		void CreatePyramidGeometry();

		//! \brief ���塣
		void CreateSphereGeometry();

	private:
		//! \brief ���ӷ�ʽͶӰ�����������ꡣ
		UGbool GenerateBoxMapping();
		UGbool GenerateBoxMappingWithRealMapSize();
		UGbool GenerateBoxMappingApplyInCATIA();

		//! \brief ���η�ʽͶӰ�����������ꡣ
		UGbool GenerateSphericalMapping();

		//! \brief Բ����ʽͶӰ�����������ꡣ
		UGbool GenerateCylindricalMapping();

		//! \brief �������Ʒ�ʽͶӰ�����������ꡣ
		UGbool GenerateShrinkWrapMapping();

		//! \brief ���淽ʽͶӰ�����������ꡣ
		UGbool GenerateFaceMapping();

		//! \brief ƽ�淽ʽͶӰ�����������ꡣ
		UGbool GeneratePlanarMapping();

		//! \brief ����������ֱ����Ϊ�������ꡣ
		UGbool GenerateXYZ2UVWMapping();

	private:
		//! \brief ��ӱߡ�
		void AddSlice(const UGPolySet* pPolygon2d,
			const UGdouble& dRotate1, const UGdouble& dRotate2, 
			const UGdouble& dHeight1, const UGdouble& dHeight2, 
			const UGVector3d& vScale1, const UGVector3d& vScale2, UGbool bClosedRing);

		//! \brief ��ȡ�����������Ϣ
		UGPolyPoint GetSlicePoint(const UGPolyPoint& srcPoint, UGdouble dHeight, const UGMatrix4d& matTran, UGbool bBotom = FALSE);

		//! \brief ���价��
		void FillRing(const UGPoly& outline2d,
			std::vector<UGVector3d>& ring, 
			const UGdouble& dAngel,
			UGbool bFlip) const;

		//! \brief ���ö���Ρ�
		//! \param vControlPoint [in] ���õ����ꡣ
		//! \param vLineTanget [in] ���õ㴦���ߡ�
		void PlacePolygon(const UGVector3d& vControlPoint, const UGVector3d& vLineTanget);

		//! \brief ͶӰ����Ρ�
		//! \param vLoftTanget [in] ����������������
		//! \param vProjPoint [in] ͶӰ�����ꡣ
		//! \param vProjNormal [in] ͶӰ������ͶӰƽ�淨�ߡ�
		void ProjectPolygon(const UGVector3d& vLoftTanget, const UGVector3d& vProjPoint, const UGVector3d& vProjNormal);

		//! \brief ��ȡ��XYƽ���ϵ�ͶӰ�����δ�󲢣���
		//! \param vecDirection [in] ͶӰ����/Ͷ���ӵ�λ�á�
		//! \param bPerspective [in] �Ƿ����͸��ͶӰ��
		//! \return ����ͶӰ�����ݡ�
		UGPolySet* GetProjectPlaneXY(UGVector3d vecDirection, UGShadowVolumeType shadowType) const;

		//! \brief ����ͶӰ�󶥵㾫�ȡ�
		//! \param destPolys [in] ��Ҫ�޸ĵ�ͶӰ���ݡ�
		//! \param srcPolys [in] ԭʼ���յ�ͶӰ���ݡ�
		//! \remark Ŀǰֻ��Project����Ӧ�á�
		void ImproveProjectData(UGPolys& destPolys, const UGPolys& srcPolys) const;

		//! \brief ���ɲ�����������
		//! \param vecShapes [in] ��������漸�������顣
		//! \param param [in] ͼƬ���������
		UGbool GenerateSliceTexCoord(UGPolySets& arrSides);
		
		//! \brief ����ʸ����������������ꡣ
		//! \param poly [in] ��������漸���塣
		//! \param arrTexCoordsOffset [out] ��������������
		//! \param dSubLength [in] ʸ�����ܳ���
		void ComputeTexOffsetAndVertexLength(UGPoly& poly, UGArray<UGdouble>& arrTexCoordsOffset, UGdouble& dSubLength);

		//! \brief ��ȡ���󹫹�������
		static void Copy(UGPolySet& des, const UGPolySet& src, UGbool bShallowCopy = FALSE);
		static void CopyParam(UGPolySet& des, const UGPolySet& src);

	protected:
		//! \brief ����μ��ϴ洢��ģ������ά�ȡ�
		UGuint m_nDimension;

		//! \brief ��Ƭ������
		UGuint m_nFragments;

		//! \brief �Ƿ�����У��(��ά)��
		mutable UGbool m_bSanitized;

		//! \brief �Ƿ����ǻ���
		mutable UGbool m_bTriangulated;

		//! \brief �Ƿ���w���ԡ�
		UGbool m_bHasW;

		//! \brief ģ�Ͷ������͡�
		UGCoordinatesType m_eCoordsType;

		//! \brief ��������������ࡣ
		UGPrimitiveParam m_priParam;

		//! \brief ������ͼ�����ࡣ
		UGUVWMapParam m_uvwParam;

		//! \brief �����尼͹����(��ά)��
		Type m_eType;

		//! \brief λ�ò�ֵ��
		UGVector3d m_vPosition;
		//! \brief ��ת��ֵ��
		UGVector3d m_vRotate;
		//! \brief ���Ų�ֵ��
		UGVector3d m_vScale;

		//! \brief ���ơ�
		UGString m_strName;
		
		//! \brief �Ƿ����ɷ��ߡ�
		UGbool m_bGenerateNormal;

		//! \brief �Ƿ������������ꡣ
		UGbool m_bGenerateMappingCoords;

		//! \brief �Ƿ�������ɫ��
		UGbool m_bGenerateColor;

		//! \brief �Ƿ�zֵ��Ϊ���Բ��������㡣
		UGbool m_bZValAsAttribute;

		//! \brief ���ݰ�������ָ�롣
		UGPolysDataPackageRefPtr m_pPolysDataPackage;
	};
}
#endif // !defined(AFX_UGPOLYSET_H__F8C91F88_9FBD_40F7_AB5D_17220764D627__INCLUDED_)

