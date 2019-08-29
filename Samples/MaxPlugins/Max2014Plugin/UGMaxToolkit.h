//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief 
//!  \details 
//!  \author zhangshuai��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#if !defined(AFX_UGMAXTOOLKIT_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_)
#define AFX_UGMAXTOOLKIT_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <ShlObj.h>
#include <Stream/ugdefs.h>
#include "Base3D/UGRenderOperationGroup.h"
#include "Base3D/UGCommon3D.h"

#undef SelectFont
#undef SelectBrush
#undef SelectPen

//!  \������������һ���ṹ���
typedef struct exportParameter
{
	UGC::UGbool RemoveDupVertex;
	UGC::UGbool IsPlanar;
	UGC::UGbool IgnoreMaterialColor;
	UGC::UGbool WithoutNormal;
	UGC::UGdouble X;
	UGC::UGdouble Y;
	UGC::UGdouble Z;
	UGC::UGString DatasourceName;
	UGC::UGString DatasetName;
}ExportParameter;
//using namespace UGC;

enum FileType
{
	origin,
	compress
};

class  UGMaxToolkit 
{
public:
	//! \brief �����ļ��жԻ���dialogNameΪ�Ի�������֣�����ѡ��Ľ����
	//! \param dialogName ��������[in]��
	static UGC::UGString GetInputPath(TCHAR* dialogName,int IDC,HWND hDlg,bool setText,TCHAR* pInitialPath =NULL);

	//!  \���е�Ŀ¼Ӧ����б�ܽ�β���ú���ʹĿ¼·������б��
	static void TransStandDir(TCHAR* pDespath);

	//!  \ �ж��ַ����Ƿ�Ϊ�Ϸ������ͺ͸����͡�
	static bool IsInt(LPTSTR intStr);

	static bool IsFloat(LPTSTR floStr);

	//!  \ ����UDB������ֻ��m_arrmodelProp��������ģ������������ģ�ͱ����������Ϣ��
	//!   \cmpathName�ļ�����·����
	//!   \cfileName������׺�����ļ�����
	//!   \m_arrmodelPropģ����Ϣ��
	//!   \longitude ����㾭�ȣ�
	//!   \latitude  �����γ�ȣ�
	//!   \altitude  �����߶ȣ�

	//static void CreateUDB(UGC::UGString cmpathName,UGC::UGString cfileName,UGArray<ModelProp>m_arrmodelProp,double longitude,double latitude,double altitude);

	//static void CreateUDBWithFilePath(UGC::UGString cmpathName,UGC::UGString cfileName,UGArray<ModelProp>m_arrmodelProp,double longitude,double latitude,double altitude);


	//!  \ ɾ������Ŀ¼�����е��ļ���
	//!  \strDeleteDir ������Ŀ¼
	static void DeleteAllMyDirFiles(UGC::UGString strDeleteDir);

	//!  \ ����Բ�����ֱ������ϵ�������ת��Ϊ��γ������� (ע�⣬�߶Ȳ��� wangxinhe 20120607)
	//!   \dLatitude ����㾭�ȣ�
	//!   \dLatitude  �����γ�ȣ�
	//!   \dAltitude  �����߶ȣ�
	//!   \p  ����Ϊֱ������ϵ�����Ϊ��������
	static void CartesianToSphericalD(double dLongitude,double dLatitude,double dAltitude,UGC::UGPoint3D& p);

	//!  \ �Ƿ���C���Ա�־������������
	//!   \strName ��ʶ������
	static bool IslegalName(UGC::UGString strName);
	

	//!  \�Ƿ�����ȷ�ľ�γ�ȱ�ʾ����
	//!   \pStrLonti ����
	//!   \pLati γ��
	static UGC::UGbool IsCorrectSphericalD(char* pStrLonti,char* pLati);


	//!  \��������������������ʵ�������
	//!   \strSrcTexPath Դ�ļ�·��
	//!   \strDesTexPath Ŀ�꿽���ļ�·��
	static void CopyTexture(const UGC::UGString& strSrcTexPath,const UGC::UGString& strDesTexPath);


	//! \brief �����ʶΪˮ�����������б�
	static std::set<UGC::UGString> m_setRegionZ;


	//! \brief �����ʶΪBillBoard����������б�
	static std::set<UGC::UGString> m_setBillboardList;

	static UGC::UGRenderOperationNode::TextureDataInfo* ImageTOTextureDataInfo(UGC::UGString strTex);

	//! \brief
	static UGC::UG3DPixelFormat GlPixelFormat2UG3DFormat(UGC::UGuint osgPixelFormat);


};

#endif //AFX_UGMAXTOOLKIT_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_
