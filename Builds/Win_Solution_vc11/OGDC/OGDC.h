#if !defined(__UGC_OGDC_H__)
#define __UGC_OGDC_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//OGDC С�汾��
#define OGDCVERSION 10324

#include "../Element/Element.h"

#ifdef _DEBUG
	#pragma message("�Զ����Ӷ�̬�� SuOGDCd.dll ...")
	#pragma comment(lib,"SuOGDCd.lib") 

#else
	#pragma message("�Զ����Ӷ�̬�� SuOGDC.dll ...") 
	#pragma comment(lib,"SuOGDC.lib") 
#endif

#endif //__UGC_OGDC_H__