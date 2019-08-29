 #include "UGMenuDec.h"
 #include "UGExportBIMDec.h"
 #include "../Builds/Win_Solution_vc11//OGDC/OGDC.h"
HINSTANCE hInstance;
//�����ǲ��������뼸��������Ҳ�ǲ����3dsMax���н������ʼ�Ľӿڣ��ر���LibClassDesc��LibNumberClasses���غ�LibClassDesc�����͸���һ��

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) {
	//��ť�����ļ�Ҫɾ����Ϊ�˵ڶ���������ť��Ч��Ȩ��֮��
	OGDC::OgdcString menuFilePath(GetCOREInterface()->GetMenuManager()->GetMenuFile());
	UGC::UGFile::Delete(menuFilePath);

	switch(fdwReason) {
		case DLL_PROCESS_ATTACH:
			hInstance = hinstDLL;
			DisableThreadLibraryCalls(hInstance);
			break;
	}
	return(TRUE);
}
//!\����dll�ļ�������
__declspec( dllexport ) const TCHAR *LibDescription() { 
	return L"SuperMapPlugin"; 
}

//!\���ز�����������ĸ���
__declspec(dllexport) int LibNumberClasses() { 
	return 2; 
}

__declspec(dllexport) ClassDesc* LibClassDesc(int i){
	switch (i){
	case 0:return new UGMenuDec(hInstance);
	case 1:return new UGExportBIMDec;
		default: return NULL;
	}
}

__declspec( dllexport ) ULONG LibVersion() { 
	return VERSION_3DSMAX;
}