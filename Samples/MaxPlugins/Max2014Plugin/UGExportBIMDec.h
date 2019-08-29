//UGExportBIMDec.h: plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class ����BIM���������Ϣ��
//!  \details ��������3dmaxͨѶ���࣬�ӿ���3dmax�ṩ��
//!  \author ljz��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifndef UGExportBIMDec_H
#define UGExportBIMDec_H
#include "iparamb2.h"
#include "UGBIMExporter.h"
//���෽�������ο�MAXSDK������Max�������н����Ľṹ Class_ID��Class_IDר�ŵ���������ȡ�����������3dsMax��װ�����ṩ
class UGExportBIMDec:public ClassDesc2{
public: 
	int IsPublic(){ return TRUE; }

	void* Create(BOOL loading = FALSE) {return new UGC::UGBIMExporter;} 

	const TCHAR* ClassName(){ return _U("SuperMapMenuDec"); }

	SClass_ID SuperClassID(){ return SCENE_EXPORT_CLASS_ID; } 

	Class_ID ClassID(){ return Class_ID(0x69e348c, 0x4f661e5b); }

	const TCHAR* Category(){ return _U("SuperMap"); }

};

#endif