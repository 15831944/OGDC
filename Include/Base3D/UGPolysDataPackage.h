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

#include "Base3D/UGReindexer.h"
#include "Base3D/UGBoundingBox.h"
#include "Toolkit/UGReferenced.h"
#include "Toolkit/UGRefPtr.h"
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
	typedef std::vector<UGPolyIndices> UGPolysIndices;

	//! \brief �������顣
	typedef UGVector3d UGPolysPoint;
	typedef std::vector<UGPolysPoint> UGPolysPoints;

	//! \brief ��ά����Polys�ṹ�е�λ����Ϣ��
	typedef std::vector<UGPosition2> UGPolysPointPosition;
	typedef std::vector<UGPolysPointPosition> UGPolysPointPositions;

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
		//! \brief ��ȡ��������(ֻ��)��
		const UGPolysIndices& GetIds() const;

		//! \brief ��ȡ��������(ֻ��)��
		const UGPolysPoints& GetPts() const;

		//! \brief ��ȡ������Polys��λ����Ϣ(ֻ��)��
		const UGPolysPointPositions& GetPtPositions() const;

		//! \brief ��ȡ����(ֻ��)��
		const UGVector3d& GetPt(UGuint id) const;

		//! \brief ��ȡ����(���¶�����������Ч)��
		UGVector3d& GetPtOfMutability(UGuint id);

		//! \brief ����������
		UGuint GetNumIds(UGuint iPolyId) const;

		//! \brief ����������
		UGuint GetNumPts() const;

		//! \brief ���ݰ�����������
		UGuint GetNumPolysIds() const;
		
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

		//! \brief ��ȡ��չλ��
		const std::vector<UGdouble>& GetExt(const UGPosition2& pos) const;


		//! \brief �������ݴ���
	public:
		//! \brief ����任��
		//! \param m4 [in] �任����
		void MatrixTransform(const UGMatrix4d& m4);


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

		//! \brief ���������ݰ���
		mutable UGPolys m_polys;

		//! \brief �������ݰ���
		mutable UGPolysIndices m_ids;
		mutable UGPolysPoints m_pts;
		mutable UGPolysPointPositions m_pps;

		//! \brief ���ݰ���Χ�С�
		mutable UGBoundingBox m_boundingbox;

		//! \brief ���ġ�
		mutable UGVector3d m_baryCenter;
	};

	//! \brief ����ṹ��
	//! \remark �����������ꡢ�����������Ϣ��
	struct UGPolyPoint
	{
		//! \brief �������顣
		UGVector3d vertex;

		//! \brief �������ꡣ
		UGUVWs uvws;

		//! \brief �������ԡ�
		UGAttribute iAttribute;

		//! \brief ��ά����(x, y, z), w0, w1, w2 ...
		std::vector<UGdouble> ext;

		//! \brief ������ɫc0, c1, c2 ...
		std::vector<UGuint> color;

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
			ext		= pt.ext;
			color	= pt.color;
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
			ext		= pt.ext;
			color	= pt.color;
			return *this;
		}

		const UGVector3d& GetVector3d() const { return vertex; }
		UGVector3d& GetVector3d() { return vertex; }
		UGVector3d GetVector2d() const { return UGVector3d(vertex.x, vertex.y, 0); }
		UGPoint2D GetPoint2D() const { return UGPoint2D(vertex.x, vertex.y); }
		UGPoint3D GetPoint3D() const { return UGPoint3D(vertex.x, vertex.y, vertex.z); }

		UGbool IsEqual2D(const UGPolyPoint& pt) const { return GetVector2d() == pt.GetVector2d(); }
		UGbool IsEqual2D(const UGVector3d& v3) const { return GetVector2d() == UGVector3d(v3.x, v3.y, 0.0); }
		UGbool IsEqual2D(const UGPoint2D& p2) const { return GetPoint2D() == p2; }
		UGbool IsEqual2D(const UGPoint3D& p3) const { return GetPoint2D() == UGPoint2D(p3.x, p3.y); }

		UGbool IsEqual3D(const UGPolyPoint& pt) const { return GetVector3d() == pt.GetVector3d(); }
		UGbool IsEqual3D(const UGVector3d& v3) const { return GetVector3d() == v3; }
		UGbool IsEqual3D(const UGPoint2D& p2) const { return GetPoint3D() == UGPoint3D(p2.x, p2.y, 0.0); }
		UGbool IsEqual3D(const UGPoint3D& p3) const { return GetPoint3D() == p3; }
	};
}

#endif // !defined(AFX_UGPOLYSDATAPACKAGE_H__6DE128A0_500E_4791_9255_4F0CA58E98C3__INCLUDED_)