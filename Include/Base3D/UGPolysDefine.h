// UGPolysDefine.h: interface for the UGPolysDefine class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGPolysDefine.h
//!  \brief ����������ģģ�ͽṹ��
//!  \details �ļ���ϸ��Ϣ��
//!  \author ����ɡ�
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGPOLYSDEFINE_H__6065BF90_B191_4740_AAA0_0CD7AD8D8A50__INCLUDED_)
#define AFX_UGPOLYSDEFINE_H__6065BF90_B191_4740_AAA0_0CD7AD8D8A50__INCLUDED_
// [Guid("6065BF90-B191-4740-AAA0-0CD7AD8D8A50")]

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Toolkit/UGColorValue3DEx.h"
#include "Base3D/UGPrerequisites3D.h"

namespace UGC
{
	//! \brief ģ���������͡�
	enum UGCoordinatesType
	{
		//! \brief �ѿ�������ϵ��
		//! \remark ����Ϊ�ֲ��ѿ�������ϵ������(x, y, z)��
		Cartesian,

		//! \brief ����ENU����ϵ��
		//! \remark �ֲ��ѿ�������ϵ��������ϵ��ϡ�
		ENU, 

		//! \brief ���徭γ�ȼ�����ϵ��
		//! \remark ����Ϊ������ϵ�¾�γ������(lon, lat, high)��
		LonLat,

		//! \brief ������ENU����ϵ��
		//! \remark �ֲ��ѿ�������ϵ����������ϵ��ϡ�
		Ellipsoidal_ENU,

		//! \brief ͶӰ����ϵ��
		Projection,

		//! \brief αֱ������ϵ��
		Pseudo_Cartesian,
	};

	//! \brief �������������͡�
	enum UGPrimitiveType
	{
		no_type,
		pt, line,
		rect, circle, ellipse, region,
		box, cylinder, ellipsoid, pyramid, sphere, polyhedron, tin, solid
	};

	//! \brief ��ģ������
	enum UGBuilderOperation
	{
		no_operation,
		linear_extrude, rotate_extrude, pipe_extrude, loft, blend, polygon_offsetting, straight_skeleton, envelop, builder,
		section_projection, plane_projection, flatten, shadow_volume, clip, mosaic, replace, cull, match
	};

	//! \brief �����������͡�
	enum UGUVWCoordinatesType { U, V, W, UV, VW, WU, UVW };

	//! \brief ������ͼӳ��ģʽ��
	//! \remark ��ģ��ʵ�ʴ�С��ͼ��4��(PLANAR, CYLINDRICAL(CYLINDRICAL_CAP), SPHERICAL��BOX)����ʵ�ʳߴ�7�֡�
	enum UGUVWMappingMode { NOMAP, PLANAR, CYLINDRICAL, CYLINDRICAL_CAP, SPHERICAL, SHRINK_WRAP, BOX, FACE, XYZ2UVW };

	//! \brief �������͡�
	enum UGShadowVolumeType
	{
		//! \brief ̫����
		sunLight, 
		//! \brief ���Դ
		pointLight,
		//! \brief �����
		directLight
		////! \brief �۹��
		//spotLight
	};

	//! \brief ͶӰ��Ľ��������ʽ
	enum UGProjectResultType
	{
		//! \brief �����ϱ���
		topFace,
		//! \brief �����±���
		bottomFace,
		//! \brief ����������
		shadowVolume
	};

	//! \brief �����������͡�
	enum UGBooleanOperationType
	{
		OP_DIFFERENCE,             // Difference                        
		OP_INTERSECTION,              // Intersection                      
		OP_UNION,                  // Union 
		OP_XOR,                     // Exclusive or
		OP_MINKOWSKI,
		OP_HULL
	};

	//! \brief ��������
	enum UGKeepType
	{
		//! \brief �ڲã������ڲ���
		KeepInside,
		//! \brief ��ã������ⲿ��
		KeepOutside
	};

	//! \brief Լ�����͡�
	enum UGConstraintType
	{
		//! \brief ��Լ��������ԭʼ���ݼ��㡣
		SoftConstraint,
		//! \brief ӲԼ�������������ݼ��㡣
		HardConstraint
	};

	//! \brief �νӽ����͡�
	enum UGJoinType
	{
		//! \brief �����νӣ����ӽ�Ϊ���ǡ�
		Square,
		//! \brief Բ���νӣ����ӽ�ΪԲ�ǡ�
		Round,
		//! \brief ֱ���νӣ����ӽ�ֱ����
		Miter
	};

	//! \brief ������
	enum UGPolyPointAttribute
	{
		CommonPt			= 0x00000000, // ��ͨ��
		PtCorner			= 0x00000001, // �ĸ����ϵĵ�
		PtInter			= 0x00000002, // ���ϵĽ���
		PtByEdge			= 0x00000004, // ���ǻ���������ڵ��ڲ���
		PtEdge			= 0x00000008, // ���ϵ�������
		InvalidPt		= 0x00000010, // ��Ч��
		PtInterInvalid	= 0x00000020, // ������Ч�Ľ���
		PtNeedRemove		= 0x00000040, // ��Ҫȥ���ĵ�
		PtEdgeWithSkirt	= 0x00000080, // ��ȹ�ߵıߵ�
		PtEdgeByClip		= 0x00000100, // ���ü����ĵ�
		PtEdgeByBound		= 0x00000200, // Լ���ıߵ�

		SolfConstraintPt	= 0x00000400, // ��Լ����
		HardConstraintPt	= 0x00000800, // ӲԼ����
		ClipPt			= 0x00001000, // �ü���
	};

	struct UGParam
	{
		/* �������� */
	};

	struct UGObject
	{
		/* ������� */
	};

	//! \brief ��������������ࡣ
	struct BASE3D_API UGPrimitiveParam
	{
		UGPrimitiveParam();
		~UGPrimitiveParam();

		//! \brief ���á�
		void Reset();

		//! \brief �������������͡�
		UGPrimitiveType ePrimitiveType;

		//! \brief ģ�͹������͡�
		UGBuilderOperation eBuilderOperation;

		//! \brief ����������Ϣ��
		UGdouble dX, dY, dZ;
		UGdouble dR1, dR2;

		// �������������
		//! \brief nResolution �ֱ��ʡ�
		UGuint nResolution;
		//! \brief nFragmentSize Ƭ�δ�С����λ���ס�
		UGuint nFragmentSize;
		//! \brief nFragmentAngle Ƭ�νǶȣ���λ�ȡ�
		UGuint nFragmentAngle;

		//! \brief �Ƿ񴴽�LOD��
		UGbool bGenerateLOD;

		//! \brief ����һ��Բ��������Ƭ��
		//! \param dRadius [in] Բ�İ뾶��
		//! \param nResolution [in] �ֱ��ʡ�
		//! \param nFragmentSize [in] Ƭ�δ�С����λ���ס�
		//! \param nFragmentAngle [in] Ƭ�νǶȣ���λ�ȡ�
		UGuint GetFragments(UGdouble dRadius);
	};

	//! \brief ������ͼ�����ࡣ
	struct BASE3D_API UGUVWMapParam
	{
		UGUVWMapParam();
		~UGUVWMapParam();

		//! \brief ���á�
		void Reset();

		//! \brief ��ͼ���͡�
		UGUVWMappingMode eMappingMode;

		//! \brief ���������Ƿ���������ϵ����ͼ��С��
		UGbool bRealWorldMapSize;

		//! \brief ������������Ƿ�ʹ������ͼƬʵ�ʳߴ���㡣
		UGbool bRealTexMapSize;

		//! \brief ������������ͨ����
		//! \remark ����[0, SMSCN_MAX_TEXTURE_COORD_SETS - 1]��
		UGuint uMapChannel;

		//! \brief �����������͡�
		UGUVWCoordinatesType eCoordType;

		//! \brief ͶӰģ�ͳ��ȡ���ȡ��߶ȡ�
		//! \remark ������bRealWorldMapSizeΪTRUEʱ�����²�����Ч��
		UGdouble dPrjModelLength;
		UGdouble dPrjModelWidth;
		UGdouble dPrjModelHeight;

		//! \brief ����ͶӰģ�ͳ��ȡ���ȡ��߶��Ƿ����û����塣
		UGbool bPrjLenghByUserDefined;
		UGbool bPrjWidthByUserDefined;
		UGbool bPrjHeightByUserDefined;

		//! \brief UVW����λ�ƾ��롣
		//! \remark ������bRealWorldMapSizeΪTRUEʱ�����²�����Ч��
		UGdouble dUOffset;
		UGdouble dVOffset;
		UGdouble dWOffset;

		//! \brief UVW�����ظ�������
		//! \remark ������bRealWorldMapSizeΪTRUEʱ�����²�����Ч��
		UGdouble dUTiling; // U Tile
		UGdouble dVTiling; // V Tile
		UGdouble dWTiling; // W Tile

		//! \brief UVW�����Ƿ�ת��
		//! \remark ������bRealWorldMapSizeΪTRUEʱ�����²�����Ч��
		UGbool bUFlip;
		UGbool bVFlip;
		UGbool bWFlip;

		//! \brief UVW������ת�Ƕȡ�
		UGdouble dUAngle;
		UGdouble dVAngle;
		UGdouble dWAngle;

		//! \brief �����������
		UGMatrix4d GetTexMatrix() const;
	};

	//! \brief �ֶ����ԡ�
	template<typename T>
	class UGAttributeTemplate
	{
	public:
		UGAttributeTemplate() : m_iAttribute(0) {}
		UGAttributeTemplate(const UGAttributeTemplate<T>& other) { m_iAttribute = other.m_iAttribute; }
		~UGAttributeTemplate() {}

		UGAttributeTemplate(T iAttribute) { m_iAttribute = iAttribute; }

		UGbool operator==(const UGAttributeTemplate<T>& other) const { return m_iAttribute == other.m_iAttribute; }
		UGbool operator!=(const UGAttributeTemplate<T>& other) const { return m_iAttribute != other.m_iAttribute; }

		UGbool Has(T attr) const { return (m_iAttribute & attr) != 0; }
		void Add(T attr) { m_iAttribute |= attr; }
		void Remove(T attr) { m_iAttribute &= ~attr; }

		T Get() const { return m_iAttribute; }
		void Set(T attr) { m_iAttribute = attr; }

	private:
		T m_iAttribute;
	};
	typedef UGAttributeTemplate<UGint> UGAttribute;

	//! \brief α��ֵ
#define PSEUDO_ZERO 0.0001

	//! \brief �����ϵĸ߶ȼ�ֵ
	//! \remark ��������ߵ������������(8848.13��)����������������ɺ���(-11034.0��)
#define GEOGRAPHICAL_MAX_ALTITUDE 9000.0
#define GEOGRAPHICAL_MIN_ALTITUDE -12000.0

	//! \brief �������
	//! \param failure�������ʧ�ܣ������ǲ������⡣
	//! \param nothing����û��δ�����������δ�޸ġ�
	//! \param success������ɹ��������Ѿ��޸ġ�
	enum UGOperationResult
	{
		failure = -1, nothing = 0, success = 1
	};

	class UGPolySet;
	typedef std::vector<UGPolySet*> UGPolySetPtrs;
	typedef std::vector<UGPolySet > UGPolySetObjs;
	typedef UGPolySetPtrs UGPolySets;

	//! \brief �ü��漯��
	struct UGClipPoly
	{
		UGPolySet*			pClipPoly;
		UGPolySet*			pRefSlopePoly;
		UGPolySet*			pSlopePoly;

		UGClipPoly() : pClipPoly(NULL), pRefSlopePoly(NULL), pSlopePoly(NULL) {}
	};
	typedef std::vector<UGClipPoly> UGClipPolys;

	struct UGOperationParam
	{
		virtual UGBuilderOperation GetType() const = 0;
	};

	//! \brief �ü�������������
	struct UGClipOperationParam : public UGOperationParam
	{
		UGBuilderOperation	op;
		UGKeepType			keep;
		UGConstraintType		constraint;
		UGdouble				radius;
		UGColorValue3D		color;

		UGClipOperationParam() : op(clip), keep(KeepInside), constraint(SoftConstraint), radius(0.0) {}

		virtual UGBuilderOperation GetType() const { return clip; }
	};

	//! \brief �޳����������ࡣ
	struct UGCullOperationParam : public UGOperationParam
	{
		UGKeepType			keep;
		UGdouble				minz;
		UGdouble				maxz;

		UGCullOperationParam() : keep(KeepOutside), minz(GEOGRAPHICAL_MIN_ALTITUDE), maxz(GEOGRAPHICAL_MAX_ALTITUDE) {}

		virtual UGBuilderOperation GetType() const { return cull; }
	};

	//! \brief ��������ࡣ
	struct UGLinearExtrudeParam : public UGOperationParam
	{
		//! \brief ��ö��
		enum Face { bottom = 0x1, top = 0x2, side = 0x4 };

		//! \brief ����߶�(��z�᷽��)��ȡֵ��Χ(0, ��)��
		UGdouble dHeight;

		//! \brief �Ƿ�������������
		UGbool bCreateTexCoord;

		//! \brief ��z����ת�ĽǶȣ�ȡֵ��Χ(-��, ��)��
		UGdouble dTwist;

		//! \brief ģ�������������X��Y��������ű�����ȡֵ��Χ(0, ��)��
		UGdouble dScaleX;
		UGdouble dScaleY;

		//! \brief ���������еĲ�����Ƭ����������Ĭ��ֵ���ɣ�ȡֵ��Χ[1, ��)��
		UGuint nSlices;

		//! \brief �Ƿ��һ��
		UGbool bGroup;

		//! \brief �Ƿ���LOD�㼶
		UGbool bHasLOD;

		//! \brief ����ģ��������
		UGAttribute attr;

		UGLinearExtrudeParam() : 
			dHeight(1.0), 
			bCreateTexCoord(FALSE), 
			dTwist(0.0), 
			dScaleX(1.0), dScaleY(1.0), 
			nSlices(1), 
			bGroup(TRUE), 
			bHasLOD(TRUE),
			attr(bottom | side | top) {}

		virtual UGBuilderOperation GetType() const { return linear_extrude; }
	};

	//! \brief ���������ࡣ
	struct UGRotateExtrudeParam : public UGOperationParam
	{
		//! \brief ��ö��
		enum Face { start = 0x1, end = 0x2, ring = 0x4 };

		//! \brief ��ת�Ƕȣ�ȡֵ��Χ[-360, 0) U (0, 360]��
		UGdouble dAngle;

		//! \brief ���������еĲ�����Ƭ����������Ĭ��ֵ���ɣ�ȡֵ��Χ[1, ��)��
		UGuint nSlices;

		//! \brief �Ƿ��һ��
		UGbool bGroup;

		//! \brief �Ƿ���LOD�㼶
		UGbool bHasLOD;

		//! \brief ����ģ��������
		UGAttribute attr;

		UGRotateExtrudeParam() : 
			dAngle(360.0), 
			nSlices(1), 
			bGroup(TRUE), 
			bHasLOD(TRUE),
			attr(ring | start | end) {}

		virtual UGBuilderOperation GetType() const { return rotate_extrude; }
	};

	//! \brief ���������ࡣ
	struct UGPipeExtrudeParam : public UGOperationParam
	{
		//! \brief ��ö��
		enum Face { start = 0x1, end = 0x2, side = 0x4 };

		//! \brief �Ƿ�������������
		UGbool bCreateTexCoord;

		//! \brief �νӽ����͡�
		UGJoinType eJoinType;

		//! \brief ���������еĲ�����Ƭ����������Ĭ��ֵ���ɣ�ȡֵ��Χ[1, ��)��
		UGuint nSlices;

		//! \brief �Ƿ��һ��
		UGbool bGroup;

		//! \brief �Ƿ���LOD�㼶
		UGbool bHasLOD;

		//! \brief ����ģ��������
		UGAttribute attr;

		UGPipeExtrudeParam() : 
			bCreateTexCoord(FALSE), 
			eJoinType(Miter),
			nSlices(1), 
			bGroup(TRUE), 
			bHasLOD(TRUE),
			attr(side | start | end) {}

		virtual UGBuilderOperation GetType() const { return pipe_extrude; }
	};

	//! \brief ƥ������ࡣ
	struct UGMatchOperationParam : public UGOperationParam
	{
		//! \brief �������͡�
		enum Attach { top, bottom };

		//! \brief ���������
		UGdouble dGranularity;

		//! \brief �������͡�
		Attach eAttach;

		UGMatchOperationParam() :
			dGranularity(0.0),
			eAttach(top) {}

		virtual UGBuilderOperation GetType() const { return match; }
	};
}
#endif