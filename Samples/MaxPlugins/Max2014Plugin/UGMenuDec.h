// SuperMapMenuDec.h: plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class �����������ࡣ
//!  \details �����˲������������ɲ���࣬�̳�3DMAX�ṩ��ClassDesc2��
//!  \author sunye��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

#include "max.h"
#include "iparamb2.h"
#include "UGMenuGUP.h" 
//#include "UGSuActions.h"
#ifndef MenuDec_H
#define MenuDec_H

//���෽�������ο�MAXSDK������Max�������н����Ľṹ Class_ID��Class_IDר�ŵ���������ȡ�����������3dsMax��װ�����ṩ
class UGMenuDec:public ClassDesc2{
public: 
	UGMenuDec(HINSTANCE outHInstance){hInstance=outHInstance;}

	int IsPublic(){ return TRUE; }

	void* Create(BOOL loading = FALSE) { return new UGMenuGUP(hInstance);} 

	const TCHAR* ClassName(){ return L"SuperMapMenuDec"; }

	SClass_ID SuperClassID(){ return GUP_CLASS_ID; } 

	Class_ID ClassID(){ return Class_ID(0x153f7592, 0x340a6dfd); }

	const TCHAR* Category(){ return  L"SuperMap"; }

	int NumActionTables(){return 1;}

	ActionTable* GetActionTable(int i){
		UGSuActions suAction(hInstance);
		return suAction.GetActions();
	}
private:
	HINSTANCE hInstance;	
};
#endif
