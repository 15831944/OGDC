
// OGDC__XML+OSGToUDB.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



// COGDC__XMLOSGToUDBApp:
// �йش����ʵ�֣������ OGDC__XML+OSGToUDB.cpp
//
using namespace std;
class COGDC__XMLOSGToUDBApp : public CWinApp
{
public:
	COGDC__XMLOSGToUDBApp();
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern COGDC__XMLOSGToUDBApp theApp;