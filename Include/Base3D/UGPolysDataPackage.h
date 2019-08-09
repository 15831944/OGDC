// UGPolySet.h: interface for the UGPolysDataPackage class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGPolysDataPackage.h
//!  \brief ����������ģģ�Ͷ�����ṹ��
//!  \details �ļ���ϸ��Ϣ��
//!  \author ����ɡ�
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGPOLYSDATAPACKAGE_H__6DE128A0_500E_4791_9255_4F0CA58E98C3__INCLUDED_)
#define AFX_UGPOLYSDATAPACKAGE_H__6DE128A0_500E_4791_9255_4F0CA58E98C3__INCLUDED_
// [Guid("6DE128A0-500E-4791-9255-4F0CA58E98C3")]

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base3D/UGGrid.h"
#include "Base3D/UGBoundingBox.h"
#include "Toolkit/UGReferenced.h"
#include "Toolkit/UGRefPtr.h"
#include "Toolkit/UGSingleton.h"
#include "Base3D/UGPolysDefine.h"

namespace UGC
{
	//! \brief �����ά�����������ꡣ
	//! \remark ��������[0, 3]��
	typedef std::pair<UGuint, UGVector3d> UGTexDimCoord;
	//! \brief �������ڵ�ͨ����������Ϣ��
	//! \remark ��������[0, SMSCN_MAX_TEXTURE_COORD_SETS - 1]��
	typedef std::pair<UGuint, UGTexDimCoord> UGTexChannelCoord;
	//! \brief ��ͨ����������ṹ��
	typedef UGTexChannelCoord UGUVW;
	//! \brief ��ͨ����������ṹ��
	//! \remark ��С����[0, SMSCN_MAX_TEXTURE_COORD_SETS]��
	typedef std::vector<UGUVW> UGUVWs;
	typedef UGUVWs UGTexMapCoords;

	//! \brief ǰ�������ṹ��
	struct UGPolyPoint;

	//! \brief ����� �� һ���ߡ�
	//	typedef std::vector<UGVector3d> UGPoly;
	typedef std::vector<UGPolyPoint> UGPoly;
	//! \brief ��������� �� �����顣
	typedef std::vector<UGPoly> UGPolys;

	//! \brief ������б�
	typedef std::list<UGPoly> UGPolyList;
	typedef std::list<UGPolyPoint> UGPolyPointList;

	//! \brief �������顣
	typedef UGuint UGPolyIndex;
	typedef std::vector<UGPolyIndex> UGPolyIndices;
	typedef std::vector<UGPolyIndices> UGPolyFacets;

	//! \brief �������顣
	typedef UGVector3d UGPolyVertex;
	typedef std::vector<UGPolyVertex> UGPolyVertices;

	//! \brief ��ά����Polys�ṹ�е�λ����Ϣ��
	typedef std::vector<UGPosition2> UGPolyVertexPosition;
	typedef std::vector<UGPolyVertexPosition> UGPolyVertexPositions;

	//! \brief ���ݰ�������ָ�롣
	class UGPolysDataPackage;
	typedef UGRefPtr<UGPolysDataPackage> UGPolysDataPackageRefPtr;

	//! \brief ���ݰ���
	//! \remark ���ݰ��д洢���������ݺͶ������ݰ���
	class BASE3D_API UGPolysDataPackage : public UGReferenced
	{
		//! \brief ���캯��������������
	public:
		UGPolysDataPackage();
		UGPolysDataPackage(const UGPolysDataPackage& package);
		UGPolysDataPackage& operator=(const UGPolysDataPackage& package);

	protected:
		virtual ~UGPolysDataPackage(); 

		//! \brief ����������
	public:
		//! \brief ������ݰ���
		void Clear();

		//! \brief ���ݰ��Ƿ�Ϊ�ա�
		UGbool IsEmpty() const;

		//! \brief ��ȡ��Χ�С�
		const UGBoundingBox& GetBoundingBox() const;

		//! \brief ��ȡ���ĵ㡣
		const UGVector3d& GetBaryCenter() const;

		//! \brief ���������ݡ�
	public:
		//! \brief ��ȡ����������(ֻ��)��
		const UGPolys& GetPolys() const;

		//! \brief ��ȡ����������(���¶���������Ч)��
		UGPolys& GetPolysOfMutability();

		//! \brief ��ȡ���洢�Ķ����������
		UGuint GetNumPolys() const;

		//! \brief �����������е�������
		UGuint GetNumPolysPts() const;

		//! \brief ����/��ȡ���������ݵ���Ч״̬��
		void SetPolysPackageDirty(UGbool bDirty);
		UGbool IsPolysPackageDirty() const;


		//! \brief �������ݡ�
	public:
		//! \brief ��ȡ����������(ֻ��)��
		const UGPolyFacets& GetFacets() const;

		//! \brief ��ȡ��������(ֻ��)��
		const UGPolyVertices& GetPts() const;

		//! \brief ��ȡ������Polys��λ����Ϣ(ֻ��)��
		const UGPolyVertexPositions& GetPtPositions() const;

		//! \brief ��ȡ����(ֻ��)��
		const UGPolyVertex& GetPt(UGPolyIndex id) const;

		//! \brief ��ȡ����(���¶�����������Ч)��
		UGPolyVertex& GetPtOfMutability(UGPolyIndex id);

		//! \brief ������������
		UGuint GetNumFacetIds(UGuint iFacetId) const;

		//! \brief ����������
		UGuint GetNumPts() const;

		//! \brief ���ݰ�����������
		UGuint GetNumFacetsIds() const;
		
		//! \brief ����/��ȡ�������ݵ���Ч״̬��
		void SetDataPackageDirty(UGbool bDirty);
		UGbool IsDataPackageDirty() const;


		//! \brief ���������ݴ���
	public:
		//! \brief ׷�Ӷ���Ρ�
		void AppendPoly();

		//! \brief ׷�Ӷ����
		//! \param poly [in] ����Ρ�
		void AppendPoly(const UGPoly& poly);

		//! \brief ׷�Ӷ��㡣
		//! \param pt [in] ���㡣
		void AppendVertex(const UGPolyPoint& pt);

		//! \brief ���붥�㡣
		//! \param pt [in] ���㡣
		void InsertVertex(const UGPolyPoint& pt);

		//! \brief ׷�Ӷ������Ρ�
		void AppendPolys(const UGPolys& polys);

		//! \brief ��ȡ��������
		const UGUVWs& GetTexCoords(const UGPosition2& pos) const;

		//! \brief ��ȡ��������չλ��
		const std::vector<UGdouble>& GetRealExt(const UGPosition2& pos) const;

		//! \brief ��ȡ��������չλ��
		const std::vector<UGuint>& GetIntegerExt(const UGPosition2& pos) const;


		//! \brief �������ݴ���
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

		//! \brief ��ȡ�㡣
		UGPolyPoint& GetPt(const UGPosition2& pos);

		//! \brief ����任��
		//! \param m4 [in] �任����
		void MatrixTransform(const UGMatrix4d& m4);

		//! \brief ��������ģʽ��
		UGbool IsOrient() const { return m_bOrientDataPackage; }
		void SetOrient(UGbool bOrient) { m_bOrientDataPackage = bOrient; }

		//! \brief ������ݡ�
		void AppendSurface(const UGPolyVertices& arrPts, const UGPolyFacets& arrFacets, const UGPolys& arrPolys = UGPolys());

	public:
		//! \brief ׷�����ݡ�
		void Append(const UGPolysDataPackage* pPackage);


	private:
		//! \brief ������������ݡ�
		void ComputePolysPackage() const;

		//! \brief ���㶥�����ݡ�
		void ComputeDataPackage() const;

		//! \brief �������ݰ�Ԫ���ݡ�
		void ComputePackageMeta() const;

		//! \brief ��ն��������ݡ�
		void ClearPolysPackage();

		//! \brief ��ն������ݡ�
		void ClearDataPackage();

	private:
		//! \brief ���������ݰ��Ƿ���Ч��
		mutable UGbool m_bPolysPackageIsDirty;

		//! \brief �������ݰ��Ƿ���Ч��
		mutable UGbool m_bDataPackageIsDirty;

		//! \brief ������Ƿ��Ѿ�У����
		UGbool m_bOrientDataPackage;

		//! \brief ���������ݰ���
		mutable UGPolys m_polys;

		//! \brief �������ݰ���
		mutable UGPolyFacets m_facets;
		mutable UGPolyVertices m_pts;
		mutable UGPolyVertexPositions m_pvs;

		//! \brief ���ݰ���Χ�С�
		mutable UGBoundingBox m_boundingbox;

		//! \brief ���ġ�
		mutable UGVector3d m_vBaryCenter;
	};

	//! \brief ����ṹ��
	//! \remark �����������ꡢ�����������Ϣ��
	struct UGPolyPoint
	{
		//! \brief �������顣
		UGPolyVertex vertex;

		//! \brief �������ꡣ
		UGUVWs uvws;

		//! \brief �������ԡ�
		UGAttribute iAttribute;

		//! \brief ��������չλ������չ(x, y, z), w0, w1, w2 ...
		std::vector<UGdouble> arrRealExts;

		//! \brief ��������չλ������չ������ɫc0, c1, c2 ...
		std::vector<UGuint> arrIntExts;

		//! \brief ���캯����
		UGPolyPoint() {}

		UGPolyPoint(const UGdouble& x, const UGdouble& y, const UGdouble& z, const UGUVWs& uvws = UGUVWs(), const UGAttribute& iAttribute = UGAttribute())
		{
			vertex = UGVector3d(x, y, z);
			this->uvws = uvws;
			this->iAttribute = iAttribute;
		}

		UGPolyPoint(const UGVector3d& vertex, const UGUVWs& uvws = UGUVWs(), const UGAttribute& iAttribute = UGAttribute())
		{
			this->vertex = vertex;
			this->uvws = uvws;
			this->iAttribute = iAttribute;
		}

		UGPolyPoint(const UGPolyPoint& pt)
		{
			vertex	= pt.vertex;
			uvws		= pt.uvws;
			iAttribute = pt.iAttribute;
			arrRealExts	= pt.arrRealExts;
			arrIntExts	= pt.arrIntExts;
		}

		//! \brief ����������
		~UGPolyPoint() {}

		//! \brief �еȺ�����
		UGbool operator==(const UGPolyPoint& pt) const
		{
			return (vertex == pt.vertex) && (uvws == pt.uvws) && (iAttribute == pt.iAttribute);
		}

		//! \brief �еȺ�����
		UGbool operator!=(const UGPolyPoint& pt) const
		{
			return (vertex != pt.vertex) || (uvws != pt.uvws) || (iAttribute != pt.iAttribute);
		}

		//! \brief ����ȽϺ�����
		UGbool operator < (const UGPolyPoint& pt) const
		{
			return UGReindexerTemplateCompareVec3D<UGdouble>(vertex.x, vertex.y, vertex.z) <
				UGReindexerTemplateCompareVec3D<UGdouble>(pt.vertex.x, pt.vertex.y, pt.vertex.z);
		}

		//! \brief ��ֵ������
		UGPolyPoint& operator=(const UGPolyPoint& pt)
		{
			vertex	= pt.vertex;
			uvws		= pt.uvws;
			iAttribute = pt.iAttribute;
			arrRealExts	= pt.arrRealExts;
			arrIntExts	= pt.arrIntExts;
			return *this;
		}

		const UGVector3d& GetVector3d() const { return vertex; }
		UGVector3d& GetVector3d() { return vertex; }
		UGVector3d GetVector2d() const { return UGVector3d(vertex.x, vertex.y, 0); }
		UGPoint2D GetPoint2D() const { return UGPoint2D(vertex.x, vertex.y); }
		UGPoint3D GetPoint3D() const { return UGPoint3D(vertex.x, vertex.y, vertex.z); }
	};

	// ���湹�������ࡣ
	struct UGSurfaceMeshParam : public UGOperationParam
	{
		//! \brief ��ɢ��������
		std::vector<UGPolyPoint> arrDotMatrix;

		//! \brief �Ƿ���UV������Ϊ�����������
		UGbool bPolarParametric;

		UGSurfaceMeshParam() :
			bPolarParametric(TRUE) {}

		virtual UGBuilderOperation GetType() const { return builder; }
	};

	//! \brief ��������
	template<class DATA_TYPE>
	class UGStreamBuffer : public UGReferenced
	{
		//! \brief ���캯��������������
	public:
		UGStreamBuffer() {}
		virtual ~UGStreamBuffer() {}

	public:
		//! \brief �������͡�
		typedef DATA_TYPE Type;

	public:
		//! \brief ���ݻ��档
		const Type& GetBuffer() const { return m_buffer; }
		Type& GetBuffer() { return m_buffer; }
		void SetBuffer(const Type& buffer) { m_buffer = buffer; }

	protected:
		//! \brief ���ݻ��档
		Type m_buffer;
	};

	template<typename MEMBER_TYPE>
	class UGStreamArrayBuffer : public UGStreamBuffer<std::vector<MEMBER_TYPE> >
	{
	public:
		UGuint GetSize() const { return this->m_buffer.size(); }
		void SetSize(UGuint nSize) { this->m_buffer.resize(nSize); } 
	};


	template<typename MEMBER_TYPE>
	class UGSingletonInstanceRef
	{
	private:
		MEMBER_TYPE* m_pValue;
		UGuint m_nRefCount;

	public:
		explicit UGSingletonInstanceRef(MEMBER_TYPE* pValue) : m_pValue(pValue), m_nRefCount(0) {}
		~UGSingletonInstanceRef()
		{
			if (m_pValue != NULL)
			{
				delete m_pValue; m_pValue = NULL;
			}
		}

	public:
		MEMBER_TYPE* GetValue() const { return m_pValue; }

		void AddRef() { ++m_nRefCount; }
		void DecRef() { --m_nRefCount; }
		UGuint GetRefCount() const { return m_nRefCount; }
	};

	template<typename Key, class Value>
	class UGSingletonInstanceCollection
	{
	public:
		typedef UGSingletonInstanceRef<Value> Instance;
		typedef std::map<Key, Instance*> Collection;
		typedef typename Collection::iterator CollectionIter;

		UGSingletonInstanceCollection() : m_mutex(TRUE) {}
		~UGSingletonInstanceCollection()
		{
			UGAutoLock locker(m_mutex);
			for (CollectionIter iter = m_mapInstances.begin(); iter != m_mapInstances.end(); ++iter)
			{
				Instance* pInstance = iter->second;
				if (pInstance != NULL)
				{
					delete pInstance; pInstance = NULL;
				}
			}
			m_mapInstances.clear();
		}

		Value* GetValue(const Key& key)
		{
			Value* pValue = NULL;
			Instance* pInstance = NULL;
			UGAutoLock locker(m_mutex);
			CollectionIter iter = m_mapInstances.find(key);	
			if (iter != m_mapInstances.end() && iter->second != NULL)
			{	
				pInstance = iter->second;
				pValue = pInstance->GetValue();
			}
			else
			{
				pValue = new Value();
				pInstance = new Instance(pValue);
				m_mapInstances[key] = pInstance;
			}
			pInstance->AddRef();
			return pValue;
		}

		void RemoveValue(const Key& key)
		{
			UGAutoLock locker(m_mutex);
			CollectionIter iter = m_mapInstances.find(key);	
			if (iter != m_mapInstances.end() && iter->second != NULL)
			{
				Instance* pInstance = iter->second;
				pInstance->DecRef();
				if (pInstance->GetRefCount() == 0)
				{
					delete pInstance; pInstance = NULL;
					m_mapInstances.erase(key);
				}
			}
		}

	private:
		Collection m_mapInstances;
		UGMutex m_mutex;
	};
}

#endif // !defined(AFX_UGPOLYSDATAPACKAGE_H__6DE128A0_500E_4791_9255_4F0CA58E98C3__INCLUDED_)