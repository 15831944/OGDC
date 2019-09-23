
//MenuGUP.h: plugin class for 3DMAX.
////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 3DMAX��һ��GUP����ࡣ
//!  \details ������ʱ���أ���ִ��Start()���˳�ʱִ��Stop()����Ӳ˵�����Start()����ɡ�
//!  \author sunye��
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
#ifndef UGMenuGUP_H
#define UGMenuGUP_H
#include "max.h"
#include "guplib.h "
#include <imenuman.h> 
#include "UGSuActions.h"
#include "UGMaxLogFile.h"
#define SUMENUCONTEXT 462484
class UGMenuGUP:public GUP{
public: 
	UGMenuGUP(HINSTANCE outHInstance){hInstance=outHInstance;}
	DWORD Start();
	void  Stop();
	void  DeleteThis(){}
private:
	void AppendMenu();
	HINSTANCE hInstance;	
};

DWORD UGMenuGUP::Start(){
	ActionCallback* pActCall=new ActionCallback;
	GetCOREInterface()->GetActionManager()->ActivateActionTable(pActCall,SuActionId);
	if(GetCOREInterface()->GetMenuManager()->RegisterMenuBarContext(SUMENUCONTEXT, _U("SuperMap"))){
		AppendMenu();
	}
	return GUPRESULT_KEEP;//����һ���̴߳���������
}


void UGMenuGUP::Stop()
{
	UGMaxLogFile * pProjectionHolder = UGMaxLogFile::GetMaxLogFile();
	delete pProjectionHolder;
}
void UGMenuGUP::AppendMenu(){
	ActionTable* pSuAT=GetCOREInterface()->GetActionManager()->FindTable(SuActionId);
	if (!pSuAT)
	{
		return ;
	}
	int actionIndex=1;
	IMenu* pSuMenu=GetIMenu();

	UGC::UGStringEx name;
	name.LoadResString(UGS_MAX_MENU);
	pSuMenu->SetTitle(name);  //��ͼMax���
	IMenuItem* pMenuItem;
	ActionItem* pSuAI;

	//!\ �����������
	pMenuItem = GetIMenuItem();
	pSuAI = pSuAT->GetAction(actionIndex++);
	pMenuItem->SetActionItem(pSuAI);
	pSuMenu->AddItem(pMenuItem);

	//!\ ��ӵ���ģ���ļ�
	pMenuItem=GetIMenuItem();
	pSuAI=pSuAT->GetAction(actionIndex++);
	pMenuItem->SetActionItem(pSuAI);
	pSuMenu->AddItem(pMenuItem);
	
	//!\ ��ӷָ���
	pMenuItem=GetIMenuItem();
	pMenuItem->ActAsSeparator();
	pSuMenu->AddItem(pMenuItem);

#ifdef MAX2014
	//!  \BIM�������ݼ�
	pMenuItem=GetIMenuItem();
	pSuAI=pSuAT->GetAction(actionIndex++);
	pMenuItem->SetActionItem(pSuAI);
	pSuMenu->AddItem(pMenuItem);
#endif

	GetCOREInterface()->GetMenuManager()->RegisterMenu(pSuMenu);
	pMenuItem=GetIMenuItem();
	pMenuItem->SetSubMenu(pSuMenu);
	IMenu* pMainMenu=GetCOREInterface()->GetMenuManager()->GetMainMenuBar();
	pMainMenu->AddItem(pMenuItem,pMainMenu->NumItems()-1);
	GetCOREInterface()->GetMenuManager()->UpdateMenuBar();
}
#endif
