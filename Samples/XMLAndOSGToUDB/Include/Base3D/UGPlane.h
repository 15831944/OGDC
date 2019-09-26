// UGPlane.h: interface for the UGPlane class.
//
//////////////////////////////////////////////////////////////////////
/* 
	\file UGPlane.h
	\brief UGC��άƽ����ͷ�ļ���
	\author ������
	\attention
	Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
	All Rights Reserved
	<b>����˵������</b>
	<em>1����һ��˵����</em>
	<em>2���ڶ���˵����</em>
*/

#if !defined(AFX_UGPLANE_H__FB442292_3E4D_49F8_A98D_245EE80AE3B2__INCLUDED_)
#define AFX_UGPLANE_H__FB442292_3E4D_49F8_A98D_245EE80AE3B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base3D/UGPrerequisites3D.h"
#include "Base3D/UGVector3d.h"

namespace UGC 
{
//! \brief ��άƽ���ࡣ
//! \remarks 	
class BASE3D_API UGPlane  
{
public:
	//! \brief Ĭ�Ϲ��캯����
	UGPlane();	
	//! \brief ���캯�����ɷ����������ԭ��ľ��빹���档
	//! \detail ����ͨ��һ��ʽ�Ƶ� Na * X + Nb * Y + Nc * Z + D / N.Length = 0������ vec = (Na, Nb, Nc)�� distance = D / N.Length
	//! \param vec ��ķ�����[in]��
	//! \param fDistance �����ԭ��ľ���[in]��
	UGPlane(const UGVector3d& vec,UGdouble fDistance);

	//! \brief ���������㹹��ƽ��
	UGPlane(const UGVector3d& rkPoint0, const UGVector3d& rkPoint1, const UGVector3d& rkPoint2);

	//! \brief �㷨ʽ
	//! \detail A * (X - X0) + B * (Y - Y0) + C * (Z - Z0) = 0
	//! \param vNormal [in] ��ķ�������
	//! \param vPt [in] ����һ�㡣
	UGPlane(const UGVector3d& vNormal, const UGVector3d& vPt);

	//! \brief �ؾ�ʽ
	//! \detail X / a + Y / b + Z / c = 1
	//! \param dCutA [in] ����X��ؾࡣ
	//! \param dCutB [in] ����Y��ؾࡣ
	//! \param dCutC [in] ����Z��ؾࡣ
	UGPlane(const UGdouble& dCutA, const UGdouble& dCutB, const UGdouble& dCutC);

	//! \brief һ��ʽ
	//! \detail A * X + B * Y + C * Z + D = 0
	//! \param dA [in] һ��ʽ����A��
	//! \param dB [in] һ��ʽ����B��
	//! \param dC [in] һ��ʽ����C��
	//! \param dD [in] һ��ʽ����D��
	UGPlane(const UGdouble& dA, const UGdouble& dB, const UGdouble& dC, const UGdouble& dD);

	//! \brief ����������ʲôҲû�ɡ�
	virtual ~UGPlane();

	//! \brief XYƽ�棬ƽ�淨��(0, 0, 1)
	static const UGPlane PlaneXY;
	//! \brief YZƽ�棬ƽ�淨��(1, 0, 0)
	static const UGPlane PlaneYZ;
	//! \brief XZƽ�棬ƽ�淨��(0, 1, 0)
	static const UGPlane PlaneXZ;

	//! \brief �ж�ƽ���Ƿ���Ч
	UGbool IsValid() const { return m_vNormal != UGVector3d::ZERO; }

	//! \brief ƽ�����ŷ����ƶ�
	//! \remark ����Ϊ����������ƽ�淨�������ƶ�����֮���ظ����ƶ���
	void Translate(const UGdouble& dOffset);

	//! \brief �����ɿռ�һ�㵽���ƽ������
	UGVector3d CalcOffsetVector(const UGVector3d& vPnt) const;

	//! \brief �����ɿռ�һ�㵽���ϵĴ�ֱͶӰ��
	UGVector3d CalcPrjPnt(const UGVector3d& vPt) const;

	//! \brief �жϿռ���Ƿ��ڸ�ƽ����
	UGbool PtInPlane(const UGVector3d& vPt) const;

	//! \brief �ж�ƽ�����߶��Ƿ��ཻ
	UGbool Intersect(const UGPoint3D& pntStart, const UGPoint3D& pntEnd, UGPoint3D& pntIntersect);

	//! \brief �ж�ƽ����ֱ���Ƿ��ཻ
	UGbool Intersect(const UGVector3d& vTangent, const UGPoint3D& pntThru, UGPoint3D& pntIntersect);

	//! \brief ����任��
	void Transform(const UGMatrix4d& mTrans);

	//! \brief ��ȡһ��ʽ4����
	//! \return ���ص�4�����Ƿ���Ч
	UGbool GetParam4(UGdouble& dA, UGdouble& dB, UGdouble& dC, UGdouble& dD) const;

	//! \�ж�����ƽ���Ƿ����
	UGbool operator==(const UGPlane& other) const;
	UGbool operator!=(const UGPlane& other) const;

	UGPlane & operator=(const UGPlane& other);

	//! \brief ������б�׼����
	void Normalize();

	//! \brief ��ȡָ���ĵ㵽��ƽ��ľ���ֵ��
	//! \param vPoint ָ������ά�ռ��еĵ�λ��[in]��
	//! \return ���ؼ�������ľ��롣
	UGdouble GetDistance(const UGVector3d& vPoint) const;

	//! \brief ��ȡ��ķ�������
	const UGVector3d& GetNormal() const;

	//! \brief ������ķ�������
	void SetNormal(const UGVector3d& val);

	//! \brief ��ȡ�����ԭ��ľ��롣
	UGdouble GetPlaneDistance() const;

	//! \brief ���������ԭ��ľ��롣
	void SetPlaneDistance(UGdouble dist);

public:
	//! \brief ���������㹹��ƽ�档
	void Redefine(const UGVector3d& rkPoint0, const UGVector3d& rkPoint1, const UGVector3d& rkPoint2);

	//! \brief �㷨ʽ��
	void Redefine(const UGVector3d& vNormal, const UGVector3d& vPnt);

	//! \brief һ��ʽ��
	void Redefine(const UGdouble& dA, const UGdouble& dB, const UGdouble& dC, const UGdouble& dD);

public:
	//! \��XML�ַ�����ȡ��������
	//! \param strXML XML�ַ���  [in]
	//! \return �����Ƿ�ɹ�
	UGbool FromXML(UGString& strXML);

	//! \����������õ�XML�ַ���
	//! \param strXML XML�ַ���  [in]
	//! \return �����Ƿ�ɹ�
	UGbool ToXML(UGString& strXML);

protected:
	//! \brief ��Ա��ķ�����
	UGVector3d m_vNormal;

	//! \brief ��Ա�����ԭ��ľ���
	UGdouble m_fDistance;
};
}
#endif // !defined(AFX_UGPLANE_H__FB442292_3E4D_49F8_A98D_245EE80AE3B2__INCLUDED_)

