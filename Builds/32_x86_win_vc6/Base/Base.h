#if !defined(__UGC_BASE_H__)
#define __UGC_BASE_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _DEBUG
	#pragma message("�Զ����Ӷ�̬�� SuBase600d.dll ...")
	#pragma comment(lib,"SuBase600d.lib") 
#else
	#pragma message("�Զ����Ӷ�̬�� SuBase600.dll ...") 
	#pragma comment(lib,"SuBase600.lib") 
#endif

#endif //__UGC_BASE_H__