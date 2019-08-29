// UGMaxProcessBar_H  : plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class ��������ʾ�ࡣ
//!  \details ��װWIN32API�������ṩ��ʾMax�����ʾ���ȵĹ��ܡ�
//!  \author sunye��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
#ifndef UGMaxProcessBar_H
#define UGMaxProcessBar_H
#include <ShlObj.h>
#include "Stream/ugdefs.h"
class UGMaxProcessBar 
{

public:
	UGMaxProcessBar(){}

	UGMaxProcessBar(HINSTANCE hInstance,HWND hWndParent);

	~UGMaxProcessBar();
	//! \brief ���ý�������ʼ�������˺����ᴴ��һ���̣߳�һ�����ȴ���
	void Start();
	//! \brief ���������һ�ι����ֽ׶����У�ÿ���׶�Ҫ����һ��Ȩ�أ�����Ȩ��֮��Ϊ1��
	void SetWeight(UGC::UGfloat fWeight);
	//! \brief ������ĳ���׶�����Ҫ���и����ܴ���
	void SetNumInWeight(UGC::UGint nSteps);
	//! \brief ˵����ĳ���׶��µĹ����Ѿ������һ��
	void Update();
	//! \brief ������Ӧ������
	void Update(UGC::UGint nIncrement);
	//! \brief �����Ѿ���ɣ��˺�������ֹ�̺߳ʹ���
	void End();
private:
	//! \�̺߳���
	static DWORD _stdcall UpdateBar(LPVOID lpParam);
	HINSTANCE m_hInstance;
	HWND m_hWndParent;
	HWND m_hWnd;
	HWND m_hpw;
	HANDLE m_hThread;
	UGC::UGfloat m_fWeight;
	UGC::UGint m_nSteps;
	UGC::UGfloat m_fAccum;
};

#endif
